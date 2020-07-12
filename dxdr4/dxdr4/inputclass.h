#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_
#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include <dinput.h>
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();
	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsEscapePressed();
	void GetMouseLocation(int&, int&);

	void GetMove(int&, int&);

	bool IsWPressed();
	bool IsSPressed();
	bool IsAPressed();
	bool IsDPressed();

	bool IsRPressed();
	bool IsGPressed();
	bool IsBPressed();

	bool IsYPressed();
	bool IsHPressed();

	bool Is1Pressed();
	bool Is2Pressed();
	bool Is3Pressed();

	bool Is4Pressed();
	bool Is5Pressed();
	bool Is6Pressed();

	bool IsSpacePressed();
	bool IsLCPressed();

	bool IsMLBCLICK();
	//void KeyDown(unsigned int);
	//void KeyUp(unsigned int);
	//bool IsKeyDown(unsigned int);

	//bool KeyDowned(unsigned int);
private:
	//bool m_keys[256];

	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;
	
	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};
#endif