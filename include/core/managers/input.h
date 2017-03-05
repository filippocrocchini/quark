#pragma once
#include <unordered_set>

#include "../graphics/window.h"

namespace eng {
	namespace Input {
		struct Event {
			bool cancelled = false;
		};

		struct Mods {
			bool shift;
			bool control;
			bool alt;
			bool super;
		};

		struct Key {
			int keyvalue;
			int scancode;
		};

		struct KeyEvent : Event, Mods {
			Key key;
			bool press;
			bool release;
			bool repeat;
		};

		struct MouseMoveEvent : Event {
			double x;
			double y;
			double deltaX;
			double deltaY;
		};

		struct MouseClickEvent : Event, Mods {
			double x;
			double y;
			int button;
			bool down;
			bool up;
		};

		struct ScrollEvent : Event {
			double xOffset = 0;
			double yOffest = 0;
		};

		typedef void(*KeyHandler)(KeyEvent*);
		typedef void(*MouseMoveHandler)(MouseMoveEvent*);
		typedef void(*MouseClickHandler)(MouseClickEvent*);
		typedef void(*ScrollHandler)(ScrollEvent*);

		extern std::unordered_set<KeyHandler> keyHandlers;
		extern std::unordered_set<MouseMoveHandler> mouseMoveHandlers;
		extern std::unordered_set<MouseClickHandler> mouseClickHandlers;
		extern std::unordered_set<ScrollHandler> scrollHandlers;

		extern double mouseX;
		extern double mouseY;

		extern void registerKeyHandler(KeyHandler);
		extern void registerMouseMoveHandler(MouseMoveHandler);
		extern void registerMouseClickHandler(MouseClickHandler);
		extern void registerScrollHandler(ScrollHandler);

		extern void bindCallbacks(Window& window);

		extern void onKey(Window* handle, int key, int scancode, int action, int mods);
		//extern void onCharacter(Window* handle, unsigned int codepoint);
		//extern void onCharacterWithModifier(Window* handle, unsigned int codepoint, int mods);
		extern void onCursorMove(Window* handle, double x, double y);
		extern void onMouseButton(Window* handle, int button, int action, int mods);
		extern void onScroll(Window* handle, double xoffset, double yoffset);
	}
}