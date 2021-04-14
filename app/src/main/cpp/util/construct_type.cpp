#include "construct_type.h"
#include "framework/il2cpp-appdata.h"

app::Type * get_type(Il2CppClass * classptr) {
    return app::Type_internal_from_handle((void *) il2cpp_class_get_type(classptr), nullptr);
}
