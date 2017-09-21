#version 330 core
layout (location = 0) in vec3 position;

out vec3 Pos;

uniform mat4 view_projection;
uniform mat4 model;

void main()
{
    gl_Position = view_projection * model * vec4(position, 1.0f);
	Pos = position;
}