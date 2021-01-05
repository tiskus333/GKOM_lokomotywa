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

#include "Cuboid.h"
#include "Composite.h"
#include "Cylinder.h"
#include "Camera.h"
#include "Scene.h"

const GLuint WIDTH = 800, HEIGHT = 800;

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

GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
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

		/*Cuboid Cube1({ 0, 0, 0 }, { 0.5, 1.5, 0.5 }, glm::vec3( 1, 0, 0 ));
		Cuboid Cube2({ 1, 0, 0 }, { 0.5, 0.5, 0.5 }, glm::vec3( 0, 0, 1 ));
		Cuboid Cube3({ 0.5, 0, 0 }, { 0.5, 0.5, 0.5 }, glm::vec3( 0, 1, 0 ));
		Cuboid Cube4({ -1,0,0 }, { 1.5, 1.5, 1.5 }, glm::vec3(0, 0, 1));
		Cube4.rotate({ 45,0,0 });

		Cylinder Cylinder1({ 0, 0, 0.5 }, { 0.5, 0.5, 0.5 }, glm::vec3(0.4f, 0.3f, 1.0f));
		Cylinder1.rotate({ 90, 0, 0 });
		Cylinder Cylinder2({ -0.5, 0, 0 }, { 0.5, 0.5, 0.5 }, glm::vec3(0.2f, 0.1f, 1.0f));
		Cylinder2.rotate({ 0,0,90 });*/
		Cuboid CompartmentBody({ 0,0,0 }, { 1,1,2 }, glm::vec3(1, 0.5, 1));
		Cylinder CompartmentRoof({ 0,0.5,0 }, { 0.707106,0.999,0.5 }, glm::vec3(0, 0, 1));
		Cylinder CompartmentWheel1({ 0.3,-0.65,0.4 }, { 0.42,0.42,0.42 }, glm::vec3(0, 0, 1));
		Cylinder CompartmentWheel2({ 0.3,-0.65,0.8 }, { 0.42,0.42,0.42 }, glm::vec3(0, 0, 1));
		Cylinder CompartmentWheel3({ 0.3,-0.65,-0.4 }, { 0.42,0.42,0.42 }, glm::vec3(0, 0, 1));
		Cylinder CompartmentWheel4({ 0.3,-0.65,-0.8 }, { 0.42,0.42,0.42 }, glm::vec3(0, 0, 1));

		Cylinder CompartmentWheel5({ -0.3,-0.65,0.4 }, { 0.42,0.42,0.42 }, glm::vec3(0, 0, 1));
		Cylinder CompartmentWheel6({ -0.3,-0.65,0.8 }, { 0.42,0.42,0.42 }, glm::vec3(0, 0, 1));
		Cylinder CompartmentWheel7({ -0.3,-0.65,-0.4 }, { 0.42,0.42,0.42 }, glm::vec3(0, 0, 1));
		Cylinder CompartmentWheel8({ -0.3,-0.65,-0.8 }, { 0.42,0.42,0.42 }, glm::vec3(0, 0, 1));
		CompartmentRoof.rotate({ 90,0,0 });
		CompartmentWheel1.rotate({ 0,0,90 });
		CompartmentWheel2.rotate({ 0,0,90 });
		CompartmentWheel3.rotate({ 0,0,90 });
		CompartmentWheel4.rotate({ 0,0,90 });
		CompartmentWheel5.rotate({ 0,0,90 });
		CompartmentWheel6.rotate({ 0,0,90 });
		CompartmentWheel7.rotate({ 0,0,90 });
		CompartmentWheel8.rotate({ 0,0,90 });
		Composite cubes({ 0,0,0 });
		cubes.addElement(CompartmentBody);
		cubes.addElement(CompartmentRoof);
		cubes.addElement(CompartmentWheel1);
		cubes.addElement(CompartmentWheel2);
		cubes.addElement(CompartmentWheel3);
		cubes.addElement(CompartmentWheel4);
		cubes.addElement(CompartmentWheel5);
		cubes.addElement(CompartmentWheel6);
		cubes.addElement(CompartmentWheel7);
		cubes.addElement(CompartmentWheel8);
		/*cubes.addElement(Cube1);
		cubes.addElement(Cube2);
		cubes.addElement(Cube3);
		cubes.addElement(Cube4);
		cubes.addElement(Cylinder1);
		cubes.addElement(Cylinder2);*/
		//cubes.rotate({ 75,0,0 });
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// prepare textures
		//GLuint texture0 = LoadMipmapTexture(GL_TEXTURE0, "piesek.png");
		// GLuint texture1 = LoadMipmapTexture(GL_TEXTURE1, "weiti.png");

		ShaderProgram shader("CubeShader.vert", "CubeShader.frag");
		// main event loop
		float num = 1;
		while (!glfwWindowShouldClose(window))
		{
			current_time = glfwGetTime();
			delta_time = current_time - last_frame;
			last_frame = current_time;
			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			shader.Use();
			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);
			shader.setMatrix4fv("projection", projection);
			shader.setMatrix4fv("view", camera.GetViewMatrix());
			shader.setVec3("point_lights[0].lightPos", glm::vec3(10.0,10.0,10.0));

			
			//set ambient lighting
			shader.setVec3("ambientColor", Scene::getScene().ambient_light);
			shader.setVec3("viewPos", camera.Position);
			shader.setVec3("point_lights[0].lightColor", glm::vec3(1.0f, 1.0f, 1.0f ));
			shader.setInt("num_of_lights", 1);

			//movement
			//cubes.move({0, 0, -0.001});
			//cubes.rotate({0, 0.1, 0} /*, { 0,0,0 }*/);

			cubes.draw();

			// Bind Textures using texture units
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, texture0);
			//glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture0"), 0);
			//glActiveTexture(GL_TEXTURE1);
			//glBindTexture(GL_TEXTURE_2D, texture1);
			//glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture1"), 1);
			

			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();
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
