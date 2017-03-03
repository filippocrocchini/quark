# Current Version alpha 1.0.0
## Changelog
+ Added Scene class.
+ Added GameObject class.
+ Added Component interface.
+ Added UpdatableComponent interface.
+ Added RenderableComponent interface.
+ The engine has a *"mainScene"* object pointer, if null nothing will be rendered.
+ A Scene contains GameObject pointers.
+ A GameObject contains Component pointers.
+ A Component method is called when the corresponding event is thrown.
+ The engine handles the events by calling the corresponding callbacks.

## Dependencies
+ GLFW - http://www.glfw.org
