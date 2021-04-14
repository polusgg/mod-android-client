#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "../../services/InnerNetObjManager.h"
#include "ino_data_serialize_patch.h"

namespace patches { namespace inner_net_client { namespace ino_data_serialize
{
    void (*orig_function)(
            app::InnerNetClient * _this,
            MethodInfo * method);

    void detoured_function(
            app::InnerNetClient * _this,
            MethodInfo * method)
    {
        services::InnerNetObjManager::getInstance().run_fixed_update();
        orig_function(_this, method);
    }

    void patch() {
        DobbyHook(
                (void *) app::InnerNetClient_FixedUpdate,
                (void *) detoured_function,
                (void **) &orig_function
        );
    }
} } }