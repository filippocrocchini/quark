#include "core/resources/shader.h"
#include "core/resources/texture.h"
#include "core/models/mesh.h"
#include "core/engine.h"

#include <SOIL2/SOIL2.h>

#include <cstdlib>

/*
void resize(Window* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_M && GLFW_MOD_CONTROL & mods) {
		window->iconify();
	}
}*/

class Triangle : public Renderable {
public:
	Triangle(GameObject& parent) : Renderable(parent) {}

	bool loaded = false;

    GLuint vao;
    float data[8] = {0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5};
    float uv[8] = {1, 0, 1, 1, 0, 0, 0, 1};
    GLubyte ind[6] = {0,1,2,1,2,3};

    glm::vec3 color = glm::vec3{ 1, 1, 1 };

    std::shared_ptr<Shader> basic;
    std::shared_ptr<Texture> fc;
    std::shared_ptr<Texture> img2;

    void randomize() {
        color.r = rand() / (float) RAND_MAX;
        color.g = rand() / (float) RAND_MAX;
        color.b = rand() / (float) RAND_MAX;
    }

    bool load() {
        auto shader = eng::resource_loader.getResource<Shader>("basic");
        if (shader == nullptr) return false;
        basic = shader;

        fc = eng::resource_loader.getResource<Texture>("fc");
        if (fc == nullptr) return false;

        img2 = eng::resource_loader.getResource<Texture>("img2");
        if (img2 == nullptr) return false;
        
        fc->setSOIL_flags(SOIL_FLAG_MIPMAPS);
        img2->setSOIL_flags(SOIL_FLAG_MIPMAPS);

        if (!fc->bind(0)) return false;
        fc->freeData();
        fc->unbind();

        if (!img2->bind(0)) return false;
        img2->freeData();
        img2->unbind();

        glGenVertexArrays(1, &vao);
     	glBindVertexArray(vao);
     	
     	{ // ------  VERTICES  ------
            GLuint vert;
            glGenBuffers(1, &vert);
	        glBindBuffer(GL_ARRAY_BUFFER, vert);
	        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	        glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
	        glEnableVertexAttribArray(0);
     	} // ------  VERTICES  ------

        { // ------  UVs  ------
            GLuint uvid;
            glGenBuffers(1, &uvid);
	        glBindBuffer(GL_ARRAY_BUFFER, uvid);
	        glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
	        glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
	        glEnableVertexAttribArray(1);
     	} // ------  UVs  ------
        
        { // ------  ELEMENTS  ------
            GLuint elem;
            glGenBuffers(1, &elem);
	        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elem);
	        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);
        } // ------  ELEMENTS  ------
        
        glBindVertexArray(0);

        return true;
    }

	void render() {
        if (!loaded) {
            loaded = load();
        } else {
            basic->use();
            fc->bind(0);
            img2->bind(1);

            basic->setUniform("u_color", color);
            basic->setUniform("albedo", 0);
            basic->setUniform("alpha", 1);

            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, sizeof(ind)/sizeof(GLubyte), GL_UNSIGNED_BYTE, 0);
            glBindVertexArray(0);

            img2->unbind();
            fc->unbind();
        }
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

GameObject go;
Triangle triangle(go);
Lifetime lifetime(go, 20);

void randomizeOnClick( eng::input::MouseClickEvent* e) {
    if(e->down)
        triangle.randomize();
}

int namespaceBased() {
    srand((unsigned)time(0));

    go.addComponent(triangle);
    //go.addComponent(lifetime);

    eng::input::registerMouseClickHandler(randomizeOnClick);

	eng::resource_loader.addResourceToQueue<Shader>("basic", "assets/basic");
    eng::resource_loader.addResourceToQueue<Texture>("fc", "assets/textures/fc.png");
    eng::resource_loader.addResourceToQueue<Texture>("img2", "assets/textures/img2.png");

	if (!eng::init()) return -1;

    WindowConfiguration wconf;
	wconf.title = "Engine Test";
	wconf.antialiasing = 4;
    wconf.openglMajorVersion = 4;
    wconf.openglMinorVersion = 3;
    wconf.openglProfile = GLFW_OPENGL_CORE_PROFILE;
    wconf.resizable = false;

    eng::setWindowConfiguration(wconf);

	eng::create();

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
