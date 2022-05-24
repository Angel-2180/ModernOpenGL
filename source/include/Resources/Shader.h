#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "../include/Core/Debug/Log.h"
#include "../maths/LibMaths/Vec3/Vec3.h"
#include "LibMaths/Mat4/Mat4.h"
#include "../include/Resources/Resourcesmanager.h"
#include "LibMaths/Mat3/Mat3.h"

namespace Resources
{
	class Shader : public IResource
	{
	private:
		//private var
		int id;

		//private func
		std::string loadSourceShader(const char* filename);
		int load_shader(GLenum type, const char* filename);
		void Link(int vertexShader, int fragmentShader);
	public:
		//Constructor / destructor
		Shader(const char* vertexShader, const  char* fragmentShader);
		~Shader();
		//public func
		void setMat4f(const lm::Mat4<float> value, const char* name);
		void setBool(const std::string& name, bool value);
		void setInt(const std::string& name, int value);
		void setFloat(const std::string& name, float value);
		void setVec3f(const lm::Vec3<float> value, const char* name);
		void setVec3f(const char* name, const lm::Vec3<float> value);
		void setMat3f(lm::Mat3<float> value, const char* name);
		void use();
		void unUse();
	};
}
