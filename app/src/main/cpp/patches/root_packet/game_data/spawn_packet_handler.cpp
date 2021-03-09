#include <sys/types.h>
#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "framework/il2cpp-helpers.h"
#include "spawn_packet_handler.h"
#include "../../../services/InnerNetObjManager.h"
#include "../../../custom_objects/inner_net/spawn_entity_types.h"
#include "../../../util/logger.h"

namespace patches { namespace root_packet { namespace game_data
{
    void (*orig_function)(
            app::InnerNetClient *_this,
            app::MessageReader * ODDHFPNFBFN,
            int BDIDGKJNIPJ,
            MethodInfo * method);

    void detoured_function(
            app::InnerNetClient *_this,
            app::MessageReader * ODDHFPNFBFN,
            int BDIDGKJNIPJ,
            MethodInfo * method)
    {
        if (ODDHFPNFBFN->Tag == 4) {
            auto messageReader = app::MessageReader_Get(ODDHFPNFBFN, nullptr);

            auto spawn_type = app::MessageReader_ReadPackedUInt32(messageReader, nullptr);
            if (spawn_type < 0x80) {
                orig_function(_this, ODDHFPNFBFN, BDIDGKJNIPJ, method);
                return;
            }

            switch (spawn_type) {
                case custom_objects::inner_net::spawn_entity_types::Image: {
                    break;
                }
                case custom_objects::inner_net::spawn_entity_types::Button: {
                    break;
                }
                case custom_objects::inner_net::spawn_entity_types::CooldownButton: {
                    break;
                }
                case custom_objects::inner_net::spawn_entity_types::DeadBody: {
                    break;
                }
                default: {
                    LOGW("[-] Unknown spawn type %d", spawn_type);
                }
            }

        } else if (ODDHFPNFBFN->Tag == 5) {
            auto messageReader = app::MessageReader_Get(ODDHFPNFBFN, nullptr);

            auto despawn_net_id = app::MessageReader_ReadPackedUInt32(messageReader, nullptr);
            services::InnerNetObjManager::getInstance().remove_inner_net_obj(despawn_net_id);

            orig_function(_this, ODDHFPNFBFN, BDIDGKJNIPJ, method);
        } else {
            orig_function(_this, ODDHFPNFBFN, BDIDGKJNIPJ, method);
        }
    }

    void patch() {
        DobbyHook(
                (void *) app::InnerNetClient_GKLKOJPKFNL,
                (void *) detoured_function,
                (void **) &orig_function
        );
    }
} } }