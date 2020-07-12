#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_
#include <d3d11.h>
#include <d3dx10math.h>
#include "textureclass.h"
#include <fstream>
using namespace std;

class ModelClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};
	struct FaceType
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	};
public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*, int*);
	bool FireInitialize(ID3D11Device*, char*, WCHAR*, WCHAR*, WCHAR*);
	ID3D11ShaderResourceView* GetTexture();
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	int GetIndexCount();
	bool LoadModel(char*);
	void ReleaseModel();
	bool LoadOBJ(char*);
	void SetPos(D3DXVECTOR3);
	void SetRotate(D3DXVECTOR3);
	void SetSacle(D3DXVECTOR3);
	void SetForceBox(D3DXVECTOR4);
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetRotate();
	D3DXVECTOR3 GetSacle();
	void SetBox(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();
	void SetMeshSize(float);
	float GetMeshSize();

	ID3D11ShaderResourceView* GetTexture1();
	ID3D11ShaderResourceView* GetTexture2();
	ID3D11ShaderResourceView* GetTexture3();
private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	bool LoadTexture(ID3D11Device*, WCHAR*);
	bool LoadFireTextures(ID3D11Device*, WCHAR*, WCHAR*, WCHAR*);
	void ReleaseTexture();
	void InitBox(D3DXVECTOR3);
	void ReSizeBox(D3DXVECTOR3);
private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	TextureClass *m_Texture1, *m_Texture2, *m_Texture3;

	ModelType* m_model;
	
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rotate;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR4 m_mesh;
	float left;
	float right;
	float top;
	float bottom;
	
	int m_polygons;

	float mesh_size;
};
#endif