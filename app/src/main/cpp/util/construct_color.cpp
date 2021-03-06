#include "construct_color.h"
#include "framework/il2cpp-appdata.h"

app::Color__Boxed* construct_color(float red, float green, float blue, float alpha) {
    auto color = (app::Color__Boxed*) il2cpp_object_new((Il2CppClass *) *app::Color__TypeInfo);
    app::Color__ctor(color, red, green, blue, alpha, nullptr);
    return color;
}

app::Color__Boxed* MessageReader_ReadColor(app::MessageReader* _this) {
    auto red = app::MessageReader_ReadByte(_this, nullptr);
    auto green = app::MessageReader_ReadByte(_this, nullptr);
    auto blue = app::MessageReader_ReadByte(_this, nullptr);
    auto alpha = app::MessageReader_ReadByte(_this, nullptr);

    return construct_color(
            (float) red / 255,
            (float) green / 255,
            (float) blue / 255,
            (float) alpha / 255);
}
