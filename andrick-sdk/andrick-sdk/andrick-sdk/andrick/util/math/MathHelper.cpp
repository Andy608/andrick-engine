#include "MathHelper.h"
#include <glm/gtx/rotate_vector.hpp>

namespace andrick
{
	GLfloat MathHelper::PI = 3.14159265359f;
	const glm::vec3 MathHelper::WORLD_RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 MathHelper::WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 MathHelper::WORLD_FORWARD = glm::vec3(0.0f, 0.0f, 1.0f);
	
	void MathHelper::rotAroundXAxis(glm::vec3& vec, GLfloat angle)
	{
		vec = glm::rotateX(vec, MathHelper::toRadians(angle));
	}

	void MathHelper::rotAroundYAxis(glm::vec3& vec, GLfloat angle)
	{
		vec = glm::rotateY(vec, MathHelper::toRadians(angle));
	}

	void MathHelper::rotAroundZAxis(glm::vec3& vec, GLfloat angle)
	{
		vec = glm::rotateZ(vec, MathHelper::toRadians(angle));
	}

	glm::mat4 MathHelper::createTranslationMat(const glm::vec3 &position)
	{
		glm::mat4 translationMat = glm::mat4(1.0f);
		return glm::translate(translationMat, position);
	}

	//Rotation sent in degrees.
	glm::mat4 MathHelper::createRotationMat(const glm::vec3 &rotationInDeg)
	{
		glm::mat4 rotationMat = glm::mat4(1.0f);
		rotationMat = glm::rotate(rotationMat, MathHelper::toRadians(rotationInDeg.x), WORLD_RIGHT);
		rotationMat = glm::rotate(rotationMat, MathHelper::toRadians(rotationInDeg.y), WORLD_UP);
		rotationMat = glm::rotate(rotationMat, MathHelper::toRadians(rotationInDeg.z), WORLD_FORWARD);
		return rotationMat;
	}

	glm::mat4 MathHelper::createScaleMat(const glm::vec3 &scale)
	{
		glm::mat4 scaleMat = glm::mat4(1.0f);
		return glm::scale(scaleMat, scale);
	}

	//Rotation sent in degrees.
	glm::mat4 MathHelper::createTransformationMat(const glm::vec3& position, const glm::vec3& rotationInDeg, const glm::vec3& scale)
	{
		glm::mat4 scaleMat = createScaleMat(scale);
		glm::mat4 rotMat = createRotationMat(rotationInDeg);
		glm::mat4 posMat = createTranslationMat(position);

		glm::mat4 transformMat = posMat * rotMat * scaleMat;

		return transformMat;
		//return createTranslationMat(position) * createRotationMat(rotationInDeg) * createScaleMat(scale);
	}

	glm::mat4 MathHelper::createNormalMat(const glm::mat4& transformationMat, const glm::mat4& viewMat)
	{
		glm::mat3 transformMat = (glm::mat3(viewMat * transformationMat));
		return glm::transpose(glm::inverse(transformMat));
	}

	std::string MathHelper::to_string(const glm::mat4& mat)
	{
		std::string s = "\n[\n";

		GLuint row, col;
		for (col = 0; col < 4; ++col)
		{
			for (row = 0; row < 4; ++row)
			{
				s.append(std::to_string(mat[col][row]));

				if (row != 3)
				{
					s.append(", ");
				}
			}

			s.append("\n");
		}

		s.append("]\n");

		return s;
	}

	GLfloat MathHelper::toRadians(const GLfloat& degrees)
	{
		return degrees * PI / 180.0f;
	}

	GLfloat MathHelper::toDegrees(const GLfloat& radians)
	{
		return radians * 180.0f / PI;
	}

	GLfloat MathHelper::magnitudeSquared(glm::vec3& vec)
	{
		return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	}
	
	GLuint MathHelper::mod(const GLuint input, const GLuint ceil)
	{
		return input > ceil ? input % ceil : input;
	}
}