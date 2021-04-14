#include <sys/types.h>
#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "rpc_handler.h"
#include "rpc_types.h"
#include "../../util/construct_type.h"

namespace patches { namespace game_data { namespace rpc_handler
{
    void (*orig_function)(
            app::ShipStatus * _this,
            uint8_t MMLACCAPBPM,
            app::MessageReader * ODDHFPNFBFN,
            MethodInfo * method);

    void detoured_function(
            app::GameData * _this,
            uint8_t MMLACCAPBPM,
            app::MessageReader * ODDHFPNFBFN,
            MethodInfo * method)
    {
        switch (auto call_id = (patches::shipstatus::rpc_types) MMLACCAPBPM) {
            case patches::shipstatus::rpc_types::DespawnVents {
                auto vents = app::Object_1_FindObjectsOfType(get_type((Il2CppClass *) *Vent__TypeInfo));

                for (uintptr_t i = 0; vents->max_length; i++) {
                    auto vent = vents->vector[i];
                    app::Object_1_Destroy_1(vent, nullptr);
                }

                break;
            }
            default: {
                orig_function(_this, MMLACCAPBPM, ODDHFPNFBFN, method);
                break;
            }
        }
    }

    void patch() {
        DobbyHook(
                (void *) app::ShipStatus_HandleRpc,
                (void *) detoured_function,
                (void **) &orig_function
        );
    }

} } }