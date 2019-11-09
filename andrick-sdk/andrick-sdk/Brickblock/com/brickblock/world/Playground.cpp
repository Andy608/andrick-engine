#include "Playground.h"

#include "../render/camera/FreeRoamCamera.h"
#include "../asset/ShaderAssetPack.h"
#include "../asset/ImageAssetPack.h"
#include "../asset/MeshAssetPack.h"

#include <andrick/window/AndrickWindow.h>
#include <andrick/util/math/MathHelper.h>
#include <andrick/render/model/Model.h>
#include <andrick/render/wrapper/buffer/fbo/FBOWrapper.h>
#include <andrick/render/wrapper/buffer/rbo/RBOWrapper.h>
#include <andrick/render/wrapper/buffer/BufferResizeRegistry.h>
#include <andrick/render/wrapper/texture/CubeMap.h>
#include <andrick/util/Timer.h>

namespace bb
{
	const std::string& Playground::msCLASS_NAME = "Playground";

	static std::vector<andrick::Model*> models;
	static std::vector<andrick::TextureWrapper*> textures;

	andrick::Model* pFloor;
	andrick::Model* pBarrel;
	andrick::Model* pLight;
	andrick::Model* pSuzanne;
	andrick::Model* pFSQ;

	andrick::FBOWrapper* pSceneFBO;
	andrick::RBOWrapper* pDepthStencilRBO;

	andrick::FBOWrapper* pSceneFBOMultisample;
	andrick::RBOWrapper* pDepthStencilRBOMultisample;

	andrick::TextureWrapper* pColRamp;
	andrick::TextureWrapper* pFBOSceneRenderTextureMultisample;
	andrick::TextureWrapper* pFBOSceneRenderTexture;

	andrick::TextureWrapper* pStoneHeightMap;
	andrick::TextureWrapper* pStoneNormalMap;
	andrick::TextureWrapper* pMetalPlateHeightMap;
	andrick::TextureWrapper* pMetalPlateNormalMap;
	andrick::TextureWrapper* pMetalGrillHeightMap;
	andrick::TextureWrapper* pMetalGrillNormalMap;
	andrick::TextureWrapper* pBrickworkHeightMap;
	andrick::TextureWrapper* pBrickworkNormalMap;
	andrick::TextureWrapper* pConcreteHeightMap;
	andrick::TextureWrapper* pConcreteNormalMap;

	andrick::TextureWrapper* pCurrentHeightMap;
	andrick::TextureWrapper* pCurrentNormalMap;

	GLfloat pCurrentPomMin;
	GLfloat pCurrentPomMax;
	
	std::vector<std::array<andrick::TextureWrapper*, 2>> pomTextureMaps;
	std::vector<std::array<GLfloat, 2>> pomRangeMaps;

	andrick::CubeMap* pCubeMap;

	glm::vec2 pomRange = glm::vec2(0.9925, 0.9975);

