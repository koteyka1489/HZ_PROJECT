#pragma once

#ifndef FULL_WINTARD // Отключение всех дополнительных компонентов WinAPI
#define WIN32_LEAN_AND_MEAN // Отключение редко используемых компонентов WinAPI
#define NOGDICAPMASKS // Отключение капсулов для вывода текста
#define NOSYSMETRICS // Отключение доступа к системным метрикам
#define NOMENUS // Отключение работы с меню
#define NOICONS // Отключение работы с иконками
#define NOSYSCOMMANDS  // Отключение системных команд
#define NORASTEROPS // Отключение операций растеризации
#define OEMRESOURCE // Отключение OEM-ресурсов
#define NOATOM // Отключение атомарных операций
#define NOCLIPBOARD // Отключение работы с буфером обмена
#define NOCOLOR // Отключение работы с цветом
#define NOCTLMGR // Отключение контроллера
#define NODRAWTEXT // Отключение вывода текста
#define NOKERNEL // Отключение вызовов ядра
#define NOMEMMGR // Отключение менеджера памяти
#define NOMETAFILE // Отключение работы с файлами метаданных
#define NOOPENFILE // Отключение доступа к открытым файлам
#define NOSCROLL // Отключение прокрутки
#define NOSERVICE // Отключение работы с службами Windows
#define NOSOUND // Отключение работы с звуком
#define NOTEXTMETRIC // Отключение работы с текстовыми метриками
#define NOWH // Отключение рабочих окон
#define NOCOMM // Отключение работы с коммуникациями
#define NOKANJI // Отключение работы с кандзи (японским шрифтом)
#define NOHELP // Отключение работы со справкой
#define NOPROFILER // Отключение профилировщика
#define NODEFERWINDOWPOS // Отключение отложенного позиционирования окон
#define NOMCX // Отключение управления медиацентром
#define NORPC // Отключение сетевой RPC
#define NOPROXYSTUB // Отключение прокси-заглушек
#define NOIMAGE // Отключение работы с изображениями
#define NOTAPE // Отключение работы с магнитофонами
#define NOCRYPT // Отключение работы с криптографией
#define NOMINMAX // Отключение определений для min() и max()
#define STRICT // Установка строгого режима для объявлений
#define NOIME // Отключение работы с методами ввода
#endif

#include <Windows.h>
#include <tchar.h> //  содержит макросы для работы с символами и строками в зависимости от настроек Unicode или ANSI приложения
#include <string>
#include <sstream>
#include <comdef.h>