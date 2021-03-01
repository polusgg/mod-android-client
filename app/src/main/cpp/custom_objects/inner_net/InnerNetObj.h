#pragma once

#include <sys/types.h>

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
        virtual void Deserialize() = 0;
        virtual void HandleRpc() = 0;

        virtual void Awake() = 0;
        virtual void FixedUpdate() = 0;

        // Pointers to itself exist in parent SpawnEntity and InnerNetObjManager
        virtual ~InnerNetObj() = 0;

        uint get_net_id();
    };
} }



