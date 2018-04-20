#version 330 core

layout (location = 0) out vec4 colour;

uniform vec2 light_pos;
uniform sampler2D texture0;

in DATA{
	vec4 position;
	vec4 colour;
	vec2 texcoord;
} fs_in;

float ambience = 0.2;

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	colour = ( fs_in.colour * 0.2 + texture(texture0, fs_in.texcoord)) * ( intensity + ambience ) ;
	// colour = fs_in.colour;
}