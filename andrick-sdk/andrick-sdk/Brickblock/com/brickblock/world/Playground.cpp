#include "Playground.h"
#include "../render/camera/FreeRoamCamera.h"
#include <andrick/window/AndrickWindow.h>
#include "../asset/ShaderAssetPack.h"

#include "../render/model/ModelTest.h"

namespace bb
{
	const std::string& Playground::msCLASS_NAME = "Playground";

	//TEMP
	static std::vector<andrick::Model*> models;

	Playground::Playground() :
		mpCamera(new FreeRoamCamera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3())),
		mpModelRenderer(new andrick::ModelRenderer())
	{
		//Temp: Set the main viewport camera to the temp camera.
		andrick::AndrickWindow::getFocusedWindow()->getViewport().setCamera(mpCamera);

		models.push_back(new ModelTest());

		mpModelRenderer->setCamera(mpCamera);
		mpModelRenderer->setShaderProgram(ShaderAssetPack::mspTestProgram);
	}

	Playground::~Playground()
	{
		delete mpCamera;
		mpCamera = nullptr;

		delete mpModelRenderer;
		mpModelRenderer = nullptr;

		GLuint i;
		for (i = 0; i < models.size(); ++i)
		{
			delete models.at(i);
		}

		models.clear();
	}

	void Playground::update(const GLdouble& deltaTime)
	{
		GLuint i;
		for (i = 0; i < models.size(); ++i)
		{
			models.at(i)->update(deltaTime);
		}
	}

	void Playground::render(const GLdouble& alpha)
	{
		mpCamera->lerp(alpha);
		mpModelRenderer->render(alpha, models);
	}
}