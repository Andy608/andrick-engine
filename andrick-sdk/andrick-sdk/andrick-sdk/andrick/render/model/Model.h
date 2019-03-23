#ifndef ANDRICK_MODEL_H_
#define ANDRICK_MODEL_H_

#include "../../memory/TrackableObject.h"
#include "../../memory/NonCopyable.h"

#include "../../asset/mesh/Mesh.h"
#include "../../util/math/Transform.h"
#include "../../asset/texture/Texture.h"
#include "../wrapper/texture/TextureWrapper.h"

namespace andrick
{
	class Model : public TrackableObject, NonCopyable
	{
	public:
		Model();
		virtual ~Model();

		virtual void update(const GLdouble& deltaTime);
		virtual void render(const GLdouble& alpha);

		inline const TextureWrapper* getTextureWrapper() const { return mpTextureWrapper; }

		void setTexture(Texture& texture,
			const TextureWrapper::EnumWrapStyle& wrapStyleS, const TextureWrapper::EnumWrapStyle& wrapStyleT,
			const TextureWrapper::EnumMinFilter& minFilter, const TextureWrapper::EnumMagFilter& magFilter);

	protected:
		struct ComponentNode
		{
			const Mesh* mpMesh;
			Transform* mpMeshTransform;
			ComponentNode* mParentComponent;

			ComponentNode(Mesh* pMesh, ComponentNode* parent = nullptr);
			~ComponentNode();

			void render(const GLdouble& alpha, const glm::mat4& modelTransform);
		};

		Transform* mpModelTransform;
		TextureWrapper* mpTextureWrapper;

	private:
		static const std::string msCLASS_NAME;
	};
}

#endif