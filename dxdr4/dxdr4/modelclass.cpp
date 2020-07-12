#include "modelclass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_Texture1 = 0;
	m_Texture2 = 0;
	m_Texture3 = 0;
	m_model = 0;
	left = 0;
	right = 0;
	top = 0;
	bottom = 0;
	mesh_size = 2.0f;
}
ModelClass::ModelClass(const ModelClass& other)
{
}
ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename, int* polycount)
{
	bool result;

	result = LoadOBJ(modelFilename);
	if (!result)
	{
		return false;
	}

	* polycount += m_polygons;

	result = LoadTexture(device, textureFilename);
	if (!result)
	{
		return false;
	}

	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}
	// Load the texture for this model.
	

	// Load in the model data,
	
	return true;
}

bool ModelClass::FireInitialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2,
	WCHAR* textureFilename3)
{
	bool result;


	// Load in the model data,
	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	// Load the textures for this model.
	result = LoadFireTextures(device, textureFilename1, textureFilename2, textureFilename3);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::Shutdown()
{

	ReleaseTexture();

	// Release the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);
	return;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}
	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	int i;


	// Load the vertex array and index array with data.
	for (i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);
		indices[i] = i;
	}


	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}
	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;
	return true;
}

bool ModelClass::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;
	// Open the model file.
	
	fin.open(filename);
	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	// Read in the vertex count.
	fin >> m_vertexCount;
	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;
	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}
	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);
	// Read in the vertex data.
	for (i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}
	// Close the model file.
	fin.close();
	return true;
}

void ModelClass::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}
	return;
}

bool ModelClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;
	// Create the texture object.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}
	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if (!result)
	{
		return false;
	}
	return true;
}

bool ModelClass::LoadFireTextures(ID3D11Device* device, WCHAR* textureFilename1, WCHAR* textureFilename2, WCHAR* textureFilename3)
{
	bool result;


	// Create the texture object.
	m_Texture1 = new TextureClass;
	if (!m_Texture1)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture1->Initialize(device, textureFilename1);
	if (!result)
	{
		return false;
	}

	// Create the texture object.
	m_Texture2 = new TextureClass;
	if (!m_Texture2)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture2->Initialize(device, textureFilename2);
	if (!result)
	{
		return false;
	}

	// Create the texture object.
	m_Texture3 = new TextureClass;
	if (!m_Texture3)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture3->Initialize(device, textureFilename3);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	// Release the texture objects.
	if (m_Texture1)
	{
		m_Texture1->Shutdown();
		delete m_Texture1;
		m_Texture1 = 0;
	}

	if (m_Texture2)
	{
		m_Texture2->Shutdown();
		delete m_Texture2;
		m_Texture2 = 0;
	}

	if (m_Texture3)
	{
		m_Texture3->Shutdown();
		delete m_Texture3;
		m_Texture3 = 0;
	}

	return;
}

void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}
	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
	return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;
	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return;
}

