/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./level.h"

#include <random>
#include <ctime>


const float PI = 3.141592653589793238;

std::mt19937 rand_gen(time(nullptr));
float difficulty;

float randFloat(float a, float b) {
    return std::uniform_real_distribution<>(a, b)(rand_gen);
}
glm::vec2 randVec2(float a, float b) {
    return glm::vec2(randFloat(a, b), randFloat(a, b));
}

glm::vec3 randVec3(float a, float b) {
    return glm::vec3(randFloat(a, b), randFloat(a, b), randFloat(a, b));
}

AsteroidBehaviour::AsteroidBehaviour() {
    velocity = randFloat(100, 500);
    ang_velocity = randFloat(0.2f, 2.f);
    direction = randVec2(0, 1);
}

void AsteroidBehaviour::Update(double delta) {
    Transform* transform = parent->GetComponent<Transform>();
    if (transform == nullptr)
        return;

    transform->position += glm::vec3(direction * static_cast<float>(velocity * delta), 0);
    transform->rotation *= glm::quat(glm::vec3(0, 0, delta * ang_velocity));

    if (transform->position.x < 0)
        transform->position.x = Quark::stage.GetWidth();
    else if (transform->position.x > Quark::stage.GetWidth())
        transform->position.x = 0;

    if (transform->position.y < 0)
        transform->position.y = Quark::stage.GetHeight();
    else if (transform->position.y > Quark::stage.GetHeight())
        transform->position.y = 0;

    transform->dirty_2d = true;
}

void AsteroidBehaviour::LateUpdate(double delta) {
}

void loadLevelResources() {
}

void initLevel(Scene* scene) {
    int width = Quark::stage.GetWidth();
    int height = Quark::stage.GetHeight();
    for (int i=0; i < 30; i++) {
        float size = randFloat(10, 100);
    scene->CreateGameObject("asteroid" + std::to_string(i))->
        AddComponent<Transform>(glm::vec3(randFloat(0, width), randFloat(0, height), 0),
            glm::vec3(size, size, 1), glm::quat(glm::vec3(0, 0, randFloat(0, 2*PI))), glm::vec3(-size/2, -size/2, 0))->
        AddComponent<Sprite>(glm::vec4(132/255.f, 78/255.f, 0, 1))->
        AddComponent<Collider2D>(true)->
        AddComponent<AsteroidBehaviour>();
    }
}
