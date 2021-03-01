#include "framework/il2cpp-appdata.h"
#include <dobby.h>
#include "version_shower_patch.h"

using namespace patches::base::version_shower_patch;

namespace patches { namespace base { namespace version_shower_patch
{
    void (*orig_function)(app::VersionShower *__this, MethodInfo *method);

    void patch() {
        DobbyHook(
                (void *) app::VersionShower_Start,
                (void *) detoured_function,
                (void **) &orig_function
        );
    }

    void detoured_function(app::VersionShower *_this, MethodInfo *method) {
        orig_function(_this, method);
        _this->text->Text = (app::String *) il2cpp_string_new("PolusGG Modded");
    }

} } }

