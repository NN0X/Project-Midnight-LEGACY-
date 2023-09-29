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
#include "ndl.h"

GLuint ImportImage(Object object, int textureFiltering, std::string path)
{
    GLuint texture;
    iVector2 size;
    int numCol;

    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(path.data(), &size.x, &size.y, &numCol, 0);

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

    renderer.Draw();

    glfwSwapBuffers(window.window);

    glfwPollEvents();

    frames++;

    return {window, frames};
}

int main()
{
    // WINDOW CONFIG
    iVector2 *windowSize = new iVector2(NDL::LoadiVector("window", "size", "resources/config.ndl"));
    std::string windowTitle = NDL::LoadString("window", "title", "resources/config.ndl");
    int windowMSAA = NDL::LoadNumber("window", "MSAA", "resources/config.ndl");
    bool windowIsFullscreen = NDL::LoadBool("window", "fullscreen", "resources/config.ndl");
    bool windowVSYNC = NDL::LoadBool("window", "vsync", "resources/config.ndl");
    iVector2 *windowGLFWversion = new iVector2(NDL::LoadiVector("window", "glfw", "resources/config.ndl"));

    // RENDERER CONFIG
    iVector2 *rendererBegin = new iVector2(NDL::LoadiVector("renderer", "begin", "resources/config.ndl"));
    iVector2 *rendererEnd = new iVector2(NDL::LoadiVector("renderer", "end", "resources/config.ndl"));
    bool rendererMSAA = NDL::LoadBool("renderer", "MSAA", "resources/config.ndl");

    // CAMERA CONFIG
    Vector3 *cameraPosition = new Vector3(NDL::LoaddVector("camera", "position", "resources/config.ndl"));
    Vector3 *cameraOrientation = new Vector3(NDL::LoaddVector("camera", "orientation", "resources/config.ndl"));
    Vector3 *cameraUp = new Vector3(NDL::LoaddVector("camera", "up", "resources/config.ndl"));
    Vector2 *cameraRotation = new Vector2(NDL::LoaddVector("camera", "rotation", "resources/config.ndl"));
    double cameraFOV = NDL::LoadNumber("camera", "fov", "resources/config.ndl");
    double cameraNearClipping = NDL::LoadNumber("camera", "nearClipping", "resources/config.ndl");
    double cameraFarClipping = NDL::LoadNumber("camera", "farClipping", "resources/config.ndl");

    // LIGHTSOURCE CONFIG
    Vector3 *lightPosition = new Vector3(NDL::LoaddVector("light", "position", "resources/config.ndl"));
    Vector3 *lightDirection = new Vector3(NDL::LoaddVector("light", "direction", "resources/config.ndl"));
    dRGB *lightColor = new dRGB(NDL::LoaddVector("light", "color", "resources/config.ndl"));
    double lightStrength = NDL::LoadNumber("light", "strength", "resources/config.ndl");
    double lightAmbient = NDL::LoadNumber("light", "ambient", "resources/config.ndl");
    double lightSpecular = NDL::LoadNumber("light", "specular", "resources/config.ndl");
    double lightFalloff = NDL::LoadNumber("light", "falloff", "resources/config.ndl");
    double lightInverseRange = NDL::LoadNumber("light", "inverseRange", "resources/config.ndl");
    double lightInnerCone = NDL::LoadNumber("light", "innerCone", "resources/config.ndl");
    double lightOuterCone = NDL::LoadNumber("light", "outerCone", "resources/config.ndl");

    // SHADER CONFIG
    std::string framebufferVertex = NDL::LoadString("shader", "framebufferVertex", "resources/config.ndl");
    std::string framebufferFrag = NDL::LoadString("shader", "framebufferFrag", "resources/config.ndl");
    std::string texturedVertex = NDL::LoadString("shader", "texturedVertex", "resources/config.ndl");
    std::string texturedFrag = NDL::LoadString("shader", "texturedFrag", "resources/config.ndl");
    int lightNumber = NDL::LoadNumber("shader", "lightNumber", "resources/config.ndl");

    // OBJECT CONFIG
    Vector3 *objectPosition = new Vector3(NDL::LoaddVector("object", "position", "resources/config.ndl"));
    Vector3 *objectScale = new Vector3(NDL::LoaddVector("object", "scale", "resources/config.ndl"));
    dRGBA *objectColor = new dRGBA(NDL::LoaddVector("object", "color", "resources/config.ndl"));
    dRGB *objectEmission = new dRGB(NDL::LoaddVector("object", "emission", "resources/config.ndl"));
    std::string objectTexture = NDL::LoadString("object", "texture", "resources/config.ndl");

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

    Window *window = new Window(*windowSize, windowTitle, windowMSAA, windowIsFullscreen, windowVSYNC);
    window->Init(*windowGLFWversion);
    Renderer *renderer = new Renderer(*rendererBegin, *rendererEnd, rendererMSAA);
    Camera *camera = new Camera(*cameraPosition, *cameraOrientation, *cameraUp, *cameraRotation, cameraFOV, cameraNearClipping, cameraFarClipping);
    LightSource *lightSource = new LightSource(*lightPosition, *lightDirection, *lightColor, lightStrength, lightAmbient, lightSpecular, lightFalloff, lightInverseRange, lightInnerCone, lightOuterCone);

    // Postprocess postprocessShadows(renderer.GetSize(), 1);
    // postprocessShadows.AttachShader("resources/shaders/shadowMapVertex.glsl", "resources/shaders/shadowMapFrag.glsl");

    Object *object = new Object(*objectPosition, *objectScale, *objectColor, *objectEmission);
    object->AttachBuffers(vertices, indices);
    object->AttachShader(texturedVertex, texturedFrag, lightNumber); // MAX 92 LIGHTSOURCES
    object->SetTexture(ImportImage(*object, GL_LINEAR, objectTexture));
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