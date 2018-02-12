#version 410 core

layout(location = 0) in int point;
layout(location = 1) in int index;

uniform mat4 transform;
uniform mat4 perspective;

out	BlockData {
	int raw;
} Block;

vec4	GenerateVertex(int point, int index)
{
	float x = index % 10;
	index /= 10;
	float y = index % 10;
	float z = index / 10;
	return vec4(x - 4.5, y - 4.5, z - 4.5, 1);
}

void	main()
{
	vec4 Vertex = GenerateVertex(point, index);
	gl_Position = Vertex;
	Block.raw = point;
}