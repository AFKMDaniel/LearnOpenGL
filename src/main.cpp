#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "camera.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

double _lastX = SCREEN_WIDTH / 2;
double _lastY = SCREEN_HEIGHT / 2;

Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

GLfloat _deltaTime = 0.0f;	// Время, прошедшее между последним и текущим кадром
GLfloat _lastFrame = 0.0f;  	// Время вывода последнего кадра

std::vector<bool> keys(1024, false);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS)
		keys[key] = true;
	if (action == GLFW_RELEASE)
		keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	GLfloat xOffset = xPos - _lastX;
	GLfloat yOffset = _lastY - yPos; // Обратный порядок вычитания потому что оконные Y-координаты возрастают с верху вниз 
	_lastX = xPos;
	_lastY = yPos;

	camera.processMouseMovement(xOffset, yOffset);
}

void doMovement()
{
	if (keys[GLFW_KEY_W])
		camera.processKeyInput(Direction::FORWARD, _deltaTime);
	if (keys[GLFW_KEY_S])
		camera.processKeyInput(Direction::BACKWARD, _deltaTime);
	if (keys[GLFW_KEY_D])
		camera.processKeyInput(Direction::RIGHT, _deltaTime);
	if (keys[GLFW_KEY_A])
		camera.processKeyInput(Direction::LEFT, _deltaTime);
	if (keys[GLFW_KEY_E])
		camera.processKeyInput(Direction::UP, _deltaTime);
	if (keys[GLFW_KEY_Q])
		camera.processKeyInput(Direction::DOWN, _deltaTime);
}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	auto window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create OpenGL window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	glfwSetCursorPos(window, _lastX, _lastY);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	std::vector<glm::vec3> cubePositions {
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),
	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//vertexes pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	//vertexes tex
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	Shader shader{ "resources/shaders/shader.vert", "resources/shaders/shader.frag" };
	Shader lightShader{ "resources/shaders/shader.vert", "resources/shaders/light.frag" };

	float alpha = 0.2f;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		auto currentFrame = glfwGetTime();
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		doMovement();

		glm::mat4 view = camera.getViewMatrix();

		glm::mat4 projection;
		projection = glm::perspective(45.0f, static_cast<float>(SCREEN_WIDTH / SCREEN_HEIGHT), 0.1f, 100.0f);

		glBindVertexArray(lightVAO);

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
		model = glm::scale(model, glm::vec3(0.2f));

		lightShader.use();
		lightShader.setUniform("model", model);
		lightShader.setUniform("view", view);
		lightShader.setUniform("projection", projection);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		shader.use();

		glm::vec3 objectColor{ 1.0f, 0.5f, 0.31f };
		shader.setUniform("objectColor", objectColor);
		glm::vec3 lightColor{ 1.0f, 1.0f, 1.0f };
		shader.setUniform("lightColor", lightColor);

		shader.setUniform("view", view);

		shader.setUniform("projection", projection);

		shader.setUniform("alpha", alpha);

		glBindVertexArray(VAO);

		for (int i = 0; i != cubePositions.size(); ++i)
		{
			model = glm::mat4();
			model = glm::translate(model, cubePositions[i]);

			GLfloat angle = 20.0f * (i + 1);
			if ((i + 1) % 3 == 0) 
				angle *= currentFrame;

			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));

			shader.setUniform("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


