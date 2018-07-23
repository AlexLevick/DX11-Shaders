#include "Coursework.h"

Coursework::Coursework(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in) : BaseApplication(hinstance, hwnd, screenWidth, screenHeight, in)
{
	screen_Width = screenWidth;
	screen_Height = screenHeight;

	// Mesh and shader set for normal scene rendering
	m_Mesh = new CourseworkMesh(m_Direct3D->GetDevice(), L"../res/HeightMap.png");
	m_Shader = new CourseworkShader(m_Direct3D->GetDevice(), hwnd);

	lightpos = XMFLOAT3(0.f, 5.0f, -5.0f);

	// Create light source (for normal scene rendering)
	Light* light = new Light();
	light->SetDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	light->SetAmbientColour(0.1f, 0.1f, 0.1f, 1.0f);
	light->SetPosition(0.f, 5.0f, -5.0f);
	m_Light.push_back(light);

	m_Gradient = new Texture(m_Direct3D->GetDevice(), L"../res/ColourGradient.png");
	m_NormalMap = new Texture(m_Direct3D->GetDevice(), L"../res/NormalMap.png");

	tessFactor = 1.f;
	wireFrame = false;
}


Coursework::~Coursework()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D object.
	if (m_Mesh)
	{
		delete m_Mesh;
		m_Mesh = 0;
	}

	if (m_Shader)
	{
		delete m_Shader;
		m_Shader = 0;
	}
}


bool Coursework::Frame()
{
	bool result;

	result = BaseApplication::Frame();
	if (!result)
	{
		return false;
	}

	// Additional user input
	UserInput();

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool Coursework::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Clear the scene. (default blue colour)
	m_Direct3D->BeginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Update();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	worldMatrix = XMMatrixRotationZ(3.14); 
	worldMatrix = XMMatrixRotationX(3.14);

	m_Mesh->SendData(m_Direct3D->GetDeviceContext());
	m_Shader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Mesh->GetTexture(), m_Gradient->GetTexture(), m_NormalMap->GetTexture(), tessFactor, m_Light);
	m_Shader->Render(m_Direct3D->GetDeviceContext(), m_Mesh->GetIndexCount());

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}

void Coursework::UserInput()
{
	// Extra user input
	if (m_Input->isKeyDown('N') && tessFactor > 1)
	{
		tessFactor --;
		m_Input->SetKeyUp('N');
	}

	if (m_Input->isKeyDown('M') && tessFactor < 64)
	{
		tessFactor ++;
		m_Input->SetKeyUp('M');
	}

	if (m_Input->isKeyDown('B'))
	{
		if (!wireFrame)
			m_Direct3D->TurnOnWireframe();
		else
			m_Direct3D->TurnOffWireframe();

		wireFrame = !wireFrame;
		m_Input->SetKeyUp('B');
	}
	/*
	if (m_Input->isKeyDown('J'))
		lightpos.x -= 0.02;

	if (m_Input->isKeyDown('L'))
		lightpos.x += 0.02;

	if (m_Input->isKeyDown('U'))
		lightpos.y -= 0.02;

	if (m_Input->isKeyDown('O'))
		lightpos.y += 0.02;

	if (m_Input->isKeyDown('I'))
		lightpos.z += 0.02;

	if (m_Input->isKeyDown('K'))
		lightpos.z += 0.02;

	m_Light[0]->SetPosition(lightpos.x, lightpos.y, lightpos.z);*/
}