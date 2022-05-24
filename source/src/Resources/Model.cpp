#include "../include/Resources/Model.h"

void	 Resources::Model::loadfromObj(const std::string& path)
{
	glfwSetTime(0);
	std::vector<lm::Vec3<float>> verticies;
	std::vector<lm::vec2> textCoords;
	std::vector<lm::vec3> normals;

	std::vector<int> vertices_indicies;
	std::vector<int> textcords_indicies;
	std::vector<int> normals_indicies;

	std::stringstream ss;
	std::ifstream in_file(path);
	std::string line = "";
	std::string prefix = "";
	lm::vec3 temp_vec3; //vertex & normals
	lm::vec2 temp_vec2; // textcoords
	int temp_int = 0;
	if (!in_file.is_open())
	{
		DEBUG_LOG("ERROR::LoadFromOBJ::could not open File");
	}

	while (std::getline(in_file, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#")
		{
			//do nothing
		}
		else if (prefix == " ")
		{
			//do nothing
		}
		else if (prefix == "o")
		{
			//do nothing
		}
		else if (prefix == "s")
		{
			//do nothing
		}
		else if (prefix == "v") //vertex
		{
			ss >> temp_vec3[0] >> temp_vec3[1] >> temp_vec3[2];
			verticies.push_back(temp_vec3);
		}
		else if (prefix == "vt")
		{
			ss >> temp_vec2[0] >> temp_vec2[1];
			textCoords.push_back(temp_vec2);
		}
		else if (prefix == "vn")
		{
			ss >> temp_vec3[0] >> temp_vec3[1] >> temp_vec3[2];
			normals.push_back(temp_vec3);
		}
		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> temp_int)
			{
				//size - 8; for reverse
				if (temp_int != 0)
				{
					if (counter == 0)
					{
						vertices_indicies.push_back(temp_int);
					}
					else if (counter == 1)
					{
						textcords_indicies.push_back(temp_int);
					}
					else if (counter == 2)
					{
						normals_indicies.push_back(temp_int);
					}

					if (ss.peek() == '/')
					{
						while (ss.peek() == '/')
						{
							++counter;
							ss.ignore(1, '/');
						}
					}
					else if (ss.peek() == ' ')
					{
						++counter;
						ss.ignore(1, ' ');
					}

					if (counter > 2)
					{
						counter = 0;
					}
				}
			}
		}
		else
		{
		}

		//Debug
		//std::cout << line << "\n";
	}

	vertex_buffer.resize(vertices_indicies.size(), Vertex());
	for (int i = 0; i < vertex_buffer.size(); ++i)
	{
		vertex_buffer[i].Position = verticies[vertices_indicies[i] - 1];

		if (textCoords.size() != 0)
		{
			vertex_buffer[i].TextureUV = textCoords[textcords_indicies[i] - 1];
		}
		if (normals.size() != 0)
		{
			vertex_buffer[i].Normal = normals[normals_indicies[i] - 1];
		}
	}
	std::cout << glfwGetTime() << "\n";
	std::cout << "nbr of verticies: " << vertex_buffer.size() << "\n";
}

Resources::Model::Model(std::string filename)
{
	this->loadfromObj(filename);

	this->vbo.initVBO(this);
	this->vao.initVAO();
}

void Resources::Model::Draw(Shader* shader)
{
	shader->use();
	vao.Bind();

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo.VBO);

	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(this->vertex_buffer.size()));
}

void Resources::Model::BindVAO()
{
	vao.Bind();
}

//Vertex Buffer / VBO / EBO?

void Resources::Model::Buffer::initVBO(Model* model)
{
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, model->vertex_buffer.size() * sizeof(Vertex), model->vertex_buffer.data(), GL_STATIC_DRAW);
}

Resources::Model::Buffer::~Buffer()
{
	glDeleteBuffers(1, &this->VBO);
}

// VertexAttribute / VAO
void Resources::Model::vertexAttributes::initVAO()
{
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position));
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TextureUV));
	glEnableVertexAttribArray(1);
	// normal  attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);

	//glVertexAttribPointer();

	glBindVertexArray(0);
}

void Resources::Model::vertexAttributes::Bind()
{
	if (VAO == GL_FALSE)
	{
		glGenVertexArrays(1, &this->VAO);
	}
	glBindVertexArray(this->VAO);
}

Resources::Model::vertexAttributes::~vertexAttributes()
{
	glDeleteVertexArrays(1, &this->VAO);
}