#include "Main.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx9.h"

using namespace std;

void InputHandler() {
	for (int i = 0; i < 5; i++) {
		ImGui::GetIO().MouseDown[i] = false;
	}

	int Button = -1;
	if (GetAsyncKeyState(VK_LBUTTON)) {
		Button = 0;
	}

	if (Button != -1) {
		ImGui::GetIO().MouseDown[Button] = true;
	}
}

void Render()
{
	if (GetAsyncKeyState(VK_INSERT) & 1) DisplayMenu = !DisplayMenu;
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ActorLoop();
	AimbotLoop();
	ImGui::GetIO().MouseDrawCursor = DisplayMenu;

	if (DisplayMenu == true)
	{
		InputHandler();
		MenuWindow();
		SetWindowLong(Overlay.Hwnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW);
		UpdateWindow(Overlay.Hwnd);
		SetFocus(Overlay.Hwnd);
	} else {
		SetWindowLong(Overlay.Hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
		UpdateWindow(Overlay.Hwnd);
	}
	ImGui::EndFrame();

	DirectX9.pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	if (DirectX9.pDevice->BeginScene() >= 0) {
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		DirectX9.pDevice->EndScene();
	}

	HRESULT result = DirectX9.pDevice->Present(NULL, NULL, NULL, NULL);
	if (result == D3DERR_DEVICELOST && DirectX9.pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
		ImGui_ImplDX9_InvalidateDeviceObjects();
		DirectX9.pDevice->Reset(&DirectX9.pParameters);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

void MainLoop() {
	static RECT OldRect;
	ZeroMemory(&DirectX9.Message, sizeof(MSG));
	while (DirectX9.Message.message != WM_QUIT) {
		if (PeekMessage(&DirectX9.Message, Overlay.Hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&DirectX9.Message);
			DispatchMessage(&DirectX9.Message);
		}
		HWND ForegroundWindow = GetForegroundWindow();
		if (ForegroundWindow == Process.Hwnd) {
			HWND TempProcessHwnd = GetWindow(ForegroundWindow, GW_HWNDPREV);
			SetWindowPos(Overlay.Hwnd, TempProcessHwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		RECT TempRect;
		POINT TempPoint;
		ZeroMemory(&TempRect, sizeof(RECT));
		ZeroMemory(&TempPoint, sizeof(POINT));

		GetClientRect(Process.Hwnd, &TempRect);
		ClientToScreen(Process.Hwnd, &TempPoint);

		TempRect.left = TempPoint.x;
		TempRect.top = TempPoint.y;
		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = Process.Hwnd;

		if (TempRect.left != OldRect.left || TempRect.right != OldRect.right || TempRect.top != OldRect.top || TempRect.bottom != OldRect.bottom) {
			OldRect = TempRect;
			Width = TempRect.right;
			Height = TempRect.bottom;
			DirectX9.pParameters.BackBufferWidth = Width;
			DirectX9.pParameters.BackBufferHeight = Height;
			SetWindowPos(Overlay.Hwnd, (HWND)0, TempPoint.x, TempPoint.y, Width, Height, SWP_NOREDRAW);
			DirectX9.pDevice->Reset(&DirectX9.pParameters);
		}
		Render();
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	if (DirectX9.pDevice != NULL) {
		DirectX9.pDevice->EndScene();
		DirectX9.pDevice->Release();
	}
	if (DirectX9.IDirect3D9 != NULL) {
		DirectX9.IDirect3D9->Release();
	}
	DestroyWindow(Overlay.Hwnd);
	UnregisterClass(Overlay.WindowClass.lpszClassName, Overlay.WindowClass.hInstance);
}

bool DirectXInit() {
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &DirectX9.IDirect3D9))) {
		return false;
	}

	bool niggerballs;

	if (fastoverlay)
	{
		niggerballs = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
	{
		niggerballs = D3DPRESENT_INTERVAL_ONE;
	}

	D3DPRESENT_PARAMETERS Params = { 0 };
	Params.Windowed = TRUE;
	Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Params.hDeviceWindow = Overlay.Hwnd;
	Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	Params.BackBufferWidth = Width;
	Params.BackBufferHeight = Height;
	Params.PresentationInterval = niggerballs;
	Params.EnableAutoDepthStencil = TRUE;
	Params.AutoDepthStencilFormat = D3DFMT_D16;
	Params.PresentationInterval = niggerballs;
	Params.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	if (FAILED(DirectX9.IDirect3D9->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Overlay.Hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &Params, 0, &DirectX9.pDevice))) {
		DirectX9.IDirect3D9->Release();
		return false;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\ow2font.ttf", 17.0f, nullptr, io.Fonts->GetGlyphRangesDefault()); //you can add whatever font, or just slash out this line (it will download the font in the int main)

	ImGui_ImplWin32_Init(Overlay.Hwnd);
	ImGui_ImplDX9_Init(DirectX9.pDevice);
	DirectX9.IDirect3D9->Release();
	return true;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message) {
	case WM_DESTROY:
		if (DirectX9.pDevice != NULL) {
			DirectX9.pDevice->EndScene();
			DirectX9.pDevice->Release();
		}
		if (DirectX9.IDirect3D9 != NULL) {
			DirectX9.IDirect3D9->Release();
		}
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (DirectX9.pDevice != NULL && wParam != SIZE_MINIMIZED) {
			ImGui_ImplDX9_InvalidateDeviceObjects();
			DirectX9.pParameters.BackBufferWidth = LOWORD(lParam);
			DirectX9.pParameters.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = DirectX9.pDevice->Reset(&DirectX9.pParameters);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}


void SetupWindow()  //hooking to geforce overlay you can change to create window, or anything (overwatch's anti cheat isnt kernel level)
{
	Overlay.Hwnd = FindWindowA(("CEF-OSC-WIDGET"), ("NVIDIA GeForce Overlay"));

	if (!Overlay.Hwnd)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		MessageBoxA(0, ("Failed To Find NVIDIA."), ("Overlay"), MB_OK);
		Sleep(5000);
		exit(1);
	}

	ShowWindow(Overlay.Hwnd, SW_SHOW);

	SetWindowLongA(Overlay.Hwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
	SetWindowLongA(
		Overlay.Hwnd,
		-20,
		static_cast<LONG_PTR>(
			static_cast<int>(GetWindowLongA(Overlay.Hwnd, -20)) | 0x20
			)
	);

	MARGINS margin = { -1, -1, -1, -1 };
	DwmExtendFrameIntoClientArea(
		Overlay.Hwnd,
		&margin
	);

	SetLayeredWindowAttributes(
		Overlay.Hwnd,
		NULL,
		0xFF,
		0x02
	);

	SetWindowPos(
		Overlay.Hwnd,
		HWND_TOPMOST,
		0, 0, 0, 0,
		0x0002 | 0x0001
	);



	UpdateWindow(Overlay.Hwnd);
	HWND(overlaywindow);
}


DWORD WINAPI ProcessCheck(LPVOID lpParameter) {
	Entity = FindPatternsExRegs(Offsets::AOB, Offsets::MASK, Offsets::EntitySize);
	while (true) {
		if (AutoUpdate) {
			Entity = FindPatternsExRegs(Offsets::AOB, Offsets::MASK, Offsets::EntitySize);
		}
		if (Process.Hwnd != NULL) {
			if (GetProcessID("Overwatch.exe") == 0) {
				CloseHandle(ProcessHandle);
				exit(0);
			}
		}
		Sleep(10);
	}
}

int main()
{
	system("color 3");
	SonyDriverHelper::api::Init();
	cout << "Welcome To Ow2 External :)" << endl;
	Sleep(1500);
	cout << "\nOpen Overwatch..." << endl;
	Sleep(1000);
	cout << "\nOnce In Overwatch Press Any Key." << endl;
	system("pause >null");
	Sleep(1000);
	cout << "\nTab Into Overwatch." << endl;


	ProcessId = GetProcessID("Overwatch.exe");
	ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, ProcessId);
	ModuleBase = GetBaseAddress(ProcessId, "Overwatch.exe");

	bool WindowFocus = false;
	while (WindowFocus == false) {
		DWORD ForegroundWindowProcessID;
		GetWindowThreadProcessId(GetForegroundWindow(), &ForegroundWindowProcessID);
		if (GetProcessID("Overwatch.exe") == ForegroundWindowProcessID) {
			Process.ID = GetCurrentProcessId();
			Process.Handle = GetCurrentProcess();
			Process.Hwnd = GetForegroundWindow();

			RECT TempRect;
			GetWindowRect(Process.Hwnd, &TempRect);
			Width = TempRect.right - TempRect.left;
			Height = TempRect.bottom - TempRect.top;
			Process.WindowLeft = TempRect.left;
			Process.WindowRight = TempRect.right;
			Process.WindowTop = TempRect.top;
			Process.WindowBottom = TempRect.bottom;

			char TempTitle[MAX_PATH];
			GetWindowText(Process.Hwnd, TempTitle, sizeof(TempTitle));
			Process.Title = TempTitle;

			char TempClassName[MAX_PATH];
			GetClassName(Process.Hwnd, TempClassName, sizeof(TempClassName));
			Process.ClassName = TempClassName;

			char TempPath[MAX_PATH];
			GetModuleFileNameEx(Process.Handle, NULL, TempPath, sizeof(TempPath));
			Process.Path = TempPath;
			
			WindowFocus = true;
		}
	}

	if (CreateConsole == false) {
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	} else {
		cout << "Process Id = " << ProcessId << endl;
		cout << "Base Address = " << hex << ModuleBase << endl;
	}

	SetupWindow();
	DirectXInit();
	CreateThread(0, 0, ProcessCheck, 0, 0, 0);
	while (TRUE) {
		MainLoop();
	}
}