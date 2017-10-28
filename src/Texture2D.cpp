
#include "Texture2D.h"

#include <iostream>

namespace antisocial
{
	namespace graphics
	{
		namespace texture2D
		{
			Texture2D::Texture2D(const std::string& texturePath)
			{
				//Allocates space for texture and stores handle in _handle
				glGenTextures(1, &_handle);
				//Sets _handle to current GL texture
				glBindTexture(GL_TEXTURE_2D, _handle);

				//Set initial texture parameters
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glGenerateMipmap(GL_TEXTURE_2D);
				setImage(texturePath, 0);
			}

			Texture2D::~Texture2D()
			{
				stbi_image_free(_data);
				glDeleteTextures(1, &_handle);
			}

			void Texture2D::setMinFilter(MIN_FILTER filter)
			{
				_minFilter = filter;
				setParameter(TEXTURE_MIN_FILTER, _minFilter);
			}

			void Texture2D::setMagFilter(MAG_FILTER filter)
			{
				_magFilter = filter;
				setParameter(TEXTURE_MAG_FILTER, _magFilter);
			}

			void Texture2D::setWrappingX(WRAPPING wrap)
			{
				_xWrapping = wrap;
				setParameter(TEXTURE_WRAP_X, _xWrapping);
			}

			void Texture2D::setWrappingY(WRAPPING wrap)
			{
				_yWrapping = wrap;
				setParameter(TEXTURE_WRAP_Y, _yWrapping);
			}

			void Texture2D::setParameter(GLenum name, GLenum param)
			{
				glBindTexture(GL_TEXTURE_2D, _handle);
				glTexParameteri(GL_TEXTURE_2D, name, param);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			const MIN_FILTER& 	Texture2D::getMinFilter() const
			{
				return _minFilter;
			}

			const MAG_FILTER& 	Texture2D::getMagFilter() const
			{
				return _magFilter;
			}

			const WRAPPING&		Texture2D::getWrappingX() const
			{
				return _xWrapping;
			}

			const WRAPPING& 	Texture2D::getWrappingY() const
			{
				return _yWrapping;
			}

			void Texture2D::bind(unsigned int unit)
			{
				glActiveTexture(GL_TEXTURE0 + unit);
				glBindTexture(GL_TEXTURE_2D, _handle);
			}

			void Texture2D::setImage(const std::string& path, unsigned int unit)
			{
				bind(0);
				_data = stbi_load(path.c_str(), &_width, &_height, &_numComponents, 4);

				if (_data == NULL)
				{
					std::cerr << "Texture2D (" << path << ") was not loaded successfully" << std::endl;
					stbi_image_free(_data);
					return;
				}

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}
	}
}