	Playground::Playground() :
		mpCamera(new FreeRoamCamera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3())),
		mpModelRenderer(new andrick::ModelRenderer())
	{
		//Temp: Set the main viewport camera to the temp camera.
		andrick::AndrickWindow::getFocusedWindow()->getViewport().setCamera(mpCamera);

		pFloor = new andrick::Model(MeshAssetPack::mspQuadMesh);
		pFloor->setImage(*ImageAssetPack::mspDefaultImage);
		pFloor->getTransform()->setRotation(-90.0f, 0.0f, 0.0f);
		pFloor->getTransform()->setScale(5.0f, 5.0f, 5.0f);

		pBarrel = new andrick::Model(MeshAssetPack::mspBarrelMesh);
		pBarrel->setImage(*ImageAssetPack::mspBarrelImage);
		pBarrel->getTransform()->setPosition(2.0f, 0.0f, 0.0f);

		pLight = new andrick::Model(MeshAssetPack::mspTestMesh);
		pLight->getTransform()->setPosition(-2.0f, 2.0f, -3.0f);

		pSuzanne = new andrick::Model(MeshAssetPack::mspSuzanneMesh);
		pSuzanne->setImage(*ImageAssetPack::mspDefaultImage,
			andrick::TextureWrapper::EnumWrapStyle::REPEAT, andrick::TextureWrapper::EnumWrapStyle::REPEAT,
			andrick::TextureWrapper::EnumMinFilter::NEAREST_MIPMAP_NEAREST, andrick::TextureWrapper::EnumMagFilter::NEAREST);

		pFSQ = new andrick::Model(MeshAssetPack::mspQuadMesh);

		models.push_back(pFloor);
		models.push_back(pBarrel);
		models.push_back(pLight);
		models.push_back(pSuzanne);
		models.push_back(pFSQ);

		pColRamp = new andrick::TextureWrapper(*ImageAssetPack::mspColorRampImage);
		pColRamp->generateGLTexture();

		pStoneHeightMap = new andrick::TextureWrapper(*ImageAssetPack::mspStoneHeightMap);
		pStoneHeightMap->generateGLTexture();

		pStoneNormalMap = new andrick::TextureWrapper(*ImageAssetPack::mspStoneNormalMap);
		pStoneNormalMap->generateGLTexture();

		pMetalPlateHeightMap = new andrick::TextureWrapper(*ImageAssetPack::mspMetalPlateHeightMap);
		pMetalPlateHeightMap->generateGLTexture();

		pMetalPlateNormalMap = new andrick::TextureWrapper(*ImageAssetPack::mspMetalPlateNormalMap);
		pMetalPlateNormalMap->generateGLTexture();

		pMetalGrillHeightMap = new andrick::TextureWrapper(*ImageAssetPack::mspMetalGrillHeightMap);
		pMetalGrillHeightMap->generateGLTexture();

		pMetalGrillNormalMap = new andrick::TextureWrapper(*ImageAssetPack::mspMetalGrillNormalMap);
		pMetalGrillNormalMap->generateGLTexture();

		pBrickworkHeightMap = new andrick::TextureWrapper(*ImageAssetPack::mspBrickworkHeightMap);
		pBrickworkHeightMap->generateGLTexture();

		pBrickworkNormalMap = new andrick::TextureWrapper(*ImageAssetPack::mspBrickworkNormalMap);
		pBrickworkNormalMap->generateGLTexture();

		pConcreteHeightMap = new andrick::TextureWrapper(*ImageAssetPack::mspConcreteHeightMap);
		pConcreteHeightMap->generateGLTexture();

		pConcreteNormalMap = new andrick::TextureWrapper(*ImageAssetPack::mspConcreteNormalMap);
		pConcreteNormalMap->generateGLTexture();

		textures.push_back(pColRamp);
		textures.push_back(pStoneHeightMap);
		textures.push_back(pStoneNormalMap);
		textures.push_back(pMetalPlateHeightMap);
		textures.push_back(pMetalPlateNormalMap);
		textures.push_back(pMetalGrillHeightMap);
		textures.push_back(pMetalGrillNormalMap);
		textures.push_back(pBrickworkHeightMap);
		textures.push_back(pBrickworkNormalMap);
		textures.push_back(pConcreteHeightMap);
		textures.push_back(pConcreteNormalMap);

		pomTextureMaps.push_back({ pStoneHeightMap, pStoneNormalMap });
		pomTextureMaps.push_back({ pMetalPlateHeightMap, pMetalPlateNormalMap });
		pomTextureMaps.push_back({ pMetalGrillHeightMap, pMetalGrillNormalMap });
		pomTextureMaps.push_back({ pBrickworkHeightMap, pBrickworkNormalMap });
		pomTextureMaps.push_back({ pConcreteHeightMap, pConcreteNormalMap });

		pomRangeMaps.push_back({ 0.9865f, 0.9975f });
		pomRangeMaps.push_back({ 0.9315f, 0.9975f });
		pomRangeMaps.push_back({ 0.815f, 0.9975f });
		pomRangeMaps.push_back({ 0.9915f, 0.9975f });
		pomRangeMaps.push_back({ 0.8975f, 0.9975f });

		pCurrentHeightMap = pomTextureMaps.at(0)[0];
		pCurrentNormalMap = pomTextureMaps.at(0)[1];
		pCurrentPomMin = pomRangeMaps.at(0)[0];
		pCurrentPomMax = pomRangeMaps.at(0)[1];

		//Setup multisample fbo
		pSceneFBOMultisample = new andrick::FBOWrapper();
		pDepthStencilRBOMultisample = new andrick::RBOWrapper();
		pFBOSceneRenderTextureMultisample = new andrick::TextureWrapper(andrick::AndrickWindow::getFocusedWindow()->getSize(), nullptr,
			andrick::EnumTextureType::TEXTURE_2D_MULTISAMPLE, GL_FALSE,
			andrick::EnumInternalFormatType::RGB, andrick::EnumDataFormat::RGB_FORMAT, andrick::EnumDataType::UNSIGNED_BYTE,
			andrick::TextureWrapper::EnumWrapStyle::CLAMP_TO_EDGE, andrick::TextureWrapper::EnumWrapStyle::CLAMP_TO_EDGE,
			andrick::TextureWrapper::EnumMinFilter::LINEAR_MIN, andrick::TextureWrapper::EnumMagFilter::LINEAR_MAG);

		pFBOSceneRenderTextureMultisample->setSampleSize(8);

		//Setup screen rendering fbo
		pSceneFBO = new andrick::FBOWrapper();
		pDepthStencilRBO = new andrick::RBOWrapper();
		pFBOSceneRenderTexture = new andrick::TextureWrapper(andrick::AndrickWindow::getFocusedWindow()->getSize(), nullptr,
			andrick::EnumTextureType::TEXTURE_2D, GL_FALSE,
			andrick::EnumInternalFormatType::RGB, andrick::EnumDataFormat::RGB_FORMAT, andrick::EnumDataType::UNSIGNED_BYTE,
			andrick::TextureWrapper::EnumWrapStyle::CLAMP_TO_EDGE, andrick::TextureWrapper::EnumWrapStyle::CLAMP_TO_EDGE,
			andrick::TextureWrapper::EnumMinFilter::LINEAR_MIN, andrick::TextureWrapper::EnumMagFilter::LINEAR_MAG);

		pSceneFBOMultisample->bind();

		pSceneFBOMultisample->attachTexture(*pFBOSceneRenderTextureMultisample, andrick::FBOWrapper::EnumBindType::FRAMEBUFFER,
			andrick::EnumAttachmentType::COLOR_ATTACHMENT0, andrick::EnumTextureType::TEXTURE_2D_MULTISAMPLE);

		pDepthStencilRBOMultisample->setStorageMultisample(andrick::AndrickWindow::getFocusedWindow()->getSize(),
			andrick::EnumInternalFormatType::DEPTH24_STENCIL8, pFBOSceneRenderTextureMultisample->getSampleSize());

		pSceneFBOMultisample->attachRBO(*pDepthStencilRBOMultisample,
			andrick::EnumAttachmentType::DEPTH_STENCIL_ATTACHMENT, andrick::EnumTextureType::TEXTURE_2D_MULTISAMPLE);

		pSceneFBOMultisample->unbind();

		pSceneFBO->bind();

		//Attach the color component to the fbo
		pSceneFBO->attachTexture(*pFBOSceneRenderTexture, andrick::FBOWrapper::EnumBindType::FRAMEBUFFER, andrick::EnumAttachmentType::COLOR_ATTACHMENT0);

		//Set the storage type for the rbo while the fbo is bound
		pDepthStencilRBO->setStorage(andrick::AndrickWindow::getFocusedWindow()->getSize(), andrick::EnumInternalFormatType::DEPTH24_STENCIL8);

		//Attach the depth and stencil components to the fbo
		pSceneFBO->attachRBO(*pDepthStencilRBO, andrick::EnumAttachmentType::DEPTH_STENCIL_ATTACHMENT);

		pSceneFBO->unbind();

		andrick::BufferResizeRegistry::addFBO(pSceneFBOMultisample);
		andrick::BufferResizeRegistry::addFBO(pSceneFBO);

		pCubeMap = new andrick::CubeMap();

		pCubeMap->addTextures(ImageAssetPack::mspCraterLakeCubeMapImages);
		pCubeMap->generateGLCubeMap();
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

		for (i = 0; i < textures.size(); ++i)
		{
			delete textures.at(i);
		}

		textures.clear();

		delete pSceneFBO;
		pSceneFBO = nullptr;

		delete pDepthStencilRBO;
		pDepthStencilRBO = nullptr;

		delete pFBOSceneRenderTexture;
		pFBOSceneRenderTexture = nullptr;

		delete pSceneFBOMultisample;
		pSceneFBOMultisample = nullptr;

		delete pDepthStencilRBOMultisample;
		pDepthStencilRBOMultisample = nullptr;

		delete pFBOSceneRenderTextureMultisample;
		pFBOSceneRenderTextureMultisample = nullptr;

		delete pCubeMap;
		pCubeMap = nullptr;
	}

	void Playground::update(const GLdouble& deltaTime)
	{
		GLuint i;
		for (i = 0; i < models.size(); ++i)
		{
			models.at(i)->update(deltaTime);
		}

		static GLfloat time = 0.0f;
		static GLfloat counter = 0.0f;
		static GLint currentIndex = 0;
		time += (60.0f * static_cast<GLfloat>(deltaTime));
		counter += deltaTime;

		GLfloat x = (3.0f * (cos(andrick::MathHelper::toRadians(time * 0.125f * 0.5f))));
		GLfloat z = (3.0f * (sin(andrick::MathHelper::toRadians(time * 0.125f * 0.5f))));

		pFloor->getTransform()->addRotation(0.0f, 0.0f, 20.0f * (GLfloat)deltaTime);
		pFloor->getTransform()->setPosition(0.0f, x * (GLfloat)deltaTime, 0.0f);

		//mpCamera->getTransform()->setPosition((-x * 1.6), 0.2f, (z * 1.6) - 5);
		//mpCamera->getTransform()->addRotation(0.0f, 7.5/2.0 * (GLfloat)deltaTime, 0.0f);

		//pBarrel->getTransform()->addRotation(0.0f, 20.0f * deltaTime, 0.0f);

		/*if (counter > 2.0f)
		{
			counter = 0.0f;
			currentIndex = (currentIndex + 1) % pomTextureMaps.size();
			pCurrentHeightMap = pomTextureMaps.at(currentIndex)[0];
			pCurrentNormalMap = pomTextureMaps.at(currentIndex)[1];
			pCurrentPomMin = pomRangeMaps.at(currentIndex)[0];
			pCurrentPomMax = pomRangeMaps.at(currentIndex)[1];
		}*/
	}

	void Playground::render(const GLdouble& alpha)
	{
		mpCamera->lerp(alpha);
		///mpModelRenderer->render(alpha, models);

		//Render to fbo
		pSceneFBOMultisample->bind();
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(andrick::ModelRenderer::EnumCullType::FRONT_ONLY, andrick::ModelRenderer::EnumDrawType::FILL);

		//glPolygonMode(andrick::ModelRenderer::EnumCullType::FRONT_ONLY, andrick::ModelRenderer::EnumDrawType::OUTLINE);
		//Picking shader program
		andrick::ShaderProgram* currentProgram = ShaderAssetPack::mspMandlebrotFractalProgram;
		currentProgram->use();

		//Loading general stuff to shader program
		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());
		currentProgram->loadFloat("time", static_cast<GLfloat>(andrick::Timer::getCurrentTime()));

		//Loading model stuff to shader program
		pFloor->prepModelTransform(alpha, *currentProgram);

		//Render models
		pFloor->getTextureWrapper()->bind(0);
		pCurrentHeightMap->bind(1);
		pCurrentNormalMap->bind(2);
		currentProgram->loadInt("texture0", pFloor->getTextureWrapper()->getTextureUnit());
		currentProgram->loadInt("texture1", pCurrentHeightMap->getTextureUnit());
		currentProgram->loadInt("texture2", pCurrentNormalMap->getTextureUnit());
		currentProgram->loadVec2("range", pCurrentPomMin, pCurrentPomMax);

		//pColRamp->bind(1);
		//currentProgram->loadInt("colRamp", pColRamp->getTextureUnit());

		pFloor->render(alpha);
		pFloor->getTextureWrapper()->unbind();
		pCurrentHeightMap->unbind();
		pCurrentNormalMap->unbind();

		//pColRamp->unbind();
		//pFloor->getTextureWrapper()->unbind();
		glPolygonMode(andrick::ModelRenderer::EnumCullType::FRONT_ONLY, andrick::ModelRenderer::EnumDrawType::FILL);

		//currentProgram = ShaderAssetPack::mspJuliaFractalProgram;
		//currentProgram->use();

		////Loading general stuff to shader program
		//currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		//currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());

		//currentProgram->loadVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));
		//currentProgram->loadVec3("lightPos", pLight->getTransform()->getLerpedPosition());
		//currentProgram->loadVec3("viewPos", mpCamera->getTransform()->getLerpedPosition());

		//currentProgram->loadMat3("normalMatrix", GL_FALSE, andrick::MathHelper::createNormalMat(pSuzanne->getTransform()->getTransformationMat(), mpCamera->getViewMatrix()));
		//currentProgram->loadFloat("lightSz", 0.01f);

		//currentProgram->loadFloat("time", static_cast<GLfloat>(andrick::Timer::getCurrentTime()));

		//pSuzanne->prepModelTransform(alpha, *currentProgram);

		//pSuzanne->getTextureWrapper()->bind();
		//pColRamp->bind(1);
		//currentProgram->loadInt("texture0", pSuzanne->getTextureWrapper()->getTextureUnit());
		//currentProgram->loadInt("colRamp", pColRamp->getTextureUnit());

		//pSuzanne->render(alpha);
		//pSuzanne->getTextureWrapper()->unbind();
		//pColRamp->unbind();

		/*currentProgram = ShaderAssetPack::mspMandlebrotFractalProgram;
		currentProgram->use();
		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());
		pBarrel->prepModelTransform(alpha, *currentProgram);
		pBarrel->getTextureWrapper()->bind();
		pStoneHeightMap->bind(1);
		pStoneNormalMap->bind(2);
		pColRamp->bind();
		currentProgram->loadInt("colRamp", pColRamp->getTextureUnit());
		currentProgram->loadInt("texture0", pBarrel->getTextureWrapper()->getTextureUnit());
		currentProgram->loadInt("texture1", pStoneHeightMap->getTextureUnit());
		currentProgram->loadInt("texture2", pStoneNormalMap->getTextureUnit());
		pBarrel->render(alpha);
		pBarrel->getTextureWrapper()->unbind();
		pStoneHeightMap->unbind();
		pStoneNormalMap->unbind();
		pColRamp->unbind();*/

		//////////////////////////////

		/*currentProgram = ShaderAssetPack::mspLightSourceProgram;
		currentProgram->use();
		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());
		currentProgram->loadVec3("color", 1.0f, 0.7f, 0.5f);
		pPodium->prepModelTransform(alpha, *currentProgram);
		pPodium->render(alpha);
		pPodium2->prepModelTransform(alpha, *currentProgram);
		pPodium2->render(alpha);
		pPodium3->prepModelTransform(alpha, *currentProgram);
		pPodium3->render(alpha);
		pPodium4->prepModelTransform(alpha, *currentProgram);
		pPodium4->render(alpha);
		pPodium5->prepModelTransform(alpha, *currentProgram);
		pPodium5->render(alpha);*/

		///////////////////////// CUBE

		//currentProgram = ShaderAssetPack::mspPomProgram;
		//currentProgram->use();

		//currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		//currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());

		//pCube->prepModelTransform(alpha, *currentProgram);

		//pCube->getTextureWrapper()->bind();
		//pStoneHeightMap->bind(1);
		//pStoneNormalMap->bind(2);
		//currentProgram->loadInt("texture0", pCube->getTextureWrapper()->getTextureUnit());
		//currentProgram->loadInt("texture1", pStoneHeightMap->getTextureUnit());
		//currentProgram->loadInt("texture2", pStoneNormalMap->getTextureUnit());
		//currentProgram->loadVec2("range", 0.9915f, 0.9975f);

		//pCube->render(alpha);
		//pCube->getTextureWrapper()->unbind();
		//pStoneHeightMap->unbind();
		//pStoneNormalMap->unbind();

		///////////////////////// CUBE 2

		//pCube2->prepModelTransform(alpha, *currentProgram);

		//pCube2->getTextureWrapper()->bind();
		//pMetalPlateHeightMap->bind(1);
		//pMetalPlateNormalMap->bind(2);
		//currentProgram->loadInt("texture0", pCube2->getTextureWrapper()->getTextureUnit());
		//currentProgram->loadInt("texture1", pMetalPlateHeightMap->getTextureUnit());
		//currentProgram->loadInt("texture2", pMetalPlateNormalMap->getTextureUnit());
		//currentProgram->loadVec2("range", 0.9315f, 0.9975f);

		//pCube2->render(alpha);
		//pCube2->getTextureWrapper()->unbind();
		//pMetalPlateHeightMap->unbind();
		//pMetalPlateNormalMap->unbind();

		///////////////////////// CUBE 3

		//pCube3->prepModelTransform(alpha, *currentProgram);

		//pCube3->getTextureWrapper()->bind();
		//pMetalGrillHeightMap->bind(1);
		//pMetalGrillNormalMap->bind(2);
		//currentProgram->loadInt("texture0", pCube3->getTextureWrapper()->getTextureUnit());
		//currentProgram->loadInt("texture1", pMetalGrillHeightMap->getTextureUnit());
		//currentProgram->loadInt("texture2", pMetalGrillNormalMap->getTextureUnit());
		//currentProgram->loadVec2("range", 0.815f, 0.9975f);

		//pCube3->render(alpha);
		//pCube3->getTextureWrapper()->unbind();
		//pMetalGrillHeightMap->unbind();
		//pMetalGrillNormalMap->unbind();

		///////////////////////// CUBE 4

		//pCube4->prepModelTransform(alpha, *currentProgram);

		//pCube4->getTextureWrapper()->bind();
		//pBrickworkHeightMap->bind(1);
		//pBrickworkNormalMap->bind(2);
		//currentProgram->loadInt("texture0", pCube4->getTextureWrapper()->getTextureUnit());
		//currentProgram->loadInt("texture1", pBrickworkHeightMap->getTextureUnit());
		//currentProgram->loadInt("texture2", pBrickworkNormalMap->getTextureUnit());
		//currentProgram->loadVec2("range", 0.9915f, 0.9975f);

		//pCube4->render(alpha);
		//pCube4->getTextureWrapper()->unbind();
		//pBrickworkHeightMap->unbind();
		//pBrickworkNormalMap->unbind();

		///////////////////////// CUBE 5

		//pCube5->prepModelTransform(alpha, *currentProgram);

		//pCube5->getTextureWrapper()->bind();
		//pConcreteHeightMap->bind(1);
		//pConcreteNormalMap->bind(2);
		//currentProgram->loadInt("texture0", pCube5->getTextureWrapper()->getTextureUnit());
		//currentProgram->loadInt("texture1", pConcreteHeightMap->getTextureUnit());
		//currentProgram->loadInt("texture2", pConcreteNormalMap->getTextureUnit());
		//currentProgram->loadVec2("range", 0.8975f, 0.9975f);

		//pCube5->render(alpha);
		//pCube5->getTextureWrapper()->unbind();
		//pConcreteHeightMap->unbind();
		//pConcreteNormalMap->unbind();


		////////////////////////////////////////

		/*currentProgram = ShaderAssetPack::mspLightSourceProgram;
		currentProgram->use();
		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());
		currentProgram->loadVec3("color", 1.0f, 1.0f, 1.0f);
		pLight->prepModelTransform(alpha, *currentProgram);
		pLight->render(alpha);
		glDepthFunc(GL_LEQUAL);
		currentProgram = ShaderAssetPack::mspSkyboxProgram;
		currentProgram->use();
		currentProgram->loadMat4("view", GL_FALSE, glm::mat4(glm::mat3(mpCamera->getViewMatrix())));
		currentProgram->loadMat4("projection", GL_FALSE, mpCamera->getProjectionMatrix());
		pCubeMap->bind();
		currentProgram->loadInt("skybox", pCubeMap->getTextureUnit());
		MeshAssetPack::mspCubeMapMesh->render();
		pCubeMap->unbind();*/

		glDepthFunc(GL_LESS);

		andrick::FBOWrapper::renderFBOToFBO(pSceneFBOMultisample, pSceneFBO, andrick::AndrickWindow::getFocusedWindow()->getSize(), andrick::AndrickWindow::getFocusedWindow()->getSize());

		pSceneFBOMultisample->unbind();
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