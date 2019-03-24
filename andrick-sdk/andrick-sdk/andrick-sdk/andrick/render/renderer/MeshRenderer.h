#ifndef ANDRICK_MESH_RENDERER_H_
#define ANDRICK_MESH_RENDERER_H_

#include "Renderer.h"
#include "../../asset/mesh/Mesh.h"

namespace andrick
{
	//This class is used for testing mesh rendering, not designed for actual rendering.
	class MeshRenderer : public Renderer
	{
	public:
		//Temp. In the future make this private and only have one of these.
		inline MeshRenderer() {};
		inline virtual ~MeshRenderer() {};

		void render(const std::vector<Mesh*>& meshes);

	private:
		static const std::string msCLASS_NAME;
	};
}

#endif