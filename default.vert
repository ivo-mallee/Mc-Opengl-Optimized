#version 330 core

// Positions/Coordinates
layout (location = 0) in uint DATA;



// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;
// Imports the camera matrix from the main function
out vec3 test;
uniform mat4 camMatrix;



uniform int ChunkID;
uniform int Xvalues[1024];
uniform int Zvalues[1024];
uniform float PlayerX;
uniform float PlayerY;
uniform float PlayerZ;
uniform int ObjInfo;





void main()
{




	vec3 Offset = vec3(Xvalues[ChunkID],0,Zvalues[ChunkID]) *15;

	
    float Values[5];
    
    Values[0] = (DATA >> 8) % 16; //X
    Values[1] = DATA % 256;  //Y
    Values[2] = (DATA >> 12) % 16; //Z
    Values[3] = (DATA >> 16) % 16; //TX
    Values[4] = (DATA >> 20) % 16; //TY
	test.x = (DATA >> 24) % 256; //LightLevel

	vec3 aPos;
	


	

if (ObjInfo ==0) {	aPos = vec3(Values[0]*2,Values[1]*2,Values[2]*2); aPos = aPos + Offset*2;} //if its a normal cube
if (ObjInfo ==1) {	aPos = vec3(Values[0]*2000,Values[1]*2000,Values[2]*2000); } //if its a skybox Cube

	 if (PlayerX ==1 && PlayerY == 1 && PlayerZ ==1 && ObjInfo == 1) {aPos = vec3(535.0,352.0,533.0);}	


	

	vec2 aTex = vec2(0.0625*(Values[3]+1),0.0625*(Values[4]+1));
	
	
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(aPos, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
	color = vec3(0.5,0.5,0.5);
	if (Values[0] == 6) {color = vec3(1.0,0.5,0.5);} //if X = 6
}