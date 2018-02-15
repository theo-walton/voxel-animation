
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
	OcclusionRecolor();

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

bool	VoxelChunk::IsBlock(int x, int y, int z)
{
	if (x <= -1 || x >= 10 || y <= -1 || y >= 10 || z <= -1 || z >= 10)
		return false;

	int block = _array[x + y * size + z * size * size];

	block <<= 8; //check to see if the color value is not 0
	
	if (!block)
		return false;
	return true;
	
}

void	VoxelChunk::OcclusionRecolor(void)
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int z = 0; z < 10; z++)
			{
				float exposedSides = 6;

				if (IsBlock(x, y, z))
				{				
					if (IsBlock(x + 1, y, z))
					{
						exposedSides--;
					}
					if (IsBlock(x - 1, y, z))
					{
						exposedSides--;
					}
					if (IsBlock(x, y + 1, z))
					{
						exposedSides--;
					}
					if (IsBlock(x, y - 1, z))
					{
						exposedSides--;
					}
					if (IsBlock(x, y, z + 1))
					{
						exposedSides--;
					}
					if (IsBlock(x, y, z - 1))
					{
						exposedSides--;
					}
					ShadeColor(_array[x + y * size + z * size * size],
						   exposedSides / 6,
						   0.2);
				}
			}
		}
	}
}

void	VoxelChunk::ShadeColor(int &col, float factor, float contrast)
{
	float shadeAmount = (factor - 0.5) * contrast * 255;

	float blue = static_cast<float>( col % 256 );
	float green = static_cast<float>( (col / 256) % 256 );
	float red = static_cast<float>( (col / (256 * 256)) % 256 );

	std::cout << shadeAmount << std::endl;
	
	blue += shadeAmount;
	green += shadeAmount;
	red += shadeAmount;
	
	int iblue = std::max(0.0f, std::min(blue, 255.0f));
	int igreen = std::max(0.0f, std::min(green, 255.0f));
	int ired = std::max(0.0f, std::min(red, 255.0f));
	
	col = iblue + igreen * 256 + ired * 256 * 256;
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
