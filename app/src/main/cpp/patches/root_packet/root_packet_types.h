#pragma once

namespace patches { namespace root_packet
{
    enum root_packet_types {
        EndGame = 0x08,
        FetchResource = 0x80,
        Resize = 0x81,
        DisplayGameStartScreen = 0x82,
        OverwriteGameOver = 0x83
    };
} }
