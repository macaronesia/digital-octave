#include <math.h>
#include "portaudio.h"
#include "pitch.h"

Napi::FunctionReference Pitch::constructor;

Napi::Object Pitch::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(
        env,
        "Pitch",
        {
            InstanceMethod("open", &Pitch::open),
            InstanceMethod("close", &Pitch::close),
            InstanceMethod("start", &Pitch::start),
            InstanceMethod("stop", &Pitch::stop)
        });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Pitch", func);
    return exports;
}

Pitch::Pitch(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Pitch>(info), stream(0)
{

}

void Pitch::stream_finished(void* user_data)
{

}

int Pitch::pa_callback_method(
    const void *input_buffer,
    void *output_buffer,
    unsigned long frames_per_buffer,
    const PaStreamCallbackTimeInfo* time_info,
    PaStreamCallbackFlags status_flags)
{
    double radians_per_frame = (double)2 * (double)M_PI * this->freq / (double)SAMPLE_RATE;
    float *out = (float*)output_buffer;
    float sample;
    unsigned long i;

    for(i=0; i<frames_per_buffer; i++)
    {
        sample = (float)sin(this->phase + i * radians_per_frame);
        *out++ = sample;
        *out++ = sample;
    }
    this->phase = fmod(this->phase + i * radians_per_frame, (double)2 * (double)M_PI);

    return paContinue;
}

int Pitch::pa_callback(
    const void *input_buffer,
    void *output_buffer,
    unsigned long frames_per_buffer,
    const PaStreamCallbackTimeInfo* time_info,
    PaStreamCallbackFlags status_flags,
    void *user_data)
{
    return ((Pitch*)user_data)->pa_callback_method(
        input_buffer,
        output_buffer,
        frames_per_buffer,
        time_info,
        status_flags);
}

Napi::Value Pitch::open(const Napi::CallbackInfo& info)
{
    PaError err;
    PaDeviceIndex device;
    PaStreamParameters output_parameters;

    err = Pa_Initialize();
    if (err != paNoError)
    {
        Pa_Terminate();
        return Napi::Boolean::New(info.Env(), false);
    };

    device = Pa_GetDefaultOutputDevice();
    if (device == paNoDevice)
    {
        Pa_Terminate();
        return Napi::Boolean::New(info.Env(), false);
    }

    output_parameters.device = device;
    output_parameters.channelCount = 2;
    output_parameters.sampleFormat = paFloat32;
    output_parameters.suggestedLatency = Pa_GetDeviceInfo(output_parameters.device)->defaultLowOutputLatency;
    output_parameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
        &this->stream,
        NULL,
        &output_parameters,
        SAMPLE_RATE,
        paFramesPerBufferUnspecified,
        paClipOff,
        &pa_callback,
        this);
    if (err != paNoError)
    {
        Pa_Terminate();
        return Napi::Boolean::New(info.Env(), false);
    }

    err = Pa_SetStreamFinishedCallback(this->stream, &Pitch::stream_finished);
    if (err != paNoError)
    {
        Pa_CloseStream(this->stream);
        this->stream = 0;
        Pa_Terminate();
        return Napi::Boolean::New(info.Env(), false);
    }

    return Napi::Boolean::New(info.Env(), true);
}

Napi::Value Pitch::close(const Napi::CallbackInfo& info)
{
    if (this->stream == 0) {
        return Napi::Boolean::New(info.Env(), false);
    }

    PaError err = Pa_CloseStream(this->stream);
    this->stream = 0;
    Pa_Terminate();

    return Napi::Boolean::New(info.Env(), err == paNoError);
}

Napi::Value Pitch::start(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return env.Null();
    }

    this->freq = info[0].As<Napi::Number>().DoubleValue();
    this->phase = 0.0;

    PaError err = Pa_StartStream(this->stream);
    if (err != paNoError)
    {
        Pa_Terminate();
        return Napi::Boolean::New(info.Env(), false);
    }

    return Napi::Boolean::New(info.Env(), true);
}

Napi::Value Pitch::stop(const Napi::CallbackInfo& info)
{
    PaError err = Pa_StopStream(this->stream);
    if (err != paNoError)
    {
        Pa_Terminate();
        return Napi::Boolean::New(info.Env(), false);
    }

    return Napi::Boolean::New(info.Env(), true);
}
