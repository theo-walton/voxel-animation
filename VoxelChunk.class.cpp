
#include "voxGL.hpp"

VoxelChunk::VoxelChunk(void)
{
}

VoxelChunk::VoxelChunk(const std::function<int(int, int)> &f)
{
	for (int i = 0; i < size * size * size; i++)
	{
		_array[i] = f(i, size);
	}
}

int	&VoxelChunk::Item(int i, int j, int k)
{	
	return _array[i + size * j + size * size * k];
}

int	&VoxelChunk::Item(int i)
{
	return _array[i];
}

void	VoxelChunk::ApplyMatrix(glm::mat4 m)
{
	_transform *= m;
}

void	VoxelChunk::Load(void)
{
	glGenBuffers(1, &_bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLint) * size * size * size,
		     _array,
		     GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	VoxelChunk::Render(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
	glEnableVertexAttribArray(0); // maybe change 0 to var in future
	glVertexAttribPointer(0, 1, GL_INT, GL_FALSE, 0, 0);
	glDrawArrays(GL_POINTS, 0, size * size * size);
	glDisableVertexAttribArray(0);
}

void	VoxelChunk::Unload(void)
{
	glDeleteBuffers(1, &_bufferID);
}

glm::mat4	&VoxelChunk::GetTransform(void)
{
	return _transform;
}
