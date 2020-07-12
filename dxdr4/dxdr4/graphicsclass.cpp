#include "graphicsclass.h"
GraphicsClass::GraphicsClass()
{
	backgroundColor = NULL;
	rotateZ = 0.0f;
	m_fill_mode = D3D11_FILL_SOLID;
	m_filter = D3D11_FILTER_ANISOTROPIC;
	m_MaxAnisotropy = 10;

	all_Obj = 0;
	m_D3D = 0;
	m_Camera = 0;
	for (int i = 0; i < 12; i++)
	{
		wall1_model[i] = 0;
	}

	for (int i = 0; i < 6; i++)
	{
		wall2_model[i] = 0;
	}

	for (int i = 0; i < 12; i++)
	{
		wall3_model[i] = 0;
	}

	for (int i = 0; i < 2; i++)
	{
		wall4_model[i] = 0;
	}

	for (int i = 0; i < 2; i++)
	{
		wall5_model[i] = 0;
	}

	for (int i = 0; i < 2; i++)
	{
		wall6_model[i] = 0;
	}

	wall9_model = 0;
	
	
	dummy_left = new ModelClass;
	dummy_right = new ModelClass;

	fire_model = 0;

	enterance_model = 0;
	torch_model = 0;

	door_model = 0;
	key_model = 0;
	farWall_model = 0;
	ceiling_model = 0;
	plane_model = 0;

	monster_model = 0;
	knife_model = 0;


	m_LightShader = 0;
	m_Light = 0;

	m_TextureShader = 0;
	m_Bitmap = 0;

	m_Text = 0;

	m_FireShader = 0;
	m_MiniMap = 0;

	all_polygons = 0;

	monster_1_exist = true;
	monster_2_exist = true;
	monster_3_exist = true;

	player_die = false;

	z = 196.8504f;
	x = 39.37f;

	camera_move = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	camera_pos = new D3DXVECTOR3(140.0f, 50.0f, -275.0f + x);
	
	
	camera_rotateX = 0.0f;
	camera_rotateY = 0.0f;

	amb_on = true;
	diff_on = true;
	spec_on = true;

	key_exist = true;
	knife_exist = true;
	is_door_opened = false;
	possess_key = 0;
	possess_knife = false;
	key_vertical = 0.0f;
	rotation = 0.0f;
	clear_game = false;

	fireframe = 0.0f;
	time_over = false;

	knife_swing = false;
	knife_swinged = false;
	knifeframe = 0.0f;


	jumpframe = -2.0f;
	squat = false;
	jump = false;
	squatC = false;

	prev_Y1 = 0.0f;
	prev_Y2 = 0.0f;
	prev_Y3 = 0.0f;
}
GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}
GraphicsClass::~GraphicsClass()
{
}
bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}
	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN,
		SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}
	// Set the initial position of the camera. Ä«¸Þ¶ó À§Ä¡ ¿Å±â´Â ÇÔ¼ö
	m_Camera->SetPosition(0.0f, 40.0f, -100.0f);
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();
	// Create the model object.

	//ºÒ²É
	fire_model = new ModelClass;
	if (!fire_model)
	{
		return false;
	}

	result = fire_model->FireInitialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/square.txt", (WCHAR*)L"../dxdr4/data/fire01.dds",
		(WCHAR*)L"../dxdr4/data/noise01.dds", (WCHAR*)L"../dxdr4/data/alpha01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	all_Obj++;

	m_FireShader = new FireShaderClass;
	if (!m_FireShader)
	{
		return false;
	}

	// Initialize the fire shader object.
	result = m_FireShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire shader object.", L"Error", MB_OK);
		return false;
	}

	//ºÒ²É






	for (int i = 0; i < 12; i++)
	{
		wall1_model[i] = new ModelClass;
		if (!wall1_model[i])
		{
			return false;
		}
		// Initialize the model object.
		//desk_model->SetPosition(0.0f, 0.0f, 0.0f);
		result = wall1_model[i]->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/1.obj", (WCHAR*)L"../dxdr4/data/Wall/Wall.dds", &all_polygons);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model1 object.", L"Error", MB_OK);
			return false;
		}
		all_Obj++;
	}

	for (int i = 0; i < 6; i++)
	{
		wall2_model[i] = new ModelClass;
		if (!wall2_model[i])
		{
			return false;
		}
		// Initialize the model object.
		//desk_model->SetPosition(0.0f, 0.0f, 0.0f);
		result = wall2_model[i]->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/2.obj", (WCHAR*)L"../dxdr4/data/Wall/Wall.dds", &all_polygons);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model1 object.", L"Error", MB_OK);
			return false;
		}
		all_Obj++;
	}

	for (int i = 0; i < 12; i++)
	{
		wall3_model[i] = new ModelClass;
		if (!wall3_model[i])
		{
			return false;
		}
		// Initialize the model object.
		//desk_model->SetPosition(0.0f, 0.0f, 0.0f);
		result = wall3_model[i]->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/3.obj", (WCHAR*)L"../dxdr4/data/Wall/Wall.dds", &all_polygons);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model1 object.", L"Error", MB_OK);
			return false;
		}
		all_Obj++;
	}

	for (int i = 0; i < 2; i++)
	{
		wall4_model[i] = new ModelClass;
		if (!wall4_model[i])
		{
			return false;
		}
		// Initialize the model object.
		//desk_model->SetPosition(0.0f, 0.0f, 0.0f);
		result = wall4_model[i]->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/4.obj", (WCHAR*)L"../dxdr4/data/Wall/Wall.dds", &all_polygons);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model1 object.", L"Error", MB_OK);
			return false;
		}
		all_Obj++;
	}

	for (int i = 0; i < 2; i++)
	{
		wall5_model[i] = new ModelClass;
		if (!wall5_model[i])
		{
			return false;
		}
		// Initialize the model object.
		//desk_model->SetPosition(0.0f, 0.0f, 0.0f);
		result = wall5_model[i]->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/5.obj", (WCHAR*)L"../dxdr4/data/Wall/Wall.dds", &all_polygons);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model1 object.", L"Error", MB_OK);
			return false;
		}
		all_Obj++;
	}

	for (int i = 0; i < 2; i++)
	{
		wall6_model[i] = new ModelClass;
		if (!wall6_model[i])
		{
			return false;
		}
		// Initialize the model object.
		//desk_model->SetPosition(0.0f, 0.0f, 0.0f);
		result = wall6_model[i]->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/6.obj", (WCHAR*)L"../dxdr4/data/Wall/Wall.dds", &all_polygons);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model1 object.", L"Error", MB_OK);
			return false;
		}
		all_Obj++;
	}

	

	wall9_model = new ModelClass;
	if (!wall9_model)
	{
		return false;
	}
	// Initialize the model object.
	//desk_model->SetPosition(0.0f, 0.0f, 0.0f);
	result = wall9_model->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/9.obj", (WCHAR*)L"../dxdr4/data/Wall/Wall.dds", &all_polygons);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model1 object.", L"Error", MB_OK);
		return false;
	}
	all_Obj++;

	




	torch_model = new ModelClass;
	if (!torch_model)
	{
		return false;
	}
	// Initialize the model object.
	//chair_model->SetPosition(0.0f, 0.0f, -50.0f);
	result = torch_model->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/torch.obj", (WCHAR*)L"../dxdr4/data/torch.dds", &all_polygons);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the torch object.", L"Error", MB_OK);
		return false;
	}
	all_Obj++;


	enterance_model = new ModelClass;
	if (!enterance_model)
	{
		return false;
	}
	// Initialize the model object.
	//chair_model->SetPosition(0.0f, 0.0f, -50.0f);
	result = enterance_model->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/enterance.obj", (WCHAR*)L"../dxdr4/data/Door/Door.dds", &all_polygons);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the enterance object.", L"Error", MB_OK);
		return false;
	}
	all_Obj++;



	door_model = new ModelClass;
	if (!door_model)
	{
		return false;
	}
	// Initialize the model object.
	//chair_model->SetPosition(0.0f, 0.0f, -50.0f);
	result = door_model->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/Door/Door.obj", (WCHAR*)L"../dxdr4/data/Door/Door.dds", &all_polygons);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model2 object.", L"Error", MB_OK);
		return false;
	}
	all_Obj++;

	key_model = new ModelClass;
	if (!key_model)
	{
		return false;
	}
	// Initialize the model object.
	//bookshelf_model->SetPosition(1.0f, -2.0f, 50.0f);
	result = key_model->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/Key/Key.obj", (WCHAR*)L"../dxdr4/data/Key/Key.dds", &all_polygons);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	all_Obj++;

	farWall_model = new ModelClass;
	if (!farWall_model)
	{
		return false;
	}
	// Initialize the model object.
	//bookshelf_model->SetPosition(1.0f, -2.0f, 50.0f);
	result = farWall_model->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/FarWall/FarWall.obj", (WCHAR*)L"../dxdr4/data/FarWall/FarWall.dds", &all_polygons);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model4 object.", L"Error", MB_OK);
		return false;
	}
	all_Obj++;

	ceiling_model = new ModelClass;
	if (!ceiling_model)
	{
		return false;
	}
	// Initialize the model object.
	//bookshelf_model->SetPosition(1.0f, -2.0f, 50.0f);
	result = ceiling_model->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/Ceiling/Ceiling.obj", (WCHAR*)L"../dxdr4/data/Ceiling/Ceiling.dds", &all_polygons);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model5 object.", L"Error", MB_OK);
		return false;
	}
	all_Obj++;


	plane_model = new ModelClass;
	if (!plane_model)
	{
		return false;
	}
	// Initialize the model object.
	//plane_model->SetPosition(0.0f, 0.0f, 0.0f);
	result = plane_model->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/Floor.obj", (WCHAR*)L"../dxdr4/data/Floor.dds", &all_polygons);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	all_Obj++;


	//all_polygons = wall_model->m_polygons + door_model->m_polygons + key_model->m_polygons + plane_model->m_polygons;


	monster_model = new ModelClass;
	if (!monster_model)
	{
		return false;
	}
	// Initialize the model object.
	//chair_model->SetPosition(0.0f, 0.0f, -50.0f);
	result = monster_model->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/monster/Monster.obj", (WCHAR*)L"../dxdr4/data/monster/diffuso.dds", &all_polygons);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the torch object.", L"Error", MB_OK);
		return false;
	}
	all_Obj++;


	knife_model = new ModelClass;
	if (!knife_model)
	{
		return false;
	}
	// Initialize the model object.
	//chair_model->SetPosition(0.0f, 0.0f, -50.0f);
	result = knife_model->Initialize(m_D3D->GetDevice(), (char*)"../dxdr4/data/monster/Knife.obj", (WCHAR*)L"../dxdr4/data/monster/knife_hand.dds", &all_polygons);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the torch object.", L"Error", MB_OK);
		return false;
	}
	all_Obj++;



	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}
	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	LightSetting(amb_on, diff_on, spec_on);


	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}
	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}
	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight,
		(WCHAR*)L"../dxdr4/data/plane.dds", 256, 256);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}


	D3DXMATRIX baseViewMatrix;

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}
	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth,
		screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// ¹Ì´Ï ¸Ê °´Ã¼¸¦ »ý¼ºÇÕ´Ï´Ù..
	m_MiniMap = new MiniMapClass;
	if (!m_MiniMap)
	{
		return false;
	}

	// ¹Ì´Ï ¸Ê °´Ã¼¸¦ ÃÊ±âÈ­ÇÕ´Ï´Ù.
	if (!m_MiniMap->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), screenWidth, screenHeight, 2700, 2850))
	{
		return false;
	}

	return true;
}
void GraphicsClass::Shutdown()
{
	// ¹Ì´Ï ¸Ê °´Ã¼¸¦ ÇØÁ¦ÇÕ´Ï´Ù.
	if (m_MiniMap)
	{
		m_MiniMap->Shutdown();
		delete m_MiniMap;
		m_MiniMap = 0;
	}

	if (m_FireShader)
	{
		m_FireShader->Shutdown();
		delete m_FireShader;
		m_FireShader = 0;
	}

	if (fire_model)
	{
		fire_model->Shutdown();
		delete fire_model;
		fire_model = 0;
	}

	// Release the model object.
	for (int i = 0; i < 12; i++)
	{
		if (wall1_model[i])
		{
			wall1_model[i]->Shutdown();
			delete wall1_model[i];
			wall1_model[i] = 0;
		}
	}
	
	for (int i = 0; i < 6; i++)
	{
		if (wall2_model[i])
		{
			wall2_model[i]->Shutdown();
			delete wall2_model[i];
			wall2_model[i] = 0;
		}
	}

	for (int i = 0; i < 12; i++)
	{
		if (wall3_model[i])
		{
			wall3_model[i]->Shutdown();
			delete wall3_model[i];
			wall3_model[i] = 0;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (wall4_model[i])
		{
			wall4_model[i]->Shutdown();
			delete wall4_model[i];
			wall4_model[i] = 0;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (wall5_model[i])
		{
			wall5_model[i]->Shutdown();
			delete wall5_model[i];
			wall5_model[i] = 0;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (wall6_model[i])
		{
			wall6_model[i]->Shutdown();
			delete wall6_model[i];
			wall6_model[i] = 0;
		}
	}

	if (wall9_model)
	{
		wall9_model->Shutdown();
		delete wall9_model;
		wall9_model = 0;
	}

	if (monster_model)
	{
		monster_model->Shutdown();
		delete monster_model;
		monster_model = 0;
	}

	if (knife_model)
	{
		knife_model->Shutdown();
		delete knife_model;
		knife_model = 0;
	}

	if (torch_model)
	{
		torch_model->Shutdown();
		delete torch_model;
		torch_model = 0;
	}

	if (enterance_model)
	{
		enterance_model->Shutdown();
		delete enterance_model;
		enterance_model = 0;
	}
	if (door_model)
	{
		door_model->Shutdown();
		delete door_model;
		door_model = 0;
	}

	if (key_model)
	{
		key_model->Shutdown();
		delete key_model;
		key_model = 0;
	}

	if (farWall_model)
	{
		farWall_model->Shutdown();
		delete farWall_model;
		farWall_model = 0;
	}

	if (ceiling_model)
	{
		ceiling_model->Shutdown();
		delete ceiling_model;
		ceiling_model = 0;
	}

	if (plane_model)
	{
		plane_model->Shutdown();
		delete plane_model;
		plane_model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}
	
	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}


	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}


	return;
}
bool GraphicsClass::Frame(int fps, int cpu, float frameTime, int mouseX, int mouseY, int screenWidth, int screenHeight, float time)
{
	bool result;

	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	key_vertical += (float)D3DX_PI * 0.05f;
		
	// Increment the frame time counter.
	fireframe += 0.01f;
	if (fireframe > 1000.0f)
	{
		fireframe = 0.0f;
	}
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	if (key_vertical > 5.0f)
	{
		key_vertical -= 10.0f;
	}

	
	if (TIMEOVER - time <= 0)
	{
		time_over = true;
	}


	// Render the graphics scene.
	result = Render(rotation, key_vertical);
	if (!result)
	{
		return false;
	}

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}


	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetObject(all_Obj, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetSize(screenWidth, screenHeight, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetPolygon(all_polygons, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetX(camera_pos->x, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetZ(camera_pos->z, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	
	result = m_Text->SetTime(TIMEOVER - time, m_D3D->GetDeviceContext(), screenWidth);
	if (!result)
	{
		return false;
	}

	result = m_Text->SetKey(possess_key, m_D3D->GetDeviceContext(), screenWidth);
	if (!result)
	{
		return false;
	}

	if (time <= 3)
	{
		result = m_Text->SetMessage((char*)"Game Start", (char*)"", m_D3D->GetDeviceContext(), screenWidth, screenHeight);
		if (!result)
		{
			return false;
		}
	}

	if (time > 3)
	{
		result = m_Text->SetMessage((char*)"", (char*)"", m_D3D->GetDeviceContext(), screenWidth, screenHeight);
		if (!result)
		{
			return false;
		}
	}

	if (player_die)
	{
		result = m_Text->SetMessage((char*)"Player Died", (char*)"Press R to restart", m_D3D->GetDeviceContext(), screenWidth, screenHeight);
		if (!result)
		{
			return false;
		}
		backgroundColor = 'r';
	}

	if (is_door_opened && TIMEOVER - time > 0 || clear_game)
	{
		clear_game = true;
		result = m_Text->SetMessage((char*)"Game Clear", (char*)"Press R to restart", m_D3D->GetDeviceContext(), screenWidth, screenHeight);
		if (!result)
		{
			return false;
		}
	}

	else if (TIMEOVER - time <= 0 && !clear_game)
	{
		result = m_Text->SetMessage((char*)"Game Over", (char*)"Press R to restart", m_D3D->GetDeviceContext(), screenWidth, screenHeight);
		if (!result)
		{
			return false;
		}
	}

	

	// ¹Ì´Ï ¸Ê À§Ä¡ Ç¥½Ã±â¸¦ ¾÷µ¥ÀÌÆ®ÇÕ´Ï´Ù.
	m_MiniMap->PositionUpdate(camera_pos->x+1685.0f, camera_pos->z+250.0f);

	// Set the location of the mouse.
	//result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	//if (!result)
	//{
	//	return false;
	//}


	return true;
}
bool GraphicsClass::Render(float rotation, float key_vertical)
{
	D3DXMATRIX orthoMatrix, worldMatrix, viewMatrix, baseViewMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	/*m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);*/
	
	if(backgroundColor == NULL)
		m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	ChangeBackground(backgroundColor);

	LightSetting(amb_on, diff_on, spec_on);

	if (squat && !jump)
	{
		squatC = true;
		camera_pos->y = 30.0f;
	}
	else if (!squat && !jump)
	{
		camera_pos->y = 50.0f;
		squatC = false;
	}
	
	if (jump)
	{
		if (squatC && !squat)
		{
			camera_pos->y += 20.0f;
			squatC = false;
		}
		if (jumpframe <= 0.0f)
		{
			camera_pos->y += pow(jumpframe, 2);
			jumpframe += 0.1f;
		}
		else if (jumpframe > 0.0f && jumpframe < 2.0f)
		{
			camera_pos->y -= pow(jumpframe, 2);
			jumpframe += 0.1f;
		}
		else if (jumpframe >= 2.0f)
		{
			camera_pos->y = 50.0f;
			jump = false;
			jumpframe = -2.0f;
		}
	}

	if (clear_game || player_die || time_over)
	{
		camera_pos = new D3DXVECTOR3(camera_pos->x, 10000.0f, camera_pos->z);
		possess_knife = false;
	}
	else
		CameraMove(camera_move->x, camera_move->y, camera_move->z);


	while (CollisionCheck()) {}

	m_Camera->SetPosition(camera_pos->x, camera_pos->y, camera_pos->z);

	if (camera_rotateX < -90.0f)
		camera_rotateX = -90.0f;
	if (camera_rotateX > 90.0f)
		camera_rotateX = 90.0f;

	m_Camera->SetRotation(camera_rotateX, camera_rotateY, 0.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();


	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);

	
	if (ModelCollisionCheck(key_model) && key_exist)
	{
		possess_key = 1;
		key_exist = false;
	}

	if (ModelCollisionCheck(knife_model) && knife_exist)
	{
		possess_knife = true;
		knife_exist = false;
	}


	if (key_vertical < 0.0f)
	{
		key_vertical = -key_vertical;
	}

	if (key_exist)
	{
		key_model->SetMeshSize(20.0f);
		SetModelinfo(key_model, D3DXVECTOR3(218.5996f + 4.0f*z - 0.5f*z + 0.5f*x - 0.5f*z + 0.5f*x - 0.5f*x - 0.5f*z, 20.0f + key_vertical, -275.0f + 3.0f*z + x + z + z + 0.5f*x), D3DXVECTOR3(0.0f, 90.0f * 0.0174532925f, rotation), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
		result = DrawModel(key_model);
		if (!result)
		{
			return false;
		}
	}

	if (knife_exist)
	{
		knife_model->SetMeshSize(20.0f);
		SetModelinfo(knife_model, D3DXVECTOR3(22.0394f - 6.0f*z - x + 0.5f *x + 0.5f *z, 30.0f + key_vertical, -275.0f + 9.5f*z + 6.5f*x), D3DXVECTOR3(rotation, 0.0f, 90.0f * 0.0174532925f), D3DXVECTOR3(0.3f, 0.3f, 0.3f));
		result = DrawModel(knife_model);
		if (!result)
		{
			return false;
		}
	}


	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//D3DXMatrixRotationY(&desk_worldMatrix, rotation);
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	SetModelinfo(wall1_model[0], D3DXVECTOR3(218.5996f + x + 2.0f*z - 0.5f*x + 2.0f*z - 0.5f*x, 0.0f, -275.0f + 1.5f*z - 0.5f*x + 1.5f*z + 0.5f*x + 0.5f*x + 0.5f*z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall1_model[0]);
	if (!result)
	{
		return false;
	}
	
	


	SetModelinfo(wall1_model[1], D3DXVECTOR3(22.0394f - 9.0f*z + x, 0.0f, -275.0f + 3.0f*z + 0.5f*x + 0.5f*z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall1_model[1]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall1_model[2], D3DXVECTOR3(218.5996f + 4.0f*z - 0.5f*z + 0.5f*x, 0.0f, -275.0f + 3.0f*z + 0.5f*x + 0.5f*z + 0.5f*x + 0.5f*z), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall1_model[2]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall1_model[3], D3DXVECTOR3(218.5996f + 4.0f*z - 0.5f*z + 0.5f*x - 0.5f*z + 0.5f*x - 0.5f*x - 0.5f*z, 0.0f, -275.0f + 3.0f*z + x + z + z + 0.5f*x + z - 0.5f*x), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall1_model[3]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall1_model[4], D3DXVECTOR3(22.0394f - 9.0f*z + x + 2.5f*z - 0.5f*x + 2.5f*z - 0.5f*x - 2.5f*z - 0.5f*x - 2.5f*z + 0.5f*x, 0.0f, -275.0f + 3.0f*z + x + z + 1.5f*z + 1.5f*z + 0.5f*x + 0.5f*z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall1_model[4]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall1_model[5], D3DXVECTOR3(22.0394f - 6.0f*z - x + 0.5f *x + 0.5f *z, 0.0f, -275.0f + 3.0f*z + x + 5.0f*z + 0.5f*x + 0.5f*x + 1.5f*z + 0.5f*x + 1.5f*z - 0.5f*x), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall1_model[5]);
	if (!result)
	{
		return false;
	}


	SetModelinfo(wall1_model[6], D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 0.5f*x + 3.0f*z - 0.5f*x, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall1_model[6]);
	if (!result)
	{
		return false;
	}


	SetModelinfo(wall1_model[7], D3DXVECTOR3(218.5996f + x - 1.5f*z + x + x - z - z - z + 0.5f*x, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*x + 3.0f*z + 0.5f*x + 3.0f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall1_model[7]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall1_model[8], D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 3.0f*z - 1.5f*z + 0.5f* x + x + x - 2.0f*z + 1.5f*z - 0.5f*x + 1.5f* z - 0.5f*x, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + z + z + z + x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall1_model[8]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall1_model[9], D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 3.0f*z - 1.5f*z + 0.5f* x + x + x - 2.0f*z - z + 0.5f*x - z - x + z - 0.5f*x + 0.5f*x + 98.2801f - 0.5f*x - z + x, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + 0.5f*z + z + z + 0.5f*x + x + z + 1.5f*z + 0.5f*x + 1.5f*z - 19.6850f + 39.37f), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall1_model[9]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall1_model[10], D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 3.0f*z - 1.5f*z + 0.5f* x + x + x - 2.0f*z - z + 0.5f*x - z - x + z - 0.5f*x + 0.5f*x - 98.2801f - 0.5f*x - z + x + z + 196.5602f + z - x, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + 0.5f*z + z + z + 0.5f*x + x + z + 1.5f*z + 0.5f*x + 1.5f*z - 19.6850f + 39.37f), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall1_model[10]);
	if (!result)
	{
		return false;
	}
	
	SetModelinfo(wall1_model[11], D3DXVECTOR3(140.0f, 0.0f, -275.0f), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall1_model[11]);
	if (!result)
	{
		return false;
	}



	SetModelinfo(wall2_model[0], D3DXVECTOR3(218.5996f + 4.0f*z - 0.5f*z + 0.5f*x - 0.5f*z + 0.5f*x, 0.0f, -275.0f + 3.0f*z + x + z + z + 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall2_model[0]);
	if (!result)
	{
		return false;
	}


	SetModelinfo(wall2_model[1], D3DXVECTOR3(218.5996f + 4.0f*z - z - z, 0.0f, -275.0f + 3.0f*z + x + z + z + 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall2_model[1]);
	if (!result)
	{
		return false;
	}


	SetModelinfo(wall2_model[2], D3DXVECTOR3(22.0394f - 9.0f*z + 1.5f*z - 0.5f*x + 1.5f*z - 0.5f *x + x + z + 2.0f *z - 0.5f *x + 2.0f*z - 0.5f*x + x, 0.0f, -275.0f + 3.0f*z + x + 4.0f*z + 0.5f*x + 0.5f*z + 0.5f*x + 0.5f*z + 1.5f*z + 0.5f*x - 1.5f *z - 0.5f *x + z - 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall2_model[2]);
	if (!result)
	{
		return false;
	}


	SetModelinfo(wall2_model[3], D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 3.0f*z - 1.5f*z + 0.5f* x + x + x - 2.0f*z, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + 0.5f*z + z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall2_model[3]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall2_model[4], D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 3.0f*z - 1.5f*z + 0.5f* x + x + x - 2.0f*z - z + 0.5f*x - z - x, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + 0.5f*z + z + z + 0.5f*x), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall2_model[4]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall2_model[5], D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 3.0f*z - 1.5f*z + 0.5f* x + x + x - 2.0f*z - z + 0.5f*x - z - x, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + 0.5f*z + z + z + 0.5f*x + x + z), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall2_model[5]);
	if (!result)
	{
		return false;
	}









	SetModelinfo(wall3_model[0], D3DXVECTOR3(22.0394f, 0.0f, -275.0f + 1.5f*z - 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall3_model[0]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall3_model[1], D3DXVECTOR3(218.5996f + x, 0.0f, -275.0f + 1.5f*z - 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall3_model[1]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall3_model[2], D3DXVECTOR3(22.0394f - 9.0f*z + x + 2.5f*z - 0.5f*x + 2.5f*z - 0.5f*x, 0.0f, -275.0f + 3.0f*z + x + z + 1.5f*z + 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall3_model[2]);
	if (!result)
	{
		return false;
	}


	SetModelinfo(wall3_model[3], D3DXVECTOR3(218.5996f + 4.0f*z - z - z - 3.0f*z + 0.5f*x - 3.0f*z + 0.5f*x, 0.0f, -275.0f + 3.0f*z + x + z + z + 0.5f*x - z - 0.5f*x + 1.5f*z + 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall3_model[3]);
	if (!result)
	{
		return false;
	}


	SetModelinfo(wall3_model[4], D3DXVECTOR3(22.0394f - 9.0f*z + 1.5f*z - 0.5f*x, 0.0f, -275.0f + 3.0f*z + x + 4.0f*z + 0.5f*x + 0.5f*z + 0.5f*x + 0.5f*z), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall3_model[4]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall3_model[5], D3DXVECTOR3(22.0394f - 9.0f*z + 1.5f*z - 0.5f*x + 1.5f*z - 0.5f *x, 0.0f, -275.0f + 3.0f*z + x + 4.0f*z + 0.5f*x + 0.5f*z + 0.5f*x + 0.5f*z + 1.5f*z + 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall3_model[5]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall3_model[6], D3DXVECTOR3(22.0394f - 9.0f*z + 1.5f*z - 0.5f*x + 1.5f*z - 0.5f *x + x + z, 0.0f, -275.0f + 3.0f*z + x + 4.0f*z + 0.5f*x + 0.5f*z + 0.5f*x + 0.5f*z + 1.5f*z + 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall3_model[6]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall3_model[7], D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 0.5f*x + 3.0f*z - 0.5f*x - 1.5f*z + 0.5f* x, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + 0.5f*x + 0.5f*z), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall3_model[7]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall3_model[8], D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 3.0f*z - 1.5f*z + 0.5f* x + x + x - 2.0f*z + 1.5f*z - 0.5f*x, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + 0.5f*z + z + z + 0.5f*x), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall3_model[8]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall3_model[9], D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 3.0f*z - 1.5f*z + 0.5f* x + x + x - 2.0f*z + 1.5f*z - 0.5f*x, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + 0.5f*z + z + z + 0.5f*x + x + z), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall3_model[9]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall3_model[10], D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 3.0f*z - 1.5f*z + 0.5f* x + x + x - 2.0f*z - z + 0.5f*x - z - x + z - 0.5f*x, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + 0.5f*z + z + z + 0.5f*x + x + z + 1.5f*z + 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall3_model[10]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall3_model[11], D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 3.0f*z - 1.5f*z + 0.5f* x + x + x - 2.0f*z, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + 0.5f*z + z + z + 0.5f*x + x + z + 1.5f*z + 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall3_model[11]);
	if (!result)
	{
		return false;
	}







	SetModelinfo(wall4_model[0], D3DXVECTOR3(218.5996f + x + 2.0f*z - 0.5f*x, 0.0f, -275.0f + 1.5f*z - 0.5f*x + 1.5f*z + 0.5f*x), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall4_model[0]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall4_model[1], D3DXVECTOR3(22.0394f - 9.0f*z + 1.5f*z - 0.5f*x + 1.5f*z - 0.5f *x + x + z + 2.0f *z - 0.5f *x, 0.0f, -275.0f + 3.0f*z + x + 4.0f*z + 0.5f*x + 0.5f*z + 0.5f*x + 0.5f*z + 1.5f*z + 0.5f*x - 1.5f *z - 0.5f *x), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall4_model[1]);
	if (!result)
	{
		return false;
	}




	SetModelinfo(wall5_model[0], D3DXVECTOR3(22.0394f - 9.0f*z + x + 2.5f*z - 0.5f*x, 0.0f, -275.0f + 3.0f*z + x + z), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall5_model[0]);
	if (!result)
	{
		return false;
	}


	SetModelinfo(wall5_model[1], D3DXVECTOR3(22.0394f - 9.0f*z + x + 2.5f*z - 0.5f*x + 2.5f*z - 0.5f*x - 2.5f*z - 0.5f*x, 0.0f, -275.0f + 3.0f*z + x + z + 1.5f*z + 1.5f*z), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall5_model[1]);
	if (!result)
	{
		return false;
	}



	SetModelinfo(wall6_model[0], D3DXVECTOR3(218.5996f + 4.0f*z - z - z - 3.0f*z + 0.5f*x, 0.0f, -275.0f + 3.0f*z + x + z + z + 0.5f*x - z - 0.5f*x), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall6_model[0]);
	if (!result)
	{
		return false;
	}

	SetModelinfo(wall6_model[1], D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 0.5f*x, 0.0f, -275.0f + 6.0f*z + x + z), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall6_model[1]);
	if (!result)
	{
		return false;
	}




	SetModelinfo(wall9_model, D3DXVECTOR3(22.0394f - 4.5f*z + 0.5f*x, 0.0f, -275.0f + 1.5f*z - 0.5f*x + 1.5f*z + 0.5f*x), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(wall9_model);
	if (!result)
	{
		return false;
	}





	SetModelinfo(enterance_model, D3DXVECTOR3(140.0f, 0.0f, -275.0f + z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	dummy_left->SetForceBox(D3DXVECTOR4(enterance_model->GetLeft(), enterance_model->GetLeft() + 60.0f, enterance_model->GetTop(), enterance_model->GetBottom()));
	dummy_right->SetForceBox(D3DXVECTOR4(enterance_model->GetRight() - 60.0f, enterance_model->GetRight(), enterance_model->GetTop(), enterance_model->GetBottom()));

	result = DrawModel(enterance_model);
	if (!result)
	{
		return false;
	}

	SetModelinfo(door_model, D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 3.0f*z - 1.5f*z + 0.5f* x + x + x - 2.0f*z - z + 0.5f*x - z - x + z - 0.5f*x + 0.5f*x + 98.2801f, 0.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + 0.5f*z + z + z + 0.5f*x + x + z + 1.5f*z + 0.5f*x + 1.5f*z - 19.6850f + 39.37f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	result = DrawModel(door_model);
	if (!result)
	{
		return false;
	}



	//farwall

	SetModelinfo(farWall_model, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	result = DrawModel(farWall_model);
	if (!result)
	{
		return false;
	}


	//ceiling

	SetModelinfo(ceiling_model, D3DXVECTOR3(0.0f, 330.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.0f, 1.5f));
	result = DrawModel(ceiling_model);
	if (!result)
	{
		return false;
	}



	//render plane

	SetModelinfo(plane_model, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.0f, 1.5f));
	result = DrawModel(plane_model);
	if (!result)
	{
		return false;
	}
	//change fill mode
	result = m_D3D->ChangeFillMode(m_fill_mode);

	if (!result)
	{
		return false;
	}

	//change filter
	result = m_LightShader->ChangeFilter(m_D3D->GetDevice(), m_filter, m_MaxAnisotropy);

	if (!result)
	{
		return false;
	}

	//È½ºÒ1
	SetModelinfo(torch_model, D3DXVECTOR3(22.0394f - 9.0f*z + x + 2.5f*z - 0.5f*x, 45.0f, -275.0f + 3.0f * z + z + 0.5f * x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	result = DrawModel(torch_model);
	if (!result)
	{
		return false;
	}

	result = RenderFire(torch_model);
	if (!result)
	{
		return false;
	}



	//È½ºÒ2
	SetModelinfo(torch_model, D3DXVECTOR3(218.5996f + x - 0.5f* x, 45.0f, -275.0f + 1.5f*z - 0.5f*x + 1.5f*z + 0.5f*x), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	result = DrawModel(torch_model);
	if (!result)
	{
		return false;
	}

	result = RenderFire(torch_model);
	if (!result)
	{
		return false;
	}





	//È½ºÒ3
	SetModelinfo(torch_model, D3DXVECTOR3(22.0394f + 0.5f * x, 45.0f, -275.0f + 1.5f*z - 0.5f*x + 1.5f*z + 0.5f*x), D3DXVECTOR3(-90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	result = DrawModel(torch_model);
	if (!result)
	{
		return false;
	}

	result = RenderFire(torch_model);
	if (!result)
	{
		return false;
	}


	//È½ºÒ4
	SetModelinfo(torch_model, D3DXVECTOR3(218.5996f + x + 2.0f*z - 0.5f*x, 45.0f, -275.0f + 1.5f*z - 0.5f*x + 1.5f*z + x), D3DXVECTOR3(-180.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	result = DrawModel(torch_model);
	if (!result)
	{
		return false;
	}

	result = RenderFire(torch_model);
	if (!result)
	{
		return false;
	}


	//È½ºÒ5
	SetModelinfo(torch_model, D3DXVECTOR3(22.0394f - 9.0f*z + x + 2.5f*z - 0.5f*x + 2.5f*z - 0.5f*x + 0.5f*x, 45.0f, -275.0f + 3.0f*z + x + z + 1.5f*z + 0.5f*x), D3DXVECTOR3(-90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	result = DrawModel(torch_model);
	if (!result)
	{
		return false;
	}

	result = RenderFire(torch_model);
	if (!result)
	{
		return false;
	}


	//È½ºÒ6
	SetModelinfo(torch_model, D3DXVECTOR3(22.0394f - 9.0f*z + x + 2.5f*z - 0.5f*x + 2.5f*z - 0.5f*x + 0.5f*x + z, 45.0f, -275.0f + 3.0f*z + x + z + 1.5f*z + 0.5f*x), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	result = DrawModel(torch_model);
	if (!result)
	{
		return false;
	}

	result = RenderFire(torch_model);
	if (!result)
	{
		return false;
	}


	//È½ºÒ7
	SetModelinfo(torch_model, D3DXVECTOR3(22.0394f - 9.0f*z + x + 2.5f*z - 0.5f*x, 45.0f, -275.0f + 3.0f * z + z + 0.5f * x - z), D3DXVECTOR3(180.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	result = DrawModel(torch_model);
	if (!result)
	{
		return false;
	}

	result = RenderFire(torch_model);
	if (!result)
	{
		return false;
	}



	//È½ºÒ8
	SetModelinfo(torch_model, D3DXVECTOR3(22.0394f - 9.0f*z + x + 2.5f*z - 0.5f*x + 2.5f*z - 0.5f*x - 2.5f*z - 0.5f*x - x, 45.0f, -275.0f + 3.0f*z + x + z + 1.5f*z + 1.5f*z + 0.5f*x), D3DXVECTOR3(180.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	result = DrawModel(torch_model);
	if (!result)
	{
		return false;
	}

	result = RenderFire(torch_model);
	if (!result)
	{
		return false;
	}



	//È½ºÒ9
	SetModelinfo(torch_model, D3DXVECTOR3(22.0394f - 9.0f*z + x + 2.5f*z - 0.5f*x + 2.5f*z - 0.5f*x - 2.5f*z - 0.5f*x - x, 45.0f, -275.0f + 3.0f*z + x + z + 1.5f*z + 1.5f*z + 0.5f*x + z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	result = DrawModel(torch_model);
	if (!result)
	{
		return false;
	}

	result = RenderFire(torch_model);
	if (!result)
	{
		return false;
	}


	//È½ºÒ10
	SetModelinfo(torch_model, D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 0.5f*x + 3.0f*z - 0.5f*x - 1.5f*z + 0.5f* x, 45.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + 0.5f*x + 0.5f*z - 0.5f *x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	result = DrawModel(torch_model);
	if (!result)
	{
		return false;
	}

	result = RenderFire(torch_model);
	if (!result)
	{
		return false;
	}


	//È½ºÒ11
	SetModelinfo(torch_model, D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 0.5f*x + 3.0f*z - 0.5f*x - 1.5f*z + 0.5f* x, 45.0f, -275.0f + 6.0f*z + x + z + 0.5f*z + 0.5f*x + 0.5f*x + 0.5f*z - 0.5f *x - z), D3DXVECTOR3(180.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	result = DrawModel(torch_model);
	if (!result)
	{
		return false;
	}

	result = RenderFire(torch_model);
	if (!result)
	{
		return false;
	}



	//È½ºÒ12
	SetModelinfo(torch_model, D3DXVECTOR3(22.0394f - 9.0f*z + 1.5f*z - 0.5f*x + 1.5f*z - 0.5f *x + x + z + 2.0f *z - 0.5f *x + 2.0f*z - 0.5f*x + x + 0.5f*x, 45.0f, -275.0f + 3.0f*z + x + 4.0f*z + 0.5f*x + 0.5f*z + 0.5f*x + 0.5f*z + 1.5f*z + 0.5f*x - 1.5f *z - 0.5f *x + z - 0.5f*x), D3DXVECTOR3(-90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	result = DrawModel(torch_model);
	if (!result)
	{
		return false;
	}

	result = RenderFire(torch_model);
	if (!result)
	{
		return false;
	}


	//È½ºÒ13
	SetModelinfo(torch_model, D3DXVECTOR3(22.0394f - 9.0f*z + 1.5f*z - 0.5f*x + 1.5f*z - 0.5f *x + x + z + 2.0f *z - 0.5f *x + 2.0f*z - 0.5f*x + x + 0.5f*x + z, 45.0f, -275.0f + 3.0f*z + x + 4.0f*z + 0.5f*x + 0.5f*z + 0.5f*x + 0.5f*z + 1.5f*z + 0.5f*x - 1.5f *z - 0.5f *x + z - 0.5f*x), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	result = DrawModel(torch_model);
	if (!result)
	{
		return false;
	}

	result = RenderFire(torch_model);
	if (!result)
	{
		return false;
	}

	//¸ó½ºÅÍ 1
	if (monster_1_exist)
	{	
		monster_model->SetMeshSize(50.0f);
		SetModelinfo(monster_model, D3DXVECTOR3(218.5996f + 4.0f*z - 0.5f*z + 0.5f*x - 2.0f*z + 0.5f*x - 0.5f*x, 0.0f, -275.0f + 3.0f*z + 0.5f*x + 0.5f*z), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
		result = RenderMonster(monster_model, 1);
		if (!result)
		{
			return false;
		}

		if (ModelCollisionCheck(monster_model) && !squat && !possess_knife)
		{
			player_die = true;
		}
		if (ModelCollisionCheck(monster_model)  && knife_swing)
		{
			monster_1_exist = false;
		}
		monster_model->SetMeshSize(20.0f);
		SetModelinfo(monster_model, D3DXVECTOR3(218.5996f + 4.0f*z - 0.5f*z + 0.5f*x - 2.0f*z + 0.5f*x - 0.5f*x, 0.0f, -275.0f + 3.0f*z + 0.5f*x + 0.5f*z), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
		if (ModelCollisionCheck(monster_model) && possess_knife && !knife_swing || ModelCollisionCheck(monster_model) && squat)
		{
			player_die = true;
		}
	}

	//¸ó½ºÅÍ 2
	if (monster_2_exist)
	{
		monster_model->SetMeshSize(50.0f);
		SetModelinfo(monster_model, D3DXVECTOR3(22.0394f - 9.0f*z + 4.5f*z + 2.5f*x, 0.0f, -275.0f + 3.0f*z + 0.5f*x + 0.5f*z), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
		result = RenderMonster(monster_model, 2);
		if (!result)
		{
			return false;
		}

		if (ModelCollisionCheck(monster_model) && !squat && !possess_knife)
		{
			player_die = true;
		}
		if (ModelCollisionCheck(monster_model) && knife_swing)
		{
			monster_2_exist = false;
		}
		monster_model->SetMeshSize(20.0f);
		SetModelinfo(monster_model, D3DXVECTOR3(22.0394f - 9.0f*z + 4.5f*z + 2.5f*x, 0.0f, -275.0f + 3.0f*z + 0.5f*x + 0.5f*z), D3DXVECTOR3(90.0f * 0.0174532925f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
		if (ModelCollisionCheck(monster_model) && possess_knife && !knife_swing || ModelCollisionCheck(monster_model) && squat)
		{
			player_die = true;
		}
	}

	//¸ó½ºÅÍ 3
	if (monster_3_exist)
	{
		monster_model->SetMeshSize(50.0f);
		SetModelinfo(monster_model, D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 3.0f*z - 1.5f*z + 0.5f* x + x + x - 2.0f*z - z + 0.5f*x - z - x + z - 0.5f*x + 0.5f*x + 98.2801f, 0.0f, -275.0f + 3.0f*z + x + 4.0f*z + 0.5f*x + 0.5f*z + 0.5f*x + 0.5f*z + 1.5f*z + 0.5f*x - 1.5f *z - 0.5f *x + z - 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
		result = RenderMonster(monster_model, 3);
		if (!result)
		{
			return false;
		}

		if (ModelCollisionCheck(monster_model) && !squat && !possess_knife)
		{
			player_die = true;
		}
		if (ModelCollisionCheck(monster_model) && knife_swing)
		{
			monster_3_exist = false;
		}
		monster_model->SetMeshSize(20.0f);
		SetModelinfo(monster_model, D3DXVECTOR3(218.5996f - 4.0f*z + x + 3.0f*z + 3.0f*z - 1.5f*z + 0.5f* x + x + x - 2.0f*z - z + 0.5f*x - z - x + z - 0.5f*x + 0.5f*x + 98.2801f, 0.0f, -275.0f + 3.0f*z + x + 4.0f*z + 0.5f*x + 0.5f*z + 0.5f*x + 0.5f*z + 1.5f*z + 0.5f*x - 1.5f *z - 0.5f *x + z - 0.5f*x), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
		if (ModelCollisionCheck(monster_model) && possess_knife && !knife_swing || ModelCollisionCheck(monster_model) && squat)
		{
			player_die = true;
		}
	}



	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();


	if (possess_knife)
	{
		SetModelinfo(knife_model, D3DXVECTOR3(33.0f, -25.0f, 10.0f), D3DXVECTOR3(180.0f * 0.0174532925f, -20.0f * 0.0174532925f, 250.0f * 0.0174532925f), D3DXVECTOR3(0.8f, 0.8f, 0.8f));
		result = DrawPlayerWapon(knife_model);
		if (!result)
		{
			return false;
		}

	}



	//// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//result = m_Bitmap->Render(m_D3D->GetDeviceContext(), camera_pos->x, camera_pos->y);
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the bitmap with the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(),
	//	worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	result = m_MiniMap->Render(m_D3D->GetDeviceContext(), m_TextureShader, worldMatrix, baseViewMatrix, orthoMatrix);
	// ¹Ì´Ï ¸ÊÀ» ·»´õ¸µÇÕ´Ï´Ù.
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();





	// Present the rendered scene to the screen.
	m_D3D->EndScene();
	return true;
}

void GraphicsClass::ChangeBackground(char c)
{
	if(c == 'r')
		m_D3D->BeginScene(1.0f, 0.0f, 0.0f, 1.0f);
	if(c == 'g')
		m_D3D->BeginScene(0.0f, 1.0f, 0.0f, 1.0f);
	if(c == 'b')
		m_D3D->BeginScene(0.0f, 0.0f, 1.0f, 1.0f);

	return;
}

void GraphicsClass::LightSetting(bool a, bool d, bool s)
{
	if (a)
		m_Light->SetAmbientColor(0.13f, 0.13f, 0.13f, 1.0f);
	else
		m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 0.0f);
	if (d)
		m_Light->SetDiffuseColor(0.8f, 1.0f, 1.0f, 1.0f);
	else
		m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 0.0f);
	

	m_Light->SetDirection(0.3f, -0.7f, 0.3f);

	if (s)
	{
		m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light->SetSpecularPower(32.0f);
	}
	else
	{
		m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light->SetSpecularPower(-1.0f);
		//ÇÈ¼¿ ½¦ÀÌ´õ¿¡¼­ Á¶°Ç¹® °É¾î¼­ -1ÀÌ µÈ °æ¿ì ²¨Áö°Ô µÊ
	}	
}

void GraphicsClass::CameraMove(float x, float y, float z)
{
	camera_move->x = z * sin(camera_rotateY*0.0174532925f) + x * cos(camera_rotateY*0.0174532925f);
	camera_move->z = z * cos(camera_rotateY*0.0174532925f) - x * sin(camera_rotateY*0.0174532925f);
	
	camera_pos->x += camera_move->x;
	camera_pos->z += camera_move->z;

	return;
}

bool GraphicsClass::CollisionCheck()
{	
	for (int i = 0; i < 12; i++)
	{
		if (ModelCollisionCheck(wall1_model[i]))
		{
			MoveCancel(wall1_model[i]);
			return true;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (ModelCollisionCheck(wall2_model[i]))
		{
			MoveCancel(wall2_model[i]);
			return true;
		}
	}

	for (int i = 0; i < 12; i++)
	{
		if (ModelCollisionCheck(wall3_model[i]))
		{
			MoveCancel(wall3_model[i]);
			return true;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (ModelCollisionCheck(wall4_model[i]))
		{
			MoveCancel(wall4_model[i]);
			return true;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (ModelCollisionCheck(wall5_model[i]))
		{
			MoveCancel(wall5_model[i]);
			return true;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (ModelCollisionCheck(wall6_model[i]))
		{
			MoveCancel(wall6_model[i]);
			return true;
		}
	}
	
	if (ModelCollisionCheck(wall9_model))
	{
		MoveCancel(wall9_model);
		return true;
	}

	if (ModelCollisionCheck(dummy_left))
	{
		MoveCancel(dummy_left);
		return true;
	}

	if (ModelCollisionCheck(dummy_right))
	{
		MoveCancel(dummy_right);
		return true;
	}

	if (!is_door_opened)
	{
		if (ModelCollisionCheck(door_model))
		{
			if (possess_key > 0 && !time_over)
			{
				is_door_opened = true;
				possess_key -= 1;
			}
			MoveCancel(door_model);
			return true;
		}
	}

	return false;
}

bool GraphicsClass::ModelCollisionCheck(ModelClass* model)
{
	if (model->GetLeft() < camera_pos->x && model->GetRight() > camera_pos->x && model->GetTop() > camera_pos->z && model->GetBottom() < camera_pos->z)
		return true;

	return false;
}

void GraphicsClass::MoveCancel(ModelClass* model)
{
	D3DXVECTOR3 n;
	float num, den, theta;

	camera_pos->x -= camera_move->x;
	camera_pos->z -= camera_move->z;

	if (model->GetBottom() > camera_pos->z && camera_pos->x > model->GetLeft() && camera_pos->x < model->GetRight())
	{
		n = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		num = n.x*-camera_move->x + n.z*-camera_move->z;
		den = (sqrt(pow(n.x, 2) + pow(n.z, 2))*sqrt(pow(-camera_move->x, 2) + pow(-camera_move->z, 2)));
		theta = acos((num / den));

		if (camera_move->z > 0.0f&&camera_move->x < 0.0f)
		{
			n.x = camera_move->z * sin(180.0f * 0.0174532925f + 2 * theta) + camera_move->x * cos(180.0f * 0.0174532925f + 2 * theta);
			n.z = camera_move->z * cos(180.0f * 0.0174532925f + 2 * theta) - camera_move->x * sin(180.0f * 0.0174532925f + 2 * theta);
			camera_move->x += n.x;
			camera_move->z += n.z;

			camera_pos->x += camera_move->x / 2;
			camera_pos->z += camera_move->z / 2;
		}

		else if (camera_move->z > 0.0f&&camera_move->x > 0.0f)
		{
			n.x = camera_move->z * sin(180.0f * 0.0174532925f - 2 * theta) + camera_move->x * cos(180.0f * 0.0174532925f - 2 * theta);
			n.z = camera_move->z * cos(180.0f * 0.0174532925f - 2 * theta) - camera_move->x * sin(180.0f * 0.0174532925f - 2 * theta);
			camera_move->x += n.x;
			camera_move->z += n.z;

			camera_pos->x += camera_move->x / 2;
			camera_pos->z += camera_move->z / 2;
		}
	}
	
	if (model->GetTop() < camera_pos->z && camera_pos->x > model->GetLeft() && camera_pos->x < model->GetRight())
	{
		n = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		num = n.x*-camera_move->x + n.z*-camera_move->z;
		den = (sqrt(pow(n.x, 2) + pow(n.z, 2))*sqrt(pow(-camera_move->x, 2) + pow(-camera_move->z, 2)));
		theta = acos((num / den));

		if (camera_move->z < 0.0f && camera_move->x < 0.0f)
		{
			n.x = camera_move->z * sin(180.0f * 0.0174532925f - 2 * theta) + camera_move->x * cos(180.0f * 0.0174532925f - 2 * theta);
			n.z = camera_move->z * cos(180.0f * 0.0174532925f - 2 * theta) - camera_move->x * sin(180.0f * 0.0174532925f - 2 * theta);
			camera_move->x += n.x;
			camera_move->z += n.z;

			camera_pos->x += camera_move->x / 2;
			camera_pos->z += camera_move->z / 2;
		}

		else if (camera_move->z < 0.0f&&camera_move->x > 0.0f)
		{
			n.x = camera_move->z * sin(180.0f * 0.0174532925f + 2 * theta) + camera_move->x * cos(180.0f * 0.0174532925f + 2 * theta);
			n.z = camera_move->z * cos(180.0f * 0.0174532925f + 2 * theta) - camera_move->x * sin(180.0f * 0.0174532925f + 2 * theta);
			camera_move->x += n.x;
			camera_move->z += n.z;

			camera_pos->x += camera_move->x / 2;
			camera_pos->z += camera_move->z / 2;
		}
	}

	if (model->GetLeft() > camera_pos->x && camera_pos->z < model->GetTop() && camera_pos->z > model->GetBottom())
	{
		n = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);

		num = n.x*-camera_move->x + n.z*-camera_move->z;
		den = (sqrt(pow(n.x, 2) + pow(n.z, 2))*sqrt(pow(-camera_move->x, 2) + pow(-camera_move->z, 2)));
		theta = acos((num / den));

		if (camera_move->z > 0.0f && camera_move->x > 0.0f)
		{
			n.x = camera_move->z * sin(180.0f * 0.0174532925f + 2 * theta) + camera_move->x * cos(180.0f * 0.0174532925f + 2 * theta);
			n.z = camera_move->z * cos(180.0f * 0.0174532925f + 2 * theta) - camera_move->x * sin(180.0f * 0.0174532925f + 2 * theta);
			camera_move->x += n.x;
			camera_move->z += n.z;

			camera_pos->x += camera_move->x / 2;
			camera_pos->z += camera_move->z / 2;
		}

		else if (camera_move->z < 0.0f && camera_move->x > 0.0f)
		{
			n.x = camera_move->z * sin(180.0f * 0.0174532925f - 2 * theta) + camera_move->x * cos(180.0f * 0.0174532925f - 2 * theta);
			n.z = camera_move->z * cos(180.0f * 0.0174532925f - 2 * theta) - camera_move->x * sin(180.0f * 0.0174532925f - 2 * theta);
			camera_move->x += n.x;
			camera_move->z += n.z;

			camera_pos->x += camera_move->x / 2;
			camera_pos->z += camera_move->z / 2;
		}
	}

	if (model->GetRight() < camera_pos->x && camera_pos->z < model->GetTop() && camera_pos->z > model->GetBottom())
	{
		n = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

		num = n.x*-camera_move->x + n.z*-camera_move->z;
		den = (sqrt(pow(n.x, 2) + pow(n.z, 2))*sqrt(pow(-camera_move->x, 2) + pow(-camera_move->z, 2)));
		theta = acos((num / den));

		if (camera_move->z > 0.0f && camera_move->x < 0.0f)
		{
			n.x = camera_move->z * sin(180.0f * 0.0174532925f - 2 * theta) + camera_move->x * cos(180.0f * 0.0174532925f - 2 * theta);
			n.z = camera_move->z * cos(180.0f * 0.0174532925f - 2 * theta) - camera_move->x * sin(180.0f * 0.0174532925f - 2 * theta);
			camera_move->x += n.x;
			camera_move->z += n.z;

			camera_pos->x += camera_move->x / 2;
			camera_pos->z += camera_move->z / 2;
		}

		else if (camera_move->z < 0.0f && camera_move->x < 0.0f)
		{
			n.x = camera_move->z * sin(180.0f * 0.0174532925f + 2 * theta) + camera_move->x * cos(180.0f * 0.0174532925f + 2 * theta);
			n.z = camera_move->z * cos(180.0f * 0.0174532925f + 2 * theta) - camera_move->x * sin(180.0f * 0.0174532925f + 2 * theta);
			camera_move->x += n.x;
			camera_move->z += n.z;

			camera_pos->x += camera_move->x / 2;
			camera_pos->z += camera_move->z / 2;
		}
	}
	
	return;
}

void GraphicsClass::SetModelinfo(ModelClass* model, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scal)
{
	model->SetRotate(rot);
	model->SetSacle(scal);
	model->SetPos(pos);

	model->SetBox(pos, rot, scal);

	return;
}

bool GraphicsClass::DrawModel(ModelClass* model)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix, rotationMatrix, scalingMatrix;
	bool result;

	
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	D3DXMatrixScaling(&scalingMatrix, model->GetSacle().x, model->GetSacle().y, model->GetSacle().z);
	worldMatrix *= scalingMatrix;

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, model->GetRotate().x, model->GetRotate().y, model->GetRotate().z);
	worldMatrix *= rotationMatrix;

	D3DXMatrixTranslation(&translateMatrix, model->GetPos().x, model->GetPos().y, model->GetPos().z);
	worldMatrix *= translateMatrix;

	model->Render(m_D3D->GetDeviceContext());

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(),
		m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}


	return true;
}

bool GraphicsClass::DrawPlayerWapon(ModelClass* model)
{
	D3DXMATRIX worldMatrix, BaseViewMatrix, projectionMatrix, translateMatrix, rotationMatrix, scalingMatrix;
	bool result;

	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetBaseViewMatrix(BaseViewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	if (knife_swing)
	{
		knifeframe += 5.0f;

		if (knifeframe > 150.0f && !knife_swinged)
		{
			knifeframe -= 300.0f;
			knife_swinged = true;
		}

		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, model->GetRotate().x, model->GetRotate().y - abs(knifeframe) * 0.0174532925f, model->GetRotate().z);
		worldMatrix *= rotationMatrix;

		if (knifeframe > 0.0f && knife_swinged)
		{
			knifeframe = 0.0f;
			knife_swing = false;
			knife_swinged = false;
		}
	}

	else
	{
		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, model->GetRotate().x, model->GetRotate().y, model->GetRotate().z);
		worldMatrix *= rotationMatrix;
	}

	D3DXMatrixScaling(&scalingMatrix, model->GetSacle().x, model->GetSacle().y, model->GetSacle().z);
	worldMatrix *= scalingMatrix;

	D3DXMatrixTranslation(&translateMatrix, model->GetPos().x, model->GetPos().y, model->GetPos().z);
	worldMatrix *= translateMatrix;

	model->Render(m_D3D->GetDeviceContext());

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(),
		worldMatrix, BaseViewMatrix, projectionMatrix, model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(),
		m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}


	return true;
}

void GraphicsClass::GameReset()
{
	squatC = false;
	jumpframe = -2.0f;
	squat = false;
	jump = false;
	backgroundColor = NULL;
	camera_pos = new D3DXVECTOR3(140.0f, 40.0f, -275.0f + x);
	camera_rotateX = 0.0f;
	camera_rotateY = 0.0f;
	possess_key = 0;
	is_door_opened = false;
	key_exist = true;
	key_vertical = 0.0f;
	rotation = 0.0f;
	clear_game = false;
	time_over = false;
	knife_exist = true;
	possess_knife = false;
	monster_1_exist = true;
	monster_2_exist = true;
	monster_3_exist = true;
	player_die = false;
	knife_swing = false;
	knife_swinged = false;
	knifeframe = 0.0f;
}

bool GraphicsClass::RenderFire(ModelClass* model)
{
	bool result;
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, translationMatrix, scaleMatrix;
	D3DXVECTOR3 scrollSpeeds, scales;
	D3DXVECTOR2 distortion1, distortion2, distortion3;
	float x;
	float z;
	float distortionScale, distortionBias;
	float modelPositionX, modelPositionZ;

	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);


	

	// Set the three scrolling speeds for the three different noise textures.
	scrollSpeeds = D3DXVECTOR3(1.3f, 2.1f, 2.3f);

	// Set the three scales which will be used to create the three different noise octave textures.
	scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);

	// Set the three different x and y distortion factors for the three different noise textures.
	distortion1 = D3DXVECTOR2(0.1f, 0.2f);
	distortion2 = D3DXVECTOR2(0.1f, 0.3f);
	distortion3 = D3DXVECTOR2(0.1f, 0.1f);

	// The the scale and bias of the texture coordinate sampling perturbation.
	distortionScale = 0.8f;
	distortionBias = 0.5f;


	// Turn on alpha blending for the fire transparency.
	m_D3D->TurnOnAlphaBlending();

	// Put the square model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	fire_model->Render(m_D3D->GetDeviceContext());

	x = -8.0f * sin(model->GetRotate().x) * model->GetSacle().x;
	z = -8.0f * cos(model->GetRotate().x) * model->GetSacle().z;
	
	modelPositionX = model->GetPos().x + x;
	modelPositionZ = model->GetPos().z + z;
	D3DXMatrixScaling(&scaleMatrix, 5.0f * model->GetSacle().x, 5.0f * model->GetSacle().y, 5.0f * model->GetSacle().z);
	D3DXMatrixRotationY(&worldMatrix, atan2(modelPositionX - camera_pos->x, modelPositionZ - camera_pos->z) * (180.0 / D3DX_PI) * 0.0174532925f);
	D3DXMatrixTranslation(&translationMatrix, modelPositionX, model->GetPos().y + 25.0f * model->GetSacle().y, modelPositionZ);

	worldMatrix *= scaleMatrix;
	worldMatrix *= translationMatrix;

	// Render the square model using the fire shader.
	result = m_FireShader->Render(m_D3D->GetDeviceContext(), fire_model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		fire_model->GetTexture1(), fire_model->GetTexture2(), fire_model->GetTexture3(), fireframe, scrollSpeeds,
		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending.
	m_D3D->TurnOffAlphaBlending();

	return true;
}

bool GraphicsClass::RenderMonster(ModelClass* model, int i)
{
	bool result;
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix, rotationMatrix, scalingMatrix;

	m_Light->SetSpecularPower(-1.0f);

	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	D3DXMatrixScaling(&scalingMatrix, model->GetSacle().x, model->GetSacle().y, model->GetSacle().z);
	worldMatrix *= scalingMatrix;

	if (i == 1)
	{
		if (!squat && model->GetPos().x > camera_pos->x)
		{
			prev_Y1 = atan2(model->GetPos().x - camera_pos->x, model->GetPos().z - camera_pos->z) * (180.0 / D3DX_PI) * 0.0174532925f;
		}

		D3DXMatrixRotationY(&rotationMatrix, prev_Y1);
		worldMatrix *= rotationMatrix;
	}

	if (i == 2)
	{
		if (!squat && model->GetPos().x < camera_pos->x)
		{
			prev_Y2 = atan2(model->GetPos().x - camera_pos->x, model->GetPos().z - camera_pos->z) * (180.0 / D3DX_PI) * 0.0174532925f;
		}

		D3DXMatrixRotationY(&rotationMatrix, prev_Y2);
		worldMatrix *= rotationMatrix;
	}

	if (i == 3)
	{
		if (!squat && model->GetPos().z > camera_pos->z)
		{
			prev_Y3 = atan2(model->GetPos().x - camera_pos->x, model->GetPos().z - camera_pos->z) * (180.0 / D3DX_PI) * 0.0174532925f;
		}

		D3DXMatrixRotationY(&rotationMatrix, prev_Y3);
		worldMatrix *= rotationMatrix;
	}

	D3DXMatrixTranslation(&translateMatrix, model->GetPos().x, model->GetPos().y, model->GetPos().z);
	worldMatrix *= translateMatrix;

	model->Render(m_D3D->GetDeviceContext());

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(),
		m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_Light->SetSpecularPower(32.0f);

	return true;
}