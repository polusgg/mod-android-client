#include "InnerNetObjManager.h"
#include "../util/logger.h"

using namespace services;

void InnerNetObjManager::init() {
    LOGI("Initializing InnerNetObjectManager");
}

void InnerNetObjManager::destroy() {
    for (auto entity : this->spawn_entities) {
        // SpawnEntity destructor will destroy contained inner net objects as well
        delete entity;
    }
}

void InnerNetObjManager::add_spawn_entity(SpawnEntity& spawnEntity) {
    this->spawn_entities.push_back(&spawnEntity);
}

void InnerNetObjManager::add_inner_net_obj(uint net_id, InnerNetObj& innerNetObj) {
    this->inner_net_objs.insert({ net_id, &innerNetObj });
}

void InnerNetObjManager::remove_spawn_entity(uint net_id) {
    for (auto entity : this->spawn_entities) {
        if (entity->get_primary_net_id() == net_id) {
            delete entity;
        }
    }
}
