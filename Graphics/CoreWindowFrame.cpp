#include "CoreWindowFrame.h"
#include <Windows.h>
#include <iostream>
#include <functional>
HDC windowHdc;
using namespace std;

void CoreWindowFrame::MessageLoop()
{
	MSG currentMsg;
	while (GetMessage(&currentMsg, windowHandle, NULL, NULL))
	{
		TranslateMessage(&currentMsg);
		DispatchMessage(&currentMsg);
	}
}

HDC CoreWindowFrame::CreateGraphicsBuffer()
{
	windowHdc = GetDC(windowHandle);
	secondaryBuffer = CreateCompatibleDC(windowHdc);
	HBITMAP map = CreateCompatibleBitmap(windowHdc, width, height);
	SelectObject(secondaryBuffer, map);
	return secondaryBuffer;
}

void CoreWindowFrame::CleanGraphicsBuffer()
{
	ReleaseDC(windowHandle, secondaryBuffer);
	ReleaseDC(windowHandle, windowHdc);
	DeleteDC(secondaryBuffer);
	DeleteDC(windowHdc);
}

void CoreWindowFrame::RenderGraphics(HDC graphicsBuffer) // BackBuffer
{
	BitBlt(windowHdc, 0, 0, width, height, secondaryBuffer, 0, 0, MERGECOPY);
}
/**
* Components should be gettable from the WindowFrame
* Should iterate through components as a tree. First you set the clipping region with the parents graphics and his graphics, then you pass render event and let it draw
*/
void CoreWindowFrame::AssignGraphicsToComponents()
{
	for (Component& i : components) //Each graphics component should have its own bitmap. The bitmap should have the size of the component. The bitmaps should be merged. 
	{
		Graphics graphics(secondaryBuffer); //Rendering is basically a tree
		i.Paint(graphics); //Handle clipping via graphics.setClip and use AND (Intersect)
	}
}

void CoreWindowFrame::ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintInfo;
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		delete this;
		break;
	case WM_SIZE:
		ConsoleWrite("WM_SIZE RECIEVED");
		width = *((unsigned short*)&lParam);
		height = ((unsigned short*)&lParam)[1];
		ConsoleWrite("ProcessMessage This: " + to_string(((long long)this)));
		ConsoleWrite(to_string(width) + " " + to_string(height));

		break;
	case WM_PAINT: // Put into function, DrawWindow since it handles WindowDrawing explicitely, from any call not just WM_PAINT
		ConsoleWrite("WM_PAINT RECIEVED");
		HDC graphicsBuffer = CreateGraphicsBuffer();
		AssignGraphicsToComponents();
		RenderGraphics(graphicsBuffer); //Performs block transfer of the secondary buffer to the primary buffer
		CleanGraphicsBuffer();
		ValidateRgn(GetWindowHandle(), NULL);
		break;
	}
}

void CoreWindowFrame::RedrawWindow()
{
	InvalidateRgn(GetWindowHandle(), NULL, true);
	UpdateWindow(windowHandle);
}

WindowFrame& CoreWindowFrame::GetWrapperFrame()
{
	return wrapperFrame;
}

HDC * CoreWindowFrame::GetHdc()
{
	return &secondaryBuffer;
}

void CoreWindowFrame::CreateConsole()
{
	AllocConsole();
}

void CoreWindowFrame::ConsoleWrite(string output)
{
	DWORD succWritten;
	output.append("\n");
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output.c_str(), output.size(), &succWritten, NULL);
}

CoreWindowFrame::CoreWindowFrame(ApplicationController::WinEntryArgs &args, WindowFrame& wrapperFrame, string windowName) : wrapperFrame(wrapperFrame)
{
	//Arguments
	HINSTANCE hInstance = args.hInstance;
	HINSTANCE hPrevInstance = args.hPrevInstance;
	LPSTR lpCmdLine = args.lpCmdLine;
	int nCmdShow = args.nCmdShow;

	CreateConsole();
	WNDCLASS* windowInfo = new WNDCLASS;
	memset(windowInfo, 0, sizeof(WNDCLASS));
	windowInfo->style = CS_HREDRAW | CS_VREDRAW;
	windowInfo->lpfnWndProc = (WNDPROC)ApplicationController::WindowProc;
	windowInfo->cbClsExtra = NULL;
	windowInfo->cbWndExtra = NULL;
	windowInfo->hInstance = hInstance;
	windowInfo->hIcon = NULL;
	windowInfo->hCursor = LoadCursor(NULL, IDC_ARROW);
	windowInfo->hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowInfo->lpszMenuName = NULL;
	windowInfo->lpszClassName = windowName.c_str();

	width = 800;
	height = 600;
	posX = 800;
	posY = 600;

	if (!RegisterClass(windowInfo))
	{
		ConsoleWrite("Register Class error" + to_string(GetLastError()));
		system("PAUSE");
		exit(0);
	}

	windowHandle = CreateWindow(windowInfo->lpszClassName, windowInfo->lpszClassName, WS_OVERLAPPEDWINDOW, width, height, posX, posY, NULL, NULL, hInstance, NULL);
	if (!windowHandle)
	{
		ConsoleWrite("Error creating window handle");
		system("PAUSE");
		exit(0);
	}
	ShowWindow(windowHandle, SW_SHOW);
	UpdateWindow(windowHandle);
	//components = new vector<reference_wrapper<Component>>();
	//Critical Section
}

void CoreWindowFrame::ComponentAdded(Component & component)
{
	components.push_back(component);
	RedrawWindow();
}

void CoreWindowFrame::SetPosition(int x, int y)
{
	posX = x;
	posY = y;
	SetWindowPos(windowHandle, NULL, x, y, NULL, NULL, SWP_NOSIZE);
}

void CoreWindowFrame::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
	SetWindowPos(windowHandle, NULL, NULL, NULL, width, height, SWP_NOMOVE);
}

int CoreWindowFrame::GetX()
{
	return posX;
}

int CoreWindowFrame::GetY()
{
	return posY;
}

HWND CoreWindowFrame::GetWindowHandle()
{
	return windowHandle;
}

CoreWindowFrame::~CoreWindowFrame()
{
	CleanGraphicsBuffer();
}
