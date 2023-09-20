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
#include "settings.h"
#include "ndl.h"

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

Camera Inputs(Window window, double speed, double sensitivity)
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

    glm::dvec3 position = glm::dvec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
    glm::dvec3 orientation = glm::dvec3(camera.GetOrientation().x, camera.GetOrientation().y, camera.GetOrientation().z);
    glm::dvec3 up = glm::dvec3(camera.GetUp().x, camera.GetUp().y, camera.GetUp().z);

    position += movementModifier.x * speed * orientation;
    position += movementModifier.y * speed * up;
    position += movementModifier.z * speed * glm::normalize(glm::cross(orientation, up));

    camera.SetRotation({rotationModifier.x * sensitivity, rotationModifier.y * sensitivity});

    glm::dmat4 rotationMatrix = glm::dmat4(1);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(double(camera.GetRotation().x)), glm::normalize(glm::cross(orientation, up)));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(double(camera.GetRotation().y)), up);
    orientation = glm::dvec3(rotationMatrix * glm::vec4(orientation, 0));

    camera.SetRotation({0, 0});
    camera.SetOrientation({orientation[0], orientation[1], orientation[2]});
    camera.SetPosition({position[0], position[1], position[2]});
    //

    return camera;
}
//

std::pair<Window, int> RendererLoop(Window window, int frames)
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Renderer renderer = window.renderer;
    Camera camera = Inputs(window, 0.001, 0.01);
    camera.SetMatrix(window.renderer.GetSize());
    renderer.SetCamera(camera);
    window.renderer = renderer;

    // renderer.Draw();
    renderer.DrawPostprocessed();

    glfwSwapBuffers(window.window);

    glfwPollEvents();

    frames++;

    return {window, frames};
}

int main()
{
    Settings *config = new Settings("", "");

    std::vector<GLfloat> vertices =
        {
            //   COORDINATES //  TexCoord  //  NORMALS       //
            -0.5, 0, -0.5, 0, 0, 0, 1, 0, //
            -0.5, 0, 0.5, 0, 1, 0, 1, 0,  //
            0.5, 0, 0.5, 1, 1, 0, 1, 0,   //
            0.5, 0, -0.5, 1, 0, 0, 1, 0   //
        };

    std::vector<GLuint> indices =
        {
            0, 3, 1, 1, 2, 3 //
        };

    Window *window = new Window({1000, 1000}, "Renderer", 4, false, false);
    window->Init({4, 6});
    Renderer *renderer = new Renderer({0, 0}, {1000, 1000}, true);
    Camera *camera = new Camera({0, 0.5, 2}, {0, 0, -1}, {0, 1, 0}, {0, 0}, 45, 0.01, 100);
    LightSource *lightSource = new LightSource({0, 1, 0}, {0, -1, 0}, {1, 1, 1}, 1, 0.3, 0.95, 0.5, 0.5, 0.95, 0.9);

    Postprocess postprocess(renderer->GetSize(), window->GetMSAA(), 0);
    postprocess.AttachShader("resources/shaders/framebufferVertex.glsl", "resources/shaders/framebufferFrag.glsl");

    // Postprocess postprocessShadows(renderer.GetSize(), 1);
    // postprocessShadows.AttachShader("resources/shaders/shadowMapVertex.glsl", "resources/shaders/shadowMapFrag.glsl");

    Object *object = new Object({0, 0, 0}, {10, 10, 10}, {1, 1, 1, 1}, {1, 1, 1});
    object->AttachBuffers(vertices, indices);
    object->AttachShader("resources/shaders/texturedVertex.glsl", "resources/shaders/texturedFrag.glsl", 1); // MAX 92 LIGHTSOURCES
    object->SetTexture(ImportImage(*object, GL_LINEAR, "default.png"));
    renderer->AttachObject(*object);

    vertices =
        {
            //   COORDINATES   /  TexCoord /     NORMALS       //
            -0.5, 0, 0.5, 0, 0, 0, -1, 0,  // Bottom side
            -0.5, 0, -0.5, 0, 5, 0, -1, 0, // Bottom side
            0.5, 0, -0.5, 1, 1, 0, -1, 0,  // Bottom side
            0.5, 0, 0.5, 1, 0, 0, -1, 0,   // Bottom side

            -0.5, 0, 0.5, 0, 0, -0.8, 0.5, 0,  // Left Side
            -0.5, 0, -0.5, 1, 0, -0.8, 0.5, 0, // Left Side
            0, 0.8, 0, 0.5, 1, -0.8, 0.5, 0,   // Left Side

            -0.5, 0, -0.5, 1, 0, 0, 0.5, -0.8, // Non-facing side
            0.5, 0, -0.5, 0, 0, 0, 0.5, -0.8,  // Non-facing side
            0, 0.8, 0, 0.5, 1, 0, 0.5, -0.8,   // Non-facing side

            0.5, 0, -0.5, 0, 0, 0.8, 0.5, 0, // Right side
            0.5, 0, 0.5, 1, 0, 0.8, 0.5, 0,  // Right side
            0, 0.8, 0, 0.5, 1, 0.8, 0.5, 0,  // Right side

            0.5, 0, 0.5, 1, 0, 0, 0.5, 0.8,  // Facing side
            -0.5, 0, 0.5, 0, 0, 0, 0.5, 0.8, // Facing side
            0, 0.8, 0, 0.5, 1, 0, 0.5, 0.8   // Facing side
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

    object->SetPosition({1, 0, 0});
    object->SetScale({1, 1, 1});
    object->AttachBuffers(vertices, indices);
    renderer->AttachObject(*object);

    renderer->SetCamera(*camera);

    lightSource->SetType(0);
    renderer->AttachLightSource(*lightSource);

    renderer->AttachPostprocess(postprocess);
    // renderer.AttachPostprocess(postprocessShadows);

    window->AttachRenderer(*renderer);

    int frames = 0;
    double start = glfwGetTime();

    while (!glfwWindowShouldClose(window->window))
    {
        auto data = RendererLoop(*window, frames);
        *window = data.first;
        frames = data.second;
    }

    double end = glfwGetTime();
    double sum = end - start;

    std::cout << "Total Frames:    " << frames << "\n";
    std::cout << "Total Time:      " << sum << "s\n";
    std::cout << "Average FPS:     " << frames / sum << "\n";

    window->Shutdown();

    std::cin.get();
}