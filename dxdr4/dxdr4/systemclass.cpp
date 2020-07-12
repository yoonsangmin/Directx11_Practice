#include "systemclass.h"

SystemClass::SystemClass()
{
	m_Input = 0;
	m_Graphics = 0;
	m_Sound = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_Timer = 0;
	IX = 0;
	IY = 0;

	c_speed = 5.0f;
	m_speed = 0.25f;
	NewTime= 0;
	OldTime = 0;
	dt = 0;
	sound_time = 142.0f;
	play_time = 0.0f;

	previous_key = 0;
	knife_sound_played = false;
	die_sound_played = false;
	monster_remain = 0;
	previous_monster = 0;
	swing_sound_played = false;
}

SystemClass::SystemClass(const SystemClass& other)
{
}

SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	bool result;
	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;
	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);
	// Create the input object. This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the graphics object. This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if (!result)
	{
		return false;
	}

	// Create the sound object.
	m_Sound = new SoundClass;
	if (!m_Sound)
	{
		return false;
	}

	// Initialize the sound object.
	result = m_Sound->Initialize(m_hwnd);
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
		return false;
	}


	// Create the fps object.
	m_Fps = new FpsClass;
	if (!m_Fps)
	{
		return false;
	}
	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the cpu object.
	m_Cpu = new CpuClass;
	if (!m_Cpu)
	{
		return false;
	}
	// Initialize the cpu object.
	m_Cpu->Initialize();

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}
	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the Timer object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void SystemClass::Shutdown()
{
	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the cpu object.
	if (m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	// Release the fps object.
	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the sound object.
	if (m_Sound)
	{
		m_Sound->Shutdown();
		delete m_Sound;
		m_Sound = 0;
	}

	// Release the graphics object.
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}
	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	// Shutdown the window.
	ShutdownWindows();
	return;
}

void SystemClass::Run()
{
	MSG msg;
	bool done, result;
	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	// Loop until there is a quit message from the window or the user.
	done = false;
	while (!done)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if (!result)
			{
				MessageBox(m_hwnd, L"Frame Processing Failed", L"Error", MB_OK);
				done = true;
			}
		}

		// Check if the user pressed escape and wants to quit.
		if (m_Input->IsEscapePressed() == true)
		{
			done = true;
		}

		//// Check if the user pressed escape and wants to exit the application.
		//if (m_Input->IsKeyDown(VK_ESCAPE))
		//{
		//	return false;
		//}
		NewTime = timeGetTime();
		if (OldTime != 0)
		{
			dt = (float)(NewTime - OldTime) / 1000; //delta time
		}
		OldTime = NewTime;

		sound_time -= dt;

		if (TIMEOVER - play_time > 0.0f)
			play_time += dt;
		else
			play_time = TIMEOVER;

		if (sound_time < 0.0f)
		{
			m_Sound->PlayWaveFile();
			sound_time = 142.0f;
		}
		
		if (previous_key < m_Graphics->possess_key)
		{
			m_Sound->KeySound();
		}

		previous_key = m_Graphics->possess_key;

		if (m_Graphics->possess_knife && !knife_sound_played)
		{
			m_Sound->KeySound();
			knife_sound_played = true;
		}

		if (m_Graphics->player_die && !die_sound_played)
		{
			m_Sound->DieSound();
			die_sound_played = true;
		}

		if (m_Graphics->monster_1_exist)
			monster_remain++;
		if (m_Graphics->monster_2_exist)
			monster_remain++;
		if (m_Graphics->monster_3_exist)
			monster_remain++;

		if (monster_remain < previous_monster)
		{
			m_Sound->KillSound();
		}

		previous_monster = monster_remain;
		monster_remain = 0;

		if (m_Graphics->knife_swing && !swing_sound_played)
		{
			m_Sound->SwingSound();
			swing_sound_played = true;
		}
		if (!m_Graphics->knife_swing)
		{
			swing_sound_played = false;
		}



		if (m_Input->IsMLBCLICK() && !m_Graphics->knife_swing && m_Graphics->possess_knife)
		{
			m_Graphics->knife_swing = true;
		}

		if (m_Input->IsSpacePressed() && !m_Graphics->jump)
		{
			m_Graphics->jump = true;
		}

		if (m_Input->IsLCPressed())
		{
			m_Graphics->squat = true;
			c_speed = 2.0f;
		}
		else
		{
			m_Graphics->squat = false;
			c_speed = 5.0f;
		}

		m_Input->GetMove(IX, IY);

		CameraMove();
		
		ChangeBackground();
		
		GameRestart();

		ChangeFillmode();
		
		ChangeFilter();

		LightSwitch();
	}
	return;
}