bool ModelClass::LoadOBJ(char* filename)
{
	ifstream fin;
	char input, input2;


	D3DXVECTOR3 *vertices, *texcoords, *normals;
	FaceType *faces;
	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;

	// Initialize the counts.
	int vertexCount = 0;
	int textureCount = 0;
	int normalCount = 0;
	int faceCount = 0;

	int i;
	// Open the model file.
	fin.open(filename);

	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}

	// Read from the file and continue to read until the end of the file is reached.
	fin.get(input);

	while (!fin.eof())
	{
		// If the line starts with 'v' then count either the vertex, the texture coordinates, or the normal vector.
		if (input == 'v')
		{
			fin.get(input);
			if (input == ' ') { vertexCount++; }
			if (input == 't') { textureCount++; }
			if (input == 'n') { normalCount++; }
		}
		// If the line starts with 'f' then increment the face count.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ') { faceCount++; }
		}
		// Otherwise read in the remainder of the line.
		while (input != '\n')
		{
			fin.get(input);
		}
		// Start reading the beginning of the next line.
		fin.get(input);
	}

	// Close the file.
	fin.close();

	// Set the vertex count.
	m_vertexCount = faceCount * 3;
	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Initialize the four data structures.
	vertices = new D3DXVECTOR3[vertexCount];
	if (!vertices)
	{
		return false;
	}
	texcoords = new D3DXVECTOR3[textureCount];
	if (!texcoords)
	{
		return false;
	}
	normals = new D3DXVECTOR3[normalCount];
	if (!normals)
	{
		return false;
	}
	faces = new FaceType[faceCount];
	if (!faces)
	{
		return false;
	}

	// Initialize the indexes.
	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	// Open the file.
	fin.open(filename);
	// Check if it was successful in opening the file.
	if (fin.fail() == true)
	{
		return false;
	}

	// Read in the vertices, texture coordinates, and normals into the data structures.
	// Important: Also convert to left hand coordinate system since Maya uses right hand coordinate system.
	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);
			// Read in the vertices.
			if (input == ' ')
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >>
					vertices[vertexIndex].z;
				// Invert the Z vertex to change to left hand system.
				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++;
			}
			// Read in the texture uv coordinates.
			if (input == 't')
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;
				// Invert the V texture coordinates to left hand system.
				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++;
			}
			// Read in the normals.
			if (input == 'n')
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >>
					normals[normalIndex].z;
				// Invert the Z normal to change to left hand system.
				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++;
			}
		}

		// Read in the faces.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				// Read the face data in backwards to convert it to a left hand system from right hand system.
				fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >>
					input2 >> faces[faceIndex].nIndex3 >> faces[faceIndex].vIndex2 >> input2 >>
					faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2 >>
					faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >>
					faces[faceIndex].nIndex1;
				faceIndex++;
			}
		}
		// Read in the remainder of the line.
		while (input != '\n')
		{
			fin.get(input);
		}
		// Start reading the beginning of the next line.
		fin.get(input);
	}

	m_polygons = faceIndex;

	// Close the file.
	fin.close();

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}


	for (i = 0; i < faceIndex; i++)
	{
		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;
		m_model[i * 3].x = vertices[vIndex].x;
		m_model[i * 3].y = vertices[vIndex].y;
		m_model[i * 3].z = vertices[vIndex].z;
		m_model[i * 3].tu = texcoords[tIndex].x;
		m_model[i * 3].tv = texcoords[tIndex].y;
		m_model[i * 3].nx = normals[nIndex].x;
		m_model[i * 3].ny = normals[nIndex].y;
		m_model[i * 3].nz = normals[nIndex].z;

		InitBox(vertices[vIndex]);

		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].tIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;
		m_model[i * 3 + 1].x = vertices[vIndex].x;
		m_model[i * 3 + 1].y = vertices[vIndex].y;
		m_model[i * 3 + 1].z = vertices[vIndex].z;
		m_model[i * 3 + 1].tu = texcoords[tIndex].x;
		m_model[i * 3 + 1].tv = texcoords[tIndex].y;
		m_model[i * 3 + 1].nx = normals[nIndex].x;
		m_model[i * 3 + 1].ny = normals[nIndex].y;
		m_model[i * 3 + 1].nz = normals[nIndex].z;

		InitBox(vertices[vIndex]);

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;
		m_model[i * 3 + 2].x = vertices[vIndex].x;
		m_model[i * 3 + 2].y = vertices[vIndex].y;
		m_model[i * 3 + 2].z = vertices[vIndex].z;
		m_model[i * 3 + 2].tu = texcoords[tIndex].x;
		m_model[i * 3 + 2].tv = texcoords[tIndex].y;
		m_model[i * 3 + 2].nx = normals[nIndex].x;
		m_model[i * 3 + 2].ny = normals[nIndex].y;
		m_model[i * 3 + 2].nz = normals[nIndex].z;

		InitBox(vertices[vIndex]);
	}

	// Release the four data structures.
	if (vertices)
	{
		delete[] vertices;
		vertices = 0;
	}
	if (texcoords)
	{
		delete[] texcoords;
		texcoords = 0;
	}
	if (normals)
	{
		delete[] normals;
		normals = 0;
	}
	if (faces)
	{
		delete[] faces;
		faces = 0;
	}
	return true;
}

