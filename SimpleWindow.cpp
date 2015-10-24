#include <Windows.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE && MessageBox(hWnd, "Are you sure you want to quit?", "Confirm", MB_YESNO) == IDNO)
			break;
		// Fall through
	default:
		return DefWindowProcA(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSA wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.lpszClassName = "SimpleWindow";
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	RegisterClassA(&wc);

	DWORD dwStyle = WS_CAPTION | WS_BORDER | WS_SYSMENU;

	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = WINDOW_WIDTH;
	rc.bottom = WINDOW_HEIGHT;
	AdjustWindowRect(&rc, dwStyle, FALSE);

	HWND hWnd = CreateWindowA(
		"SimpleWindow",
		"Simple Window",
		dwStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	ShowWindow(hWnd, nCmdShow);

	while (true)
	{
		bool bQuit = false;

		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{

				bQuit = true;
				break;
			}
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}

		if (bQuit) break;
	}

	return 0;
}
