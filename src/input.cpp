#include "../include/core/managers/input.h"

std::unordered_set<eng::Input::KeyHandler> eng::Input::keyHandlers;
std::unordered_set<eng::Input::MouseMoveHandler> eng::Input::mouseMoveHandlers;
std::unordered_set<eng::Input::MouseClickHandler> eng::Input::mouseClickHandlers;
std::unordered_set<eng::Input::ScrollHandler> eng::Input::scrollHandlers;

double eng::Input::mouseX = 0;
double eng::Input::mouseY = 0;

void eng::Input::bindCallbacks(Window *window) {
	std::printf("Binding input callbacks to %s.\n", window->config.title.c_str());
	window->keyCallback = onKey;
	//window->characterWithModifierCallback = onCharacterWithModifier;
	window->cursorCallback = onCursorMove;
	window->mouseButtonCallback = onMouseButton;
	window->scrollCallback = onScroll;
}

void eng::Input::registerKeyHandler(KeyHandler handler) {
	keyHandlers.insert(handler);
}

void eng::Input::registerMouseMoveHandler(MouseMoveHandler handler) {
	mouseMoveHandlers.insert(handler);
}

void eng::Input::registerMouseClickHandler(MouseClickHandler handler) {
	mouseClickHandlers.insert(handler);
}

void eng::Input::registerScrollHandler(ScrollHandler handler) {
	scrollHandlers.insert(handler);
}

void eng::Input::onKey(Window* handle, int key, int scancode, int action, int mods) {
	if (keyHandlers.size() <= 0) return;

	KeyEvent e;
	e.key.keyvalue = key;
	e.key.scancode = scancode;
	
	e.press = action == GLFW_PRESS;
	e.release = action == GLFW_RELEASE;
	e.repeat = action == GLFW_REPEAT;

	e.alt = GLFW_MOD_ALT & mods;
	e.control = GLFW_MOD_CONTROL & mods;
	e.shift = GLFW_MOD_SHIFT & mods;
	e.super = GLFW_MOD_SUPER & mods;

	auto callback = keyHandlers.begin();
	while (!e.cancelled && callback != keyHandlers.end()) {
		(*callback)(&e);
		callback++;
	}
}


//void eng::Input::onCharacterWithModifier(Window* handle, unsigned int codepoint, int mods) {
//	std::printf("Charcter with Modifier typed: %d + %d.\n", codepoint, mods);
//}

void eng::Input::onCursorMove(Window* handle, double x, double y) {
	if (mouseMoveHandlers.size() <= 0) return;

	MouseMoveEvent e;
	e.x = x;
	e.y = y;
	e.deltaX = x - mouseX;
	e.deltaY = y - mouseY;

	auto callback = mouseMoveHandlers.begin();

	while (!e.cancelled && callback != mouseMoveHandlers.end()) {
		(*callback)(&e);
		callback++;
	}

	mouseX = x;
	mouseY = y;
}

void eng::Input::onMouseButton(Window* handle, int button, int action, int mods) {
	if (mouseClickHandlers.size() <= 0) return;

	MouseClickEvent e;
	e.x = mouseX;
	e.y = mouseY;
	e.button = button;
	e.up = action == 0;
	e.down = action == 1;
	e.alt = GLFW_MOD_ALT & mods;
	e.control = GLFW_MOD_CONTROL & mods;
	e.shift = GLFW_MOD_SHIFT & mods;
	e.super = GLFW_MOD_SUPER & mods;

	auto callback = mouseClickHandlers.begin();
	while (!e.cancelled && callback != mouseClickHandlers.end()) {
		(*callback)(&e);
		callback++;
	}
}

void eng::Input::onScroll(Window* handle, double xoffset, double yoffset) {
	if (scrollHandlers.size() <= 0) return;

	ScrollEvent e;
	e.xOffset = xoffset;
	e.yOffest = yoffset;

	auto callback = scrollHandlers.begin();
	while (!e.cancelled && callback != scrollHandlers.end()) {
		(*callback)(&e);
		callback++;
	}
}