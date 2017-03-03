#pragma once

#include "core\managers\render.h"
#include "core\managers\update.h"
#include "core\managers\input.h"

struct EngineConfiguration {
	WindowConfiguration winodowConfiguration;
};

namespace eng {
	EngineConfiguration configuration;
	RenderManager renderer;
	UpdateManager updater;
	Input input;

	bool isRunning = false;

	//Start all threads
	void start();

	//Join and stop all threads
	void stop();
}
