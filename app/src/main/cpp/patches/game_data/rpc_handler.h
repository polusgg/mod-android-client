#pragma once

#include "framework/il2cpp-appdata.h"
#include <sys/types.h>

namespace patches { namespace game_data { namespace rpc_handler
{
    extern void (*orig_function)(
            app::GameData * _this,
            uint8_t MMLACCAPBPM,
            app::MessageReader * ODDHFPNFBFN,
            MethodInfo * method);

    void detoured_function(
            app::GameData * _this,
            uint8_t MMLACCAPBPM,
            app::MessageReader * ODDHFPNFBFN,
            MethodInfo * method);

    void patch();

} } }