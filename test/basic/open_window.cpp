#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


GLFWwindow* createWindow(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, true);
    glfwWindowHint(GLFW_SAMPLES, 16);

    GLFWwindow* windowHandle = glfwCreateWindow(1024, 768, "Window", 0, 0);

    return windowHandle;
}

int main(){
    if(!glfwInit())
        return 1;

    GLFWwindow* window = createWindow();

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    if(window == nullptr)
        return 1;

    GLenum error = glewInit();
    if(error != GLEW_OK)
        return 1;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
