#pragma once
#include "framework/il2cpp-appdata.h"

namespace patches { namespace base { namespace version_shower_patch
{
    extern void (*orig_function)(app::VersionShower *__this, MethodInfo *method);

    void detoured_function(app::VersionShower *__this, MethodInfo *method);

    void patch();

} } }
