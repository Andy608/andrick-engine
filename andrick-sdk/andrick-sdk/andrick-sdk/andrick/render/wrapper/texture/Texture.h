//#ifndef ANDRICK_TEXTURE_H_
//#define ANDIRKC_TEXTURE_H_
//
//#include "../../../memory/TrackableObject.h"
//#include "../../../memory/NonCopyable.h"
//#include <glad/glad.h>
//
//namespace andrick
//{
//	class Texture : public TrackableObject, NonCopyable
//	{
//		friend class Image;
//		friend class TextureWrapper;
//
//	public:
//		Texture();
//		~Texture();
//
//		inline const GLuint getWidth() const { return mWidth; };
//		inline const GLuint getHeight() const { return mHeight; };
//
//	private:
//		GLint mWidth;
//		GLint mHeight;
//		GLint mColorChannels;
//		GLubyte *mPixelData;
//	};
//}
//
//#endif