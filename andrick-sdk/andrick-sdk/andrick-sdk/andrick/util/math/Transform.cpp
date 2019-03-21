#include "Transform.h"
#include "MathHelper.h"

namespace andrick
{
	Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) :
		mTransformationMat(MathHelper::createTransformationMat(pos, rot, scale)),
		mOrigin(glm::vec3()),//For now
		mPosition(pos), mRotation(rot), mScale(scale),
		mPrevPosition(pos), mPrevRotation(rot), mPrevScale(scale),
		mLerpedPosition(pos), mLerpedRotation(rot), mLerpedScale(scale)
	{

	}

	void Transform::sync()
	{
		mPrevPosition = mPosition;
		mPrevRotation = mRotation;
		mPrevScale = mScale;
	}

	void Transform::lerp(const GLdouble& alpha)
	{
		mLerpedPosition = glm::mix(mPrevPosition, mPosition, alpha);
		mLerpedRotation = glm::mix(mPrevRotation, mRotation, alpha);
		mLerpedScale = glm::mix(mPrevScale, mScale, alpha);

		mTransformationMat = MathHelper::createTransformationMat(mLerpedPosition, mLerpedRotation, mLerpedScale);
	}
}