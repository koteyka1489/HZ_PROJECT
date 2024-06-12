#include "Drawable.h"
#include <cassert>

void Drawable::Draw(Graphics& gfx)
{
	for (auto& b : binds)
	{
		b.get()->Bind(gfx);
	}
	gfx.DrawIndexed(pIndexBuffer->GetCount());
}

void Drawable::AddBind(std::unique_ptr<Bindable> bind) 
{
	assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
	binds.push_back(std::move(bind));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> ibuf) 
{
	assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);
	pIndexBuffer = ibuf.get();
	binds.push_back(std::move(ibuf));
}
