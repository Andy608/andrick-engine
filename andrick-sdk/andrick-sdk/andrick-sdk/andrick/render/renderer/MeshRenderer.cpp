#include "MeshRenderer.h"
#include "../../logger/LoggerMaster.h"

namespace andrick
{
	const std::string MeshRenderer::msCLASS_NAME = "MeshRenderer";

	void MeshRenderer::render(const std::vector<Mesh*>& meshes)
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

		auto iter = meshes.begin();
		for (; iter != meshes.end(); ++iter)
		{
			Mesh* currentObj = *iter;

			if (currentObj)
			{
				//Uses the identity matrix. If you want to move meshes around, you need a model object that holds the transform data.
				mpShaderProgram->loadMat4("transformMatrix", GL_FALSE, glm::value_ptr(glm::mat4x4(1.0f)));
				currentObj->render();
			}
		}

		glDisable(GL_DEPTH_TEST);
	}
}