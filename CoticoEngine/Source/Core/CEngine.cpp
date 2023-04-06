#include "CEngine.h"

int scrWidth = 800, scrHeight = 800;

CEngine::CEngine()
{
	appWindow = new AppWindow;
	appWindow->CreateWindow("Cool Window", scrWidth, scrHeight);
	glfwMakeContextCurrent(appWindow->GetGLWindow());
	gladLoadGL();

	renderer = new Renderer(this);
	World::Get()->SetEngine(this);
	camera = new Camera(scrWidth, scrHeight, glm::vec3(0.0f, 0.0f, 2.0f));
}

void CEngine::Draw()
{
	renderer->Render();
}

void CEngine::Update()
{
	World::Get()->Update();
	camera->Inputs(appWindow->GetGLWindow());
	camera->UpdateMatrix(45.0f, 0.1f, 100.f);

	glfwPollEvents();
}

CEngine::~CEngine()
{
	delete appWindow;
	delete renderer;
}