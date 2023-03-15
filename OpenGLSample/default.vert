#version 330 core
layout (location = 0) in vec 3 aPos;
layout (location = 1) in vec 3 aColor;

layout (location - 2) in vec 2 aTex;

out vec3 color;

out vec2 texCoord;

uniform float scale;

void main()
{
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z aPos.z * scale, 1.0);
	color = aColor;
	texCoord = aTex;
}