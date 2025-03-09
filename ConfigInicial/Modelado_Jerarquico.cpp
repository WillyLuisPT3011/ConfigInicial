//Práctica 5: Modelado Jerárquico en OpenGL
//Arroyo Chavarría José Luis
//Número de cuenta : 317290967
//Fecha : 04 / 03 / 2025

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = -3.0f,
movY = 0.0f,
movZ = -10.0f,
rot = 0.0f;

//For model
float	hombro = 0.0f;
float	codo = -2.60f;
float	muneca = 0.0f;

float	dedo1 = 0.0f;
float	falanged1 = 0.0f;

float	dedo2 = 0.0f;
float	falanged2 = 0.0f;

float	dedo3 = 0.0f;
float	falanged3 = 0.0f;

float	dedo4 = 0.0f;
float	falanged4 = 0.0f;

//movimiento
float hombro_max_mov_up = 85.0f;
float hobro_max_mov_down = -90.0f;

float bicep_max_mov_up = 110.0f;
float bicep_max_mov_down = -1.0f;

float muneca_max_mov_up = 100.0f;
float muneca_max_mov_down = -37.0f;

float dedo_max_mov_up = 22.0f;
float dedo_max_mov_down = -3.0f;
float falange_max_mov_up = 5.0f;
float falange_max_mov_down = -30.0f;

int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 5: Modelado Jerarquico_Jose Luis_Arroyo", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificaci�n de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);

	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f, -0.5f,-0.5f,
		 0.5f, -0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		-0.5f,  0.5f,-0.5f,
		-0.5f, -0.5f,-0.5f,

		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp2

		//View set up 
		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		glBindVertexArray(VAO);

		//Model Bicep
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //hombro
		modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));//Escala del Bicep para su tamaño deseado
		color = glm::vec3(0.0f, 0.0f, 1.0f);// Define el color RGB
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//A

		//Model Antebrazo 
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 1.0, 0.0f)); 
		modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));//Escala del antebrazo para su tamaño deseado
		color = glm::vec3(0.0f, 1.0f, 1.0f);// Define el color RGB
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//B

		//Model Palma 
		model = glm::translate(modelTemp, glm::vec3(1.25f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(muneca), glm::vec3(1.0f, 0.0, 0.0f)); //Rotacion de muñeca en x
		modelTemp2 = modelTemp = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f)); 
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//C

		//Dedos

		//Model dedo1
		model = glm::translate(modelTemp, glm::vec3(0.005f, 0.35f, 0.375f));
		model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0, 1.0f)); //Rotacion en Z
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 0.0f);// Define el color RGB 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		//Model Falange2_Dedo1
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.00f, 0.0f)); //Acomodo el falange al final del dedo1
		model = glm::rotate(model, glm::radians(falanged1), glm::vec3(0.0f, 0.0, 1.0f));//Rotacion en Z
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);// Define el color RGB
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//F

		//Modelo Dedo1 C
		model = glm::translate(modelTemp, glm::vec3(0.32f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(falanged1), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.5f, 0.0, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//F

		//Para solucionar esto usaremos el modelTemp2 para resetear el modelTemp a sus coordenadas originales de la palma
		//modedlTemp normal sera para unir las articulaciones
		
		//Model dedo2
		//modeltemp2 pasa la palma punto de partida para colocar los dedos
		model = glm::translate(modelTemp2, glm::vec3(0.005f, 0.35f, -0.0f));
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);// Define el color RGB 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//G

		//Model Falange2_Dedo2
		//model Temp maneja donde esta el dedo 2 se le agrea 1 en x para que este al final 
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0));
		model = glm::rotate(model, glm::radians(falanged2), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 0.0f, 1.0f);// Define el color RGB
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//H 

		//Modelo Dedo2 C
		model = glm::translate(modelTemp, glm::vec3(0.32f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(falanged2), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.5f, 0.0, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//I

		//Model dedo3
		//modeltemp3 pasa la palma punto de partida para colocar los dedos
		model = glm::translate(modelTemp2, glm::vec3(0.005f, 0.35f, -0.4f));
		model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //reasignacion del modelTemp para la articulacion
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);// Define el color RGB 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//J

		//Model Falange3_Dedo3
		//model Temp maneja donde esta el dedo 3 se le agrea 1 en x para que este al final 
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0));
		model = glm::rotate(model, glm::radians(falanged3), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 0.0f);// Define el color RGB
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//K 

		//Modelo Dedo3 C
		model = glm::translate(modelTemp, glm::vec3(0.32f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(falanged3), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.5f, 0.0, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//L

		//Model dedo4
		//modeltemp4 pasa la palma punto de partida para colocar los dedos
		model = glm::translate(modelTemp2, glm::vec3(0.005f, -0.35f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo4), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //reasignacion del modelTemp para la articulacion
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 1.0f, 0.0f);// Define el color RGB 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//M

		//Model Falange4_Dedo4
		//model Temp maneja donde esta el dedo 4 se le agrea 1 en x para que este al final 
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0));
		model = glm::rotate(model, glm::radians(falanged4), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); //Pivote matriz auxiliar para trasladar el modelo
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);// Define el color RGB
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//N

		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
}

