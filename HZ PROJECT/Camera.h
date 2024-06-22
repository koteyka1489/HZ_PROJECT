#pragma once
#include "Graphics.h"
#include "Window.h"

class Camera
{
public:
	DirectX::XMMATRIX GetMatrix() const noexcept;
	void SpawnControlButton() noexcept;
	void Control(Window& wnd, float dt);
	void Reset() noexcept;


private:
    float x = 0.f;
    float y = 0.f;
    float z = -20.f;
    float pitch = 0.f;
    float yaw = 0.f;
    float roll = 0.f;
    float cameraSpeed = 50.f;
    float rotationSpeed = DirectX::XM_PIDIV2; // Pi/2 radians per second
	
};

