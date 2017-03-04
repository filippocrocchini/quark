#pragma once
#include <thread>
#include <unordered_set>

#include "../graphics/window.h"
#include "../object/gameobject.h"

class Renderable : public Component {
public:
	Renderable(GameObject* parent) : Component(parent) {};
	virtual void render() = 0;
};

class RenderManager {
public:
	std::thread* thread;
	std::unordered_set<Renderable*> renderables;

	Window window; //Extend this for multiple windows (I don't think it's a good idea though)

	RenderManager() = default;

	void init(WindowConfiguration);
	void start();
	void join();
private:
	static void renderThreadMain(RenderManager* self);
};