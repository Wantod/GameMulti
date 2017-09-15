#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 pPos;

out vec3 ourColor;
out vec4 viewSpace;
out vec3 world_pos;

void main()
{
	world_pos = (model * vec4(position, 1.0)).xyz - pPos;
	viewSpace = view * model * vec4(position, 1.0);
    gl_Position = projection * viewSpace;
	
    ourColor = color;
}
