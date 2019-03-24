#include "ModelTest.h"
#include <andrick/util/math/Transform.h>
#include <andrick/util/math/MathHelper.h>
#include <andrick/asset/AssetManager.h>
#include <andrick/asset/mesh/Mesh.h>
#include <andrick/logger/LoggerMaster.h>
#include "../../asset/ShaderAssetPack.h"

namespace bb
{
	ModelTest::ModelTest()
	{
		andrick::Mesh* mesh = ShaderAssetPack::mspTestMesh;
		mTest = new ComponentNode(mesh, nullptr);
		mOrbit = new ComponentNode(mesh, mTest);

		//mModelTransform->addPosition(1.0, 0.0, 0.0);
		//mTest->mpMeshTransform->addPosition(2.0, 0.0, 0.0);

		andrick::Transform* orbitTransform = mOrbit->mpMeshTransform;
		orbitTransform->setPosition(0.0f, 0.5f, 0.0f);
		orbitTransform->setScale(0.5, 0.5, 0.5);

		orbitTransform->mPosition.x = (3.0f * (cos(andrick::MathHelper::toRadians(0.0f))));
		orbitTransform->mPosition.z = (3.0f * (sin(andrick::MathHelper::toRadians(0.0f))));

		sync();
	}

	ModelTest::~ModelTest()
	{
		delete mTest;
		delete mOrbit;
	}

	void ModelTest::sync()
	{
		mpModelTransform->sync();
		mTest->mpMeshTransform->sync();
		mOrbit->mpMeshTransform->sync();
	}

	void ModelTest::update(const GLdouble& deltaTime)
	{
		Model::update(deltaTime);

		andrick::Transform* orbitTransform = mOrbit->mpMeshTransform;

		static GLdouble time = 0.0f;
		time += (10.0f * deltaTime);

		orbitTransform->mPosition.x = (3.0f * (cos(andrick::MathHelper::toRadians(time))));
		orbitTransform->mPosition.z = (3.0f * (sin(andrick::MathHelper::toRadians(time))));

		//orbitTransform->mRotation.y += (30.0f * deltaTime * (cos(MathHelper::toRadians(time))));
		orbitTransform->addRotation(0.0f, static_cast<GLfloat>(100.0f * deltaTime), 0.0f);

		//mModelTransform->mPosition.y = (3.0f * (sin(MathHelper::toRadians(time))));
		//mTest->mMeshTransform->mRotation.z += (2.0f * deltaTime);

		//mModelTransform->mScale += (5.0f * deltaTime * (sin(MathHelper::toRadians(time))));
	}

	void ModelTest::render(const GLdouble& alpha, const andrick::ShaderProgram& activeShader)
	{
		Model::render(alpha, activeShader);

		mTest->render(alpha, mpModelTransform->getTransformationMat(), activeShader);
		mOrbit->render(alpha, mpModelTransform->getTransformationMat(), activeShader);
	}
}