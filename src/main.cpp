#include "../include/engine.h"
#include "../include/core/graphics/window.h"

void render();
/*
void resize(Window* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_M && GLFW_MOD_CONTROL & mods) {
		window->iconify();
	}
}*/

class Test : public Renderable {
public:
	Test(std::shared_ptr<GameObject> parent) : Renderable(parent) {};
	
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

int main() {
	if (!eng::init()) return -1;

	eng::configuration.windowConfiguration.title = "Engine Test";
	eng::configuration.windowConfiguration.antialiasing = 4;
	
	eng::prepare();

	GameObject go(nullptr);
	Test comp(std::make_shared<GameObject>(go));
	
	go.addComponent(std::make_shared<Component>(comp));

	//TODO make a "root" or something to load on start
	eng::renderer.renderables.insert((Renderable*) &comp);

	//setup
	eng::start();
	eng::joinAll();//wait for all threads to finish
	eng::terminate();
	return 0;
}