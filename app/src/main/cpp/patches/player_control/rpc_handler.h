#pragma once

#include "framework/il2cpp-appdata.h"
#include <sys/types.h>

namespace patches { namespace player_control { namespace rpc_handler
{
    extern void (*orig_function)(
        app::PlayerControl * _this,
        uint8_t MMLACCAPBPM,
        app::MessageReader * ODDHFPNFBFN,
        MethodInfo * method);

    void detoured_function(
        app::PlayerControl * _this,
        uint8_t MMLACCAPBPM,
        app::MessageReader * ODDHFPNFBFN,
        MethodInfo * method);

    void patch();

} } }