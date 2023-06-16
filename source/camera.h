#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "datatypes.h"

class Camera
{
private:
    dVector3 position;
    dVector3 orientation;
    dVector3 up;
    dVector2 rotation;
    glm::dmat4 view;
    glm::dmat4 projection;
    glm::dmat4 matrix;
    double FOV;
    double nearClipping;
    double farClipping;

public:
    Camera();
    Camera(dVector3 pPosition, dVector3 pOrientation, dVector3 pUp, dVector2 pRotation, double pFOV, double pNearClipping, double pFarClipping);

    bool IsVisible(dVector3 pPosition);

    void SetPosition(dVector3 pPosition);
    void SetOrientation(dVector3 pOrientation);
    void SetUp(dVector3 pUp);
    void SetRotation(dVector2 pRotation);
    void SetMatrix(iVector2 pSize);
    void SetFOV(double pFOV);
    void SetNearClipping(double pNearClipping);
    void SetFarClipping(double pFarClipping);

    dVector3 GetPosition();
    dVector3 GetOrientation();
    dVector3 GetUp();
    dVector2 GetRotation();
    glm::dmat4 GetMatrix();
    double GetFOV();
    double GetNearClipping();
    double GetFarClipping();
};