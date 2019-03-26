#ifndef ANDRICK_MODEL_H_
#define ANDRICK_MODEL_H_

#include "../../memory/TrackableObject.h"
#include "../../memory/NonCopyable.h"

#include "../../asset/mesh/Mesh.h"
#include "../../util/math/Transform.h"
#include "../wrapper/texture/TextureWrapper.h"
#include "../../asset/image/Image.h"
#include "../../asset/shader/ShaderProgram.h"

#include <set>

namespace andrick
{
	class Model : public TrackableObject, NonCopyable
	{
	public:
		Model(Mesh* pMesh, Transform* parentTransform = nullptr);
		virtual ~Model();

		virtual void update(const GLdouble& deltaTime);

		//Loads the model's transform to the shader
		virtual void prepModelTransform(const GLdouble& alpha, const ShaderProgram& currentShader);
		//Load up other variables to your shader between these two method calls
		//Call this to render model
		virtual void render(const GLdouble& alpha);

		inline TextureWrapper* getTextureWrapper() const { return mpTextureWrapper; }
		inline Transform* getTransform() const { return mpTransform; };
		inline void setParent(Transform* pParentTransform) { mpParentTransform = pParentTransform; }

		//Update the previous transform values to equal the current transform values
		//so the next frame can use the updated values for lerping.
		virtual void updateTransform();

		void setImage(Image& image,
			const TextureWrapper::EnumWrapStyle& wrapStyleS = TextureWrapper::EnumWrapStyle::CLAMP_TO_BORDER, 
			const TextureWrapper::EnumWrapStyle& wrapStyleT = TextureWrapper::EnumWrapStyle::CLAMP_TO_BORDER,
			const TextureWrapper::EnumMinFilter& minFilter = TextureWrapper::EnumMinFilter::LINEAR_MIPMAP_LINEAR, 
			const TextureWrapper::EnumMagFilter& magFilter = TextureWrapper::EnumMagFilter::LINEAR_MAG);

	protected:
		////In the future make this a true component where you can add them. I dont wanna have to make a new object for each new model.
		//struct ComponentNode
		//{
		//	const Mesh* mpMesh;
		//	Transform* mpMeshTransform;
		//	ComponentNode* mParentComponent;

		//	ComponentNode(Mesh* pMesh, ComponentNode* parent = nullptr);
		//	~ComponentNode();

		//	void render(const GLdouble& alpha, const glm::mat4& modelTransform, const ShaderProgram& activeShader);
		//};

		Transform* mpTransform;

		//The parent is responsible for deleting their own transform.
		Transform* mpParentTransform;
		//std::set<Transform*> mpChildTransforms;

		TextureWrapper* mpTextureWrapper;

		Mesh* mpMesh;

	private:
		static const std::string msCLASS_NAME;
	};
}

#endif