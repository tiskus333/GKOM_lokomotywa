#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Camera.h"
#include "Scene.h"
#include "Wagon.h"
#include "Locomotive.h"

const GLuint WIDTH = 1920, HEIGHT = 1080;

static Camera camera(glm::vec3(0.f,0.f,3.f), glm::vec3(0.f, 1.f, 0.f));
float current_time = 0.0, delta_time = 0.0f, last_frame = 0.0f;
double lastX = WIDTH/2;
double lastY = HEIGHT/2;
bool firstMouse = true;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::FORWARD, delta_time);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, delta_time);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::LEFT, delta_time);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::RIGHT, delta_time);
}
void scroll_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.ProcessMouseScroll(ypos);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

int main()
{
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 206.z Lokomotywa", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);
		glEnable(GL_DEPTH_TEST);

		Cuboid LightCube({ 3, 3, 3 }, { 0.5, 0.5, 0.5 }, glm::vec3( 1, 1, 1 ), true);
		
		Cylinder LightCylinder({ -1, 1, 1 }, { 0.5, 0.5, 0.5 }, glm::vec3( 1, 0, 0 ), true);
		
		Cuboid TextureCube({ 1,1,1 }, { 1,1,1 }, "kolory.png");
		Cylinder TextureCylinder({ 3,2,1 }, { 1,1,1 }, "kolo2.bmp",false);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// prepare textures
		//GLuint texture0 = LoadMipmapTexture(GL_TEXTURE0, "piesek.png");
		// GLuint texture1 = LoadMipmapTexture(GL_TEXTURE1, "weiti.png");

		

		

	

		
		Wagon Wagon1; 
		Wagon1.move({ 0,0,3 });
		Locomotive Loc1;

		
		//comp.addElement(LocomotiveHullRoof);

		ShaderProgram shader("CubeShader.vert", "CubeShader.frag");
		// main event loop
		float num = 1;
		while (!glfwWindowShouldClose(window))
		{
			current_time = glfwGetTime();
			delta_time = current_time - last_frame;
			last_frame = current_time;
			glfwPollEvents();
			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);
			Scene::getScene().setMatrix4fvInShaders("projection", projection);
			Scene::getScene().setMatrix4fvInShaders("view", camera.GetViewMatrix());
			Scene::getScene().setVec3InShaders("viewPos", camera.Position);

			

			//movement
			Scene::getScene().updateLights();
			
			Wagon1.move({0,0,-0.01});
			LightCube.draw();
			LightCylinder.draw();
			Wagon1.draw();
			Loc1.move({ 0,0,-0.01 });
			Loc1.draw();
			TextureCube.draw();
			


			// Bind Textures using texture units
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, texture0);
			//glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture0"), 0);
			//glActiveTexture(GL_TEXTURE1);
			//glBindTexture(GL_TEXTURE_2D, texture1);
			//glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture1"), 1);
			

			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			// Swap the screen buffers
			glfwSwapBuffers(window);
		}

	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}
