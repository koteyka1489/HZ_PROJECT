#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			Press,
			Release,
			Invalid
		};
		Event()
			:
			type(Type::Invalid),
			code(0u)
		{}
		Event(Type type, unsigned char code)
			:
			type(type),
			code(code)
		{}
		bool IsPress()
		{
			return type == Type::Press;
		}
		bool IsRelease()
		{
			return type == Type::Release;
		}
		bool IsInvalid()
		{
			return type == Type::Invalid;
		}
		unsigned char GetCode()
		{
			return code;
		}
	private:
		Type type;
		unsigned char code;
	};

public:
	// keyevent handling
	bool KeyIsPressed(unsigned char keycode);
	Event ReadKey();
	bool KeyIsEmpty();
	void FlushKey();

	// char handling
	char ReadChar();
	bool CharIsEmpty();
	void FlushChar();
	void FlushAll();

	// autorepeat control
	void EnableAutoRepeat();
	void DisableAutoRepeat();
	bool AutoRepeatIsEnabled();

private:
	//Window side
	void OnKeyPressed(unsigned char keycode);
	void OnKeyReleased(unsigned char keycode);
	void OnChar(char character);

	void ClearState(); // очистка keystates

	template <typename T>
	static void TrimBuffer(std::queue<T> buffer) // обрезка излишков keybuffer and charbeffer
	{
		while (buffer.size() > bufferSize)
		{
			buffer.pop();
		}
	}

private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned bufferSize = 16u;
	bool AutorepeatEnabled = false;
	std::bitset<nKeys> keyStates;
	std::queue<Event> keyBuffer;
	std::queue<char> charBuffer;
};
