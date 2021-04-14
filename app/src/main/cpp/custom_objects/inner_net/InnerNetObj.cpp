#include "InnerNetObj.h"

using namespace custom_objects::inner_net;

InnerNetObj::InnerNetObj(uint net_id) {
    this->net_id = net_id;
    this->dirty_bits = 0;
}

uint InnerNetObj::get_net_id() {
    return this->net_id;
}
