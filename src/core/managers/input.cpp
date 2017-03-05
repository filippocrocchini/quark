#include "core/managers/input.h"

std::unordered_set<eng::input::KeyHandler> eng::input::keyHandlers;
std::unordered_set<eng::input::MouseMoveHandler> eng::input::mouseMoveHandlers;
std::unordered_set<eng::input::MouseClickHandler> eng::input::mouseClickHandlers;
std::unordered_set<eng::input::ScrollHandler> eng::input::scrollHandlers;

double eng::input::mouseX = 0;
double eng::input::mouseY = 0;

void eng::input::bindCallbacks(Window& window) {
	std::printf("Binding input callbacks to %s.\n", window.config.title.c_str());
	window.keyCallback = onKey;
	//window->characterWithModifierCallback = onCharacterWithModifier;
	window.cursorCallback = onCursorMove;
	window.mouseButtonCallback = onMouseButton;
	window.scrollCallback = onScroll;
}

void eng::input::registerKeyHandler(KeyHandler handler) {
	keyHandlers.insert(handler);
}

void eng::input::registerMouseMoveHandler(MouseMoveHandler handler) {
	mouseMoveHandlers.insert(handler);
}

void eng::input::registerMouseClickHandler(MouseClickHandler handler) {
	mouseClickHandlers.insert(handler);
}

void eng::input::registerScrollHandler(ScrollHandler handler) {
	scrollHandlers.insert(handler);
}

void eng::input::onKey(Window* handle, int key, int scancode, int action, int mods) {
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


//void eng::input::onCharacterWithModifier(Window* handle, unsigned int codepoint, int mods) {
//	std::printf("Charcter with Modifier typed: %d + %d.\n", codepoint, mods);
//}

void eng::input::onCursorMove(Window* handle, double x, double y) {
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

void eng::input::onMouseButton(Window* handle, int button, int action, int mods) {
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

void eng::input::onScroll(Window* handle, double xoffset, double yoffset) {
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