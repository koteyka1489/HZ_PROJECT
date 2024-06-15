#include "Drawable.h"
#include <cassert>

void Drawable::Draw(Graphics& gfx)
{
	for (auto& b : binds)
	{
		b->Bind(gfx);
	}

    for (auto& b : GetStaticBinds())
    {
        b->Bind(gfx);
    }

	gfx.DrawIndexed(GetpStaticIndexBuffer()->GetCount());
}

void Drawable::AddBind(std::unique_ptr<Bindable> bind) 
{
    // Проверка утверждения: нельзя добавлять индексный буфер с помощью AddBind, для этого есть AddIndexBuffer.
    // Если тип передаваемого объекта - IndexBuffer, выбрасывается ошибка.
    assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));

    // Перемещение уникального указателя bind в контейнер binds.
    binds.push_back(std::move(bind));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> ibuf)
{
    // Проверка утверждения: нельзя добавлять индексный буфер больше одного раза.
    // Если индексный буфер уже установлен (pIndexBuffer не равен nullptr), выбрасывается ошибка.
    assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);

    // Сохранение указателя на индексный буфер в члене pIndexBuffer.
    pIndexBuffer = ibuf.get();

    // Перемещение уникального указателя ibuf в контейнер binds.
    binds.push_back(std::move(ibuf));
}
