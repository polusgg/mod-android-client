#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "../../services/InnerNetObjManager.h"
#include "endgamehook.h"

namespace patches { namespace lifecycle { namespace endgamehook
{
    void (*orig_function)(
            app::InnerNetClient * _this,
            app::OGGOENGMEPD__Enum BMAENELAJND,
            app::String * NGAGJHHKKNJ,
            MethodInfo * method);

    void detoured_function(
            app::InnerNetClient * _this,
            app::OGGOENGMEPD__Enum BMAENELAJND,
            app::String * NGAGJHHKKNJ,
            MethodInfo * method)
    {
        services::InnerNetObjManager::getInstance().destroy();
        orig_function(_this, BMAENELAJND, NGAGJHHKKNJ, method);
    }

    void patch() {
        DobbyHook(
                (void *) app::InnerNetClient_HandleDisconnect,
                (void *) detoured_function,
                (void **) &orig_function
        );
    }
} } }