bool SystemClass::Frame()
{
	bool result;
	int mouseX, mouseY;

	// Update the system stats.
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	// Do the input frame processing.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}
	// Get the location of the mouse from the input object,
	m_Input->GetMouseLocation(mouseX, mouseY);



	m_Graphics->rotateZ += 0.001f;


	// Do the frame processing for the graphics object.
	result = m_Graphics->Frame(m_Fps->GetFps(), m_Cpu->GetCpuPercentage(), m_Timer->GetTime(), mouseX, mouseY, screenWidth, screenHeight, play_time);
	if (!result)
	{
		return false;
	}
	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM
	lparam)
{
	//switch (umsg)
	//{
	//	// Check if a key has been pressed on the keyboard.
	//case WM_KEYDOWN:
	//{
	//	// If a key is pressed send it to the input object so it can record that state.
	//	m_Input->KeyDown((unsigned int)wparam);
	//	return 0;
	//}
	//// Check if a key has been released on the keyboard.
	//case WM_KEYUP:
	//{
	//	// If a key is released then send it to the input object so it can unset the state for that key.
	//	m_Input->KeyUp((unsigned int)wparam);
	//	return 0;
	//}
	//// Any other messages send to the default message handler as our application won't make use of them.
	//default:
	//{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	/*}
	}*/
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;
	// Get an external pointer to this object.
	ApplicationHandle = this;
	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);
	// Give the application a name.
	m_applicationName = L"Engine";
	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);
	// Register the window class.
	RegisterClassEx(&wc);
	// Determine the resolution of the clients desktop screen.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 600;
		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}
	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, posX, posY, screenWidth,
		screenHeight, NULL, NULL, m_hinstance, NULL);
	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	// Hide the mouse cursor.
	ShowCursor(false);
	return;
}

void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);
	// Fix the display settings if leaving full screen mode.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}
	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;
	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;
	// Release the pointer to this class.
	ApplicationHandle = NULL;
	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	// All other messages pass to the message handler in the system class.
	default:
	{
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}

void SystemClass::ChangeBackground()
{
	//1번 배경색 변환 코드 else if 쓰면 누르는 순서에 따라서 동시입력이 되어서 예외처리를 해주었습니다.
	//if (m_Input->IsRPressed() && !m_Input->IsGPressed() && !m_Input->IsBPressed()) //r
	//{
	//	m_Graphics->backgroundColor = 'r';
	//}

	if (m_Input->IsGPressed() && !m_Input->IsBPressed() && !m_Input->IsRPressed()) //g
	{
		m_Graphics->backgroundColor = 'g';
	}

	if (m_Input->IsBPressed() && !m_Input->IsRPressed() && !m_Input->IsGPressed()) //b
	{
		m_Graphics->backgroundColor = 'b';
	}
}

void SystemClass::GameRestart()
{
	if (m_Input->IsRPressed())
	{
		swing_sound_played = false;
		monster_remain = 0;
		previous_monster = 0;
		knife_sound_played = false;
		die_sound_played = false;
		play_time = 0;
		m_Graphics->GameReset();
	}
}

void SystemClass::ChangeFillmode()
{
	if (m_Input->IsYPressed() && !m_Input->IsHPressed())
	{
		m_Graphics->m_fill_mode = D3D11_FILL_WIREFRAME;
	}
	if (m_Input->IsHPressed() && !m_Input->IsYPressed())
	{
		m_Graphics->m_fill_mode = D3D11_FILL_SOLID;
	}
}

