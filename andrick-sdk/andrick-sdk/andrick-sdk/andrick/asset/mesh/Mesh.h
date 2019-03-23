#ifndef ANDRICK_MESH_H_
#define ANDRICK_MESH_H_

#include "../Asset.h"
#include "../../filesystem/path/file/FileLocation.h"
#include "../../render/wrapper/vao/VAOWrapper.h"
#include "../../render/wrapper/vbo/VBOWrapper.h"
#include "../../render/wrapper/ebo/EBOWrapper.h"
#include "../../render/IRenderable.h"
#include <vector>

namespace andrick
{
	class Mesh : public Asset
	{
		friend class MeshFactory;

	public:
		Mesh(const std::string& assetID, FileLocation meshDataLocation);
		virtual ~Mesh();

		virtual GLboolean load() override;
		virtual GLboolean unload() override;

		virtual void render(/*const GLdouble& alpha*/) const;

		const VBOWrapper* getVBO(VBOWrapper::EnumBufferType type) const;

	private:
		static const std::string msCLASS_NAME;

		VAOWrapper* mVAO;
		std::vector<VBOWrapper*> mVBOs;
		EBOWrapper* mEBO;

		FileLocation mMeshDataLocation;

		virtual void buildMesh();

		void addBufferData(VBOWrapper* bufferData);
		void clearBufferData();
	};
}

#endif