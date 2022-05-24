#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../include/Core/Debug/Log.h"
#include "../include/Core/Debug/Assertion.h"
#include "../maths/LibMaths/Mat4/Mat4.h"
#include "../maths/LibMaths/Vec3/Vec3.h"
#include "../include/Resources/Model.h"
#include "../include/Resources/Shader.h"
#include "../include/LowRenderer/Camera.h"
#include "../include/LowRenderer/Mesh.h"
#include "../include/LowRenderer/Light.h"
#include "../include/Resources/Texture.h"
#include <cstdio>
#include <ostream>
#include <iostream>
namespace Resources
{
	class Application
	{
	private:
		//var
		GLFWwindow* window;
		LowRenderer::Camera cam;
		lm::Mat4<float> projectionMat;
		const int SCR_WIDTH;
		const int SCR_HEIGHT;
		std::vector<LowRenderer::Mesh> meshes;

		//Delta Time
		float delta;
		float currentTime;
		float lastTime;

		//Mouse Input
		double lastMouseX;
		double lastMouseY;
		double mouseX;
		double mouseY;
		double mouseOffSetX;
		double	mouseOffSetY;
		bool firstMouse;

		//private function
		void initWindow(const char* title);
		void initGlad();
		void initOpenGLOption();
	public:
		//constructor / destructor
		Application(
			char const* title,
			const int SCR_WIDTH,
			const int SCR_HEIGHT);
		//public function
		void Run();
		void updateDelta();
		void updateMouseInput();

		void updateInput();
		void processInput(GLFWwindow* window);

		//static function
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	};
}

//
