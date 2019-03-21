#ifndef ANDRICK_MATH_HELPER_H_
#define ANDRICK_MATH_HELPER_H_

#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <string>

namespace andrick
{
	struct MathHelper
	{
		static GLfloat PI;
		static const glm::vec3 WORLD_UP;
		static const glm::vec3 WORLD_RIGHT;
		static const glm::vec3 WORLD_FORWARD;

		static void rotAroundXAxis(glm::vec3& vec, GLfloat angle);
		static void rotAroundYAxis(glm::vec3& vec, GLfloat angle);
		static void rotAroundZAxis(glm::vec3& vec, GLfloat angle);

		static glm::mat4 createTranslationMat(const glm::vec3& position);

		//Rotation sent in degrees.
		static glm::mat4 createRotationMat(const glm::vec3& rotationInDeg);
		static glm::mat4 createScaleMat(const glm::vec3& scale);

		//Rotation sent in degrees.
		static glm::mat4 createTransformationMat(const glm::vec3& position, const glm::vec3& rotationInDeg, const glm::vec3& scale);

		static std::string to_string(const glm::mat4& mat);

		static GLfloat toRadians(const GLfloat& degrees);
		static GLfloat toDegrees(const GLfloat& radians);

		static GLfloat magnitudeSquared(glm::vec3& vec);

		//Input and ceil must be positive.
		static GLuint mod(const GLuint input, const GLuint ceil);
	};
}

#endif