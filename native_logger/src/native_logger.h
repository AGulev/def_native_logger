#pragma once
#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_HTML5) || defined(DM_PLATFORM_OSX)
    void NativeLogger_LogInternal(int severity, const char* message);
#endif