#version 410 core

in VertexData {
	vec4 normal;
} VertexIn;

out vec4 color;

void	main()
{

	float dot = dot( VertexIn.normal, normalize(vec4(-1, -2, -3, 0)) );
	if (dot < 0.1)
	{
		color = vec4(0.1, 0.1, 0, 1);
		return;
	}

	color = vec4(dot, dot, 0, 1);
}