#include "Playground.h"
#include <andrick/window/AndrickWindow.h>
#include <andrick/util/math/MathHelper.h>
#include <andrick/render/model/Model.h>

#include "../render/camera/FreeRoamCamera.h"
#include "../asset/ShaderAssetPack.h"
#include "../asset/MeshAssetPack.h"
#include <andrick/render/wrapper/buffer/fbo/FBOWrapper.h>
#include <andrick/render/wrapper/buffer/rbo/RBOWrapper.h>
#include <andrick/render/wrapper/buffer/BufferResizeRegistry.h>
#include <andrick/util/Timer.h>

namespace bb
{
	const std::string& Playground::msCLASS_NAME = "Playground";

	//TEMP
	static std::vector<andrick::Model*> models;
	andrick::Model* pFloor;
	andrick::TextureWrapper* pColRamp;

	andrick::Model* pBarrel;
	andrick::Model* pLight;
	andrick::Model* pSuzanne;
	andrick::Model* pLol;

	andrick::FBOWrapper* pSceneFBO;
	andrick::RBOWrapper* pDepthStencilRBO;
	andrick::TextureWrapper* pFBOSceneRenderTexture;
	andrick::Model* pFSQ;

	Playground::Playground() :
		mpCamera(new FreeRoamCamera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3())),
		mpModelRenderer(new andrick::ModelRenderer())
	{
		//Temp: Set the main viewport camera to the temp camera.
		andrick::AndrickWindow::getFocusedWindow()->getViewport().setCamera(mpCamera);

		pFloor = new andrick::Model(MeshAssetPack::mspQuadMesh);
		pFloor->setImage(*MeshAssetPack::mspLoveTexture);
		pFloor->getTransform()->setRotation(-90.0f, 0.0f, 0.0f);
		pFloor->getTransform()->setScale(5.0f, 5.0f, 5.0f);

		pBarrel = new andrick::Model(MeshAssetPack::mspBarrelMesh);
		pBarrel->setImage(*MeshAssetPack::mspBarrelTexture);
		pBarrel->getTransform()->setPosition(2.0f, 2.0f, 0.0f);

		pColRamp = new andrick::TextureWrapper(*MeshAssetPack::mspColorRampTexture);
		pColRamp->generateGLTexture();

		pLight = new andrick::Model(MeshAssetPack::mspTestMesh);
		pLight->getTransform()->setPosition(-2.0f, 2.0f, -3.0f);

		pSuzanne = new andrick::Model(MeshAssetPack::mspSuzanneMesh);
		pSuzanne->setImage(*MeshAssetPack::mspDefaultTexture,
			andrick::TextureWrapper::EnumWrapStyle::REPEAT, andrick::TextureWrapper::EnumWrapStyle::REPEAT, 
			andrick::TextureWrapper::EnumMinFilter::NEAREST_MIPMAP_NEAREST, andrick::TextureWrapper::EnumMagFilter::NEAREST);

		pLol = new andrick::Model(MeshAssetPack::mspSuzanneMesh);
		pLol->setImage(*MeshAssetPack::mspDefaultTexture,
			andrick::TextureWrapper::EnumWrapStyle::REPEAT, andrick::TextureWrapper::EnumWrapStyle::REPEAT,
			andrick::TextureWrapper::EnumMinFilter::NEAREST_MIPMAP_NEAREST, andrick::TextureWrapper::EnumMagFilter::NEAREST);

		pLol->getTransform()->setPosition(0.0f, 4.0f, 0.0f);

		pFSQ = new andrick::Model(MeshAssetPack::mspQuadMesh);

		models.push_back(pFloor);
		models.push_back(pBarrel);
		models.push_back(pLight);
		models.push_back(pSuzanne);
		models.push_back(pLol);
		models.push_back(pFSQ);

		pSceneFBO = new andrick::FBOWrapper();
		pDepthStencilRBO = new andrick::RBOWrapper();
		pFBOSceneRenderTexture = new andrick::TextureWrapper(andrick::AndrickWindow::getFocusedWindow()->getSize(), nullptr,
			andrick::EnumInternalFormatType::RGB, andrick::EnumDataFormat::RGB_FORMAT, andrick::EnumDataType::UNSIGNED_BYTE,
			andrick::TextureWrapper::EnumWrapStyle::CLAMP_TO_EDGE, andrick::TextureWrapper::EnumWrapStyle::CLAMP_TO_EDGE,
			andrick::TextureWrapper::EnumMinFilter::LINEAR_MIN, andrick::TextureWrapper::EnumMagFilter::LINEAR_MAG);

		//pFBOSceneRenderTexture->resizeWithScreen();

		pSceneFBO->bind();

		//Attach the color component to the fbo
		pSceneFBO->attachTexture(*pFBOSceneRenderTexture, andrick::FBOWrapper::EnumBindType::FRAMEBUFFER, andrick::EnumAttachmentType::COLOR_ATTACHMENT0);
		
		//Set the storage type for the rbo while the fbo is bound
		pDepthStencilRBO->setStorage(andrick::AndrickWindow::getFocusedWindow()->getSize(), andrick::EnumInternalFormatType::DEPTH24_STENCIL8);
		
		//Attach the depth and stencil components to the fbo
		pSceneFBO->attachRBO(*pDepthStencilRBO, andrick::EnumAttachmentType::DEPTH_STENCIL_ATTACHMENT);

		pSceneFBO->unbind();

		andrick::BufferResizeRegistry::addFBO(pSceneFBO);

		///mpModelRenderer->setCamera(mpCamera);
		///mpModelRenderer->setShaderProgram(ShaderAssetPack::mspTestProgram);
	}

	Playground::~Playground()
	{
		delete mpCamera;
		mpCamera = nullptr;

		delete mpModelRenderer;
		mpModelRenderer = nullptr;

		delete pColRamp;
		pColRamp = nullptr;

		GLuint i;
		for (i = 0; i < models.size(); ++i)
		{
			delete models.at(i);
		}

		models.clear();

		delete pSceneFBO;
		pSceneFBO = nullptr;

		delete pDepthStencilRBO;
		pDepthStencilRBO = nullptr;
		
		delete pFBOSceneRenderTexture;
		pFBOSceneRenderTexture = nullptr;
	}

	void Playground::update(const GLdouble& deltaTime)
	{
		GLuint i;
		for (i = 0; i < models.size(); ++i)
		{
			models.at(i)->update(deltaTime);
		}

		///pFloor->getTransform()->addRotation(0.0f, 180.0f * (GLfloat)deltaTime, 0.0f);

		static GLfloat time = 0.0f;
		time += (100.0f * static_cast<GLfloat>(deltaTime));

		GLfloat x = (3.0f * (cos(andrick::MathHelper::toRadians(time))));
		GLfloat z = (3.0f * (sin(andrick::MathHelper::toRadians(time))));

		pLight->getTransform()->setPosition(x - 3.0f, 60.0f * (GLfloat)deltaTime, z);
		pLight->getTransform()->addRotation(0.0f, 180.0f * (GLfloat)deltaTime, 0.0f);

		pSuzanne->getTransform()->setPosition(-3.0f, (x * 0.5f) + 3.0f, 0.0f);
		pSuzanne->getTransform()->addRotation(10.0f * (GLfloat)deltaTime, 0.0f, 0.0f);

		///pFloor->getTransform()->addRotation(0.0f, 0.0f, -5.0f * (GLfloat)deltaTime);

		pLol->getTransform()->addRotation(180.0f * (GLfloat)deltaTime, 90.0f * (GLfloat)deltaTime, 90.0f * (GLfloat)deltaTime);
	}

	void Playground::render(const GLdouble& alpha)
	{
		mpCamera->lerp(alpha);
		///mpModelRenderer->render(alpha, models);

		//Render to fbo
		pSceneFBO->bind();
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(andrick::ModelRenderer::EnumCullType::FRONT_ONLY, andrick::ModelRenderer::EnumDrawType::FILL);

		//Picking shader program
		andrick::ShaderProgram* currentProgram = ShaderAssetPack::mspJuliaFractalProgram;
		currentProgram->use();

		//Loading general stuff to shader program
		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());
		currentProgram->loadFloat("time", static_cast<GLfloat>(andrick::Timer::getCurrentTime()));

		//Loading model stuff to shader program
		pFloor->prepModelTransform(alpha, *currentProgram);

		//Render models
		pFloor->getTextureWrapper()->bind(0);
		currentProgram->loadInt("texture0", pFloor->getTextureWrapper()->getTextureUnit());
		
		pColRamp->bind(1);
		currentProgram->loadInt("colRamp", pColRamp->getTextureUnit());

		pFloor->render(alpha);
		
		pColRamp->unbind();
		pFloor->getTextureWrapper()->unbind();

		currentProgram = ShaderAssetPack::mspPhongShadingProgram;
		currentProgram->use();

		//Loading general stuff to shader program
		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());
		
		currentProgram->loadVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));
		currentProgram->loadVec3("lightPos", pLight->getTransform()->getLerpedPosition());
		currentProgram->loadVec3("viewPos", mpCamera->getTransform()->getLerpedPosition());
		
		currentProgram->loadMat3("normalMatrix", GL_FALSE, andrick::MathHelper::createNormalMat(pSuzanne->getTransform()->getTransformationMat(), mpCamera->getViewMatrix()));
		currentProgram->loadFloat("lightSz", 0.01f);

		pSuzanne->prepModelTransform(alpha, *currentProgram);
		
		pSuzanne->getTextureWrapper()->bind();
		currentProgram->loadInt("texture0", pSuzanne->getTextureWrapper()->getTextureUnit());

		pSuzanne->render(alpha);
		pSuzanne->getTextureWrapper()->unbind();

		currentProgram = ShaderAssetPack::mspMandlebrotFractalProgram;
		currentProgram->use();
		
		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());
		
		pBarrel->prepModelTransform(alpha, *currentProgram);
		
		pBarrel->getTextureWrapper()->bind();
		currentProgram->loadInt("texture0", pBarrel->getTextureWrapper()->getTextureUnit());
		
		pBarrel->render(alpha);
		pBarrel->getTextureWrapper()->unbind();

		currentProgram = ShaderAssetPack::mspLightSourceProgram;
		currentProgram->use();

		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());

		pLight->prepModelTransform(alpha, *currentProgram);
		pLight->render(alpha);

		currentProgram = ShaderAssetPack::mspTestProgram;
		currentProgram->use();

		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());

		pLol->prepModelTransform(alpha, *currentProgram);
		pLol->getTextureWrapper()->bind();
		pLol->render(alpha);
		pLol->getTextureWrapper()->unbind();

		pSceneFBO->unbind();
		glDisable(GL_DEPTH_TEST);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		currentProgram = ShaderAssetPack::mspTextureProgram;
		currentProgram->use();

		pFBOSceneRenderTexture->bind();
		currentProgram->loadInt("screenTexture", pFBOSceneRenderTexture->getTextureUnit());
		
		pFSQ->render(alpha);
		pFBOSceneRenderTexture->unbind();

		glDisable(GL_DEPTH_TEST);
		glActiveTexture(0);
	}
}