#version 330 core

layout (location = 0) out vec4 colour;

uniform vec2 light_pos;
uniform sampler2D textures[32];

in DATA{
	vec4 position;
	vec4 colour;
	vec2 texcoord;
	float tslot;
} fs_in;

float ambience = 1;

void main()
{
	// float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	float intensity = ambience;

	colour = fs_in.colour * intensity;
	// colour = vec4(1, 0, 1, 1);

}
