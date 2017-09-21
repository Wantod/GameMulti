#version 330 core

in vec3 ourColor;
in vec4 viewSpace;
in vec3 world_pos;

out vec4 color;

uniform float near;
uniform float far;

void main()
{
	float dist = length(world_pos.xz);
	
	float fogFactor;
	fogFactor = (far - dist)/(far - near);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );
	
	//if you inverse color in glsl mix function you have to
	//put 1.0 - fogFactor
	vec3 finalColor = mix(vec3(0.0901,0.12549,0.16078), ourColor, fogFactor);
	
	// Gama correction
	//float gamma = 1.0 / 2.2;
	//color = pow(color, gamma);
    color = vec4(finalColor, 1.0f);
}
