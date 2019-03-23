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
		//sync();
	}

	void Model::render(const GLdouble& alpha)
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

	Model::ComponentNode::render(const GLdouble& alpha)
	{

	}
}