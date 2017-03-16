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

		//auto itr = eng::resource_manager::loadedResources.find("readme");
		//if (itr != eng::resource_manager::loadedResources.end()) {
			//TextFileResource* res = dynamic_cast<TextFileResource*>(&(itr->second));
			//if (res != nullptr) {
			//	std::printf("Text file content:\n%s\n", res->text.c_str());
			//}
		//}
	}
};

typedef int myint;

int namespaceBased() {
	GameObject go;
	Triangle triangle(go);
	Lifetime lifetime(go, 20);
	go.addComponent(triangle);
	go.addComponent(lifetime);
	ResourceManager::registerLoader<std::string>([](std::string filepath) -> std::string { return "Ciao io sono una risorsa."; });
    std::string test = "hello";

	ResourceManager m;
	m.loadResource<std::string>("Hello", test);

	std::cout << m.getResource<std::string>("Hello")->c_str() << std::endl;
	std::cout << m.getResource<GameObject>("BALL") << std::endl;

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


