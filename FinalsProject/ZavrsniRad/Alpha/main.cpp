#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include <assimp\Importer.hpp>

//#include "StbImage.h"

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "Material.h"
#include "Model.h"
#include "Skybox.h"




Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;

Material shinyMaterial;
Material dullMaterial;

Model xwing;
Model blackhawk;
Model testModel;
Model imperialStarDestroyer;
Model moon;
Model sun;

GLfloat startingAngle = 0.0f;

DirectionalLight mainLight;
Skybox skybox;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";
//Fragment shader
static const char * fShader = "Shaders/shader.frag";

//const char * brickTexturepath = "Textures/brick.png";






void CreateShaders() {
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(shader1);
}

void RenderModels(const GLuint &uniformModel, const GLuint &uniformSpecularIntensity, const GLuint &uniformShininess)
{
	glm::mat4 model{ 1.0f };


	
	startingAngle += 0.1f;
	if (startingAngle > 360.0f)
	{
		startingAngle = 0.1f;
	}


	// FOR voyager
	model = glm::mat4{ 1.0f };
	model = glm::translate(model, glm::vec3(-8.0f, 2.0f, 0.0f));
	model = glm::rotate(model, glm::radians(+startingAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-8.0f, 2.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	testModel.RenderModel();


	// FOR moon
	model = glm::mat4{ 1.0f };
	model = glm::translate(model, glm::vec3(10.0f, -10.0f, -3.0f));
	model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, glm::radians(startingAngle), glm::vec3(0.0f, 0.5, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	moon.RenderModel();
}

void Render(GLuint &uniformModel, GLuint &uniformProjection, GLuint &uniformView, GLuint &uniformEyePosition, GLuint &uniformSpecularIntensity, GLuint &uniformShininess, glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	// s cim ocistiti sto
	// clear window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// what needs to be "cleared"
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox.DrawSkyBox(viewMatrix, projectionMatrix);

	shaderList[0]->UseShader();
	uniformModel = shaderList[0]->GetModelLocation();
	uniformProjection = shaderList[0]->GetProjectionLocation();
	uniformView = shaderList[0]->GetViewLocation();
	uniformEyePosition = shaderList[0]->GetEyePositionLocation();
	uniformSpecularIntensity = shaderList[0]->GetSpecularIntensityLocation();
	uniformShininess = shaderList[0]->GetShininessLocation();



	shaderList[0]->SetDirectionalLight(&mainLight);



	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
	glUniform3f(uniformEyePosition, camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);
}

int main(int argc, char** argv)
{
	Window mainWindow = Window(1366, 768);
	mainWindow.InitialiseWindow();

	
	CreateShaders();

	// camera init (-180.0f can be put as -90.0f but have 2 find still
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);

	
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureAlpha();

	shinyMaterial = Material(4.0f, 256);
	dullMaterial = Material(0.3f, 4);
	
	
	testModel.LoadModel("Models/voyager.obj", "Voyager"); 
	moon =  Model();
	moon.LoadModel("Models/Death_Star.obj", "DeathStar");

	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
									0.2f, 0.6f,
									0.0f, 0.0f, -1.0f);

	
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/purplenebula_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/purplenebula_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/purplenebula_up.tga");
	skyboxFaces.push_back("Textures/Skybox/purplenebula_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/purplenebula_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/purplenebula_ft.tga");

	skybox = Skybox(skyboxFaces);

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(), 0.1f, 100.0f);

	while (mainWindow.GetWindowShouldClose() == false)
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now; 

		Render(uniformModel, uniformProjection, uniformView, uniformEyePosition, uniformSpecularIntensity, uniformShininess, projection, camera.CalculateViewMatrix());

		RenderModels(uniformModel, uniformSpecularIntensity, uniformShininess);

		//unassign shader
		glUseProgram(0);

		mainWindow.SwapBuffers();

		// get and handle user input events - check for any actiosn like key presses, etc.
		glfwPollEvents();

		//check for key presses
		camera.KeyboardControl(mainWindow.GetKeyboardKeys(), deltaTime);
		camera.MouseControl(mainWindow.GetXChange(), mainWindow.GetYChange());
	}
	return 0;
}


