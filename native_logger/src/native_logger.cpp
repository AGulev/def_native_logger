#define EXTENSION_NAME NativeLogger
#define LIB_NAME "NativeLogger"
#define MODULE_NAME "native_logger"
#define DLIB_LOG_DOMAIN LIB_NAME

#include <dmsdk/sdk.h>
#include "native_logger.h"

static int log(lua_State* L) {
    int log_level = luaL_checkinteger(L, 1);
    const char* message = luaL_checkstring(L, 2);

    #if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_HTML5)
    NativeLogger_LogInternal(log_level, message);
#endif
    return 0;
}

static void LogListener(LogSeverity severity, const char *type, const char *message)
{
    #if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_HTML5)
        NativeLogger_LogInternal(severity, message);
    #endif
}


static const luaL_reg Module_methods[] =
{
    {"log", log},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result InitializeNativeLogger(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

bool regular_logs = false;

static dmExtension::Result AppInitialize(dmExtension::AppParams *params)
{
    const char *settings_str = dmConfigFile::GetString(params->m_ConfigFile, "native_logger.regular_logs", "false");
    regular_logs = settings_str[0] == 't' || settings_str[0] == '1';
    if (regular_logs)
    {
        dmLogRegisterListener(&LogListener);
    }
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalize(dmExtension::AppParams *params)
{
    if (regular_logs)
    {
        dmLogUnregisterListener(&LogListener);
    }
    return dmExtension::RESULT_OK;
}


DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitialize, AppFinalize, InitializeNativeLogger, 0, 0, 0)
