#pragma once
#include <thread>
#include <unordered_set>

#include "core/graphics/window.h"

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