#pragma once

#include "framework/il2cpp-appdata.h"

namespace patches { namespace root_packet { namespace root_packet_handler
{
    extern void (*orig_function)(
        app::InnerNetClient *_this,
        app::MessageReader * ODDHFPNFBFN,
        app::SendOption__Enum KJJKMAEPHIK,
        MethodInfo * method);

    void detoured_function(
            app::InnerNetClient *_this,
            app::MessageReader * ODDHFPNFBFN,
            app::SendOption__Enum KJJKMAEPHIK,
            MethodInfo * method);

    void patch();

} } }