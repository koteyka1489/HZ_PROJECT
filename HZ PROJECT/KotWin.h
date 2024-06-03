#pragma once

#ifndef FULL_WINTARD // ���������� ���� �������������� ����������� WinAPI
#define WIN32_LEAN_AND_MEAN // ���������� ����� ������������ ����������� WinAPI
#define NOGDICAPMASKS // ���������� �������� ��� ������ ������
#define NOSYSMETRICS // ���������� ������� � ��������� ��������
#define NOMENUS // ���������� ������ � ����
#define NOICONS // ���������� ������ � ��������
#define NOSYSCOMMANDS  // ���������� ��������� ������
#define NORASTEROPS // ���������� �������� ������������
#define OEMRESOURCE // ���������� OEM-��������
#define NOATOM // ���������� ��������� ��������
#define NOCLIPBOARD // ���������� ������ � ������� ������
#define NOCOLOR // ���������� ������ � ������
#define NOCTLMGR // ���������� �����������
#define NODRAWTEXT // ���������� ������ ������
#define NOKERNEL // ���������� ������� ����
#define NOMEMMGR // ���������� ��������� ������
#define NOMETAFILE // ���������� ������ � ������� ����������
#define NOOPENFILE // ���������� ������� � �������� ������
#define NOSCROLL // ���������� ���������
#define NOSERVICE // ���������� ������ � �������� Windows
#define NOSOUND // ���������� ������ � ������
#define NOTEXTMETRIC // ���������� ������ � ���������� ���������
#define NOWH // ���������� ������� ����
#define NOCOMM // ���������� ������ � ��������������
#define NOKANJI // ���������� ������ � ������ (�������� �������)
#define NOHELP // ���������� ������ �� ��������
#define NOPROFILER // ���������� ��������������
#define NODEFERWINDOWPOS // ���������� ����������� ���������������� ����
#define NOMCX // ���������� ���������� ������������
#define NORPC // ���������� ������� RPC
#define NOPROXYSTUB // ���������� ������-��������
#define NOIMAGE // ���������� ������ � �������������
#define NOTAPE // ���������� ������ � �������������
#define NOCRYPT // ���������� ������ � �������������
#define NOMINMAX // ���������� ����������� ��� min() � max()
#define STRICT // ��������� �������� ������ ��� ����������
#define NOIME // ���������� ������ � �������� �����
#endif

#include <Windows.h>
#include <tchar.h> //  �������� ������� ��� ������ � ��������� � �������� � ����������� �� �������� Unicode ��� ANSI ����������
#include <string>
#include <sstream>
#include <comdef.h>