#pragma once
#include "Graphics.h"
#include <string>
#include <vector>

class Bindable
{
public:
	virtual void Bind(Graphics& gfx) noexcept = 0;

protected:
	static ID3D11DeviceContext* GetContext(Graphics& gfx);
	static ID3D11Device* GetDevice(Graphics& gfx);
	static DxgiInfoManager& GetInfoManager(Graphics& gfx);
};

