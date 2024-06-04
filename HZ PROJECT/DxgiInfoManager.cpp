
#include "DxgiInfoManager.h"
#include "Window.h"
#include "Graphics.h"
#include <dxgidebug.h>
#include <memory>
#include "ThrowMacros.h"

#pragma comment(lib, "dxguid.lib")


DxgiInfoManager::DxgiInfoManager()
{
	// define function signature of DXGIGetDebugInterface
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

	// load the dll that contains the function DXGIGetDebugInterface
	const auto hModDxgiDebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	if (hModDxgiDebug == nullptr)
	{
		THROW_COM_ERROR_LAST("Erorr load dxgidebug.dll");
	}

	// get address of DXGIGetDebugInterface in dll
	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"))
		);
	if (DxgiGetDebugInterface == nullptr)
	{
		THROW_COM_ERROR_LAST("Erorr get address of DXGIGetDebugInterface in dll");
	}

	HRESULT hr;
	hr = DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &pDxgiInfoQueue);
	THROW_COM_ERROR_NOINFO(hr, "Error DxgiGetDebugInterface");
}

void DxgiInfoManager::Set() noexcept
{
	// set the index (next) so that the next all to GetMessages()
	// will only get errors generated after this call
	next = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::string> DxgiInfoManager::GetMessages() const
{
	std::vector<std::string> messages;
	const auto end = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (auto i = next; i < end; i++)
	{
		HRESULT hr;
		SIZE_T messageLength;
		// get the size of message i in bytes
		hr = pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength);
		THROW_COM_ERROR_NOINFO(hr, "pDxgiInfoQueue->GetMessage get the size of message i in bytes");
		// allocate memory for message
		auto bytes = std::make_unique<byte[]>(messageLength);
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		// get the message and push its description into the vector
		hr = pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength);
		THROW_COM_ERROR_NOINFO(hr, "pDxgiInfoQueue->GetMessage get the message and push");
		messages.emplace_back(pMessage->pDescription);
	}
	return messages;
}