void ModelClass::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	return;
}

void ModelClass::SetRotate(D3DXVECTOR3 rotate)
{
	m_rotate = rotate;

	return;
}

void ModelClass::SetSacle(D3DXVECTOR3 scale)
{
	m_scale = scale;

	return;
}

D3DXVECTOR3 ModelClass::GetPos()
{
	return m_pos;
}

D3DXVECTOR3 ModelClass::GetRotate()
{
	return m_rotate;
}

D3DXVECTOR3 ModelClass::GetSacle()
{
	return m_scale;
}

void ModelClass::InitBox(D3DXVECTOR3 ver)
{
	if (ver.x < left)
		left = ver.x;
	if (ver.x > right)
		right = ver.x;
	if (ver.z > top)
		top = ver.z;
	if (ver.z < bottom)
		bottom = ver.z;
}

void ModelClass::ReSizeBox(D3DXVECTOR3 ver)
{
	if (ver.x < m_mesh.x)
		m_mesh.x = ver.x;
	if (ver.x > m_mesh.y)
		m_mesh.y = ver.x;
	if (ver.z > m_mesh.z)
		m_mesh.z = ver.z;
	if (ver.z < m_mesh.w)
		m_mesh.w = ver.z;
}

void ModelClass::SetBox(D3DXVECTOR3 pos, D3DXVECTOR3 rotate, D3DXVECTOR3 scale)
{
	D3DXVECTOR3 l_t, r_t, l_b, r_b;

	l_t = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	r_t = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	l_b = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	r_b = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	l_t.x = top * sin(rotate.x) + left * cos(rotate.x);
	l_t.z = top * cos(rotate.x) - left * sin(rotate.x);

	r_t.x = top * sin(rotate.x) + right * cos(rotate.x);
	r_t.z = top * cos(rotate.x) - right * sin(rotate.x);

	l_b.x = bottom * sin(rotate.x) + left * cos(rotate.x);
	l_b.z = bottom * cos(rotate.x) - left * sin(rotate.x);

	r_b.x = bottom * sin(rotate.x) + right * cos(rotate.x);
	r_b.z = bottom * cos(rotate.x) - right * sin(rotate.x);

	m_mesh = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	ReSizeBox(l_t);
	ReSizeBox(r_t);
	ReSizeBox(l_b);
	ReSizeBox(r_b);


	m_mesh.x = m_mesh.x * scale.x + pos.x - mesh_size;
	m_mesh.y = m_mesh.y * scale.x + pos.x + mesh_size;
	m_mesh.z = m_mesh.z * scale.z + pos.z + mesh_size;
	m_mesh.w = m_mesh.w * scale.z + pos.z - mesh_size;
}

float ModelClass::GetLeft()
{
	return m_mesh.x;
}

float ModelClass::GetRight()
{
	return m_mesh.y;
}

float ModelClass::GetTop()
{
	return m_mesh.z;
}

float ModelClass::GetBottom()
{
	return m_mesh.w;
}

void ModelClass::SetMeshSize(float size)
{
	mesh_size = size;
	return;
}

float ModelClass::GetMeshSize()
{
	return mesh_size;
}

void ModelClass::SetForceBox(D3DXVECTOR4 box)
{
	m_mesh = box;
	return;
}

ID3D11ShaderResourceView* ModelClass::GetTexture1()
{
	return m_Texture1->GetTexture();
}


ID3D11ShaderResourceView* ModelClass::GetTexture2()
{
	return m_Texture2->GetTexture();
}


ID3D11ShaderResourceView* ModelClass::GetTexture3()
{
	return m_Texture3->GetTexture();
}