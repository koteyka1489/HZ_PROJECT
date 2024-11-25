#include "ImguiManager.h"
#include "imgui.h"

ImguiManager::ImguiManager()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

}

ImguiManager::~ImguiManager()
{
	ImGui::DestroyContext();
}
