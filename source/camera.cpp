#include "camera.h"

Camera::Camera()
{
    position = {0.0f, 0.0f, 0.0f};
    orientation = {0.0f, 0.0f, -1.0f};
    up = {0.0f, 1.0f, 0.0f};
    rotation = {0.0f, 0.0f};
    matrix = glm::mat4(1.0f);
    FOV = 45.0f;
    nearClipping = 0.01f;
    farClipping = 100.0f;
}

Camera::Camera(fVector3 pPosition, fVector3 pOrientation, fVector3 pUp, fVector2 pRotation, float pFOV, float pNearClipping, float pFarClipping)
{
    position = pPosition;
    orientation = pOrientation;
    up = pUp;
    rotation = pRotation;
    matrix = glm::mat4(1.0f);
    FOV = pFOV;
    nearClipping = pNearClipping;
    farClipping = pFarClipping;
}

void Camera::SetPosition(fVector3 pPosition)
{
    position = pPosition;
}

void Camera::SetOrientation(fVector3 pOrientation)
{
    orientation = pOrientation;
}

void Camera::SetUp(fVector3 pUp)
{
    up = pUp;
}

void Camera::SetRotation(fVector2 pRotation)
{
    rotation = pRotation;
}

void Camera::SetMatrix(u16Vector2 pSize)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    glm::vec3 glmPosition = glm::vec3(position.x, position.y, position.z);
    glm::vec3 glmOrientation = glm::vec3(orientation.x, orientation.y, orientation.z);
    glm::vec3 glmUp = glm::vec3(up.x, up.y, up.z);

    view = glm::lookAt(glmPosition, glmPosition + glmOrientation, glmUp);
    projection = glm::perspective(glm::radians(FOV), float(pSize.x) / float(pSize.y), nearClipping, farClipping);
    matrix = projection * view;
}

void Camera::SetFOV(float pFOV)
{
    FOV = pFOV;
}

void Camera::SetNearClipping(float pNearClipping)
{
    nearClipping = pNearClipping;
}

void Camera::SetFarClipping(float pFarClipping)
{
    farClipping = pFarClipping;
}

fVector3 Camera::GetPosition() { return position; }
fVector3 Camera::GetOrientation() { return orientation; }
fVector3 Camera::GetUp() { return up; }
fVector2 Camera::GetRotation() { return rotation; }
glm::mat4 Camera::GetMatrix() { return matrix; }
float Camera::GetFOV() { return FOV; }
float Camera::GetNearClipping() { return nearClipping; }
float Camera::GetFarClipping() { return farClipping; }