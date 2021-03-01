#include "InnerNetObj.h"

using namespace custom_objects::inner_net;

InnerNetObj::InnerNetObj(uint owner_id, uint net_id) {
    this->owner_id = owner_id;
    this->net_id = net_id;
}

uint InnerNetObj::get_net_id() {
    return this->net_id;
}
