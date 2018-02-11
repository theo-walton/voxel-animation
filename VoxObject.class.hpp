#ifndef VOXOBJECT_CLASS_HPP
#define VOXOBJECT_CLASS_HPP

#include "voxGL.hpp"


class	VoxObject
{
	struct AnimatedChunk
	{
		VoxelChunk *chunk;
		std::vector<glm::mat4> animaTransform;
		std::vector<float> animaTime;		
		float animaCycle;

		//the point a chunk will be moved to after all transformations are applied
		glm::vec3 chunkPos;

		//a transform matrix that is applied to each chunk prior to the animaTransform.
	        //useful for rotating/sizeing parts while keeping animations intact
		glm::mat4 relativeTransform;
	};

private:
	
	std::vector<AnimatedChunk> _parts;
	float _totalTime;
	GLuint _transformID;

	glm::vec3 _pos;

	std::string	ReadFile(std::string);

	glm::mat4	getRelativeTransform(std::string&);
	glm::vec3	getChunkPos(std::string&);
	AnimatedChunk	getAnimatedChunk(std::string&);
	float	getAnimaCycle(std::string&);
	VoxelChunk	*getChunk(std::string&);
	std::vector<float>	getAnimaTime(std::string&);
	std::vector<glm::mat4>	getAnimaTransform(std::string&);

	glm::mat4	ExtrapolateMatrix(AnimatedChunk part);

public:

	VoxObject(std::string filepath);
	
	GLuint	&TransformID(void);
	void	Render(void);
	void	Load(void);
	void	Unload(void);
	
	int	TotalParts(void);
	int	TotalAnima(int part);
	
	void	Rotate(glm::vec3 axis, float angle, int part, int index);
	void	Move(glm::vec3 amount, int part, int index);
	void	ToFile(std::string filepath);
	
	void	print(void);
};

#endif
