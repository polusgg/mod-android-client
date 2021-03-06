#include "InnerNetObjManager.h"
#include "../util/logger.h"

using namespace services;

void InnerNetObjManager::init() {
    LOGI("Initializing InnerNetObjectManager");
}

void InnerNetObjManager::destroy() {
    for (auto& pair : this->inner_net_objs) {
        delete pair.second;
    }
    this->inner_net_objs.clear();
}

void InnerNetObjManager::add_inner_net_obj(uint net_id, InnerNetObj& innerNetObj) {
    this->inner_net_objs.insert({ net_id, &innerNetObj });
}

void InnerNetObjManager::remove_inner_net_obj(uint net_id) {
    for (auto& pair : this->inner_net_objs) {
        if (pair.second->get_net_id() == net_id) {
            delete pair.second;
        }
    }
}
