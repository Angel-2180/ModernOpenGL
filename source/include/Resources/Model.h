#pragma once
#include <glad/glad.h>
#include "Resourcesmanager.h"
#include "../include/Core/Debug/Log.h"
#include "../include/Resources/Shader.h"
#include <fstream>
#include <sstream>

#include "LibMaths/Vec2/Vec2.h"

namespace Resources
{
	struct Vertex
	{
		lm::Vec3<float> Position;
		lm::vec2 TextureUV;
		lm::Vec3<float> Normal;
	};
	class Model : public IResource
	{
	public:
		//nested class

		//VBO

		class Buffer
		{

		public:
			//constructor / destructor

			GLuint VBO = GL_FALSE;
			~Buffer();

			//func
			void initVBO(Model* model);
		};

		//VAO

		class vertexAttributes
		{
			GLuint VAO = GL_FALSE;
		public:
			//constructor / destructor
			~vertexAttributes();

			//func
			void initVAO();
			void Bind();
		};

		//public function

		void loadfromObj(const std::string& path);

		Model(std::string filename);

		void BindVAO();
		void Draw(Shader* shader);

	private:
		Buffer vbo;

		vertexAttributes vao;
		std::vector<Vertex> vertex_buffer;
		std::vector<uint32_t> index_buffer;
	};
}
