#pragma once

namespace patches { namespace root_packet
{
    enum root_packet_types {
        FetchResource = 0x80,
        Resize = 0x81
    };
} }
