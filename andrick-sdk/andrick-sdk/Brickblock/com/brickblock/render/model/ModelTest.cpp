//#include "ModelTest.h"
//#include <andrick/util/math/Transform.h>
//#include <andrick/util/math/MathHelper.h>
//#include <andrick/asset/AssetManager.h>
//#include <andrick/asset/mesh/Mesh.h>
//#include <andrick/logger/LoggerMaster.h>
//#include "../../asset/MeshAssetPack.h"
//
//namespace bb
//{
//	ModelTest::ModelTest()
//	{
//		andrick::Mesh* barrel = MeshAssetPack::mspBarrelMesh;
//		andrick::Mesh* plane = MeshAssetPack::mspQuadMesh;
//		mTest = new ComponentNode(barrel, nullptr);
//		mOrbit = new ComponentNode(barrel, mTest);
//		mFloor = new ComponentNode(plane, mTest);
//
//		setTexture(*MeshAssetPack::mspBarrelTexture,
//			andrick::TextureWrapper::EnumWrapStyle::CLAMP_TO_BORDER, andrick::TextureWrapper::EnumWrapStyle::CLAMP_TO_BORDER, 
//			andrick::TextureWrapper::EnumMinFilter::LINEAR_MIPMAP_LINEAR, andrick::TextureWrapper::EnumMagFilter::LINEAR);
//
//		//mModelTransform->addPosition(1.0, 0.0, 0.0);
//		//mTest->mpMeshTransform->addPosition(2.0, 0.0, 0.0);
//
//		andrick::Transform* orbitTransform = mOrbit->mpMeshTransform;
//		orbitTransform->setPosition(0.0f, 0.5f, 0.0f);
//		orbitTransform->setScale(0.5, 0.5, 0.5);
//
//		orbitTransform->mPosition.x = (3.0f * (cos(andrick::MathHelper::toRadians(0.0f))));
//		orbitTransform->mPosition.z = (3.0f * (sin(andrick::MathHelper::toRadians(0.0f))));
//
//		andrick::Transform* floorTransform = mFloor->mpMeshTransform;
//		floorTransform->setPosition(0.0f, -0.5f, 0.0f);
//		floorTransform->setScale(2.0f, 2.0f, 2.0f);
//
//		sync();
//	}
//
//	ModelTest::~ModelTest()
//	{
//		delete mTest;
//		delete mOrbit;
//		delete mFloor;
//	}
//
//	void ModelTest::sync()
//	{
//		mpModelTransform->sync();
//		mTest->mpMeshTransform->sync();
//		mOrbit->mpMeshTransform->sync();
//		mFloor->mpMeshTransform->sync();
//	}
//
//	void ModelTest::update(const GLdouble& deltaTime)
//	{
//		Model::update(deltaTime);
//
//		andrick::Transform* orbitTransform = mOrbit->mpMeshTransform;
//
//		static GLfloat time = 0.0f;
//		time += (10.0f * static_cast<GLfloat>(deltaTime));
//
//		orbitTransform->mPosition.x = (3.0f * (cos(andrick::MathHelper::toRadians(time))));
//		orbitTransform->mPosition.z = (3.0f * (sin(andrick::MathHelper::toRadians(time))));
//
//		//orbitTransform->mRotation.y += (30.0f * deltaTime * (cos(MathHelper::toRadians(time))));
//		orbitTransform->addRotation(0.0f, static_cast<GLfloat>(100.0f * deltaTime), 0.0f);
//
//		//mModelTransform->mPosition.y = (3.0f * (sin(MathHelper::toRadians(time))));
//		//mTest->mMeshTransform->mRotation.z += (2.0f * deltaTime);
//
//		//mModelTransform->mScale += (5.0f * deltaTime * (sin(MathHelper::toRadians(time))));
//	}
//
//	void ModelTest::render(const GLdouble& alpha, const andrick::ShaderProgram& activeShader)
//	{
//		Model::render(alpha, activeShader);
//
//		mTest->render(alpha, mpModelTransform->getTransformationMat(), activeShader);
//		mOrbit->render(alpha, mpModelTransform->getTransformationMat(), activeShader);
//		mFloor->render(alpha, mpModelTransform->getTransformationMat(), activeShader);
//	}
//}
//
//void Model::ComponentNode::render(const GLdouble& alpha, const glm::mat4& modelTransform, const ShaderProgram& activeShader)
//{
//	mpMeshTransform->lerp(alpha);
//
//	glm::mat4 parentTransform;
//
//	if (mParentComponent)
//	{
//		Transform* pParent = mParentComponent->mpMeshTransform;
//		pParent->lerp(alpha);
//		parentTransform = pParent->getTransformationMat();
//	}
//	else
//	{
//		parentTransform = glm::mat4(1.0f);
//	}
//
//	glm::mat4 modelSpace = modelTransform * parentTransform * mpMeshTransform->getTransformationMat();
//
//	activeShader.loadMat4("transformMatrix", GL_FALSE, glm::value_ptr(modelSpace));
//	mpMesh->render(/*alpha*/);
//}