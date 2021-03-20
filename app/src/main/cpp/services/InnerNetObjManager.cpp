#include "InnerNetObjManager.h"
#include "../util/logger.h"

using namespace services;

void InnerNetObjManager::init() {
    LOGI("[+] Initializing InnerNetObjectManager");
}

void InnerNetObjManager::destroy() {
    LOGI("[-] Destroying InnerNetObjManager");

    this->clear_all_inner_net_obj();
}

void InnerNetObjManager::add_inner_net_obj(uint net_id, InnerNetObj* innerNetObj) {
    this->inner_net_objs.insert({ net_id, innerNetObj });
}

InnerNetObj *InnerNetObjManager::get_inner_net_obj(uint net_id) {
    if (this->inner_net_objs.find(net_id) == this->inner_net_objs.end()) {
        return nullptr;
    } else {
        return this->inner_net_objs.at(net_id);
    }
}

void InnerNetObjManager::run_fixed_update() {
    for (auto& pair : this->inner_net_objs) {
        pair.second->FixedUpdate();
    }
}

void InnerNetObjManager::remove_inner_net_obj(uint net_id) {
    for (auto& pair : this->inner_net_objs) {
        if (pair.second->get_net_id() == net_id) {
            delete pair.second;
        }
    }
    this->inner_net_objs.erase(net_id);
}

void InnerNetObjManager::clear_all_inner_net_obj() {
    for (auto& pair : this->inner_net_objs) {
        delete pair.second;
    }
    this->inner_net_objs.clear();
}
