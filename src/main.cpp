#include "core/engine.h"

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
	Lifetime(GameObject& parent, double lifetime) : Updatable(parent) {
		this->lifetime = lifetime;
	};
	
	void update(double delta) {
		std::printf("lifetime: %f.\n", lifetime);
		if (lifetime < 0)
			parent->disable();
		lifetime -= delta * 10;
	}
};

int main() {
	if (!eng::init()) return -1;

	eng::configuration.windowConfiguration.title = "Engine Test";
	eng::configuration.windowConfiguration.antialiasing = 4;

	eng::create();

	ResourceTemplate newRes{"","test",RESOURCE_TEXT_FILE};
	eng::resource_manager::loadResource(newRes);

	Scene mainScene;
	GameObject go(nullptr);
	Triangle triangle(go);
	Lifetime lifetime(go, 20);

	go.addComponent(triangle);
	go.addComponent(lifetime);

	mainScene.addRootGameObject(go);

	eng::setCurrentScene(mainScene);
	//setup
	eng::start();
	eng::joinAll();//wait for all threads to finish
	eng::terminate();
	return 0;
}