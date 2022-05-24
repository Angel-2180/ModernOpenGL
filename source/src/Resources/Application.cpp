#include "../include/Resources/Application.h"

using namespace Resources;

void Application::initWindow(const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(this->SCR_WIDTH, this->SCR_HEIGHT, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Application::framebuffer_size_callback);

	this->window = window;
}

void Application::initGlad()
{
	// glad: load all OpenGL function pointers
// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	GLint flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(Application::glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
}

void Resources::Application::initOpenGLOption()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Application::Application(
	char const* title,
	const int SCR_WIDTH,
	const int SCR_HEIGHT
)
	:
	window(nullptr),
	cam(lm::Vec3<float>(0, 0, 1), lm::Vec3<float>(0, 0, 1), lm::Vec3<float>(0, 1, 0)),
	SCR_WIDTH(SCR_WIDTH),
	SCR_HEIGHT(SCR_HEIGHT)
{
	this->projectionMat = lm::mat4::perspectiveProjection(90, static_cast<float>(SCR_WIDTH / SCR_HEIGHT), 0.01f, 1000.f);

	this->delta = 0.f;
	this->currentTime = 0.f;
	this->lastTime = 0.f;

	this->lastMouseX = 0.0;
	this->lastMouseY = 0.0;
	this->mouseX = 0.0;
	this->mouseY = 0.0;
	this->mouseOffSetX = 0.0;
	this->mouseOffSetY = 0.0;
	this->firstMouse = true;
	this->initWindow(title);
	this->initGlad();
	this->initOpenGLOption();
}

void Application::Run()
{
	Core::Debug::Log log;
	log.Openfile("log.txt");
	log.Print("Hey,you're awake ?\n");
	Resources::ResourcesManager mng;

	Model* model1 = mng.Create<Model>("assets/meshes/Young__Red_Dragon.obj");
	//Model* model1 = mng.Create<Model>("assets/meshes/armadillo.obj");
	Model* model2 = mng.Create<Model>("assets/meshes/floor.obj");
	Shader* shader = mng.Create<Shader>("source/shaders/core_vertex.glsl", "source/shaders/core_fragment.glsl");
	//Texture text("assets/textures/container.jpg");

	LowRenderer::Mesh mesh(mng.Get<Model>("assets/meshes/Young__Red_Dragon.obj"), lm::Vec3(0.f), lm::Vec3(-90.f, 0.f, 0.f), lm::Vec3(1.f));
	LowRenderer::Mesh mesh1(mng.Get<Model>("assets/meshes/floor.obj"), lm::Vec3(0.f), lm::Vec3(0.f, 0.f, 0.f), lm::Vec3(1.f) /*,&text*/);
	meshes.emplace_back(mesh);
	meshes.emplace_back(mesh1);

	LowRenderer::SpotLight spotLight(cam.getPosition(), cam.getFront(), lm::vec3(0.8f), lm::vec3(0.f), lm::vec3(1.f), 1.f, 0.09f, 0.032f);
	LowRenderer::DirectionLight directionLight(lm::vec3(-0.2f, -1.0f, -0.3f), lm::vec3(0.4f), lm::vec3(0.05f), lm::vec3(0.5f));
	LowRenderer::PointLight pointLight(0, lm::vec3(0.f), lm::vec3(0.8f), lm::vec3(0.05f), lm::vec3(1.f), 1.f, 0.09f, 0.032f);
	LowRenderer::PointLight pointLight1(1, lm::vec3(3.f), lm::vec3(1.f), lm::vec3(0.05f), lm::vec3(1.f));

	while (!glfwWindowShouldClose(this->window))
	{
		// input
		//
		updateDelta();
		updateInput();
		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto i : meshes)
		{
			/*	if (i.texture != nullptr)
				{
					i.texture->Bind();
				}*/
			pointLight.sendToShader(shader);
			pointLight1.sendToShader(shader);
			directionLight.sendToShader(shader);
			spotLight.updateVec(this->cam);
			spotLight.sendToShader(shader);
			i.updateUniform(shader, this->cam);
			//this->updateUniform(shader);
			i.model->BindVAO();
			i.model->Draw(shader);
		}

		//draw

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(this->window);
	}
	//end of function
	glfwTerminate();
}

void Resources::Application::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	this->mouseOffSetX = this->mouseX - this->lastMouseX;
	this->mouseOffSetY = this->mouseY - this->lastMouseY;

	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;
}

void Resources::Application::updateDelta()
{
	this->currentTime = static_cast<float>(glfwGetTime());
	this->delta = this->currentTime - this->lastTime;
	this->lastTime = this->currentTime;
}

void Resources::Application::updateInput()
{
	glfwPollEvents();
	processInput(this->window);
	this->updateMouseInput();
	this->cam.updateInput(this->delta, this->mouseOffSetX, this->mouseOffSetY);
}

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Application::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		this->cam.move(this->delta, LowRenderer::Camera::FORWARD);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		this->cam.move(this->delta, LowRenderer::Camera::BACKWARD);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		this->cam.move(this->delta, LowRenderer::Camera::LEFT);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		this->cam.move(this->delta, LowRenderer::Camera::RIGHT);
}

void APIENTRY Application::glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}