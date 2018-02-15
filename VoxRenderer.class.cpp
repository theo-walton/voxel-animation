
#include "voxGL.hpp"

VoxRenderer::VoxRenderer(ShadingProgram &program) : _program(program)
{
	_perspectiveID = glGetUniformLocation(program.ID(), "perspective");
	_transformID = glGetUniformLocation(program.ID(), "transform");

	for (int i = 0; i < 1000; i++)
	{
		_numlist[i] = i;
	}
}

void	VoxRenderer::AttachObject(VoxObject *object)
{
	_objects.push_back(object);
	object->TransformID() = _transformID;
}

void	VoxRenderer::Render(void)
{
	GLuint id;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLint) * 1000,
		     _numlist,
		     GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_INT, GL_FALSE, 0, 0);

	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->Render();
	}
	glDisableVertexAttribArray(1);
}

void	VoxRenderer::NewPerspective(glm::mat4 m)
{
	_perspective = m;
}

void	VoxRenderer::UsePerspective(void)
{
	glUniformMatrix4fv(_perspectiveID,
			   1,
			   GL_FALSE,
			   glm::value_ptr(_perspective));
}
