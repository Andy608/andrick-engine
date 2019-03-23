#include "Mesh.h"
#include "../../logger/LoggerMaster.h"
#include "MeshFactory.h"

namespace andrick
{
	const std::string Mesh::msCLASS_NAME = "Mesh";

	Mesh::Mesh(const std::string& assetID, FileLocation meshDataLocation) :
		Asset(assetID), mMeshDataLocation(meshDataLocation)
	{

	}

	Mesh::~Mesh()
	{
		if (mIsLoaded)
		{
			unload();
		}
	}

	GLboolean Mesh::load()
	{
		if (!mIsLoaded)
		{
			MeshFactory::extractMeshDataFromFile(*this);
		}

		return mIsLoaded;
	}

	GLboolean Mesh::unload()
	{
		if (mIsLoaded)
		{
			clearBufferData();
			delete mVAO;
			delete mEBO;
			mIsLoaded = GL_FALSE;
		}

		return (mIsLoaded == GL_FALSE);
	}

	void Mesh::render(/*const GLdouble& alpha*/) const
	{
		mVAO->bind();
		mEBO->bind();
		glDrawElements(GL_TRIANGLES, mEBO->getIndiceCount(), GL_UNSIGNED_INT, 0);
		mEBO->unbind();
		mVAO->unbind();
	}

	void Mesh::buildMesh()
	{
		mVAO->bind();
		mEBO->bind();

		GLuint i;
		for (i = 0; i < mVBOs.size(); ++i)
		{
			VBOWrapper* currentVBO = mVBOs.at(i);
			mVAO->bindVBOToVAO(i, currentVBO);
		}

		mEBO->unbind();
		mVAO->unbind();
	}

	void Mesh::addBufferData(VBOWrapper* bufferData)
	{
		mVBOs.push_back(bufferData);
	}

	void Mesh::clearBufferData()
	{
		auto iter = mVBOs.begin();
		for (; iter != mVBOs.end(); ++iter)
		{
			delete *iter;
		}

		mVBOs.clear();
	}

	const VBOWrapper* Mesh::getVBO(VBOWrapper::EnumBufferType type) const
	{
		auto iter = mVBOs.begin();
		for (; iter != mVBOs.end(); ++iter)
		{
			VBOWrapper* vbo = *iter;
			if (vbo->mBUFFER_TYPE == type)
			{
				return vbo;
			}
		}

		return nullptr;
	};
}