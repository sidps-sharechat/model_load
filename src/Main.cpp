#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main()
{
    // glfw initialise
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // open gl version 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // version is 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // use core profile
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for Mac
#endif

    // window creation
    GLFWwindow *window = glfwCreateWindow(800, 600, "Test Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glfwSetCursorPosCallback(window, mouse_callback);
    // glfwSetScrollCallback(window, scroll_callback);

    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS); // Closer objects will be drawn in front

    // glEnable(GL_CULL_FACE); // Enable Face Culling
    // glCullFace(GL_BACK);    // To Cull Back Faces (do no draw)
    // glFrontFace(GL_CCW);    // Front faces are those with CCW motion

    std::string versionText = "#version " + std::to_string(3) + std::to_string(3) + "0";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(versionText.c_str());
    // Render ImGui
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to intialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui::Begin("UI Window");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

// callback on  window size change
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// // callback for mouse movement
// void mouse_callback(GLFWwindow *window, double xpos, double ypos)
// {
//     if (rCamera.isFirstMouse)
//     {
//         rCamera.isFirstMouse = false;
//         rCamera.lastX = xpos;
//         rCamera.lastY = ypos;
//     }
//     float xOffset = xpos - rCamera.lastX;
//     float yOffset = rCamera.lastY - ypos; // y is reversed
//     rCamera.lastX = xpos;
//     rCamera.lastY = ypos;
//     rCamera.xOff = xOffset;
//     rCamera.yOff = yOffset;
// }

// // callback for the mouse scroll wheel
// void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
// {
//     rCamera.camera->process_scroll(yoffset);
// }
