#ifndef ANDRICK_MESH_FACTORY_H_
#define ANDRICK_MESH_FACTORY_H_

#include <string>
#include <glad/glad.h>
#include <vector>

namespace andrick
{
	//Might merge this into the Mesh class but this is kind of nice to have separated.
	class Mesh;
	class MeshFactory
	{
	public:
		static void extractMeshDataFromFile(Mesh& mesh);

	private:
		//Copied from old project. Might recode this in the future.
		static const std::string msCLASS_NAME;

		static const char SPACE_DELIMITER;
		static const char SLASH_DELIMITER;

		static const std::string VERTEX_DELIMITER;
		static const std::string VERTEX_TEX_COORD_DELIMITER;
		static const std::string VERTEX_NORMAL_DELIMITER;
		static const std::string FACE_DELIMITER;

		static const GLuint INDEX_DELIMITER_START;
		static const GLuint INDEX_DELIMITER_END;

		static void addFloatsFromString(std::string line, std::vector<GLfloat>& data, GLuint beginIndex, const char DELIMITER);
		static void addIntsFromString(std::string line, std::vector<GLint>& data, GLuint beginIndex, const char DELIMITER);
	};

	struct Vertex
	{
		inline Vertex(GLuint pos, GLuint tex, GLuint norm) : mPositionIndex(pos), mTextureIndex(tex), mNormalIndex(norm) {};

		GLuint mPositionIndex;
		GLuint mTextureIndex;
		GLuint mNormalIndex;

		inline GLboolean operator==(const Vertex& another)
		{
			return (mPositionIndex == another.mPositionIndex &&
				mTextureIndex == another.mTextureIndex &&
				mNormalIndex == another.mNormalIndex);
		}
	};
}

#endif