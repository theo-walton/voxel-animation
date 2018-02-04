#version 410 core

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

uniform mat4 transform;
uniform mat4 perspective;

in BlockData {
	int exist;
} Block[];

out VertexData {
	vec4 normal;
} VertexOut;

void	main()
{

	if (Block[0].exist == 0)
		return;

	vec4 p = gl_in[0].gl_Position;

	//face up

	gl_Position = perspective * transform *	(p + vec4(0, 1, 0, 0));
	VertexOut.normal = transform * vec4(0, 1, 0, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 1, 1, 0));
	VertexOut.normal = transform * vec4(0, 1, 0, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 1, 0, 0));
	VertexOut.normal = transform * vec4(0, 1, 0, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 1, 1, 0));
	VertexOut.normal = transform * vec4(0, 1, 0, 0);
	EmitVertex();

	EndPrimitive();

	//face down

	gl_Position = perspective * transform *	(p + vec4(0, 0, 0, 0));
	VertexOut.normal = transform * vec4(0, -1, 0, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 0, 1, 0));
	VertexOut.normal = transform * vec4(0, -1, 0, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 0, 0, 0));
	VertexOut.normal = transform * vec4(0, -1, 0, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 0, 1, 0));
	VertexOut.normal = transform * vec4(0, -1, 0, 0);
	EmitVertex();

	EndPrimitive();

	//face left

	gl_Position = perspective * transform *	(p + vec4(0, 1, 0, 0));
	VertexOut.normal = transform * vec4(-1, 0, 0, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 1, 1, 0));
	VertexOut.normal = transform * vec4(-1, 0, 0, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 0, 0, 0));
	VertexOut.normal = transform * vec4(-1, 0, 0, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 0, 1, 0));
	VertexOut.normal = transform * vec4(-1, 0, 0, 0);
	EmitVertex();

	EndPrimitive();

	//face right

	gl_Position = perspective * transform *	(p + vec4(1, 1, 0, 0));
	VertexOut.normal = transform * vec4(1, 0, 0, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 1, 1, 0));
	VertexOut.normal = transform * vec4(1, 0, 0, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 0, 0, 0));
	VertexOut.normal = transform * vec4(1, 0, 0, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 0, 1, 0));
	VertexOut.normal = transform * vec4(1, 0, 0, 0);
	EmitVertex();

	EndPrimitive();

	//face forward

	gl_Position = perspective * transform *	(p + vec4(0, 0, 0, 0));
	VertexOut.normal = transform * vec4(0, 0, -1, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 0, 0, 0));
	VertexOut.normal = transform * vec4(0, 0, -1, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 1, 0, 0));
	VertexOut.normal = transform * vec4(0, 0, -1, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 1, 0, 0));
	VertexOut.normal = transform * vec4(0, 0, -1, 0);
	EmitVertex();

	EndPrimitive();

	//face backward

	gl_Position = perspective * transform *	(p + vec4(0, 0, 1, 0));
	VertexOut.normal = transform * vec4(0, 0, 1, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 0, 1, 0));
	VertexOut.normal = transform * vec4(0, 0, 1, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 1, 1, 0));
	VertexOut.normal = transform * vec4(0, 0, 1, 0);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 1, 1, 0));
	VertexOut.normal = transform * vec4(0, 0, 1, 0);
	EmitVertex();

	EndPrimitive();
}