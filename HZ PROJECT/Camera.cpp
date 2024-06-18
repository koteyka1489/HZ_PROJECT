#include "Camera.h"

DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{
	const auto pos = DirectX::XMVector3Transform(
		DirectX::XMVectorSet(0.f, 0.f, -r, 0.f),
		DirectX::XMMatrixRotationRollPitchYaw(phi, -theta, 0.f)
	);

	return  DirectX::XMMatrixLookAtLH(pos, DirectX::XMVectorZero(), DirectX::XMVectorSet(0.f, 1.f, 0.f, 0.f)) * DirectX::XMMatrixRotationRollPitchYaw(pitch, -yaw, roll);
}

void Camera::SpawnControlButton() noexcept
{
	if (ImGui::Begin("Camera"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("R", &r, 0.0f, 100.0f, "%.1f");
		ImGui::SliderAngle("Theta", &theta, -180.f, 180.f);
		ImGui::SliderAngle("phi", &phi, -89.f, 89.f);
		ImGui::Text("Orientation");
		ImGui::SliderAngle("roll", &roll, -180.f, 180.f);
		ImGui::SliderAngle("pitch", &pitch, -180.f, 180.f);
		ImGui::SliderAngle("yaw", &yaw, -180.f, 180.f);

		if (ImGui::Button("Reset"))
		{
			Reset();
		}
	}
	ImGui::End();
}

void Camera::Reset() noexcept
{
	r = 50.f;
	theta = 0.f;
	phi = 0.f;
	pitch = 0.f;
	yaw = 0.f;
	roll = 0.f;
}
