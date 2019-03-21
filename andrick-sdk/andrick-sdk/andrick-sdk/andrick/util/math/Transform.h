#ifndef ANDRICK_TRANSFORM_H_
#define ANDRICK_TRANSFORM_H_

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "../../memory/TrackableObject.h"

namespace andrick
{
	class Transform : public TrackableObject
	{
	public:
		glm::vec3 mPosition;
		glm::vec3 mRotation;
		glm::vec3 mScale;

		Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
		inline ~Transform() {};

		inline void setPosition(const glm::vec3& pos) { setPosition(pos.x, pos.y, pos.z); };
		inline void setRotation(const glm::vec3& rot) { setRotation(rot.x, rot.y, rot.z); };
		inline void setScale(const glm::vec3& scale) { setScale(scale.x, scale.y, scale.z); };

		inline void setPosition(GLfloat x, GLfloat y, GLfloat z)
		{ 
			mPosition.x = x;
			mPosition.y = y;
			mPosition.z = z;
		};

		inline void setRotation(GLfloat x, GLfloat y, GLfloat z)
		{
			mRotation.x = x;
			mRotation.y = y;
			mRotation.z = z;
		};

		inline void setScale(GLfloat x, GLfloat y, GLfloat z)
		{
			mScale.x = x;
			mScale.y = y;
			mScale.z = z;
		};

		inline void addPosition(const glm::vec3& pos) { addPosition(pos.x, pos.y, pos.z); };
		inline void addRotation(const glm::vec3& rot) { addRotation(rot.x, rot.y, rot.z); };
		inline void addScale(const glm::vec3& scale) { addScale(scale.x, scale.y, scale.z); };

		inline void addPosition(GLfloat x, GLfloat y, GLfloat z)
		{
			mPosition.x += x;
			mPosition.y += y;
			mPosition.z += z;
		};

		inline void addRotation(GLfloat x, GLfloat y, GLfloat z)
		{
			mRotation.x += x;
			mRotation.y += y;
			mRotation.z += z;
		};

		inline void addScale(GLfloat x, GLfloat y, GLfloat z)
		{
			mScale.x += x;
			mScale.y += y;
			mScale.z += z;
		};

		//Syncs the prevTransform with the currentTransform so unwanted lerping doesn't take place.
		void sync();
		void lerp(const GLdouble& alpha);

		inline const glm::vec3& getPosition() const { return mPosition; };
		inline const glm::vec3& getRotation() const { return mRotation; };
		inline const glm::vec3& getScale() const { return mScale; };
		inline const glm::mat4& getTransformationMat() const { return mTransformationMat; };

		inline const glm::vec3& getLerpedPosition() const { return mLerpedPosition; };
		inline const glm::vec3& getLerpedRotation() const { return mLerpedRotation; };
		inline const glm::vec3& getLerpedScale() const { return mLerpedScale; };

	private:
		glm::vec3 mOrigin;//for now (0, 0, 0)
		
		glm::vec3 mLerpedPosition;
		glm::vec3 mLerpedRotation;
		glm::vec3 mLerpedScale;

		glm::vec3 mPrevPosition;
		glm::vec3 mPrevRotation;
		glm::vec3 mPrevScale;

		glm::mat4 mTransformationMat;
	};
}

#endif