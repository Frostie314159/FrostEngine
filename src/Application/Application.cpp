#include "Application.hpp"

Application::Application() {

}
Application::~Application() {

}

void Application::run() {
	Config m_appConfig = ConfigLoader::loadConfigFile("../res/Config.json");
	glfwInit();
	ImageLoadingScheduler m_imageLoadingScheduler = ImageLoadingScheduler(m_appConfig);
	Window m_appWindow = Window(m_appConfig,std::make_shared<ImageLoadingScheduler>(m_imageLoadingScheduler));
	/*
	GraphicsAPI m_graphicsAPI = APIUtil::getAPIByCascade();
	if (m_graphicsAPI == GraphicsAPI::GRAPHICS_API_OPENGL) {
		glfwMakeContextCurrent(m_appWindow.getWindow());
		ErrorHandler::handleOpenGLErrorCode(glewInit());
		Version m_version = OpenGLUtil::getOpenGLVersion();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_version.getMajorVersion());
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_version.getMinorVersion());
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);
		static const std::vector<GLfloat> m_vertexBufferData = {
		1.0f,1.0f,0.0f,
		1.0f,-1.0f,0.0f,
		-1.0f,-1.0f,0.0f
		};
		VAO m_buffer = VAO(std::make_tuple(m_vertexBufferData, 3));
		std::chrono::high_resolution_clock::time_point t;
		do {
			t = std::chrono::high_resolution_clock::now();
			glClear(GL_COLOR_BUFFER_BIT);
			//m_buffer.bind();
			//glBindVertexArray(m_buffer.getVAOID());
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer.getVAOID());
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			//glBindVertexArray(0);
			glDisableVertexAttribArray(0);
			glfwSwapBuffers(m_appWindow.getWindow());
			glfwPollEvents();

			double frametime = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t).count());
			std::cout << "FPS: " << 1000 / frametime << std::endl;
		} 		
		while (!glfwWindowShouldClose(m_appWindow.getWindow()));
		m_buffer.unbind();
		m_buffer.deleteVAO();
	}
	else if (m_graphicsAPI == GraphicsAPI::GRAPHICS_API_VULKAN) {
		glfwWindowHint(GLFW_NO_API, GLFW_TRUE);
		Instance m_instance = Instance(m_appConfig);
		while (!glfwWindowShouldClose(m_appWindow.getWindow())) {
			glfwPollEvents();
		}
		m_instance.destroy();
	}
	*/
	
	/*GLuint m_vertexBuffer;
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexBufferData), m_vertexBufferData.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);*/
	
	
	//m_buffer.bind();
	
	
	glfwTerminate();
}