#pragma once

#include <atomic>
#include <mutex>

#include "core\managers\render.h"
#include "core\managers\update.h"
#include "core\managers\input.h"
#include "core\managers\scene.h"

struct EngineConfiguration {
	WindowConfiguration windowConfiguration;
};

namespace eng {
	extern EngineConfiguration configuration;

	extern std::atomic_bool isRunning;
	extern std::mutex engineMtx;

	extern Scene* _currentScene;

	extern void setCurrentScene(Scene&);
	
	//Start all threads, create window etc..
	extern bool init();

	extern void create();
	
	extern void start();
	extern void joinAll();
	extern void terminate();
}
