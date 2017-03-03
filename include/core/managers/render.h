#pragma once
#include <thread>

#include "../graphics/window.h"

class RenderManager {
public:
	std::thread* thread;

	RenderManager() = default;

	void init(WindowConfiguration);
	void start();
	void join();
private:
	Window window; //Extend this for multiple windows (I don't think it's a good idea though)

	static void renderThreadMain(RenderManager* self);
};