#pragma once

#include <atomic>
#include <mutex>

#include "core/managers/render.h"
#include "core/managers/update.h"
#include "core/managers/input.h"
#include "core/managers/scene.h"
#include "core/managers/resource.h"

struct EngineConfiguration {
	WindowConfiguration windowConfiguration;
};

namespace eng {
	extern EngineConfiguration configuration;

	extern Thread render_thread;
	extern Thread update_thread;
	extern Thread resource_thread;

	extern RenderManager renderer;
	extern UpdateManager updater;
	extern AsyncResourceManager resource_loader;

	extern std::atomic_bool isRunning;
	extern std::mutex engineMtx;

	extern Scene* _currentScene;

	extern void setCurrentScene(Scene&);

	//Start all threads, create window etc..
	extern bool init();
	extern void create();

	/*
	 * @brief Returns when all engine threads are terminated
	 */
	extern void startLoopJoinAndTerminate();
	extern void startLoop();
	extern void joinAll();
	extern void terminate();
}
