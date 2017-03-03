#pragma once

#include <atomic>
#include <mutex>

#include "core\managers\render.h"
#include "core\managers\update.h"
#include "core\managers\input.h"

struct EngineConfiguration {
	WindowConfiguration windowConfiguration;
};

namespace eng {
	extern EngineConfiguration configuration;

	extern RenderManager renderer;
	extern UpdateManager updater;
	extern Input input;

	extern std::atomic_bool isRunning;
	extern std::mutex engineMtx;

	//Start all threads, create window etc..
	extern bool init();

	extern void start();
	extern void joinAll();
	extern void terminate();
}
