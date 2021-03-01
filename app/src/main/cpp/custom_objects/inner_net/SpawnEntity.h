#pragma once
#include <vector>
#include "spawn_entity_types.h"
#include "InnerNetObj.h"

namespace custom_objects { namespace inner_net
{
    class SpawnEntity {
    private:
        uint owner_id;
        spawn_entity_types spawn_type;
        std::vector<InnerNetObj*> children;
    public:
        SpawnEntity(uint owner_id, spawn_entity_types spawn_type);

        // Pointer to itself and children InnerNetObj are in InnerNetObjManager
        ~SpawnEntity();

        uint get_primary_net_id();
    };
} }



