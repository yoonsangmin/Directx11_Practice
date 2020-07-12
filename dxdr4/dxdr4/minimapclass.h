#ifndef _MINIMAPCLASS_H_
#define _MINIMAPCLASS_H_
#include "BitmapClass.h"
#include "textureshaderclass.h"

class MiniMapClass
{
public:
	MiniMapClass();
	MiniMapClass(const MiniMapClass&);
	~MiniMapClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, int, int, float, float);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, TextureShaderClass*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);

	void PositionUpdate(float, float);

private:
	int m_mapLocationX;
	int m_mapLocationY;
	int m_pointLocationX;
	int m_pointLocationY;
	float m_mapSizeX;
	float m_mapSizeY;
	float m_terrainWidth;
	float m_terrainHeight;
	BitmapClass* m_MiniMapBitmap;
	BitmapClass* m_PointBitmap;
};
#endif