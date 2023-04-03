#include "CubeMapTexture.h"
#include<iostream>

CubeMapTexture::CubeMapTexture(std::vector<const char*> textures, const char* texType, GLenum slot, GLenum format, GLenum pixelType) 
{
	type = texType;
	std::cout << texType << std::endl;
	stbi_set_flip_vertically_on_load(false);

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (int i = 0; i < textures.size(); i++)
	{
		int widthImg, heightImg, numColCh;
		unsigned char* bytes = stbi_load(textures[i], &widthImg, &heightImg, &numColCh, 0);
		if (bytes)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP + i, 0, GL_RGB, widthImg, heightImg, 0, format, pixelType, bytes);
			stbi_image_free(bytes);
		}
		else
		{
			std::cout << "Failde to load texture: " << textures[i] << std::endl;
			stbi_image_free(bytes);
		}
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

//void CubeMapTexture::texUnit(Shader& shader, const char* uniform, GLuint unit)
//{
//	GLuint texUnit = glGetUniformLocation(shader.ID, uniform);
//	shader.Activate();
//	glUniform1i(texUnit, unit);
//}

void CubeMapTexture::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void CubeMapTexture::UnBind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMapTexture::Delete()
{
	glDeleteTextures(1, &ID);
}