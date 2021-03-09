#pragma once
#include "framework/il2cpp-appdata.h"

namespace services { namespace icalls {
    app::Texture2D * CreateTexture(app::Texture2D& tex);

    void LoadImage(app::Texture2D& tex, app::Byte__Array& data);

    app::Sprite *CreateSprite(app::Texture2D& tex);
} }