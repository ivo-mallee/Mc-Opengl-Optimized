//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include <time.h>    
#include "ChunkSet.h"
#include "multi threading objects.h"
#include<thread>

int VOffset = 0;
int IOffset = 0;
int IOffsetArray[1024];
const unsigned int width = 1920;
const unsigned int height = 1000;
int MAX = 0;
long total = 0;

GLint XarrayForShader[1024];
GLint ZarrayForShader[1024];
GLint UniformChunkIdID;
GLint XarrayId;
GLint ZarrayId;
Camera camera(width, height, glm::vec3(0.0f, 400.0f, -10.0f));


void CheckForRemeshFlags(ChunkSet &WorldSet, GLuint (&indices)[300000],GLuint (&vertices)[1572864],VBO (&VBO1A)[1024],EBO (&EBO1A)[1024],VAO (&VAO1)[1024])
{

	// Generates Vertex Array Object and binds it
	for (int X = 0; X < 32; X++)
	{
		for (int Z = 0; Z < 32; Z++)
		{
			int i = (Z * 32) + X;

			if (WorldSet.SET[X][Z].ReMeshFlag == true) {
				VAO1[i].Bind(); //problem when multithreading
				WorldSet.GenerateMesh(indices, vertices, X, Z);
				VOffset = WorldSet.VOffset;
				IOffset = WorldSet.IOffset;

				IOffsetArray[i] = IOffset;
				// Generates Vertex Buffer Object and links it to vertices

				VBO1A[i].Set(vertices, VOffset * 4);
				// Generates Element Buffer Object and links it to indices
				EBO1A[i].Set(indices, IOffset * 6);
				// Links VBO attributes such as coordinates and colors to VAO
				VAO1[i].LinkAttrib(VBO1A[i], 0, 1, GL_INT, 1 * sizeof(GLuint), (void*)0);
				// Unbind all to prevent accidentally modifying them
				VAO1[i].Unbind();
				VBO1A[i].Unbind();
				EBO1A[i].Unbind();

				XarrayForShader[i] = WorldSet.SET[X][Z].ChunkX;
				ZarrayForShader[i] = WorldSet.SET[X][Z].ChunkY;
			}



		}

	}
	glUniform1iv(XarrayId, 1024, XarrayForShader);
	glUniform1iv(ZarrayId, 1024, ZarrayForShader);



}






VBO VBO1A[1024];
VAO VAO1[1024];
EBO EBO1A[1024];

GLuint indices[300000];
GLuint vertices[1572864];
ChunkSet WorldSet;
GLFWwindow* window;
int ObjectRemeshed = 0;
MultiThreadingRemeshObject RemeshObjectSet[20];
bool RemeshThreadDone = false;
void ReGenThread() 
{
	while (true) {
		for (int X = 0; X < 32; X++)
		{
			for (int Z = 0; Z < 32; Z++)
			{
				int i = (Z * 32) + X;

				if (WorldSet.SET[X][Z].ReGenFlag == true) {
					GenerateWorld(WorldSet.SET[X][Z]);
				}



			}

		}
	}
}



void ChunkSetterThread() 
{
while (true) 
{

	for (float i = 0; i < 359; i += 1) {


		for (int P = 1; P < 15; P++) {
			int X = cos(i) * P;
			int Y = sin(i) * P;
			int LOCY = (int)(camera.Position.z / 30) + Y;
			int LOCX = ((int)(camera.Position.x / 30) - 1) + X;
			int ChunkX;
			int ChunkY;
			WorldSet.GetFurthestChunk(LOCX, LOCY, ChunkX, ChunkY);

			if (WorldSet.IsChunkSpotavailable(LOCX, LOCY))

			{
				WorldSet.MoveChunk(ChunkX, ChunkY, LOCX, LOCY);
			}
		}

	}
}}




