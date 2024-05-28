#include <windows.h>
#include <tchar.h> //  содержит макросы для работы с символами и строками в зависимости от настроек Unicode или ANSI приложения


// Определение статических строковых переменных с использованием макроса _T для поддержки обоих ANSI и Unicode символов.
static TCHAR pClassName[] = _T("HZ PROJECT");
static TCHAR pTitle[] = _T("HZ");


// кастомный обработчик сообщений окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(666);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam); // DefWindowProc обрабатывает остальные сообщения по умолчанию.
}


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	// Заполнение параметров  для регистрации класса Windows
	WNDCLASSEX wcex = {0}; //  структура, которая содержит информацию о классе окна
	wcex.cbSize = sizeof(WNDCLASSEX); // размер структуры
	wcex.style = CS_OWNDC; // стиль класса окна, в данном случае устанавливается флаг CS_OWNDC, который позволяет окну иметь собственный контекст устройства отображения (device context).
	wcex.lpfnWndProc = WndProc; // указатель на функцию WndProc, которая будет обработчиком сообщений окна.
	wcex.cbClsExtra = 0; // количество дополнительной памяти, выделенной для класса окна
	wcex.cbWndExtra = 0; // количество дополнительной памяти, выделенной для каждого экземпляра окна
	wcex.hInstance = hInstance; // дескриптор экземпляра приложения
	wcex.hIcon = nullptr; // дескриптор значка для класса окна
	wcex.hCursor = nullptr; // дескриптор курсора для класса окна
	wcex.hbrBackground = nullptr; //  дескриптор кисти для фона окна
	wcex.lpszMenuName = nullptr; //  имя строки меню для класса окна
	wcex.lpszClassName = pClassName; //  указатель на строку с именем класса окна.
	wcex.hIconSm = nullptr;//  дескриптор маленького значка для класса окна

	// Регистрация класса Windows
	RegisterClassEx(&wcex);

	// создание экземляра окна
	HWND hWnd = CreateWindowEx( 
		0, // дополнительные стили окна (в данном случае отсутствуют)
		pClassName, // указатель на строку с именем класса окна
		pTitle, // указатель на строку с заголовком окна
		WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, //  стили окна, в данном случае окно будет иметь заголовок, кнопку максимизации и системное меню
		200, 200, // стартовая точка x y
		1200, 800, // размеры окна ширина и высота
		nullptr, nullptr, // указатель на родительское окно (в данном случае отсутствует)
		hInstance, // дескриптор экземпляра приложения
		nullptr // указатель на данные созданного окна (в данном случае отсутствуют)
	);


	// отображение окна
	ShowWindow(hWnd, SW_SHOW);

	// Обработка сообщений
	MSG msg;
	while ( GetMessage(&msg, nullptr, 0, 0) > 0 )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
};