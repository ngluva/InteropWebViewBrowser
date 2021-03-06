#pragma once

#include "stdafx.h"
#include "resource.h"
#include <vector>
#include <functional>

class WebViewWindow {
public:
	Microsoft::WRL::ComPtr<ABI::Windows::Web::UI::IWebViewControl> m_webview;
	HWND m_window = nullptr;

	void InitializeAsync(HWND parent, RECT position, std::function<void()> initializedCallback);
	void Resize(RECT position);
	void Show(bool show);
};

class App
{
public:
	static int RunNewInstance(_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ LPWSTR    lpCmdLine,
		_In_ int       nCmdShow)
	{
		App* app = new App();
		int result = app->Run(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
		delete app;
		app = nullptr;
		return result;
	}

protected:
	static LRESULT CALLBACK WndProcStatic(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam);

	static const size_t s_maxLoadString = 100;
	static const DWORD s_initializeWindowMessage = WM_USER;

	int Run(_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ LPWSTR    lpCmdLine,
		_In_ int       nCmdShow);
	void MyRegisterClasses(_In_ HINSTANCE hInstance);
	BOOL InitInstance(_In_ HINSTANCE hInstance, _In_ int nCmdShow);
	LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam, _Out_ bool* handled);
	void InitializeWin32WebView() { }

	void AddTab(std::function<void()> callback);
	WebViewWindow& GetCurrentTab();

	HINSTANCE m_hInst = nullptr;                                // current instance
	LPWSTR m_cmdline = nullptr;
	INT m_nShow = 0;
	WCHAR m_windowClass[s_maxLoadString];            // the main window class name
	static const WCHAR s_hostClass[s_maxLoadString];

	static const DWORD s_controlWebViewHeight = 45 * 2;
	friend class WebViewWindow;

	HWND m_mainWindow = 0;
	WebViewWindow m_controlWebView;
	std::vector<WebViewWindow> m_tabs;
	size_t m_tabIdx = 0;
};
