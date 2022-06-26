#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

int main()
{
    glfwInit();
    std::cout << "Hello World!" << std::endl;
    glfwTerminate();
    return 0;
}
