#include "core/resources/shader.h"
#include "core/engine.h"
#include "core/resources/textfile.h"

/*
void resize(Window* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_M && GLFW_MOD_CONTROL & mods) {
		window->iconify();
	}
}*/

class Triangle : public Renderable {
public:
	Triangle(GameObject& parent) : Renderable(parent) {};

	void render() {
		glColor3f(1, 1, 1);
		glBegin(GL_TRIANGLES);
		{
			glVertex2f(-1, -1);
			glVertex2f( 1, -1);
			glVertex2f( 1,  1);
		}
		glEnd();
	}
};

class Lifetime : public Updatable {
public:
	double lifetime;
	bool done = false;

	Lifetime(GameObject& parent, double lifetime) : Updatable(parent) {
		this->lifetime = lifetime;
	};

	void update(double delta) {
		//std::printf("lifetime: %f.\n", lifetime);
		if (lifetime < 0)
			parent->disable();
		//lifetime -= delta * 10;

		if (!done) {
			TextFileResource *res = eng::resource_loader.getResource<TextFileResource>("readme");
			if (res != nullptr) {
				std::cout << res->text << std::endl;
				done = true;
			}
		}
	}
};


int namespaceBased() {
	GameObject go;
	Triangle triangle(go);
	Lifetime lifetime(go, 20);
	go.addComponent(triangle);
	go.addComponent(lifetime);

	eng::resource_loader.addResourceToQueue<TextFileResource>("readme", "readme.md", [](TextFileResource&){}, [](){});
	eng::resource_loader.addResourceToQueue<Shader>("basic", "assets/basic", [](Shader&) {}, []() {});

	system("pause");
	if (!eng::init()) return -1;

	eng::configuration.windowConfiguration.title = "Engine Test";
	eng::configuration.windowConfiguration.antialiasing = 4;

	eng::create();

	//ResourceTemplate newRes{"readme.md","readme",RESOURCE_TEXT_FILE};
	//eng::resource_manager::loadResource(newRes);

	Scene mainScene;
	mainScene.addRootGameObject(go);

	eng::setCurrentScene(mainScene);
	//setup
    eng::startLoopJoinAndTerminate();
    std::cout<<"Terminated."<<std::endl;
	return 0;
}

int main() {
	return namespaceBased();
}
