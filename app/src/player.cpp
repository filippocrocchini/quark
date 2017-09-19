/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./player.h"

#include <glm/gtx/vector_angle.hpp>

#include <cmath>
#include <algorithm>

PlayerBehaviour::PlayerBehaviour(float speed, float rot_speed) : speed(speed), rot_speed(rot_speed) {}

int deaths = 0;
float inv_timeout = 2;
float inv_time = 0;

float play_time = 0;

void PlayerBehaviour::Update(double delta) {
    play_time += delta;
    if (deaths == 3) {
        Quark::stage.SetCurrentScene("menu_scene");
        std::cout << "You survived for " << static_cast<int>(play_time/60) << " minutes and " << std::fmod(play_time, 60) << " seconds\n";
        play_time = 0;
        deaths = 0;
        inv_time = 0;
    }
    Transform* transform = parent->GetComponent<Transform>();
    Sprite* sprite = parent->GetComponent<Sprite>();
    Collider2D* collider = parent->GetComponent<Collider2D>();
    if (transform == nullptr)
        return;
    if (inv_timeout > 0) {
        transform->position = glm::vec3(Quark::stage.GetWidth()/2-10, Quark::stage.GetHeight()/2-10, 0);
        if (sprite) {
            inv_time += delta * 1.f;
            sprite->color.w = std::abs(std::sin(inv_time));
        }
        if (collider)
            collider->is_trigger = true;
        inv_timeout -= delta;
    } else {
        if (sprite) {
            sprite->color.w = 1;
            inv_time = 0;
        }
        if (collider)
            collider->is_trigger = false;
        float mousex = Quark::stage.mouse.x;
        float mousey = Quark::stage.GetHeight()-Quark::stage.mouse.y;
        float deltay = transform->position.y-mousey;
        float deltax = transform->position.x-mousex;
        float angle = glm::orientedAngle(glm::vec2(1, 0), glm::normalize(glm::vec2(deltax, deltay))) - 3.141592f;

        transform->rotation = glm::slerp(transform->rotation, glm::quat(glm::vec3(0, 0, angle)), static_cast<float>(rot_speed * delta));
        if (glm::length(glm::vec2(deltax, deltay)) > 30)
            transform->position = glm::mix(transform->position, glm::vec3(mousex, mousey, 0), static_cast<float>(speed * delta));
    }
    transform->dirty_2d = true;
}

void PlayerBehaviour::LateUpdate(double delta) {}

void loadPlayerResources() {
    Quark::LoadResource<Texture>("ship_texture", "assets/ship.png", SOIL_FLAG_INVERT_Y);
    Quark::LoadResource<Material>("ship_material", glm::vec4(1, 1, 1, 1), "ship_texture", "sprite_shader");
}


void initPlayer(Scene* scene) {
    Material* ship_material = Quark::GetResource<Material>("ship_material");
    if (scene == nullptr || ship_material == nullptr)
        return;
    scene->CreateGameObject("ship")->
        AddComponent<Transform>(glm::vec3(Quark::stage.GetWidth()/2-10, Quark::stage.GetHeight()/2-10, 0),
            glm::vec3(20, 20, 1), glm::quat(), glm::vec3(-10, -10, 0))->
        AddComponent<Sprite>(ship_material, glm::vec4(1, 1, 1, 1))->
        AddComponent<Collider2D>([deaths, inv_timeout](Collider2D* collider){std::cout << ++deaths << std::endl; inv_timeout = 2;}, false)->
        AddComponent<PlayerBehaviour>(2.f, 5.f);
}
