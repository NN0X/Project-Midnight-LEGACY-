#include <iostream>
#include <vector>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.h"

GLuint ImportImage(Object object, int textureFiltering, std::string path)
{
    GLuint texture;
    iVector2 size;
    int numCol;

    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(("resources/textures/" + path).data(), &size.x, &size.y, &numCol, 0);

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFiltering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFiltering);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint textureUniform = glGetUniformLocation(object.GetShader(), "tex");
    glUseProgram(object.GetShader());
    glUniform1i(textureUniform, 0);

    return texture;
}

Camera Inputs(Window window, float speed, float sensitivity)
{

    if (glfwGetKey(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window.window, GL_TRUE);
    }

    iVector3 movementModifier = {0, 0, 0};
    iVector2 rotationModifier = {0, 0};

    if (glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS)
    {
        movementModifier.x = 1;
    }
    if (glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS)
    {
        movementModifier.z = -1;
    }
    if (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS)
    {
        movementModifier.x = -1;
    }
    if (glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS)
    {
        movementModifier.z = 1;
    }
    if (glfwGetKey(window.window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        movementModifier.y = 1;
    }
    if (glfwGetKey(window.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        movementModifier.y = -1;
    }
    if (glfwGetKey(window.window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        rotationModifier.y = 1;
    }
    if (glfwGetKey(window.window, GLFW_KEY_E) == GLFW_PRESS)
    {
        rotationModifier.y = -1;
    }
    if (glfwGetKey(window.window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotationModifier.x = 1;
    }
    if (glfwGetKey(window.window, GLFW_KEY_C) == GLFW_PRESS)
    {
        rotationModifier.x = -1;
    }

    // Placeholder
    Renderer renderer = window.renderer;
    Camera camera = renderer.GetCamera();

    glm::vec3 position = glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
    glm::vec3 orientation = glm::vec3(camera.GetOrientation().x, camera.GetOrientation().y, camera.GetOrientation().z);
    glm::vec3 up = glm::vec3(camera.GetUp().x, camera.GetUp().y, camera.GetUp().z);

    position += movementModifier.x * speed * orientation;
    position += movementModifier.y * speed * up;
    position += movementModifier.z * speed * glm::normalize(glm::cross(orientation, up));

    camera.SetRotation({rotationModifier.x * sensitivity, rotationModifier.y * sensitivity});

    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(camera.GetRotation().x), glm::normalize(glm::cross(orientation, up)));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(camera.GetRotation().y), up);
    orientation = glm::vec3(rotationMatrix * glm::vec4(orientation, 0.0f));

    camera.SetRotation({0.0f, 0.0f});
    camera.SetOrientation({orientation[0], orientation[1], orientation[2]});
    camera.SetPosition({position[0], position[1], position[2]});
    //

    return camera;
}
//

std::pair<Window, int> RendererLoop(Window window, int frames)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Renderer renderer = window.renderer;
    Camera camera = Inputs(window, 0.001f, 0.01f);
    camera.SetMatrix(window.renderer.GetSize());
    renderer.SetCamera(camera);
    window.renderer = renderer;

    renderer.DrawObjects();

    glfwSwapBuffers(window.window);

    glfwPollEvents();

    frames++;

    return {window, frames};
}

int main()
{
    std::vector<GLfloat> vertices =
        {
            //   COORDINATES //  TexCoord  //  NORMALS       //
            -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, //
            -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  //
            0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,   //
            0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f   //
        };

    std::vector<GLuint> indices =
        {
            0, 3, 1, 1, 2, 3 //
        };

    Window window({1000, 1000}, "Renderer", 4, false, false);
    window.Init({4, 6});
    Renderer renderer({0, 0}, {1000, 1000}, true);
    Camera camera({0.0f, 0.5f, 2.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, 45.0f, 0.01f, 100.0f);
    LightSource lightSource({0.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0.5f, 0.3f, 0.95f);

    Object object({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f, 10.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f});
    object.AttachBuffers(vertices, indices);
    object.AttachShader("resources/shaders/texturedVertex.glsl", "resources/shaders/texturedFrag.glsl");
    object.SetTexture(ImportImage(object, GL_LINEAR, "default.png"));
    renderer.AttachObject(object);

    vertices =
        {
            //   COORDINATES   /  TexCoord /     NORMALS       //
            -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,  // Bottom side
            -0.5f, 0.0f, -0.5f, 0.0f, 5.0f, 0.0f, -1.0f, 0.0f, // Bottom side
            0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,  // Bottom side
            0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,   // Bottom side

            -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, -0.8f, 0.5f, 0.0f,  // Left Side
            -0.5f, 0.0f, -0.5f, 1.0f, 0.0f, -0.8f, 0.5f, 0.0f, // Left Side
            0.0f, 0.8f, 0.0f, 0.5f, 1.0f, -0.8f, 0.5f, 0.0f,   // Left Side

            -0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f, 0.5f, -0.8f, // Non-facing side
            0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.8f,  // Non-facing side
            0.0f, 0.8f, 0.0f, 0.5f, 1.0f, 0.0f, 0.5f, -0.8f,   // Non-facing side

            0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.8f, 0.5f, 0.0f, // Right side
            0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.8f, 0.5f, 0.0f,  // Right side
            0.0f, 0.8f, 0.0f, 0.5f, 1.0f, 0.8f, 0.5f, 0.0f,  // Right side

            0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.5f, 0.8f,  // Facing side
            -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.8f, // Facing side
            0.0f, 0.8f, 0.0f, 0.5f, 1.0f, 0.0f, 0.5f, 0.8f   // Facing side
        };

    indices =
        {
            0, 1, 2,    // Bottom side
            0, 2, 3,    // Bottom side
            4, 6, 5,    // Left side
            7, 9, 8,    // Non-facing side
            10, 12, 11, // Right side
            13, 15, 14  // Facing side
        };

    object.SetPosition({1.0f, 0.0f, 0.0f});
    object.SetScale({1.0f, 1.0f, 1.0f});
    object.AttachBuffers(vertices, indices);
    renderer.AttachObject(object);

    renderer.SetCamera(camera);
    renderer.SetLightSource(lightSource);
    window.AttachRenderer(renderer);

    int frames = 0;
    double start = glfwGetTime();

    while (!glfwWindowShouldClose(window.window))
    {
        auto data = RendererLoop(window, frames);
        window = data.first;
        frames = data.second;
    }

    double end = glfwGetTime();
    double sum = end - start;

    std::cout << "Total Frames:    " << frames << "\n";
    std::cout << "Total Time:      " << sum << "s\n";
    std::cout << "Average FPS:     " << frames / sum << "\n";

    window.Shutdown();

    std::cin.get();
}