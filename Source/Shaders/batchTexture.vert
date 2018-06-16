#version 330 core

layout ( location = 0) in vec4 position;
layout ( location = 1) in vec4 colour;
layout ( location = 2) in vec2 texCoords;
layout ( location = 3) in float tSlot;
layout ( location = 4) in float useColour;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out DATA{

	vec4 position;
	vec4 colour;
	vec2 texcoord;
	float tslot;
	float useColour;

} vs_out;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
	vs_out.position = ml_matrix * position;
	vs_out.colour = colour;
	vs_out.texcoord = texCoords;
	vs_out.tslot = tSlot;
	vs_out.useColour = useColour;
}