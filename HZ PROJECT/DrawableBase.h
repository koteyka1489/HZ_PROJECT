#pragma once
#include "Drawable.h"

template <class T>
class DrawableBase : public Drawable
{
public:

	bool IsStaticInitialized()
	{
		return staticBinds.empty();
	}

	void AddStaticBind(std::unique_ptr<Bindable> bind)
	{
		assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));

		staticBinds.push_back(std::move(bind));
	}

	void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> ibuf)
	{
		assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);

		// Сохранение указателя на индексный буфер в члене pIndexBuffer.
		pStaticIndexBuffer = ibuf.get();

		// Перемещение уникального указателя ibuf в контейнер binds.
		staticBinds.push_back(std::move(ibuf));
	}



private:
	const std::vector < std::unique_ptr<Bindable>>& GetStaticBinds() const override
	{
		return staticBinds;
	}
	const IndexBuffer* GetpStaticIndexBuffer() override
	{
		return pStaticIndexBuffer;
	}

private:
	static std::vector < std::unique_ptr<Bindable>> staticBinds;
	static const IndexBuffer* pStaticIndexBuffer;
};

template<class T>
std::vector <std::unique_ptr<Bindable>> DrawableBase<T>::staticBinds;

template<class T>
const IndexBuffer* DrawableBase<T>::pStaticIndexBuffer = nullptr;
