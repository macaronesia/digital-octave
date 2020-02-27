#include <napi.h>
#include "pitch.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return Pitch::Init(env, exports);
}

NODE_API_MODULE(addon, InitAll)