/* Ajustar a movimientos naturales de un humano*/

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.15f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.15f;

	//Movimiento hombros
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		hombro = (hombro >= hombro_max_mov_up) ? hombro : hombro + 0.18f;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		hombro = (hombro <= hobro_max_mov_down) ? hombro : hombro - 0.18f;

	//movimiwnro bicep
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		codo = (codo <= -bicep_max_mov_up) ? codo : codo - 0.18f;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		codo = (codo >= -bicep_max_mov_down) ? codo : codo + 0.18f;

	//movimiento muneca
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		muneca = (muneca <= -muneca_max_mov_up) ? muneca : muneca - 0.18f;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		muneca = (muneca >= -muneca_max_mov_down) ? muneca : muneca + 0.18f;

	// Dedo1
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		dedo1 = (dedo1 >= dedo_max_mov_up) ? dedo1 : dedo1 + 0.18f;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		dedo1 = (dedo1 <= dedo_max_mov_down) ? dedo1 : dedo1 - 0.18f;
	//Falange2 Dedo1 
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		falanged1 = (falanged1 >= falange_max_mov_up) ? falanged1 : falanged1 + 0.18f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		falanged1 = (falanged1 <= falange_max_mov_down) ? falanged1 : falanged1 - 0.18f;

	// Dedo2 
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		dedo2 = (dedo2 >= dedo_max_mov_up) ? dedo2 : dedo2 + 0.18f;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		dedo2 = (dedo2 <= dedo_max_mov_down) ? dedo2 : dedo2 - 0.181f;
	//Falange2 Dedo2 
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		falanged2 = (falanged2 >= falange_max_mov_up) ? falanged2 : falanged2 + 0.18f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		falanged2 = (falanged2 <= falange_max_mov_down) ? falanged2 : falanged2 - 0.18f;

	// Dedo3
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		dedo3 = (dedo3 >= dedo_max_mov_up) ? dedo3 : dedo3 + 0.18f;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		dedo3 = (dedo3 <= dedo_max_mov_down) ? dedo3 : dedo3 - 0.18f;
	//Falange3 Dedo3 
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		falanged3 = (falanged3 >= falange_max_mov_up) ? falanged3 : falanged3 + 0.18f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		falanged3 = (falanged3 <= falange_max_mov_down) ? falanged3 : falanged3 - 0.18f;


	// Dedo4
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		dedo4 = (dedo4 <= -dedo_max_mov_up) ? dedo4 : dedo4 - 0.18f;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		dedo4 = (dedo4 >= -dedo_max_mov_down) ? dedo4 : dedo4 + 0.18f;
	//Falange4 Dedo4 
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		falanged4 = (falanged4 <= -falange_max_mov_up) ? falanged4 : falanged4 - 0.18f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		falanged4 = (falanged4 >= -falange_max_mov_down) ? falanged4 : falanged4 + 0.18f;

}