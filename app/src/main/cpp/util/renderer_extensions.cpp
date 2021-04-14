#include "renderer_extensions.h"
#include "framework/il2cpp-appdata.h"

void SpriteRenderer_SetAlpha(app::SpriteRenderer* renderer, float new_alpha) {
    auto current_color = app::SpriteRenderer_get_color(renderer, nullptr);
    current_color.a = new_alpha;
    app::SpriteRenderer_set_color(renderer, current_color, nullptr);
}
