//Práctica 4: Modelado geométrico
//Arroyo Chavarría José Luis
//Número de cuenta : 317290967
//Fecha : 02 / 03 / 2025

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Práctica 4_Modelado geometrico_JoseLuisArroyo", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,1.0f,//Front
		0.5f, -0.5f, 0.5f,  0.0f, 0.0f,1.0f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.0f,1.0f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.0f,1.0f,
		-0.5f,  0.5f, 0.5f, 0.0f, 0.0f,1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,1.0f,

		-0.5f, -0.5f,-0.5f, 1.0f, 0.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 1.0f, 0.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 0.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 0.0f,0.0f,
		-0.5f,  0.5f,-0.5f, 1.0f, 0.0f,0.0f,
		-0.5f, -0.5f,-0.5f, 1.0f, 0.0f,0.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,//lado derecho
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 1.0f,1.0f,

		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,//lado IZQUIERDO
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,0.0f, //arriba
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,0.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,0.0f, //abajo
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f,0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,0.0f,

	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);
		
		// Capturas con lo datos/codigo
		// 1 pie 
	    model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 3.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f)); //Posicion
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		// 1 detalle de bota 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 0.7f, 3.0f)); //Tamaño
		model = glm::translate(model, glm::vec3(0.0f, 1.8f, -0.08f)); //Posicion
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 2 pie 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 3.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(2.0f, 0.5f, 0.0f)); //Posicion
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 2 detalle de bota 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 0.7f, 3.0f)); //Tamaño
		model = glm::translate(model, glm::vec3(2.0f, 1.8f, -0.08f)); //Posicion
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// torso 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(4.0f, 5.5f, 2.5f)); //Tamaño
		model = glm::translate(model, glm::vec3(0.5f, 0.79f, -0.6f)); //Posicion
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// cuello 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(3.0f, 0.5f, 1.5f)); //Tamaño
		model = glm::translate(model, glm::vec3(0.65f, 14.5f, -1.0f)); //Posicion
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// cabeza 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(5.0f, 5.5f, 5.0f)); //Tamaño
		model = glm::translate(model, glm::vec3(0.4f, 1.85f, -0.28f)); //Posicion
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		// pico 1 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(0.0f, 7.94f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(0.0f, 7.94f, -5.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(0.0f, 7.94f, -6.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(0.0f, 8.94f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(0.0f, 8.94f, -5.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(0.0f, 9.94f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// pico 2 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(4.0f, 7.94f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(4.0f, 7.94f, -5.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(4.0f, 7.94f, -6.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(4.0f, 8.94f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(4.0f, 8.94f, -5.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(4.0f, 9.94f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// pico 3 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(2.0f, 10.48f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(2.0f, 10.48f, -5.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(2.0f, 10.48f, -6.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(2.0f, 11.48f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(2.0f, 11.48f, -5.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(2.0f, 12.48f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// pico 4 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(2.0f, 7.94f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(2.0f, 7.94f, -5.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(2.0f, 8.94f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// pico 5 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(3.0f, 9.94f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(3.0f, 9.94f, -5.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(3.0f, 10.94f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// pico 6 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(1.0f, 9.94f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(1.0f, 9.94f, -5.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(1.0f, 10.94f, -4.4f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Hombro 1 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(-0.5f, 5.94f, -1.5f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Hombro 2 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(2.5f, 5.94f, -1.5f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brazo 1 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 3.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(6.5f, 1.65f, -1.5f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brazo 2 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 3.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(-2.5f, 1.65f, -1.5f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// mano 1 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(-1.27f, 1.25f, -0.76f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// mano 2 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(3.27f, 1.25f, -0.76f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// oreja 1 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.5f, 0.5f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(4.0f, 9.0f, -0.76f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// oreja 2 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.0f, 1.5f, 0.5f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(0.0f, 9.0f, -0.76f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// hocico 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.5f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(1.4f, 9.5f, 0.76f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Nariz 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(4.3f, 19.0f, 4.0f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Boca 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(5.0f, 2.5f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(0.4f, 3.5f, 1.0f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Panza 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(2.5f, 3.0f, 0.5f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(0.82f, 1.5f, 0.0f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojos 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(5.0f, 2.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(0.4f, 5.6f, 1.0f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(2.0f, 2.49f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(0.25f, 4.6f, 1.0f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(1.64f, 2.49f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(2.25f, 4.6f, 1.0f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Pupilas 
		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(0.5f, 2.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(2.5f, 5.6f, 1.25f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);  // Restablecer matriz de modelo
		model = glm::scale(model, glm::vec3(0.5f, 2.0f, 1.0f)); // Ajusta el tamaño del pico
		model = glm::translate(model, glm::vec3(6.25f, 5.6f, 1.25f)); // Ajusta la posición del pico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.4f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.4f;
 }


