/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./button.h"

#include <functional>

Button::Button(std::function<void(void)> on_click): on_click(on_click) {}

void Button::Update(double delta) {
    Transform* transform = parent->GetComponent<Transform>();
    Sprite* sprite = parent->GetComponent<Sprite>();

    if (transform == nullptr || sprite == nullptr)
        return;

    uint xdist = Quark::stage.mouse.x - transform->position.x;
    uint ydist = Quark::stage.mouse.y - transform->position.y;

    sprite->color.w = 0.6f;
    if (xdist > 0 && xdist < transform->scale.x && ydist > 0 && ydist < transform->scale.y) {
        if (Quark::stage.mouse.pressed && Quark::stage.mouse.button == 0) {
            sprite->color.w = 1.f;
        } else if (Quark::stage.mouse.released && Quark::stage.mouse.button == 0) {
            on_click();
        } else {
            sprite->color.w = 0.8f;
        }
    }
}
void Button::LateUpdate(double delta) {}
