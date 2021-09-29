#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Gets the Texture Unit from the main function
in vec3 test;

uniform sampler2D tex0;


void main()
{
	 FragColor = texture(tex0, texCoord)/test.x;
	  //FragColor = vec4(color.x,color.y,color.z,255);
}