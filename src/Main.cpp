#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "FileSystem.h"
#include "Transform.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

bool check_key(GLFWwindow *window, int key);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

Camera cam(glm::vec3(0.0f, 0.0f, 5.0f));
VertexArray vArray;

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); // Closer objects will be drawn in front

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

    vArray.GenerateBuffers();
    vArray.BindVAO();
    vArray.BindVBO(36, 8 * sizeof(float), vertices);
    vArray.SetAttribArray(0, 3, 8 * sizeof(float));
    vArray.SetAttribArray(1, 3, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    vArray.SetAttribArray(2, 2, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    vArray.UnBindVBO();
    vArray.UnBindVAO();

    Shader shdr(FileSystem::get_path("shaders/shader_model.vs"), FileSystem::get_path("shaders/shader_model.fs"));

    Texture tex;
    tex.id = load_texture_from_path(FileSystem::get_path("resources/textures/brickwall.jpg"));
    tex.path = "resources/textures/brickwall.jpg";
    tex.type = TEXTURE_DIFFUSE;

    // Define Data
    ImVec4 bgColor(0.1f, 0.1f, 0.15f, 1.0f);
    Transform tr;
    bool freeRoam = false;
    float cTime = 0.0f;
    float pTime = 0.0f;
    float deltaTime = 0.0f;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        cTime = glfwGetTime();
        deltaTime = cTime - pTime;
        pTime = cTime;
        // New Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Process Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
        if (freeRoam)
        {
            if (check_key(window, GLFW_KEY_W))
            {
                cam.process_keyboard(FORWARD_DIR, deltaTime);
            }
            if (check_key(window, GLFW_KEY_S))
            {
                cam.process_keyboard(BACKWARD_DIR, deltaTime);
            }
            if (check_key(window, GLFW_KEY_A))
            {
                cam.process_keyboard(LEFT_DIR, deltaTime);
            }
            if (check_key(window, GLFW_KEY_D))
            {
                cam.process_keyboard(RIGHT_DIR, deltaTime);
            }
            if (check_key(window, GLFW_KEY_Q))
            {
                cam.process_keyboard(UP_DIR, deltaTime);
            }
            if (check_key(window, GLFW_KEY_E))
            {
                cam.process_keyboard(DOWN_DIR, deltaTime);
            }
        }

        glClearColor(bgColor.x, bgColor.y, bgColor.z, bgColor.w);
        // glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Setup Data
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, tr.position);
        model = glm::rotate(model, glm::radians(tr.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(tr.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, glm::radians(tr.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, tr.scale);

        glm::mat4 view = cam.get_view_matrix();

        glm::mat4 projection(1.0f);
        int currentWidth, currentHeight;
        glfwGetWindowSize(window, &currentWidth, &currentHeight);
        if (currentHeight == 0 || currentWidth == 0)
        {
            currentHeight = 1.0f;
            currentWidth = 1.0f;
        }
        projection = glm::perspective((float)glm::radians(cam.fovZoom), (((float)currentWidth) / ((float)currentHeight)), 0.1f, 100.0f);

        // Render Objects
        shdr.use();
        shdr.setFloat("material.texture_diffuse1", tex.id);
        shdr.setMat4("model", model);
        shdr.setMat4("view", view);
        shdr.setMat4("projection", projection);
        vArray.DrawTriangles(36, 0);

        // Setup UI
        ImGui::Begin("UI Window");
        ImGui::ColorEdit3("Background", &bgColor.x);
        ImGui::SliderFloat3("Position", &tr.position.x, -10.0f, 10.0f);
        ImGui::SliderFloat3("Rotation", &tr.rotation.x, -180.0f, 180.0f);
        ImGui::SliderFloat3("Scale", &tr.scale.x, -5.0f, 5.0f);
        if (ImGui::Button("Reset"))
        {
            tr.reset_to_origin();
        }
        ImGui::Checkbox("Free Roam", &freeRoam);
        ImGui::End();

        // Draw UI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // End Frame
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    shdr.FreeData();
    vArray.FreeData();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

bool check_key(GLFWwindow *window, int key)
{
    return (glfwGetKey(window, key) == GLFW_PRESS);
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
