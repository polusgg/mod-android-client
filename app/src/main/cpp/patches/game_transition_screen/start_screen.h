#pragma once
#include "sys/types.h"
#include "framework/il2cpp-appdata.h"

namespace patches { namespace game_start_screen {
    inline app::String* title_text;
    inline app::String* subtitle_text;

    inline app::Color__Boxed* background_color;

    inline app::Byte__Array* your_team;

    void patch();
} }