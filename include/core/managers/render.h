#pragma once
#include "../graphics/window.h"

class RenderManager {
public:
	RenderManager();
private:
	Window window; //Extend this for multiple windows (I don't think it's a good idea though)
};