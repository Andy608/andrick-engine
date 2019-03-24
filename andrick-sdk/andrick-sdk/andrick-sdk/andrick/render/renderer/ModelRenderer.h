#ifndef ANDRICK_MODEL_RENDERER_H_
#define ANDRICK_MODEL_RENDERER_H_

#include "Renderer.h"
#include "../model/Model.h"

namespace andrick
{
	//This class is used for testing mesh rendering, not designed for actual rendering.
	class ModelRenderer : public Renderer
	{
	public:
		//Temp. In the future make this private and only have one of these.
		inline ModelRenderer() {};
		inline virtual ~ModelRenderer() {};

		void render(const GLdouble& alpha, const std::vector<Model*>& models);

	private:
		static const std::string msCLASS_NAME;
	};
}

#endif