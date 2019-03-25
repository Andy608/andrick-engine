#include "Playground.h"
#include "../render/camera/FreeRoamCamera.h"
#include <andrick/window/AndrickWindow.h>
#include "../asset/ShaderAssetPack.h"

//#include "../render/model/ModelTest.h"
#include <andrick/render/model/Model.h>
#include "../asset/MeshAssetPack.h"

namespace bb
{
	const std::string& Playground::msCLASS_NAME = "Playground";

	//TEMP
	static std::vector<andrick::Model*> models;
	andrick::Model* pFloor;
	andrick::Model* pBarrel;

	Playground::Playground() :
		mpCamera(new FreeRoamCamera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3())),
		mpModelRenderer(new andrick::ModelRenderer())
	{
		//Temp: Set the main viewport camera to the temp camera.
		andrick::AndrickWindow::getFocusedWindow()->getViewport().setCamera(mpCamera);

		pFloor = new andrick::Model(MeshAssetPack::mspQuadMesh);
		pFloor->setTexture(*MeshAssetPack::mspLoveTexture);
		pFloor->getTransform()->setRotation(-90.0f, 0.0f, 0.0f);
		pFloor->getTransform()->setScale(5.0f, 5.0f, 5.0f);

		pBarrel = new andrick::Model(MeshAssetPack::mspBarrelMesh);
		pBarrel->setTexture(*MeshAssetPack::mspBarrelTexture);

		models.push_back(pFloor);
		models.push_back(pBarrel);

		//mpModelRenderer->setCamera(mpCamera);
		//mpModelRenderer->setShaderProgram(ShaderAssetPack::mspTestProgram);
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

		//pFloor->getTransform()->addRotation(0.0f, 180.0f * (GLfloat)deltaTime, 0.0f);
		//pBarrel->getTransform()->addRotation(0.0f, 60.0f * (GLfloat)deltaTime, 0.0f);
	}

	void Playground::render(const GLdouble& alpha)
	{
		mpCamera->lerp(alpha);
		//mpModelRenderer->render(alpha, models);

		glPolygonMode(andrick::ModelRenderer::EnumCullType::FRONT_ONLY, andrick::ModelRenderer::EnumDrawType::FILL);
		glEnable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE0);

		//Picking shader program
		andrick::ShaderProgram* currentProgram = ShaderAssetPack::mspTestProgram;
		currentProgram->use();

		//Loading general stuff to shader program
		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrixPtr());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrixPtr());

		//Loading model stuff to shader program
		pFloor->prepModelTransform(alpha, *currentProgram);

		//Render model
		pFloor->getTextureWrapper()->bind();
		pFloor->render(alpha);
		pFloor->getTextureWrapper()->unbind();

		pBarrel->prepModelTransform(alpha, *currentProgram);
		
		pBarrel->getTextureWrapper()->bind();
		pBarrel->render(alpha);
		pBarrel->getTextureWrapper()->unbind();

		glDisable(GL_DEPTH_TEST);
		glActiveTexture(0);
	}
}