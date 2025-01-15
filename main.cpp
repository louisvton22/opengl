#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include "stb_image.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Shader shader);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
float mixValue = 0.2f;
// camera coordinates
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
bool firstMouse = true;
// camera zoom
//float Zoom = 45.0f;

//light source global coords
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//float yaw = -90.0f;
//float pitch = 0.0f;
float deltaTime = 0.0f; // time between current and last frame
float lastFrame = 0.0f; //time of last frame
float lastX = 400, lastY = 300; // mouse default position
int main() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if(window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initalize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600); // first two parameters set the location of the lower left corner
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//cube vertices 
	float vertices[] = {
		// positions
		// normals
		// texture coords-0.5f,-0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,
 0.5f,-0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 1.0f, 0.0f,
 0.5f, 0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 1.0f, 1.0f,
 0.5f, 0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 1.0f, 1.0f,-0.5f, 0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 0.0f, 1.0f,-0.5f,-0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,-0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
 0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,-0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,-0.5f, 0.5f, 0.5f,-1.0f, 0.0f, 0.0f, 1.0f, 0.0f,-0.5f, 0.5f,-0.5f,-1.0f, 0.0f, 0.0f, 1.0f, 1.0f,-0.5f,-0.5f,-0.5f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f,-0.5f,-0.5f,-0.5f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f,-0.5f,-0.5f, 0.5f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f,-0.5f, 0.5f, 0.5f,-1.0f, 0.0f, 0.0f, 1.0f, 0.0f
	, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
 0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
 0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
 0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
 0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,-0.5f,-0.5f,-0.5f, 0.0f,-1.0f, 0.0f, 0.0f, 1.0f,
 0.5f,-0.5f,-0.5f, 0.0f,-1.0f, 0.0f, 1.0f, 1.0f,
 0.5f,-0.5f, 0.5f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f,
 0.5f,-0.5f, 0.5f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f,-0.5f,-0.5f, 0.5f, 0.0f,-1.0f, 0.0f, 0.0f, 0.0f,-0.5f,-0.5f,-0.5f, 0.0f,-1.0f, 0.0f, 0.0f, 1.0f,-0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
 0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,-0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// glm vector transformations
	/*glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);*/
	// translate by (1,1,0)
	// trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	
	// rotate by 90 degrees around the z axis over time and translate right and down
	/*trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	vec = trans * vec;*/

	//bind vertex attribute to vao
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//vertex buffer object to store vertex information
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//element buffer object
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//lighting VAO
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);



	////shader
	//const char* vertexShaderSource = "#version 330 core \n"
	//	"layout (location = 0) in vec3 aPos;\n"
	//	"layout (location = 1) in vec3 aColor;\n"
	//	"out vec3 ourColor;\n"
	//	"void main()\n"
	//	"{\n"
	//	" gl_Position = vec4(aPos, 1.0);\n"
	//	" ourColor = aColor;\n"
	//	"}\0";
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	//const char* fragShaderSource = "#version 330 core\n"
	//	"out vec4 FragColor;\n"
	//	"in vec3 ourColor;\n"
	//	"void main()\n"
	//	"{\n"
	//	"FragColor = vec4(ourColor, 1.0);\n"
	//	"}\0";
	//unsigned int fragShader;
	//fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	//glCompileShader(fragShader);

	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragShader);
	//glLinkProgram(shaderProgram);
	//
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragShader);
	
	// create shader obejct which encapsulates everything above 
	Shader shader = Shader("shader.vs", "shader.fs");
	Shader lightingShader = Shader("lightshader.vs", "lightshader.fs");
	Shader lightCubeShader = Shader("lightshader.vs", "lightsource.fs");

	
	// GETTING STARTED : setting up boxes 
	// set vertex attributes pointers 
	// position
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//// color
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	// texture
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	glBindVertexArray(VAO);
	// COLORS: setting up lighting environment
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	/* CH1: texture mapping 
	// load and create a texture 
   // -------------------------
	unsigned int texture1, texture2;
	// texture 1
	// ---------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load("C:/Users/tonsa/Downloads/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// texture 2
	// ---------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// we want to repeat the awesomeface pattern so we kept it at GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture and generate mipmaps
	data = stbi_load("C:/Users/tonsa/Downloads/awesomeface.png", & width, & height, & nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	*/

	glm::mat4 model = glm::mat4(1.0f);
	// rotate about x axis so it looks like its laying on the floor
	/*model = glm::rotate(model, glm::radians(-50.0f) * .0001f, glm::vec3(0.5f, 1.0f, 0.0f));*/
	// to make it appear in view closer, we bring everything closer to camera
	glm::mat4 view = glm::mat4(1.0f);
	/*view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));*/

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.9f, 50.0f);
	//activate shader NOTE: any uniform values must be set after shader's activated



	// set transformation uniforms in vertex shader
	/*int modelLoc = glGetUniformLocation(shader.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(shader.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projectionLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));*/
	glfwSetScrollCallback(window, scroll_callback);
	
	lightingShader.use();
	lightingShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
	//lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);

	// set subject material lighting props
	/*lightingShader.setVec3("material.ambient", 1.0f, 0.4f, 0.31f);
	lightingShader.setVec3("material.diffuse", 1.0f, 0.4f, 0.31f);*/
	lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	lightingShader.setFloat("material.shininess", 32.0f);

	// set subject light intensity props
	lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	lightingShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
	lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);


	lightCubeShader.use();
	lightCubeShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
	lightCubeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	lightCubeShader.setVec3("lightPos", 0.0f, 0.0f, 0.0f);
	// set light source material lighting props
	lightCubeShader.setVec3("material.ambient", 1.0f, 0.4f, 0.31f);
	lightCubeShader.setVec3("material.diffuse", 1.0f, 0.4f, 0.31f);
	lightCubeShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	lightCubeShader.setFloat("material.shininess", 32.0f);

	// set light source light intensity props
	lightCubeShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	lightCubeShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	lightCubeShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	// create texture for diffuse map
	unsigned int texture1, texture2, texture3;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	int width, height, nrChannels;

	// diffusion map
	unsigned char* data = stbi_load("C:/Users/tonsa/Downloads/container2.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	lightingShader.use();
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	
	// specular map
	data = stbi_load("C:/Users/tonsa/Downloads/container2_specular.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} 
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// emission map
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	data = stbi_load("C:/Users/tonsa/Downloads/matrix.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	
	stbi_image_free(data);
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setVec3("light.direction", glm::vec3(1, 0, 0));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	lightingShader.setInt("material.specular", 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	lightingShader.setInt("material.emission", 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture3);

	// pass transformation matrix to shader
	/*unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));*/
	glEnable(GL_DEPTH_TEST);


	//translation indices to see depth in perspective projection
	glm::vec3 cubePositions[] = {
		 glm::vec3(0.0f, 0.0f, 0.0f),
		 glm::vec3(2.0f, 5.0f,-15.0f),
		 glm::vec3(-1.5f,-2.2f,-2.5f),
		 glm::vec3(-3.8f,-2.0f,-12.3f),
		 glm::vec3(2.4f,-0.4f,-3.5f),
		 glm::vec3(-1.7f, 3.0f,-7.5f),
		 glm::vec3(1.3f,-2.0f,-2.5f),
		 glm::vec3(1.5f, 2.0f,-2.5f),
		 glm::vec3(1.5f, 0.2f,-1.5f),
		 glm::vec3(-1.3f, 1.0f,-1.5f)
	};
	//float rotation = (float)glm::radians(50.0f);

	// camera positioning 
	//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	//// create orthagonal right direction vector between camera direction and world up direction
	//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	//// create camera up axis by cross product of camera direction and right 
	//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	// camera rotation
	
	camera.setFront();
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	//render loop
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//handle inputs
		processInput(window, lightingShader);

		// rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// Depth buffer bit must be cleared if using glEnable depth test
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render triangle
		glBindVertexArray(VAO);
		// scaling over time 
		/*trans = glm::mat4(1.0f);
		trans = glm::scale(trans, glm::vec3((float)sin(glfwGetTime()), (float)sin(glfwGetTime()), 0.0f));
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));*/
		float time = glfwGetTime();
		glm::vec3 rotatePos = glm::vec3(sin(time), 1.0f, cos(time));

		lightingShader.use();
		camera.setFront();
		view = glm::lookAt(camera.position, camera.position + camera.front, camera.up);

		lightingShader.setVec3("light.position", camera.position);
		lightingShader.setVec3("light.direction", camera.front);
		lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(10.5f)));
		lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(15.5f)));
		lightingShader.setMat4("view", view);
		lightingShader.setVec3("viewPos", camera.position.x, camera.position.y, camera.position.z);
		//glm::mat4 rotateTransform = glm::mat4(1.0f);
		//rotateTransform = glm::rotate(rotateTransform, (float)glfwGetTime() * glm::radians(10.0f), glm::vec3(0.0f, 0.3f, 0.5f));
		projection = glm::perspective(glm::radians(camera.zoom), 800.0f / 600.0f, 0.1f, 100.0f);
		
		
		model = glm::mat4(1.0f);
		lightingShader.setMat4("model", model);
		lightingShader.setMat4("projection", projection);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texture3);

		lightingShader.setFloat("light.constant", 1.0f);
		lightingShader.setFloat("light.linear", 0.09f);
		lightingShader.setFloat("light.quadratic", 0.032f);

		for (int i = 0; i < 10; i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			//rotateTransform = rotateTransform * glm::rotate(rotateTransform, glm::radians(10.0f), glm::vec3(0.0f, 0.3f, 0.5f));

			if (i % 3 == 0)
			{
				model = model;
			}
			//rotation += 1;
			//rotateBox = glm::rotate(rotateBox, glm::radians(50.0f), glm::vec3(0.0f, 0.3f, 0.5f));

			lightingShader.setMat4("model", model);
			lightingShader.setMat4("projection", projection);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		////change light color over time
		//glm::vec3 lightColor;
		//lightColor.x = sin(glfwGetTime() * 2.0f);
		//lightColor.y = sin(glfwGetTime() * 0.7f);
		//lightColor.z = sin(glfwGetTime() * 1.3f);
		//glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		//glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
		//lightingShader.setVec3("light.ambient", ambientColor);
		//lightingShader.setVec3("light.diffuse", diffuseColor);

		lightCubeShader.use();
		model = glm::mat4(1.0f);
		
		model = glm::translate(model, rotatePos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightCubeShader.setMat4("model", model);
		lightCubeShader.setMat4("view", view);
		lightCubeShader.setMat4("projection", projection);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// check and call events and swap the buffers
		glfwSwapBuffers(window); // 
		glfwPollEvents(); // check keyboard input, mouse events, etc.
	}
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Shader shader)
{
	const float cameraSpeed = 2.5f * deltaTime; 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.0001f;
		if (mixValue > 1.0f)
		{
			mixValue = 1.0f;
		}

	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.0001f;
		if (mixValue < 0.0f)
		{
			mixValue = 0.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		/*cameraPos += cameraSpeed * cameraFront;*/
		camera.moveForward(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		/*cameraPos -= cameraSpeed * cameraFront;*/
		camera.moveBackward(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		/*cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;*/
		camera.moveRight(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		/*cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;*/
		camera.moveLeft(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		/*cameraPos += cameraUp * cameraSpeed;*/
		camera.moveUp(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{ 
		/*cameraPos -= cameraUp * cameraSpeed;*/
		camera.moveDown(cameraSpeed);
	}
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
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	camera.rotate(xoffset, yoffset);
		/*const float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f) {
			pitch = 89.0f;
		}
		if (pitch < -89.0f) {
			pitch = -89.0f;
		}
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));;
		direction.y = sin(glm::radians(pitch));
		cameraFront = glm::normalize(direction);*/
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	/*Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
	{
		Zoom = 1.0f;
	}
	if (Zoom > 45.0f)
	{
		Zoom = 45.0f;
	}*/
	camera.zoomCamera(yoffset);
};