void SystemClass::ChangeFilter()
{
	if (m_Input->Is4Pressed())
	{
		m_Graphics->m_filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		m_Graphics->m_MaxAnisotropy = 1;
	}
	else if (m_Input->Is5Pressed())
	{
		m_Graphics->m_filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		m_Graphics->m_MaxAnisotropy = 1;
	}
	else if (m_Input->Is6Pressed())
	{
		m_Graphics->m_filter = D3D11_FILTER_ANISOTROPIC;
		m_Graphics->m_MaxAnisotropy = 10;
	}
}

void SystemClass::CameraMove()
{
	if (m_Input->IsWPressed() && !m_Input->IsSPressed())
	{
		/*m_Graphics->camera_move->x = 1.0f;*/
		m_Graphics->camera_move->z = +c_speed;
	}
	else if (m_Input->IsSPressed() && !m_Input->IsWPressed())
	{
		m_Graphics->camera_move->z = -c_speed;
	}
	else if (!m_Input->IsWPressed() && !m_Input->IsSPressed())
	{
		m_Graphics->camera_move->z = 0.0f;
	}
	if (m_Input->IsAPressed() && !m_Input->IsDPressed())
	{
		m_Graphics->camera_move->x = -c_speed;
	}
	else if (m_Input->IsDPressed() && !m_Input->IsAPressed())
	{
		m_Graphics->camera_move->x = +c_speed;
	}
	else if (!m_Input->IsAPressed() && !m_Input->IsDPressed())
	{
		m_Graphics->camera_move->x = 0.0f;
	}

	if (m_Input->IsWPressed() && m_Input->IsDPressed() && !m_Input->IsAPressed())
	{
		m_Graphics->camera_move->z = +c_speed * 0.7071067812f;
		m_Graphics->camera_move->x = +c_speed * 0.7071067812f;
	}

	else if (m_Input->IsWPressed() && m_Input->IsAPressed() && !m_Input->IsDPressed())
	{
		m_Graphics->camera_move->z = +c_speed * 0.7071067812f;
		m_Graphics->camera_move->x = -c_speed * 0.7071067812f;
	}

	else if (m_Input->IsSPressed() && m_Input->IsDPressed() && !m_Input->IsAPressed())
	{
		m_Graphics->camera_move->z = -c_speed * 0.7071067812f;
		m_Graphics->camera_move->x = +c_speed * 0.7071067812f;
	}

	else if (m_Input->IsSPressed() && m_Input->IsAPressed() && !m_Input->IsDPressed())
	{
		m_Graphics->camera_move->z = -c_speed * 0.7071067812f;
		m_Graphics->camera_move->x = -c_speed * 0.7071067812f;
	}

	//D3DXMatrixRotationYawPitchRoll()

	m_Graphics->camera_rotateY += m_speed * IX;
	m_Graphics->camera_rotateX += m_speed * IY;
	/*if (m_Input->m_keyboardState[DIK_RIGHT])
	{
		m_Graphics->camera_rotateY += 3.0f;
	}
	if (m_Input->m_keyboardState[DIK_UP])
	{
		m_Graphics->camera_rotateX -= 3.0f;
	}
	if (m_Input->m_keyboardState[DIK_DOWN])
	{
		m_Graphics->camera_rotateX += 3.0f;
	}*/
}

void SystemClass::LightSwitch()
{
	
	if (m_Input->Is1Pressed() && !pressed1)
	{
		if (m_Graphics->amb_on)
			m_Graphics->amb_on = false;
		else
			m_Graphics->amb_on = true;
		pressed1 = true;
	}
	else if (!m_Input->Is1Pressed() && pressed1)
	{
		pressed1 = false;
	}

	if (m_Input->Is2Pressed() && !pressed2)
	{
		if (m_Graphics->diff_on)
			m_Graphics->diff_on = false;
		else
			m_Graphics->diff_on = true;
		pressed2 = true;
	}
	else if (!m_Input->Is2Pressed() && pressed2)
	{
		pressed2 = false;
	}

	if (m_Input->Is3Pressed() && !pressed3)
	{
		if (m_Graphics->spec_on)
			m_Graphics->spec_on = false;
		else
			m_Graphics->spec_on = true;
		pressed3 = true;
	}
	else if (!m_Input->Is3Pressed() && pressed3)
	{
		pressed3 = false;
	}
}