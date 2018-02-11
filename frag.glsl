#version 410 core

in VertexData {
	vec4 normal;
	vec3 color;
} VertexIn;

out vec3 color;

void	main()
{

	float dot = dot( normalize(VertexIn.normal), normalize(vec4(-1, -2, -3, 0)) );

	if (dot < 0.1)
	{
		color = VertexIn.color * 0.1;
		return;
	}

	color = VertexIn.color * dot;
}