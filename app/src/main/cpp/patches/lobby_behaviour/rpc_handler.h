#pragma once

#include <sys/types.h>
#include "framework/il2cpp-appdata.h"

namespace patches { namespace lobby_behaviour { namespace rpc_handler
{
    extern void (*orig_function)(
            app::LobbyBehaviour * _this,
            uint8_t MMLACCAPBPM,
            app::MessageReader * ODDHFPNFBFN,
            MethodInfo * method);

    void detoured_function(
            app::LobbyBehaviour * _this,
            uint8_t MMLACCAPBPM,
            app::MessageReader * ODDHFPNFBFN,
            MethodInfo * method);

    void patch();

} } }