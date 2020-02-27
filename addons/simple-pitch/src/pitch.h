#ifndef PITCH_H
#define PITCH_H

#include <napi.h>
#include "portaudio.h"

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (64)

#ifndef M_PI
#define M_PI (3.14159265)
#endif

class Pitch : public Napi::ObjectWrap<Pitch>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Pitch(const Napi::CallbackInfo& info);

private:
    static Napi::FunctionReference constructor;

    static void stream_finished(void* user_data);
    int pa_callback_method(
        const void *input_buffer,
        void *output_buffer,
        unsigned long frames_per_buffer,
        const PaStreamCallbackTimeInfo* time_info,
        PaStreamCallbackFlags status_flags);
    static int pa_callback(
        const void *input_buffer,
        void *output_buffer,
        unsigned long frames_per_buffer,
        const PaStreamCallbackTimeInfo* time_info,
        PaStreamCallbackFlags status_flags,
        void *user_data);
    Napi::Value open(const Napi::CallbackInfo& info);
    Napi::Value close(const Napi::CallbackInfo& info);
    Napi::Value start(const Napi::CallbackInfo& info);
    Napi::Value stop(const Napi::CallbackInfo& info);

    PaStream *stream;
    double freq;
    double phase;
};

#endif
