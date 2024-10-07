#include "Camera.h"

ImVec2 Camera::ToWorldPositionOLD(ImVec2 pos)
{
    ImVec2 screenPosition;
    screenPosition.x = (pos.x - position.x) * this->zoom;
    screenPosition.y = (pos.y - position.y) * this->zoom;
    return screenPosition;
}

ImVec2 Camera::ToScreenPositionOLD(ImVec2 pos)
{
    ImVec2 worldPosition;
    worldPosition.x = (pos.x / this->zoom) + position.x;
    worldPosition.y = (pos.y / this->zoom) + position.y;
    return worldPosition;
}

ImVec2 Camera::ToWorldPosition(ImVec2 pos)
{
    ImVec2 screenPosition;
    screenPosition.x = (pos.x * this->zoom) + position.x;
    screenPosition.y = (pos.y * this->zoom) + position.y;
    return screenPosition;
}

ImVec2 Camera::ToScreenPosition(ImVec2 pos)
{
    ImVec2 worldPosition;
    worldPosition.x = (pos.x - position.x) / this->zoom;
    worldPosition.y = (pos.y - position.y) / this->zoom;
    return worldPosition;
}
