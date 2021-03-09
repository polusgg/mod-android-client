#include "unstrip.h"
#include "../ICallHelper.h"

app::Texture2D *CreateTexture(app::Texture2D& tex) {
    auto texture = (app::Texture2D *) il2cpp_object_new((Il2CppClass *) *app::Texture2D__TypeInfo);
    app::Texture2D__ctor_1(texture, 1, 1, app::TextureFormat__Enum::ARGB32, false, nullptr);
    return texture;
}

void LoadImage(app::Texture2D *tex, app::Byte__Array *data) {
    auto load_img = (void(*)(app::Texture2D *, app::Byte__Array *, bool))
            services::ICallHelper::getInstance().ResolveICall("UnityEngine.ImageConversion::LoadImage");

    load_img(tex, data, false);
}

app::Sprite *CreateSprite(app::Texture2D *tex) {
    auto create_sprite = (app::Sprite *(*)(
            app::Texture2D *,
            app::Rect__Boxed *,
            app::Vector2__Boxed *,
            float,
            uint,
            int,
            app::Vector4__Boxed *,
            bool)
        ) services::ICallHelper::getInstance().ResolveICall("UnityEngine.Sprite::CreateSprite_Injected");

    auto rect = (app::Rect__Boxed *) il2cpp_object_new((Il2CppClass *) *app::Rect__TypeInfo);
    app::Rect__ctor(rect, 0, 0, 1, 1, nullptr);

    auto pivot = (app::Vector2__Boxed *) il2cpp_object_new((Il2CppClass *) *app::Vector2__TypeInfo);
    app::Vector2__ctor(pivot, 0.5f, 0.5f, nullptr);

    auto bounds = (app::Vector4__Boxed *) il2cpp_object_new((Il2CppClass *) *app::Vector4__TypeInfo);
    app::Vector4__ctor(bounds, 0, 0, 0, 0, nullptr);

    return create_sprite(
            tex,
            rect,
            pivot,
            100,
            0,
            1,
            bounds,
            false
    );
}