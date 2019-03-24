#include "Model.h"
#include "../../logger/LoggerMaster.h"
#include <glm/gtc/type_ptr.hpp>

namespace andrick
{
	const std::string Model::msCLASS_NAME = "Model";

	Model::Model() :
		mpModelTransform(new Transform(glm::vec3(), glm::vec3(), glm::vec3(1.0f))),
		mpTextureWrapper(nullptr)
	{

	}

	Model::~Model()
	{
		delete mpModelTransform;
		mpModelTransform = nullptr;

		if (mpTextureWrapper)
		{
			delete mpTextureWrapper;
			mpTextureWrapper = nullptr;
		}
	}

	void Model::update(const GLdouble& deltaTime)
	{
		sync();
	}

	void Model::render(const GLdouble& alpha, const ShaderProgram& activeShader)
	{
		mpModelTransform->lerp(alpha);
	}

	void Model::setTexture(Texture& texture,
		const TextureWrapper::EnumWrapStyle& wrapStyleS, const TextureWrapper::EnumWrapStyle& wrapStyleT,
		const TextureWrapper::EnumMinFilter& minFilter, const TextureWrapper::EnumMagFilter& magFilter)
	{
		if (!texture.isLoaded())
		{
			LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, "The texture: " + texture.getID() + " is not loaded! Either you forgot to load it, or there was an error while loading the texture.");
			return;
		}

		if (!mpTextureWrapper)
		{
			mpTextureWrapper = new TextureWrapper(texture);
		}
		else
		{
			mpTextureWrapper->setTexture(texture);
		}

		mpTextureWrapper->setWrapStyleS(wrapStyleS);
		mpTextureWrapper->setWrapStyleT(wrapStyleT);
		mpTextureWrapper->setMinifyFilter(minFilter);
		mpTextureWrapper->setMagnifyFilter(magFilter);
	}

	/* Component Node */

	Model::ComponentNode::ComponentNode(Mesh* pMesh, ComponentNode* pParent) :
		mpMesh(pMesh),
		mParentComponent(pParent),
		mpMeshTransform(new Transform(glm::vec3(), glm::vec3(), glm::vec3(1.0f)))
	{

	}

	Model::ComponentNode::~ComponentNode()
	{
		delete mpMeshTransform;
		mpMeshTransform = nullptr;
	}

	void Model::ComponentNode::render(const GLdouble& alpha, const glm::mat4& modelTransform, const ShaderProgram& activeShader)
	{
		mpMeshTransform->lerp(alpha);

		glm::mat4 parentTransform;

		if (mParentComponent)
		{
			Transform* pParent = mParentComponent->mpMeshTransform;
			pParent->lerp(alpha);
			parentTransform = pParent->getTransformationMat();
		}
		else
		{
			parentTransform = glm::mat4(1.0f);
		}

		glm::mat4 modelSpace = modelTransform * parentTransform * mpMeshTransform->getTransformationMat();

		//BBLogger::logDebug("Model.cpp", "MODEL TRANSFORM: " + MatrixUtil::to_string(modelTransform), Logger::EnumLogLocation::CONSOLE);

		activeShader.loadMat4("transformMatrix", GL_FALSE, glm::value_ptr(modelSpace));
		mpMesh->render(/*alpha*/);
	}
}