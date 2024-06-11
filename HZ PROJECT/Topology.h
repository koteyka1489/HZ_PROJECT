#pragma once
#include "Bindable.h"
class Topology :   public Bindable
{
public:
	Topology(Graphics& gfx, D3D_PRIMITIVE_TOPOLOGY topology_in);
	void Bind(Graphics& gfx) override;
protected:
	D3D_PRIMITIVE_TOPOLOGY topology;
};

