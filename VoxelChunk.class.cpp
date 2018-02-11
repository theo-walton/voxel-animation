
#include "voxGL.hpp"

VoxelChunk::VoxelChunk(void)
{
}

VoxelChunk::VoxelChunk(int arr[])
{
	for (int i = 0; i < size * size * size; i++)
	{
		_array[i] = arr[i];
	}
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
	_pos = glm::vec3(glm::vec4(_pos, 1) * m);
}

void	VoxelChunk::UseMatrix(glm::mat4 m)
{
	_transform = m;
	_pos = glm::vec3(glm::vec4(_pos, 1) * m);
}

void	VoxelChunk::Load(void)
{
	RemoveHiddenSides();
	
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

glm::vec3	VoxelChunk::Pos(void)
{
	return _pos;
}

void	VoxelChunk::RemoveHiddenSides(void)
{
	const int top =		0b00000001000000000000000000000000;
	const int bot =		0b00000010000000000000000000000000;
	const int left =	0b00000100000000000000000000000000;
	const int right =	0b00001000000000000000000000000000;
	const int front =	0b00010000000000000000000000000000;
	const int back =	0b00100000000000000000000000000000;

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int z = 0; z < 10; z++)
			{
				if (IsBlock(x + 1, y, z))
				{
					_array[x + y * size + z * size * size] |= right;
				}
				if (IsBlock(x - 1, y, z))
				{
					_array[x + y * size + z * size * size] |= left;
				}
				if (IsBlock(x, y + 1, z))
				{
					_array[x + y * size + z * size * size] |= top;
				}
				if (IsBlock(x, y - 1, z))
				{
					_array[x + y * size + z * size * size] |= bot;
				}
				if (IsBlock(x, y, z + 1))
				{
					_array[x + y * size + z * size * size] |= back;
				}
				if (IsBlock(x, y, z - 1))
				{
					_array[x + y * size + z * size * size] |= front;
				}						
			}
		}
	}
}

void	VoxelChunk::print(void)
{
	for (int i = 0; i < 1000; i++)
	{
		std::cout << _array[i] << " ";
	}

	std::cout << std::endl << "matrix:" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << _transform[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
