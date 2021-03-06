#pragma once

namespace patches { namespace root_packet
{
    enum root_packet_types {
        FetchResource = 0x80,
        Resize = 0x81,
        DisplayGameStartScreen = 0x90,
        OverwriteGameOver = 0x91
    };
} }
