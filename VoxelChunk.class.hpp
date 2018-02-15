#ifndef VOXELCHUNK_CLASS_HPP
#define VOXELCHUNK_CLASS_HPP

#include "voxGL.hpp"

class	VoxelChunk
{
private:

	static const int size = 10;

	GLuint _bufferID;
	GLint _array[size * size * size] = {};		
	glm::mat4 _transform;
	glm::vec3 _pos;

	void	RemoveHiddenSides(void);
	void	OcclusionRecolor(void);
	void	ShadeColor(int &col, float factor, float contrast);

	
	bool	IsBlock(int x, int y, int z);	
	
public:

	VoxelChunk(void);
	VoxelChunk(int[]);
	VoxelChunk(const std::function<int(int, int)> &f);

	//access _array like a triple array
	int	&Item(int i, int j, int k);
	
	//access _array like single array
	int	&Item(int);
	
	void	ApplyMatrix(glm::mat4);

	void	UseMatrix(glm::mat4);
	
	void	Load(void);

	void	Render(void);

	void	Unload(void);

	glm::mat4	&GetTransform(void);

	glm::vec3	Pos(void);

	void	print(void);
};

//stores a 10/10/10 array of ints and a transform matrix

#endif
