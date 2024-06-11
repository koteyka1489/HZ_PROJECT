#pragma once
#include "Bindable.h"
class IndexBuffer :  public Bindable
{
public:
	IndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indexes);
	void Bind(Graphics& gfx) override;
	UINT GetCount();
protected:
	UINT count;
	ComPtr<ID3D11Buffer> pIndexBuffer;
};

