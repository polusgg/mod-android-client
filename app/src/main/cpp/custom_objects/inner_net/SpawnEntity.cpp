#include "SpawnEntity.h"

using namespace custom_objects::inner_net;

SpawnEntity::SpawnEntity(uint owner_id, spawn_entity_types spawn_type) {
    this->owner_id = owner_id;
    this->spawn_type = spawn_type;
}

SpawnEntity::~SpawnEntity() {
    for (auto inner_net_obj : this->children) {
        delete inner_net_obj;
    }
}

uint SpawnEntity::get_primary_net_id() {
    return this->children.front()->get_net_id();
}

