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
	bool done = false;

    GLuint vao;
    float data[6] = {0.5, 0.5, 0.5, -0.5, -0.5, 0};
    GLubyte ind[3] = {0,1,2};

	void render() {
        if (!done) {
			auto res = eng::resource_loader.getResource<Shader>("basic");
			if (res != nullptr) {
                for (auto itr = res->uniforms.begin(); itr != res->uniforms.end(); itr++) {
				    std::cout << itr->first << " : " << itr->second->getType().name() << std::endl;
                }
                res->use();
                res->setUniform("u_color", Vec3{0.1f,0.1f,.0f});
				done = true;
			}

            glGenVertexArrays(1, &vao);
     	    glBindVertexArray(vao);
     	
     	    { // ------  VERTICES  ------
                GLuint vert;
                glGenBuffers(1, &vert);
	            glBindBuffer(GL_ARRAY_BUFFER, vert);
	            glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, data, GL_STATIC_DRAW);
	            glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
	            glEnableVertexAttribArray(0);
     	    } // ------  VERTICES  ------
        
            { // ------  ELEMENTS  ------
                GLuint elem;
                glGenBuffers(1, &elem);
	            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elem);
	            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*3, ind, GL_STATIC_DRAW);
            } // ------  ELEMENTS  ------
        
            glBindVertexArray(0);
        }

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);
        glBindVertexArray(vao);
	}
};

class Lifetime : public Updatable {
public:
	double lifetime;

	Lifetime(GameObject& parent, double lifetime) : Updatable(parent) {
		this->lifetime = lifetime;
	};

	void update(double delta) {
		//std::printf("lifetime: %f.\n", lifetime);
		if (lifetime < 0)
			parent->disable();
		lifetime -= delta * 10;
	}
};


int namespaceBased() {
	GameObject go;
	Triangle triangle(go);
	Lifetime lifetime(go, 20);
	go.addComponent(triangle);
	go.addComponent(lifetime);

	eng::resource_loader.addResourceToQueue<TextFileResource>("readme", "readme.md", [](std::shared_ptr<TextFileResource>){});
	eng::resource_loader.addResourceToQueue<Shader>("basic", "assets/basic", [](std::shared_ptr<Shader>) {});

	system("pause");
	if (!eng::init()) return -1;

	eng::configuration.windowConfiguration.title = "Engine Test";
	eng::configuration.windowConfiguration.antialiasing = 4;
    eng::configuration.windowConfiguration.openglMajorVersion = 4;
    eng::configuration.windowConfiguration.openglMinorVersion = 4;
    eng::configuration.windowConfiguration.openglProfile = GLFW_OPENGL_CORE_PROFILE;

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
