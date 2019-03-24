#ifndef ANDRICK_MODEL_H_
#define ANDRICK_MODEL_H_

#include "../../memory/TrackableObject.h"
#include "../../memory/NonCopyable.h"

#include "../../asset/mesh/Mesh.h"
#include "../../util/math/Transform.h"
#include "../../asset/texture/Texture.h"
#include "../wrapper/texture/TextureWrapper.h"
#include "../../asset/shader/ShaderProgram.h"

namespace andrick
{
	class Model : public TrackableObject, NonCopyable
	{
	public:
		Model();
		virtual ~Model();

		virtual void sync() = 0;

		virtual void update(const GLdouble& deltaTime);
		virtual void render(const GLdouble& alpha, const ShaderProgram& activeShader);

		inline const TextureWrapper* getTextureWrapper() const { return mpTextureWrapper; }

		void setTexture(Texture& texture,
			const TextureWrapper::EnumWrapStyle& wrapStyleS, const TextureWrapper::EnumWrapStyle& wrapStyleT,
			const TextureWrapper::EnumMinFilter& minFilter, const TextureWrapper::EnumMagFilter& magFilter);

	protected:

		//In the future make this a true component where you can add them. I dont wanna have to make a new object for each new model.
		struct ComponentNode
		{
			const Mesh* mpMesh;
			Transform* mpMeshTransform;
			ComponentNode* mParentComponent;

			ComponentNode(Mesh* pMesh, ComponentNode* parent = nullptr);
			~ComponentNode();

			void render(const GLdouble& alpha, const glm::mat4& modelTransform, const ShaderProgram& activeShader);
		};

		Transform* mpModelTransform;
		TextureWrapper* mpTextureWrapper;

	private:
		static const std::string msCLASS_NAME;
	};
}

#endif