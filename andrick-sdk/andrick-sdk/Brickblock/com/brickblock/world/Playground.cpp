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

	andrick::Model* pFloor_Pom;
	andrick::Model* pFloor_Phong;
	andrick::Model* pFloor_Julia;
	andrick::Model* pFloor_Mandelbrot;

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

		//Floor init
		pFloor_Pom = new andrick::Model(MeshAssetPack::mspQuadMesh);
		pFloor_Pom->setImage(*ImageAssetPack::mspDefaultImage);
		pFloor_Pom->getTransform()->setRotation(-90.0f, 0.0f, 0.0f);
		pFloor_Pom->getTransform()->setScale(5.0f, 5.0f, 5.0f);

		pFloor_Phong = new andrick::Model(MeshAssetPack::mspQuadMesh);
		pFloor_Phong->setImage(*ImageAssetPack::mspLoveImage);
		pFloor_Phong->getTransform()->setRotation(-90.0f, 0.0f, 180.0f);
		pFloor_Phong->getTransform()->setScale(5.0f, 5.0f, 5.0f);
		pFloor_Phong->getTransform()->setPosition(15.0f, 0.0f, 0.0f);

		pFloor_Julia = new andrick::Model(MeshAssetPack::mspQuadMesh);
		pFloor_Julia->setImage(*ImageAssetPack::mspLoveImage);
		pFloor_Julia->getTransform()->setRotation(-90.0f, 0.0f, 0.0f);
		pFloor_Julia->getTransform()->setScale(5.0f, 5.0f, 5.0f);
		pFloor_Julia->getTransform()->setPosition(0.0f, 0.0f, 15.0f);

		pFloor_Mandelbrot = new andrick::Model(MeshAssetPack::mspQuadMesh);
		pFloor_Mandelbrot->setImage(*ImageAssetPack::mspLoveImage);
		pFloor_Mandelbrot->getTransform()->setRotation(-90.0f, 0.0f, 0.0f);
		pFloor_Mandelbrot->getTransform()->setScale(5.0f, 5.0f, 5.0f);
		pFloor_Mandelbrot->getTransform()->setPosition(15.0f, 0.0f, 15.0f);

		//Light init
		pLight = new andrick::Model(MeshAssetPack::mspTestMesh);
		pLight->getTransform()->setPosition(13.0f, 2.0f, -3.0f);

		//Suzanne init
		pSuzanne = new andrick::Model(MeshAssetPack::mspSuzanneMesh);
		pSuzanne->setImage(*ImageAssetPack::mspDefaultImage,
			andrick::TextureWrapper::EnumWrapStyle::REPEAT, andrick::TextureWrapper::EnumWrapStyle::REPEAT,
			andrick::TextureWrapper::EnumMinFilter::NEAREST_MIPMAP_NEAREST, andrick::TextureWrapper::EnumMagFilter::NEAREST);

		//Full Screen Quad init
		pFSQ = new andrick::Model(MeshAssetPack::mspQuadMesh);

		//Basic model tracking
		models.push_back(pFloor_Pom);
		models.push_back(pFloor_Phong);
		models.push_back(pFloor_Julia);
		models.push_back(pFloor_Mandelbrot);
		models.push_back(pLight);
		models.push_back(pSuzanne);
		models.push_back(pFSQ);

		//Texture init
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

		//Basic texture tracking
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

		//Current pom details
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

		//Init fbo with multisample
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

		//Init cubemap
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
		//Update all tracked models
		GLuint i;
		for (i = 0; i < models.size(); ++i)
		{
			models.at(i)->update(deltaTime);
		}

		//Keep track of persistent time for cos/sin functions
		static GLfloat time = 0.0f;
		time += (60.0f * static_cast<GLfloat>(deltaTime));

		//Update the relevant demos
		updatePomDemo(deltaTime, time, 3.0f);
		updatePhongDemo(deltaTime, time);
	}

	void Playground::render(const GLdouble& alpha)
	{
		//Lerp the camera position so it's smooth between updates
		mpCamera->lerp(alpha);

		//Render to fbo
		pSceneFBOMultisample->bind();
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(andrick::ModelRenderer::EnumCullType::FRONT_ONLY, andrick::ModelRenderer::EnumDrawType::FILL);

		//Setting up the shader program
		andrick::ShaderProgram* currentProgram;

		//Render the demos
		renderPomDemo(alpha, currentProgram);
		renderPhongDemo(alpha, currentProgram);
		renderJuliaDemo(alpha, currentProgram);
		renderMandelbrotDemo(alpha, currentProgram);

		//Transfer fbo data to prep for drawing
		glDepthFunc(GL_LESS);
		andrick::FBOWrapper::renderFBOToFBO(pSceneFBOMultisample, pSceneFBO, andrick::AndrickWindow::getFocusedWindow()->getSize(), andrick::AndrickWindow::getFocusedWindow()->getSize());

		//Unbind
		pSceneFBOMultisample->unbind();
		glDisable(GL_DEPTH_TEST);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw the fbo on the full screen quad
		currentProgram = ShaderAssetPack::mspTextureProgram;
		currentProgram->use();

		pFBOSceneRenderTexture->bind();

		//Load texture to shader.
		currentProgram->loadInt("screenTexture", pFBOSceneRenderTexture->getTextureUnit());

		//Render
		pFSQ->render(alpha);

		//Unbind
		pFBOSceneRenderTexture->unbind();
		glDisable(GL_DEPTH_TEST);
		glActiveTexture(0);
	}

	void Playground::updatePomDemo(const double& deltaTime, const double& time, const float& switchTime)
	{
		static GLfloat counter = 0.0f;
		static GLint currentIndex = 0;
		counter += deltaTime;

		//Switch floor type every "switchTime" seconds.
		if (counter > switchTime)
		{
			counter = 0.0f;
			currentIndex = (currentIndex + 1) % pomTextureMaps.size();

			//Swap the current pom data for the next pom data.
			pCurrentHeightMap = pomTextureMaps.at(currentIndex)[0];
			pCurrentNormalMap = pomTextureMaps.at(currentIndex)[1];
			pCurrentPomMin = pomRangeMaps.at(currentIndex)[0];
			pCurrentPomMax = pomRangeMaps.at(currentIndex)[1];
		}

		pFloor_Pom->getTransform()->addRotation(glm::vec3(0.0f, 0.0f, 10.0f * (float)deltaTime));
	}

	void Playground::updatePhongDemo(const double& deltaTime, const double& time)
	{
		//Motion setup
		const GLfloat x = (3.0f * (cos(andrick::MathHelper::toRadians(time * 0.5f))));
		const GLfloat z = (3.0f * (sin(andrick::MathHelper::toRadians(time * 0.5f))));

		//Update position and rotation
		pSuzanne->getTransform()->setPosition(15.0f, (x * 0.5f) + 5.0f, 0.0f);
		pLight->getTransform()->setPosition(15.0f + x, 5.0f, z);
		pLight->getTransform()->addRotation(0.0f, 90.0f * (GLfloat)deltaTime, 0.0f);
	}

	void Playground::renderPomDemo(const double& alpha, andrick::ShaderProgram*& currentProgram)
	{
		currentProgram = ShaderAssetPack::mspPomProgram;

		//Setting up the shader program
		currentProgram->use();
		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());
		currentProgram->loadFloat("time", static_cast<GLfloat>(andrick::Timer::getCurrentTime()));

		//Bind/load model stuff to shader program
		pFloor_Pom->prepModelTransform(alpha, *currentProgram);
		pFloor_Pom->getTextureWrapper()->bind(0);
		pCurrentHeightMap->bind(1);
		pCurrentNormalMap->bind(2);
		currentProgram->loadInt("texture0", pFloor_Pom->getTextureWrapper()->getTextureUnit());
		currentProgram->loadInt("texture1", pCurrentHeightMap->getTextureUnit());
		currentProgram->loadInt("texture2", pCurrentNormalMap->getTextureUnit());
		currentProgram->loadVec2("range", pCurrentPomMin, pCurrentPomMax);

		//Render the models
		pFloor_Pom->render(alpha);

		//Unbind
		pFloor_Pom->getTextureWrapper()->unbind();
		pCurrentHeightMap->unbind();
		pCurrentNormalMap->unbind();
	}

	void Playground::renderPhongDemo(const double& alpha, andrick::ShaderProgram*& currentProgram)
	{
		//Render Floor and Suzanne using the phong shader
		currentProgram = ShaderAssetPack::mspPhongShadingProgram;
		currentProgram->use();

		//Loading general stuff to shader program
		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());
		currentProgram->loadVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));
		currentProgram->loadVec3("lightPos", pLight->getTransform()->getLerpedPosition());
		currentProgram->loadVec3("viewPos", mpCamera->getTransform()->getLerpedPosition());
		currentProgram->loadMat3("normalMatrix", GL_FALSE, andrick::MathHelper::createNormalMat(pFloor_Phong->getTransform()->getTransformationMat(), mpCamera->getViewMatrix()));
		currentProgram->loadFloat("lightSz", 0.01f);
		currentProgram->loadFloat("time", static_cast<GLfloat>(andrick::Timer::getCurrentTime()));

		//Calculate parent/child transforms
		pFloor_Phong->prepModelTransform(alpha, *currentProgram);

		//Bind/load model stuff to shader program
		pFloor_Phong->getTextureWrapper()->bind();
		currentProgram->loadInt("texture0", pFloor_Phong->getTextureWrapper()->getTextureUnit());

		//Render the models
		pFloor_Phong->render(alpha);

		//Unbind
		pFloor_Phong->getTextureWrapper()->unbind();

		//Swap out the floor's normal matrix with suzanne's normal matrix.
		currentProgram->loadMat3("normalMatrix", GL_FALSE, andrick::MathHelper::createNormalMat(pSuzanne->getTransform()->getTransformationMat(), mpCamera->getViewMatrix()));

		//Calculate parent/child transforms
		pSuzanne->prepModelTransform(alpha, *currentProgram);

		//Bind/load model stuff to shader program
		pSuzanne->getTextureWrapper()->bind();
		pColRamp->bind(1);
		currentProgram->loadInt("texture0", pSuzanne->getTextureWrapper()->getTextureUnit());

		//Render the models
		pSuzanne->render(alpha);

		//Unbind
		pSuzanne->getTextureWrapper()->unbind();

		//Render light
		currentProgram = ShaderAssetPack::mspLightSourceProgram;
		currentProgram->use();

		//Bind/load model stuff to shader program
		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());
		currentProgram->loadVec3("color", 1.0f, 1.0f, 1.0f);

		//Calculate parent/child transforms
		pLight->prepModelTransform(alpha, *currentProgram);

		//Render the models
		pLight->render(alpha);

		//Render skybox
		glDepthFunc(GL_LEQUAL);
		currentProgram = ShaderAssetPack::mspSkyboxProgram;
		currentProgram->use();

		//Loading general stuff to shader program
		currentProgram->loadMat4("view", GL_FALSE, glm::mat4(glm::mat3(mpCamera->getViewMatrix())));
		currentProgram->loadMat4("projection", GL_FALSE, mpCamera->getProjectionMatrix());
		
		//Bind/load cubemap to shader program
		pCubeMap->bind();
		currentProgram->loadInt("skybox", pCubeMap->getTextureUnit());

		//Render the models
		MeshAssetPack::mspCubeMapMesh->render();
		
		//Unbind
		pCubeMap->unbind();
	}

	void Playground::renderJuliaDemo(const double& alpha, andrick::ShaderProgram*& currentProgram)
	{
		//Setting up the shader program
		currentProgram = ShaderAssetPack::mspJuliaFractalProgram;
		currentProgram->use();

		//Load general stuff to shader program
		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());
		currentProgram->loadFloat("time", static_cast<GLfloat>(andrick::Timer::getCurrentTime()));

		//Calculate parent/child transforms
		pFloor_Julia->prepModelTransform(alpha, *currentProgram);

		//Bind/load texture to shader program
		pFloor_Julia->getTextureWrapper()->bind(0);
		pColRamp->bind(1);
		currentProgram->loadInt("texture0", pFloor_Julia->getTextureWrapper()->getTextureUnit());
		currentProgram->loadInt("colRamp", pColRamp->getTextureUnit());

		//Render
		pFloor_Julia->render(alpha);

		//Unbind
		pFloor_Julia->getTextureWrapper()->unbind();
		pColRamp->unbind();
	}

	void Playground::renderMandelbrotDemo(const double& alpha, andrick::ShaderProgram*& currentProgram)
	{
		//Setting up the shader program
		currentProgram = ShaderAssetPack::mspMandlebrotFractalProgram;
		currentProgram->use();

		//Load general stuff to shader program
		currentProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrix());
		currentProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrix());

		//Calculate parent/child transforms
		pFloor_Mandelbrot->prepModelTransform(alpha, *currentProgram);

		//Bind/load texture to shader program
		pFloor_Mandelbrot->getTextureWrapper()->bind(0);
		currentProgram->loadInt("texture0", pFloor_Mandelbrot->getTextureWrapper()->getTextureUnit());

		//Render
		pFloor_Mandelbrot->render(alpha);
		
		//Unbind
		pFloor_Mandelbrot->getTextureWrapper()->unbind();
	}
}