#version 410 core

in VertexData {
	vec4 normal;
	vec3 color;
	vec3 dis;
} VertexIn;

out vec3 color;

void	main()
{
	float nearD = min(min(VertexIn.dis[0], VertexIn.dis[1]), VertexIn.dis[2]);

	if (nearD < 0.05)
	{
		color = vec3(0.3, 0.3, 0.3);
		return;
	}

	float dot = dot( normalize(VertexIn.normal), normalize(vec4(-1, -2, -3, 0)) );

	if (dot < 0.1)
	{
		color = VertexIn.color * 0.1;
		return;
	}

	color = VertexIn.color * dot;
}