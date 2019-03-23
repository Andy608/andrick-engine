#include "Playground.h"
#include "../render/camera/FreeRoamCamera.h"
#include <andrick/window/AndrickWindow.h>
#include "../asset/ShaderAssetPack.h"

namespace bb
{
	const std::string& Playground::msCLASS_NAME = "Playground";

	//TEMP
	static std::vector<andrick::Mesh*> meshes;

	Playground::Playground() :
		mpCamera(new FreeRoamCamera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3())),
		mpMeshRenderer(new andrick::MeshRenderer())
	{
		//Temp: Set the main viewport camera to the temp camera.
		andrick::AndrickWindow::getFocusedWindow()->getViewport().setCamera(mpCamera);

		meshes.push_back(ShaderAssetPack::mspTestMesh);

		mpMeshRenderer->setCamera(mpCamera);
		mpMeshRenderer->setShaderProgram(ShaderAssetPack::mspTestProgram);
	}

	Playground::~Playground()
	{
		delete mpCamera;
		mpCamera = nullptr;

		delete mpMeshRenderer;
		mpMeshRenderer = nullptr;
	}

	void Playground::update(const GLdouble& deltaTime)
	{
		/*GLuint i;
		for (i = 0; i < meshes.size(); ++i)
		{
			meshes.at(i)->update(deltaTime);
		}*/
	}

	void Playground::render(const GLdouble& alpha)
	{
		mpCamera->lerp(alpha);
		mpMeshRenderer->render(meshes);
	}
}