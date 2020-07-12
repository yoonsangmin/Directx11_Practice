#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_
#define TIMEOVER 100

#include "d3dclass.h"

#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"

#include "textureshaderclass.h"
#include "bitmapclass.h"

#include "textclass.h"

#include "fireshaderclass.h"
#include "minimapclass.h"

// Globals
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int, float, int, int, int, int, float);

	void ChangeBackground(char);
	char backgroundColor;
	void LightSetting(bool, bool, bool);
	void GameReset();

	float rotateZ;
	D3D11_FILL_MODE m_fill_mode;
	D3D11_FILTER m_filter;
	int m_MaxAnisotropy;

	D3DXVECTOR3* camera_move;
	D3DXVECTOR3* camera_pos;
	float camera_rotateX;
	float camera_rotateY;
	
	bool amb_on;
	bool diff_on;
	bool spec_on;

	bool key_exist;
	bool knife_exist;
	bool is_door_opened;
	int possess_key;
	bool possess_knife;
	bool clear_game;
	bool time_over;

	bool monster_1_exist;
	bool monster_2_exist;
	bool monster_3_exist;

	bool player_die;

	bool knife_swing;
	bool knife_swinged;

	bool squat;
	bool jump;

	bool squatC;

	float x;
	float z;
private:
	bool Render(float, float);
	void CameraMove(float, float, float);
	bool CollisionCheck();
	bool ModelCollisionCheck(ModelClass*);
	void MoveCancel(ModelClass*);
	void SetModelinfo(ModelClass*, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
	bool DrawModel(ModelClass*);
	bool DrawPlayerWapon(ModelClass*);
	bool RenderFire(ModelClass*);
	bool RenderMonster(ModelClass*, int);
private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	
	ModelClass* wall1_model[12];
	ModelClass* wall2_model[6];
	ModelClass* wall3_model[12];
	ModelClass* wall4_model[2];
	ModelClass* wall5_model[2];
	ModelClass* wall6_model[2];
	ModelClass* wall9_model;

	ModelClass* dummy_left;
	ModelClass* dummy_right;

	ModelClass* fire_model;


	ModelClass* door_model;
	ModelClass* enterance_model;
	ModelClass* torch_model;
	ModelClass* key_model;
	ModelClass* farWall_model;
	ModelClass* ceiling_model;
	ModelClass* plane_model;

	ModelClass* monster_model;
	ModelClass* knife_model;

	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;
	TextClass* m_Text;
	FireShaderClass* m_FireShader;
	MiniMapClass* m_MiniMap;

	int all_polygons;
	float key_vertical;
	float rotation;
	float fireframe;
	float knifeframe;
	float jumpframe;

	float prev_Y1;
	float prev_Y2;
	float prev_Y3;

	int all_Obj;
};
#endif