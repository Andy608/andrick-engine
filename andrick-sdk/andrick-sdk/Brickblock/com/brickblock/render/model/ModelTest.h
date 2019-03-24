#ifndef MODEL_TEST_H_
#define MODEL_TEST_H_

#include <andrick/render/model/Model.h>

namespace bb
{
	class ModelTest : public andrick::Model
	{
	public:
		ModelTest();
		~ModelTest();

		void sync() override;

		void update(const GLdouble& deltaTime) override;
		void render(const GLdouble& deltaTime, const andrick::ShaderProgram& activeShader) override;

	private:
		ComponentNode* mTest;
		ComponentNode* mOrbit;
	};
}

#endif