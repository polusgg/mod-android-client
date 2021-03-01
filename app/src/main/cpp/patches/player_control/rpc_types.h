#pragma once

namespace patches { namespace player_control
{
    enum rpc_types {
        SetRole = 0x88,
        CloseHud = 0x89,
        Revive = 0x8a,
        PlaySound = 0x8c
    };
} }