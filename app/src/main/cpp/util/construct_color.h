#pragma once
#include "framework/il2cpp-appdata.h"

app::Color__Boxed* construct_color(float red, float green, float blue, float alpha);

app::Color__Boxed* MessageReader_ReadColor(app::MessageReader* _this);