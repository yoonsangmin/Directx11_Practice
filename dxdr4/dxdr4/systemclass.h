#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <time.h>
#include "inputclass.h"
#include "graphicsclass.h"
#include "soundclass.h"
#include "fpsclass.h"
#include "cpuclass.h"
#include "timerclass.h"

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();
	bool Initialize();
	void Shutdown();
	void Run();
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	void ChangeBackground();
	void ChangeFillmode();
	void ChangeFilter();
private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
	void CameraMove();
	void LightSwitch();
	void GameRestart();
private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	InputClass* m_Input;
	GraphicsClass* m_Graphics;
	SoundClass* m_Sound;
	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	TimerClass* m_Timer;

	int screenWidth, screenHeight;

	bool pressed1;
	bool pressed2;
	bool pressed3;

	int IX;
	int IY;

	float c_speed;
	float m_speed;

	int NewTime;
	int OldTime;
	float dt;
	float sound_time;
	float play_time;

	int previous_key;
	bool knife_sound_played;
	bool die_sound_played;
	int monster_remain;
	int previous_monster;
	bool swing_sound_played;
};
// Function prototypes
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// Globals
static SystemClass* ApplicationHandle = 0;
#endif