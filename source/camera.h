#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "structs.h"

class Camera
{
private:
    fVector3 position;
    fVector3 orientation;
    fVector3 up;
    fVector2 rotation;
    glm::mat4 matrix;
    float FOV;
    float nearClipping;
    float farClipping;

public:
    Camera();
    Camera(fVector3, fVector3, fVector3, fVector2, float, float, float);

    void SetPosition(fVector3);
    void SetOrientation(fVector3);
    void SetUp(fVector3);
    void SetRotation(fVector2);
    void SetMatrix(u16Vector2);
    void SetFOV(float);
    void SetNearClipping(float);
    void SetFarClipping(float);

    fVector3 GetPosition();
    fVector3 GetOrientation();
    fVector3 GetUp();
    fVector2 GetRotation();
    glm::mat4 GetMatrix();
    float GetFOV();
    float GetNearClipping();
    float GetFarClipping();
};