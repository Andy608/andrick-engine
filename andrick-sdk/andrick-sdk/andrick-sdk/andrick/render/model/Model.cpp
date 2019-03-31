#include "Model.h"
#include "../../logger/LoggerMaster.h"
#include <glm/gtc/type_ptr.hpp>

namespace andrick
{
	const std::string Model::msCLASS_NAME = "Model";

	Model::Model(Mesh* pMesh, Transform* parentTransform) :
		mpTransform(new Transform(glm::vec3(), glm::vec3(), glm::vec3(1.0f))),
		mpParentTransform(parentTransform),
		mpMesh(pMesh),
		mpTextureWrapper(nullptr)
	{
		//TODO: Added a default asset pack for andrick engine and make add a default texture for models
	}

	Model::~Model()
	{
		delete mpTransform;
		mpTransform = nullptr;

		if (mpTextureWrapper)
		{
			delete mpTextureWrapper;
			mpTextureWrapper = nullptr;
		}
	}

	void Model::updateTransform()
	{
		mpTransform->sync();
	}

	void Model::update(const GLdouble& deltaTime)
	{
		updateTransform();
	}

	void Model::prepModelTransform(const GLdouble& alpha, const ShaderProgram& currentShader)
	{
		mpTransform->lerp(alpha);

		glm::mat4 pParentTransformation;

		if (mpParentTransform)
		{
			mpParentTransform->lerp(alpha);
			pParentTransformation = mpParentTransform->getTransformationMat();
		}
		else
		{
			pParentTransformation = glm::mat4(1.0f);
		}

		//TODO: Fix. This doesn't work right now.
		glm::mat4 modelSpace = mpTransform->getTransformationMat() * pParentTransformation;
		currentShader.loadMat4("transformMatrix", GL_FALSE, modelSpace);
	}

	void Model::render(const GLdouble& alpha)
	{
		mpMesh->render();
	}

	void Model::setImage(Image& image,
		const TextureWrapper::EnumWrapStyle& wrapStyleS, const TextureWrapper::EnumWrapStyle& wrapStyleT,
		const TextureWrapper::EnumMinFilter& minFilter, const TextureWrapper::EnumMagFilter& magFilter)
	{
		if (!image.isLoaded())
		{
			LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, "The image: " + image.getID() + " is not loaded! Either you forgot to load it, or there was an error while loading the image.");
			return;
		}

		if (!mpTextureWrapper)
		{
			mpTextureWrapper = new TextureWrapper(image, wrapStyleS, wrapStyleT, minFilter, magFilter, GL_TRUE);
		}
		else
		{
			mpTextureWrapper->setProperties(image.getWidth(), image.getHeight(), image.getPixelData(), EnumTextureType::TEXTURE_2D, GL_TRUE, EnumInternalFormatType::RGBA, EnumDataFormat::RGBA_FORMAT, EnumDataType::UNSIGNED_BYTE, wrapStyleS, wrapStyleT, minFilter, magFilter);
		}

		mpTextureWrapper->generateGLTexture();
	}

	/* Component Node */

	//Model::ComponentNode::ComponentNode(Mesh* pMesh, ComponentNode* pParent) :
	//	mpMesh(pMesh),
	//	mParentComponent(pParent),
	//	mpMeshTransform(new Transform(glm::vec3(), glm::vec3(), glm::vec3(1.0f)))
	//{

	//}

	//Model::ComponentNode::~ComponentNode()
	//{
	//	delete mpMeshTransform;
	//	mpMeshTransform = nullptr;
	//}

	//void Model::ComponentNode::render(const GLdouble& alpha, const glm::mat4& modelTransform, const ShaderProgram& activeShader)
	//{
	//	mpMeshTransform->lerp(alpha);

	//	glm::mat4 parentTransform;

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

	//	glm::mat4 modelSpace = modelTransform * parentTransform * mpMeshTransform->getTransformationMat();

	//	activeShader.loadMat4("transformMatrix", GL_FALSE, glm::value_ptr(modelSpace));
	//	mpMesh->render(/*alpha*/);
	//}
}