#include "Camera.h"

DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{
    using namespace DirectX;

    
    const XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
    const XMMATRIX rotation = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
    const XMVECTOR forward = XMVector3TransformCoord(XMVectorSet(0.f, 0.f, 1.f, 0.f), rotation);
    const XMVECTOR up = XMVector3TransformCoord(XMVectorSet(0.f, 1.f, 0.f, 0.f), rotation);

    return XMMatrixLookToLH(pos, forward, up);
}

void Camera::SpawnControlButton() noexcept
{
	if (ImGui::Begin("Camera"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &x, -100.0f, 100.0f, "%.1f");
		ImGui::SliderFloat("Y", &y, -100.0f, 100.0f, "%.1f");
		ImGui::SliderFloat("Z", &z, -100.0f, 100.0f, "%.1f");
		ImGui::Text("Orientation");
		ImGui::SliderAngle("Roll", &roll, -180.f, 180.f);
		ImGui::SliderAngle("Pitch", &pitch, -89.f, 89.f);
		ImGui::SliderAngle("Yaw", &yaw, -180.f, 180.f);

		if (ImGui::Button("Reset"))
		{
			Reset();
		}
	}
	ImGui::End();
}

void Camera::Control(Window& wnd, float dt)
{
    if (wnd.kbd.KeyIsPressed('W'))
    {
        // Вперед
        x += sinf(yaw) * cosf(pitch) * cameraSpeed * dt;
        y -= sinf(pitch) * cameraSpeed * dt;
        z += cosf(yaw) * cosf(pitch) * cameraSpeed * dt;
       
    }
    if (wnd.kbd.KeyIsPressed('S'))
    {
        // Назад
        x -= sinf(yaw) * cosf(pitch) * cameraSpeed * dt;
        y += sinf(pitch) * cameraSpeed * dt;
        z -= cosf(yaw) * cosf(pitch) * cameraSpeed * dt;
        
    }
    if (wnd.kbd.KeyIsPressed('A'))
    {
        // Влево
        x -= cosf(yaw) * cameraSpeed * dt;
        z += sinf(yaw) * cameraSpeed * dt;
    }
    if (wnd.kbd.KeyIsPressed('D'))
    {
        // Вправо
        x += cosf(yaw) * cameraSpeed * dt;
        z -= sinf(yaw) * cameraSpeed * dt;
    }

    // Rotation
    if (wnd.kbd.KeyIsPressed(VK_UP))
    {
        pitch -= rotationSpeed * dt;
       
    }
    if (wnd.kbd.KeyIsPressed(VK_DOWN))
    {
        pitch += rotationSpeed * dt;
      
    }
    if (wnd.kbd.KeyIsPressed('Q'))
    {
        yaw -= rotationSpeed * dt;
    }
    if (wnd.kbd.KeyIsPressed('E'))
    {
        yaw += rotationSpeed * dt;
    }
}



void Camera::Reset() noexcept
{
    x = 0.f;
    y = 0.f;
    z = -50.f;
    pitch = 0.f;
    yaw = 0.f;
    roll = 0.f;
}
