#include "Topology.h"

Topology::Topology(Graphics& gfx, D3D_PRIMITIVE_TOPOLOGY topology_in)
	:
	topology(topology_in)
{
}

void Topology::Bind(Graphics& gfx)
{
	//set primitive Topology
	GetContext(gfx)->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
