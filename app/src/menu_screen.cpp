/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./menu_screen.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL2.h>

#include <thread>  // NOLINT()

#include <chrono>  // NOLINT()

#include "./button.h"


class Dummy : public Resource {
 public:
    Dummy() = default;

    bool Load() override {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return true;
    }

    void onLoad() override {}
    void onFail() override {}
};

const char MENU_SCREEN_SCENE[] = "menu_scene";

Camera menu_screen_camera;

void loadMenuScreenResources() {
    Quark::LoadResource<Texture>("play_button_texture", "assets/playbutton.png", SOIL_FLAG_INVERT_Y);
//    Quark::WaitForResources();
    // TODO(filippocrocchini): Sort resources based on dependencies
    // In this case "play_button_material" depends on play_button_texture
    // Maybe add a flag to tell the resource loader which resources are REQUIRED
    Quark::LoadResource<Material>("play_button_material", glm::vec4(1, 1, 1, 1), "play_button_texture", "sprite_shader");

    for (int i=0; i < 10;  i++) {
        Quark::LoadResource<Dummy>(std::to_string(i));
    }
}

bool initMenuScreen(int width, int height) {
    // for (int i=0; i < 10;  i++) {
    //    Quark::DeleteResource(std::to_string(i)); // TODO(filippocrocchini): I don't see why this could be useful but... consider adding it
    // }

    menu_screen_camera = Camera {glm::ortho(0.f, static_cast<float>(width), 0.f,
                                                 static_cast<float>(height), 0.f, 1000.f),
                                 glm::vec3(.1f, .1f, .1f)};
    Scene* menu_screen = Quark::stage.CreateScene(MENU_SCREEN_SCENE, &menu_screen_camera);
    Material* play_button_material = Quark::GetResource<Material>("play_button_material");
    if (menu_screen == nullptr || play_button_material == nullptr)
        return false;
    menu_screen->CreateGameObject("play_button")->
        AddComponent<Transform>(glm::vec3(Quark::stage.GetWidth()/2-150, Quark::stage.GetHeight()/2-50, 0), glm::vec3(300, 100, 1), glm::quat())->
        AddComponent<Sprite>(play_button_material, glm::vec4(1, 1, 1, 1))->
        AddComponent<Button>([](){ std::cout << "Play!\n"; });
    return true;
}