void remeshThread() 
{
	while (true) {
		if (RemeshThreadDone == false) {
			for (int X = 0; X < 32; X++)
			{
				for (int Z = 0; Z < 32; Z++)
				{
					int i = (Z * 32) + X;

					if (WorldSet.SET[X][Z].ReMeshFlag == true && ObjectRemeshed < 19) {
						WorldSet.FindChunkNeighbhors(X, Z);
						WorldSet.GenerateMesh(RemeshObjectSet[ObjectRemeshed].indices, RemeshObjectSet[ObjectRemeshed].vertices, X, Z);
						RemeshObjectSet[ObjectRemeshed].Ioffset = WorldSet.IOffset;
						RemeshObjectSet[ObjectRemeshed].Voffset = WorldSet.VOffset;
						RemeshObjectSet[ObjectRemeshed].ArrayOffset = i;
						RemeshObjectSet[ObjectRemeshed].LocX = WorldSet.SET[X][Z].ChunkX;
						RemeshObjectSet[ObjectRemeshed].LocY = WorldSet.SET[X][Z].ChunkY;
						ObjectRemeshed++;

					}



				}

			}
			if (ObjectRemeshed != 0) { RemeshThreadDone = true; }
		}
	}
}


void CheckMeshQueue()
{
	if (ObjectRemeshed != 0 && RemeshThreadDone == true)
	{
		for (int i = 0; i < ObjectRemeshed; i++)
		{
			int arrayOffset = RemeshObjectSet[i].ArrayOffset;
			VAO1[arrayOffset].Bind(); //problem when multithreading


			IOffsetArray[arrayOffset] = RemeshObjectSet[i].Ioffset;
			// Generates Vertex Buffer Object and links it to vertices

			VBO1A[arrayOffset].Set(RemeshObjectSet[i].vertices, RemeshObjectSet[i].Voffset * 4);
			// Generates Element Buffer Object and links it to indices
			EBO1A[arrayOffset].Set(RemeshObjectSet[i].indices, RemeshObjectSet[i].Ioffset * 6);
			// Links VBO attributes such as coordinates and colors to VAO
			VAO1[arrayOffset].LinkAttrib(VBO1A[arrayOffset], 0, 1, GL_INT, 1 * sizeof(GLuint), (void*)0);
			// Unbind all to prevent accidentally modifying them
			VAO1[arrayOffset].Unbind();
			VBO1A[arrayOffset].Unbind();
			EBO1A[arrayOffset].Unbind();

			XarrayForShader[arrayOffset] = RemeshObjectSet[i].LocX;
			ZarrayForShader[arrayOffset] = RemeshObjectSet[i].LocY;
		}
		ObjectRemeshed = 0;
		RemeshThreadDone = false;
		glUniform1iv(XarrayId, 1024, XarrayForShader);
		glUniform1iv(ZarrayId, 1024, ZarrayForShader);

	}



}


int main() 
{	


	
	WorldSet.INIT();
	

	
	initGeneration();
	WorldSet.GenerateSet();
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object
	window = glfwCreateWindow(width, height, "MC clone", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);


	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	shaderProgram.Activate();
	
	for (int i = 0; i < 1024; i++)
	{
		VAO1[i].SET(); //generates the vertex arrays
	}
	

	
	
	UniformChunkIdID = glGetUniformLocation(shaderProgram.ID, "ChunkID");

	XarrayId = glGetUniformLocation(shaderProgram.ID, "Xvalues");
	ZarrayId = glGetUniformLocation(shaderProgram.ID, "Zvalues");

	std::string TextureFolder = (fs::current_path().string() + "\\TEXTURE.png");


	Texture textureAtlas(TextureFolder.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	textureAtlas.texUnit(shaderProgram, "tex0", 0);


	


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	
	

	//setup our required threads
	
	std::thread RemeshThread(remeshThread);

	std::thread ReGenThread(ReGenThread);

	std::thread ChunkSetterThread(ChunkSetterThread);







	//start the main game loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(1.00f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		




		CheckMeshQueue();
		

		




		
		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 2000.0f, shaderProgram, "camMatrix");

		// Binds texture so that is appears in rendering
		textureAtlas.Bind();
		
		
		// Draw primitives, number of indices, datatype of indices, index of indices
		for (int i = 0; i < 1024; i++) {
			glUniform1i(UniformChunkIdID, i);
			VAO1[i].Bind(); // Bind the VAO so OpenGL knows to use it
			glDrawElements(GL_TRIANGLES, IOffsetArray[i] * 6 / sizeof(int), GL_UNSIGNED_INT, 0);
			VAO1[i].Unbind(); //unbind the VAO
		}
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	
	for (int i = 0; i < 1024;i++) {
		VAO1[i].Delete();
		VBO1A[i].Delete();
		EBO1A[i].Delete();
	}
	


	//detach our threads

	RemeshThread.detach();

	ReGenThread.detach();

	ChunkSetterThread.detach();








	textureAtlas.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}