#include "inputclass.h"
InputClass::InputClass()
{
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;
}
InputClass::InputClass(const InputClass& other)
{
}
InputClass::~InputClass()
{
}
bool InputClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;


	// Store the screen size which will be used for positioning the mouse cursor.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Initialize the location of the mouse on the screen.
	m_mouseX = 0;
	m_mouseY = 0;

	// Initialize the main direct input interface.
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Initialize the direct input interface for the keyboard.
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the keyboard to not share with other programs.
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// Now acquire the keyboard.
	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}



	// Initialize the direct input interface for the mouse.
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the data format for the mouse using the pre-defined mouse data format.
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the mouse to share with other programs.
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// Acquire the mouse.
	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	// Initialize all the keys to being released and not pressed. 
	////////////////////////���̷�Ʈ ��ǲ �ƴ�
	/*for (i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}*/
	return true;
}


void InputClass::Shutdown()
{
	// Release the mouse.
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	// Release the keyboard.
	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	// Release the main interface to direct input.
	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}

	return;
}

bool InputClass::Frame()
{
	bool result;

	// Read the current state of the keyboard.
	result = ReadKeyboard();
	if (!result)
	{
		return false;
	}

	// Read the current state of the mouse.
	result = ReadMouse();
	if (!result)
	{
		return false;
	}

	// Process the changes in the mouse and keyboard.
	ProcessInput();

	return true;
}

bool InputClass::ReadKeyboard()
{
	HRESULT result;


	// Read the keyboard device.
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool InputClass::ReadMouse()
{
	HRESULT result;


	// Read the mouse device.
	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

void InputClass::ProcessInput()
{
	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if (m_mouseX < 0) { m_mouseX = 0; }
	if (m_mouseY < 0) { m_mouseY = 0; }

	if (m_mouseX > m_screenWidth) { m_mouseX = m_screenWidth; }
	if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }

	return;
}

bool InputClass::IsEscapePressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return true;
	}

	return false;
}

void InputClass::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;
	return;
}

void InputClass::GetMove(int& _iX, int& _iY)
{
	_iX = m_mouseState.lX;
	_iY = m_mouseState.lY;
}

bool InputClass::IsWPressed()
{

	if (m_keyboardState[DIK_W] & 0x80)
	{
		return true;
	}

	return false;
}
bool InputClass::IsSPressed()
{

	if (m_keyboardState[DIK_S] & 0x80)
	{
		return true;
	}

	return false;
}
bool InputClass::IsAPressed()
{

	if (m_keyboardState[DIK_A] & 0x80)
	{
		return true;
	}

	return false;
}
bool InputClass::IsDPressed()
{

	if (m_keyboardState[DIK_D] & 0x80)
	{
		return true;
	}

	return false;
}
bool InputClass::IsRPressed()
{

	if (m_keyboardState[DIK_R] & 0x80)
	{
		return true;
	}

	return false;
}
bool InputClass::IsGPressed()
{

	if (m_keyboardState[DIK_G] & 0x80)
	{
		return true;
	}

	return false;
}
bool InputClass::IsBPressed()
{

	if (m_keyboardState[DIK_B] & 0x80)
	{
		return true;
	}

	return false;
}
bool InputClass::IsYPressed()
{

	if (m_keyboardState[DIK_Y] & 0x80)
	{
		return true;
	}

	return false;
}
bool InputClass::IsHPressed()
{

	if (m_keyboardState[DIK_H] & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::Is1Pressed()
{

	if (m_keyboardState[DIK_1] & 0x80)
	{
		return true;
	}

	return false;
}
bool InputClass::Is2Pressed()
{

	if (m_keyboardState[DIK_2] & 0x80)
	{
		return true;
	}

	return false;
}
bool InputClass::Is3Pressed()
{

	if (m_keyboardState[DIK_3] & 0x80)
	{
		return true;
	}

	return false;
}
bool InputClass::Is4Pressed()
{

	if (m_keyboardState[DIK_4] & 0x80)
	{
		return true;
	}

	return false;
}
bool InputClass::Is5Pressed()
{

	if (m_keyboardState[DIK_5] & 0x80)
	{
		return true;
	}

	return false;
}
bool InputClass::Is6Pressed()
{

	if (m_keyboardState[DIK_6] & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::IsSpacePressed()
{

	if (m_keyboardState[DIK_SPACE] & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::IsLCPressed()
{

	if (m_keyboardState[DIK_LCONTROL] & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::IsMLBCLICK()
{

	if (m_mouseState.rgbButtons[0] & 0x80)
	{
		return true;
	}

	return false;
}

////////////////////////���̷�Ʈ ��ǲ �ƴ�
//void InputClass::KeyDown(unsigned int input)
//{
//	// If a key is pressed then save that state in the key array.
//	m_keys[input] = true;
//	return;
//}
//void InputClass::KeyUp(unsigned int input)
//{
//	// If a key is released then clear that state in the key array.
//	m_keys[input] = false;
//	return;
//}
//bool InputClass::IsKeyDown(unsigned int key)
//{
//	// Return what state the key is in (pressed/not pressed).
//	return m_keys[key];
//}

//bool InputClass::KeyDowned(unsigned int input)
//{
//	if (m_keys[input])
//	{
//		m_keys[input] = false;
//		return true;
//	}
//	return false;
//}