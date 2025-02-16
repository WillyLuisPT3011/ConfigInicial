#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);
const GLint WIDTH = 800, HEIGHT = 600;

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2 Dibujo de primitivas_Jose Luis_Arroyo", NULL, NULL);
    glfwSetFramebufferSizeCallback(window, resize);

    if (window == NULL) {
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

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    float vertices[] = {
        // Triángulo rectángulo izquierdo (pico)
        -0.2f,   0.4f,   0.0f,     1.0f, 0.0f, 0.0f,  // Vértice izquierdo (0)
         0.0f,   0.6f,   0.0f,     1.0f, 0.0f, 0.0f,  // Vértice superior (1)
         0.0f,   0.4f,   0.0f,     1.0f, 0.0f, 0.0f,  // Vértice medio (2)

         // Triángulo rectángulo derecho (cabeza)
         0.2f,   0.4f,   0.0f,     0.0f, 1.0f, 0.0f,  // Vértice derecho (3)
         0.0f,   0.6f,   0.0f,     0.0f, 1.0f, 0.0f,  // Vértice superior (4)
         0.0f,   0.4f,   0.0f,     0.0f, 1.0f, 0.0f,  // Vértice medio (5)

         // Cuadrado (Cuello)
         0.0f,   0.4f,   0.0f,     0.0f, 0.0f, 1.0f,  // Superior izquierdo (6)
         0.2f,   0.4f,   0.0f,     0.0f, 0.0f, 1.0f,  // Superior derecho (7)
         0.0f,   0.2f,   0.0f,     0.0f, 0.0f, 1.0f,  // Inferior izquierdo (8)
         0.2f,   0.2f,   0.0f,     0.0f, 0.0f, 1.0f,  // Inferior derecho (9)

         // Triángulo debajo del cuadrado (pecho)
         0.0f,   0.2f,   0.0f,     1.0f, 1.0f, 0.0f,  // Punto superior (10) 
         0.2f,   0.2f,   0.0f,     1.0f, 1.0f, 0.0f,  // Punto derecho (11) 
         0.2f,   0.0f,   0.0f,     1.0f, 1.0f, 0.0f,  // Punto inferior (12)

         // Triángulo rectángulo (pata izquierda)
         0.0f,  -0.2f,   0.0f,     1.0f, 0.0f, 1.0f,  // Vértice izquierdo (13)
         0.2f,   0.0f,   0.0f,     1.0f, 0.0f, 1.0f,  // Vértice superior (14)
         0.2f,  -0.2f,   0.0f,     1.0f, 0.0f, 1.0f,  // Vértice medio (15)

         // Cuadrado al lado derecho del triángulo (pecho)
         0.2f,   0.0f,   0.0f,     1.0f, 1.0f, 1.0f,  // Vértice inferior izquierdo (16)  
         0.4f,   0.0f,   0.0f,     1.0f, 1.0f, 1.0f,  // Vértice inferior derecho (17) 
         0.2f,   0.2f,   0.0f,     1.0f, 1.0f, 1.0f,  // Vértice superior izquierdo (18)  
         0.4f,   0.2f,   0.0f,     1.0f, 1.0f, 1.0f,  // Vértice superior derecho (19)

         // Triángulo rectángulo a la derecha del cuadrado (cola)
         0.6f,   0.2f,   0.0f,     0.0f, 1.0f, 1.0f,  // Vértice derecho (20)
         0.4f,   0.2f,   0.0f,     0.0f, 1.0f, 1.0f,  // Vértice izquierdo superior (21)
         0.4f,   0.0f,   0.0f,     0.0f, 1.0f, 1.0f,  // Vértice izquierdo inferior (22)

         // Triángulo rectángulo (pata derecha)
         0.6f,   0.0f,   0.0f,     0.0f, 1.0f, 0.0f,  // Vértice derecho superior (23)
         0.4f,   0.0f,   0.0f,     1.0f, 0.0f, 0.0f,  // Vértice izquierdo superior (24)
         0.6f,  -0.2f,   0.0f,     0.0f, 0.0f, 1.0f   // Vértice derecho inferior (25)

    };

    unsigned int indices[] = { 
        0, 1, 2,                // Triángulo izquierdo
        3, 4, 5,                // Triángulo derecho
        6, 7, 8, 7, 8, 9,       // Cuadrado
        10, 11, 12,             // Triángulo invertido debajo del cuadrado
        13, 14, 15,             // Triángulo izquierdo debajo del anterior triangulo puesto
        16, 17, 18, 17, 18, 19, // Cuadrado a lado del triangulo invertido
        20, 21, 22,             // Triángulo invertido a lado del cuadrado
        23, 24, 25              // Triángulo invertido debajo del anterior triangulo puesto
    };


    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}