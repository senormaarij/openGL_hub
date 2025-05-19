#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//shader src code --- dont need to know what it does for now 
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";
using namespace std;





int main() {
	
	glfwInit(); //init GLFW

	//Tell GLFW which verison we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tell GLFW we are using core profile so modern funcs 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.5f, -0.0f, 0.0f, // Lower left corner
		0.5f, 0.0f, 0.0f, // Lower right corner
		0.0f, 0.5f, 0.0f // Upper corner
	};



	GLFWwindow* window = glfwCreateWindow(600, 800, "Yippee", NULL, NULL);

	if (window == NULL) {
		cout << "Failed to init the window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); //tells the glfw to use the window


	// load GLAD to config OpenGL
	gladLoadGL();

	// specifies the viewport to OpenGL 
	// the screen begins from bottom Left, x = 0, y = 0 uptil the window size 
	glViewport(0, 0, 600, 800);


	//Vertex Shader 
	//shaders are OpenGL obj; all OGL obj are accessed by references
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER); //obj ref int/num is return we store that
	glShaderSource(vertex_shader, 1, &vertexShaderSource, NULL);
	//GPU cant understand the shader src code so we compile into Machine code 
	glCompileShader(vertex_shader);


	//Fragment Shader
	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader, 1, &fragmentShaderSource, NULL);
	glCompileShader(frag_shader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertex_shader);

	glAttachShader(shaderProgram, frag_shader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertex_shader);
	glDeleteShader(frag_shader);

	//sending things form CPU to GPU is dogshit so use buffers/batches to send them
	//this isnt same as front and back buffer

	GLuint VAO, VBO; //usually an array but since only one object so 1; VAO (Vertex Array Object)
	
	glGenVertexArrays(1, &VAO); //should come first, to tell OGL where to find the Vertex Data

	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	//binding making an obj a current obj in OG,
	//so whenver we modify the obj, it modifies the current obj
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //using GL_ARRAY_BUFFER bcuz thats the type of buffer for vertex

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	
	//specifies the color of the bg 
	glClearColor(0.0f, 0.07f, 0.17f, 1.0f);

	//clear the back buffer and assign the new color to it 
	glClear(GL_COLOR_BUFFER_BIT);

	// swaps the back and front buffer/frames 
	glfwSwapBuffers(window);

	
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.0f, 0.07f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		 
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);




		glfwPollEvents(); // to process events in the window else it will be in a state of not responding 


	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}