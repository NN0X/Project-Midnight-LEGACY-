#include "camera.h"

Camera::Camera()
{
    position = {0, 0, 0};
    orientation = {0, 0, -1};
    up = {0, 1, 0};
    rotation = {0, 0};
    view = glm::dmat4(1);
    projection = glm::dmat4(1);
    matrix = glm::dmat4(1);
    FOV = 45;
    nearClipping = 0.01;
    farClipping = 100;
}

Camera::Camera(dVector3 pPosition, dVector3 pOrientation, dVector3 pUp, dVector2 pRotation, double pFOV, double pNearClipping, double pFarClipping)
{
    position = pPosition;
    orientation = pOrientation;
    up = pUp;
    rotation = pRotation;
    view = glm::dmat4(1);
    projection = glm::dmat4(1);
    matrix = glm::dmat4(1);
    FOV = pFOV;
    nearClipping = pNearClipping;
    farClipping = pFarClipping;
}

bool Camera::IsVisible(dVector3 pPosition)
{
    double distance = sqrt(pow((position.x - pPosition.x), 2) + pow((position.y - pPosition.y), 2) + pow((position.z - pPosition.z), 2));

    if (distance > farClipping)
        return false;
}

void Camera::SetPosition(dVector3 pPosition)
{
    position = pPosition;
}

void Camera::SetOrientation(dVector3 pOrientation)
{
    orientation = pOrientation;
}

void Camera::SetUp(dVector3 pUp)
{
    up = pUp;
}

void Camera::SetRotation(dVector2 pRotation)
{
    rotation = pRotation;
}

void Camera::SetMatrix(iVector2 pSize)
{
    glm::dmat4 view = glm::dmat4(1);
    glm::dmat4 projection = glm::dmat4(1);

    glm::dvec3 glmPosition = glm::dvec3(position.x, position.y, position.z);
    glm::dvec3 glmOrientation = glm::dvec3(orientation.x, orientation.y, orientation.z);
    glm::dvec3 glmUp = glm::dvec3(up.x, up.y, up.z);

    view = glm::lookAt(glmPosition, glmPosition + glmOrientation, glmUp);
    projection = glm::perspective(glm::radians(FOV), double(pSize.x / pSize.y), nearClipping, farClipping);
    matrix = projection * view;
}

void Camera::SetFOV(double pFOV)
{
    FOV = pFOV;
}

void Camera::SetNearClipping(double pNearClipping)
{
    nearClipping = pNearClipping;
}

void Camera::SetFarClipping(double pFarClipping)
{
    farClipping = pFarClipping;
}

dVector3 Camera::GetPosition() { return position; }
dVector3 Camera::GetOrientation() { return orientation; }
dVector3 Camera::GetUp() { return up; }
dVector2 Camera::GetRotation() { return rotation; }
glm::dmat4 Camera::GetMatrix() { return matrix; }
double Camera::GetFOV() { return FOV; }
double Camera::GetNearClipping() { return nearClipping; }
double Camera::GetFarClipping() { return farClipping; }