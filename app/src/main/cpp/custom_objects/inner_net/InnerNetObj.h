#pragma once

#include <sys/types.h>
#include "framework/il2cpp-appdata.h"

namespace custom_objects { namespace inner_net
{
    class InnerNetObj {
    private:
        uint owner_id;
        uint net_id;
        uint8_t dirty_bits;

    public:
        InnerNetObj(uint owner_id, uint net_id);

        virtual void Serialize() = 0;
        virtual void Deserialize(app::MessageReader * messageReader) = 0;
        virtual void HandleRpc() = 0;

        virtual void Awake() = 0;
        virtual void FixedUpdate() = 0;

        // Pointer to itself exists in InnerNetObjManager
        virtual ~InnerNetObj() = 0;

        uint get_net_id();
    };
} }



