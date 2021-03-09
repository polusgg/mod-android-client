#pragma once
#include <list>
#include <map>
#include "../custom_objects/inner_net/InnerNetObj.h"

using namespace custom_objects::inner_net;

namespace services
{
    class InnerNetObjManager {
    public:
        static InnerNetObjManager& getInstance() {
            // Guaranteed to be destroyed.
            static InnerNetObjManager instance;
            // Instantiated on first use.
            return instance;
        }
    private:
        InnerNetObjManager() {}

        std::map<uint, InnerNetObj*> inner_net_objs;
    public:
        InnerNetObjManager(InnerNetObjManager const&) = delete;
        void operator = (InnerNetObjManager const&) = delete;

        void init();
        void destroy();

        void add_inner_net_obj(uint net_id, custom_objects::inner_net::InnerNetObj& innerNetObj);
        void remove_inner_net_obj(uint net_id);
        void clear_all_inner_net_obj();
    };
}




