#pragma once

namespace patches { namespace player_control
{
    enum rpc_types {
        SetRole = 0x82,
        CloseHud = 0x83,
        Revive = 0x84,
        SetOutline = 0x8a,
        SetOpacity = 0x8b,
        BeginAnimation = 0x8c,
    };
} }