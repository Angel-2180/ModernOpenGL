#pragma once
#include <glad/glad.h>

#include <stb_image.h>
#include "../Resources/Resourcesmanager.h"

namespace Resources
{
	class Texture : IResource
	{
	public:
		GLuint texture = GL_FALSE;

		Texture(char const* const& filename);

		void loadTexture(char const* const& filename);

		void Bind();
	};
}
