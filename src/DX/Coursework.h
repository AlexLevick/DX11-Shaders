// Application.h
#ifndef _COURSEWORK_H
#define _COURSEWORK_H

// Includes
#include "baseapplication.h"
#include "Light.h"
#include <vector>
#include "CourseworkMesh.h"
#include "CourseworkShader.h"
#include "Texture.h"

class Coursework : public BaseApplication
{
public:

	Coursework(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input*);
	~Coursework();

	bool Frame();

private:
	bool Render();
	void UserInput();

private:
	float screen_Width;
	float screen_Height;
	float tessFactor;
	XMFLOAT3 lightpos;
	bool wireFrame;

	CourseworkShader* m_Shader;

	CourseworkMesh* m_Mesh;

	std::vector<Light*> m_Light;

	Texture* m_Gradient;
	Texture* m_NormalMap;
};

#endif