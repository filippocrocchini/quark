#pragma once

#include "core/graphics/window.h"
#include "core/threads/mythread.h"

class RenderManager : public ThreadLoop{
public:
	Window window;
	void init(WindowConfiguration);

	void start();
	void stop();

	void loop();
};

/*
namespace eng {
	namespace render_manager {
		extern std::thread* thread;

		extern Window window; //Extend this for multiple windows (I don't think it's a good idea though)

		extern void init(WindowConfiguration);
		extern void start();
		extern void join();
		extern void renderThreadMain();
	}
}
*/