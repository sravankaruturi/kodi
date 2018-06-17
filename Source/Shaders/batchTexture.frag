#version 330 core

layout (location = 0) out vec4 colour;

uniform vec2 light_pos;
uniform sampler2D textures[32];

in DATA{
	vec4 position;
	vec4 colour;
	vec2 texcoord;
	float tslot;
	float useColour;
} fs_in;

float ambience = 0.4;

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);

	if ( fs_in.tslot <= 0){

		colour = ( fs_in.colour * ( intensity + ambience )) ;

	}else{

		//	Thappu cast avvakundaa.
		int index = int(fs_in.tslot - 0.5);

		// colour = (texture(textures[index], fs_in.texcoord) + (fs_in.colour * fs_in.useColour)) * ( intensity + ambience )/(fs_in.useColour + 1) ;
		colour = (texture(textures[index], fs_in.texcoord) + (fs_in.colour * fs_in.useColour)) /(fs_in.useColour + 1) ;
		// colour = vec4(fs_in.useColour, 1.0, 0.0, 1.0);
		// colour = vec4(1, 1, 1, 1);
		// colour = fs_in.colour;
		// colour = texture(textures[index], fs_in.texcoord) * (intensity + ambience);
	}

	
}