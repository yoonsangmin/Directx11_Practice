#include "minimapclass.h"


MiniMapClass::MiniMapClass()
{
	m_mapLocationX = 0;
	m_mapLocationY = 0;
	m_pointLocationX = 0;
	m_pointLocationY = 0;
	m_mapSizeX = 0.0f;
	m_mapSizeY = 0.0f;
	m_terrainWidth = 0.0f;
	m_terrainHeight = 0.0f;
	m_MiniMapBitmap = 0;
	m_PointBitmap = 0;
}


MiniMapClass::MiniMapClass(const MiniMapClass& other)
{
}


MiniMapClass::~MiniMapClass()
{
}


bool MiniMapClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int screenWidth, int screenHeight,
	float terrainWidth, float terrainHeight)
{
	// 미니 맵의 크기에서 테두리를 뺀 값을 설정합니다.
	m_mapSizeX = 150.0f;
	m_mapSizeY = 150.0f;

	// 화면에서 미니 맵의 위치를 ​​초기화합니다.
	m_mapLocationX = screenWidth - (int)m_mapSizeX - 30;
	m_mapLocationY = screenHeight - (int)m_mapSizeY - 60;

	// 지형 크기를 저장합니다.
	m_terrainWidth = terrainWidth;
	m_terrainHeight = terrainHeight;

	// 미니 맵 비트 맵 객체를 생성합니다..
	m_MiniMapBitmap = new BitmapClass;
	if (!m_MiniMapBitmap)
	{
		return false;
	}

	// 미니 맵 비트 맵 객체를 초기화합니다.
	if (!m_MiniMapBitmap->Initialize(device, screenWidth, screenHeight, (WCHAR*)L"../dxdr4/data/minimap/minimap.dds", 154, 154))
	{
		return false;
	}

	// 포인트 비트 맵 객체를 생성합니다..
	m_PointBitmap = new BitmapClass;
	if (!m_PointBitmap)
	{
		return false;
	}

	// 포인트 비트 맵 객체를 초기화합니다.
	if (!m_PointBitmap->Initialize(device, screenWidth, screenHeight, (WCHAR*)L"../dxdr4/data/minimap/point.dds", 3, 3))
	{
		return false;
	}

	return true;
}


void MiniMapClass::Shutdown()
{
	// 포인트 비트 맵 객체를 해제합니다.
	if (m_PointBitmap)
	{
		m_PointBitmap->Shutdown();
		delete m_PointBitmap;
		m_PointBitmap = 0;
	}

	// 미니 맵 비트 맵 객체를 해제합니다.
	if (m_MiniMapBitmap)
	{
		m_MiniMapBitmap->Shutdown();
		delete m_MiniMapBitmap;
		m_MiniMapBitmap = 0;
	}
}


bool MiniMapClass::Render(ID3D11DeviceContext* deviceContext, TextureShaderClass* TextureShader, D3DXMATRIX worldMatrix,
	D3DXMATRIX viewMatrix, D3DXMATRIX orthoMatrix)
{
	// 미니 맵 비트 맵 버텍스와 인덱스 버퍼를 그래픽 파이프 라인에 배치하여 그리기를 준비합니다.
	bool result = m_MiniMapBitmap->Render(deviceContext, m_mapLocationX, m_mapLocationY);
	if (!result)
	{
		return false;
	}

	// 텍스처 셰이더를 사용하여 미니 맵 비트 맵을 렌더링합니다.
	/*result = ShaderManager->RenderTextureShader(deviceContext, m_MiniMapBitmap->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, m_MiniMapBitmap->GetTexture());*/
	result = TextureShader->Render(deviceContext, m_MiniMapBitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_MiniMapBitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	// 포인트 비트 맵 버텍스와 인덱스 버퍼를 그래픽 파이프 라인에 배치하여 그리기를 준비합니다.
	result = m_PointBitmap->Render(deviceContext, m_pointLocationX, m_pointLocationY);
	if (!result)
	{
		return false;
	}

	// 텍스처 셰이더를 사용하여 포인트 비트 맵을 렌더링합니다.
	/*result = ShaderManager->RenderTextureShader(deviceContext, m_PointBitmap->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, m_PointBitmap->GetTexture());*/
	TextureShader->Render(deviceContext, m_PointBitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_PointBitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	return true;
}


void MiniMapClass::PositionUpdate(float positionX, float positionZ)
{
	// 카메라가 지형 경계선을 지난 경우에도 포인트가 미니 맵 경계를 벗어나지 않도록합니다.
	if (positionX < 0)
	{
		positionX = 0;
	}

	if (positionZ < 0)
	{
		positionZ = 0;
	}

	if (positionX > m_terrainWidth)
	{
		positionX = m_terrainWidth;
	}

	if (positionZ > m_terrainHeight)
	{
		positionZ = m_terrainHeight;
	}

	// 미니 맵에서 카메라의 위치를 ​​백분율로 계산합니다.
	float percentX = positionX / m_terrainWidth;
	float percentY = 1.0f - (positionZ / m_terrainHeight);

	// 미니 맵에서 포인트의 픽셀 위치를 결정합니다.
	m_pointLocationX = (m_mapLocationX + 2) + (int)(percentX * m_mapSizeX);
	m_pointLocationY = (m_mapLocationY + 2) + (int)(percentY * m_mapSizeY);

	// 3x3 포인트 픽셀 이미지 크기에 따라 미니 맵에서 포인트의 중심에 위치에서 1을 뺍니다.
	m_pointLocationX = m_pointLocationX - 1;
	m_pointLocationY = m_pointLocationY - 1;
}