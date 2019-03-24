#include "ModelRenderer.h"
#include "../../logger/LoggerMaster.h"

namespace andrick
{
	const std::string ModelRenderer::msCLASS_NAME = "ModelRenderer";

	void ModelRenderer::render(const GLdouble& alpha, const std::vector<Model*>& models)
	{
		if (!mpShaderProgram)
		{
			andrick::LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "A shaderprogram is not assigned. Unable to render!");
			return;
		}

		if (!mpCamera)
		{
			andrick::LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "A camera is not assigned. Unable to render!");
			return;
		}

		glPolygonMode(mCullType, mDrawType);

		glEnable(GL_DEPTH_TEST);

		mpShaderProgram->use();

		mpShaderProgram->loadMat4("viewMatrix", GL_FALSE, mpCamera->getViewMatrixPtr());
		mpShaderProgram->loadMat4("projectionMatrix", GL_FALSE, mpCamera->getProjectionMatrixPtr());

		auto iter = models.begin();
		for (; iter != models.end(); ++iter)
		{
			Model* currentObj = *iter;

			if (currentObj)
			{
				glActiveTexture(GL_TEXTURE0);
				currentObj->getTextureWrapper()->bind();
				//I don't like how this takes in the shader program. Change in the future.
				currentObj->render(alpha);

				currentObj->getTextureWrapper()->unbind();
			}
		}

		glDisable(GL_DEPTH_TEST);
	}
}