#ifndef _COURSEWORKMESH_H_
#define _COURSEWORKMESH_H_

#include "BaseMesh.h"

using namespace DirectX;

class CourseworkMesh : public BaseMesh
{

public:
	CourseworkMesh(ID3D11Device* device, WCHAR* textureFilename);
	~CourseworkMesh();

	void SendData(ID3D11DeviceContext*);

protected:
	void InitBuffers(ID3D11Device* device);

};

#endif