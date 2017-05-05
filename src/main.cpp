#include <iostream>
#include <GLEW/glew.h>
#include <GLFW3/glfw3.h>

GLFWwindow* createWindow(){
    glfwWindowHint(GLFW_RESIZABLE, true);
    glfwWindowHint(GLFW_SAMPLES, 16);

    GLFWwindow* windowHandle = glfwCreateWindow(1024, 768, "Window", 0, 0);

    if (windowHandle == nullptr) {
        std::cerr << "Failed to create GLFW Window.\n";
        return 0;
    }

    glfwMakeContextCurrent(windowHandle);
    glfwSwapInterval(0);

    return windowHandle;
}

int main(){
    if(!glfwInit()){
        std::cout << "GLFW failed initialization.  " << std::endl;
        return 1;
    }

    createWindow();

    GLenum error = glewInit();
    if(error != GLEW_OK){
        std::cout << "GLEW failed initialization.  " << glewGetErrorString(error) << std::endl;
        return 1;
    }

    std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
    return 0;
}
