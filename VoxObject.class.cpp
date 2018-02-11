
#include "voxGL.hpp"

std::string	VoxObject::ReadFile(std::string filepath)
{
	std::ifstream f(filepath);
	std::stringstream buf;

	buf << f.rdbuf();
	return buf.str();
}

std::vector<glm::mat4>	VoxObject::getAnimaTransform(std::string &format)
{
	std::vector<glm::mat4> container;
	glm::mat4 transform;

	size_t sz = 0;

	while (1)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				size_t tmp = sz;
				transform[i][j] = std::stof(format.substr(tmp), &sz);
				sz += tmp;
			}
		}
		container.push_back(transform);
		
		while (std::isspace(format[sz]))
			sz++;
		if (format[sz] == 'T')
			break;
	}
	format.erase(0, sz);
	return container;
}

std::vector<float>	VoxObject::getAnimaTime(std::string &format)
{
	std::vector<float> container;
	float time;

	size_t sz = 0;
	
	while (1)
	{
		size_t tmp = sz;
		time = std::stof(format.substr(tmp), &sz);
		container.push_back(time);
		sz += tmp;

		while (std::isspace(format[sz]))
			sz++;
		if (format[sz] == 'C')
			break;
	}
	format.erase(0, sz);
	return container;
}

VoxelChunk	*VoxObject::getChunk(std::string &format)
{
	int arr[1000];

	size_t sz = 0;
	
	for (int i = 0; i < 1000; i++)
	{
		size_t tmp = sz;
		
		arr[i] = std::stof(format.substr(tmp), &sz);
		sz += tmp;
	}
	while (std::isspace(format[sz]))
		sz++;
	format.erase(0, sz);
	return new VoxelChunk(arr);
}

float	VoxObject::getAnimaCycle(std::string &format)
{

	size_t sz = 0;
	float cycle = std::stof(format, &sz);

	while (std::isspace(format[sz]))
		sz++;
	format.erase(0, sz);
	return cycle;
}

glm::vec3	VoxObject::getChunkPos(std::string &format)
{
	glm::vec3 out;
	size_t sz = 0;

	for (int j = 0; j < 3; j++)
	{
		size_t tmp = sz;
		out[j] = std::stof(format.substr(tmp), &sz);
		sz += tmp;

		while (std::isspace(format[sz]))
			sz++;
	}
	format.erase(0, sz);
	return out;
}

glm::mat4	VoxObject::getRelativeTransform(std::string &format)
{
	glm::mat4 out;
	size_t sz = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			size_t tmp = sz;
			out[i][j] = std::stof(format.substr(tmp), &sz);
			sz += tmp;
		}
	}
	while (std::isspace(format[sz]))
		sz++;
	format.erase(0, sz);
	return out;
}

VoxObject::AnimatedChunk	VoxObject::getAnimatedChunk(std::string &format)
{
	AnimatedChunk ac;

	int i;

	i = format.find("Relative Transform:") + 19;
	format.erase(0, i);

	ac.relativeTransform = getRelativeTransform(format);
	
	i = format.find("Transform:") + 10;
	format.erase(0, i);
	
	ac.animaTransform = getAnimaTransform(format);

	std::cout << "test2" <<	std::endl;
	
	i = format.find("Time:") + 5;
	format.erase(0, i);
	ac.animaTime = getAnimaTime(format);

	std::cout << "test3" <<	std::endl;
	
	i = format.find("Chunk:") + 6;
	format.erase(0, i);
	ac.chunk = getChunk(format);

	std::cout << "test4" <<	std::endl;
	
	i = format.find("Cycle:") + 6;
	format.erase(0, i);
	ac.animaCycle = getAnimaCycle(format);

	std::cout << "test5" << std::endl;

	i = format.find("Chunk Position:") + 15;
	format.erase(0, i);
	ac.chunkPos = getChunkPos(format);
	
	return ac;
}

VoxObject::VoxObject(std::string filepath)
{
	_totalTime = 0;
	_pos = glm::vec3(0, 0, 0);
	std::string format = ReadFile(filepath);

	while (format.length())
		_parts.push_back( getAnimatedChunk(format) );
}

GLuint	&VoxObject::TransformID(void)
{
	return _transformID;
}

glm::mat4	VoxObject::ExtrapolateMatrix(AnimatedChunk part)
{
	float cycleTime = fmod(_totalTime, part.animaCycle);
	
	int i = 0;
	
	while ( i < part.animaTime.size() )
	{		
		if (cycleTime < part.animaTime[i])
			break;
		i++;
	}
	i--;

	float a = cycleTime - part.animaTime[i];
	float b;
 
	
	if (i != part.animaTime.size() - 1)
		b = part.animaTime[i + 1] - part.animaTime[i];
	else
		b = part.animaCycle - part.animaTime[i];

	std::cout << cycleTime << " " << i << std::endl;
	
	float ratio = a / b;

	glm::mat4 x = part.animaTransform[i];
	glm::mat4 y;

	if ( i != part.animaTransform.size() - 1)
		y = part.animaTransform[i + 1];
	else
		y = part.animaTransform[0];

	glm::mat4 z = y - x;

	return x + z * ratio;
}

void	VoxObject::Render(void)
{
	for (int i = 0; i < _parts.size(); i++)
	{

		glm::mat4 matrix = ExtrapolateMatrix(_parts[i]);
		glm::mat4 translate = glm::translate(_pos + _parts[i].chunkPos);

		matrix = translate * matrix * _parts[i].relativeTransform;
		
		_parts[i].chunk->UseMatrix( matrix );
         	glUniformMatrix4fv(_transformID,				   
				   1,
				   GL_FALSE,
				   glm::value_ptr(_parts[i].chunk->GetTransform()));

		_parts[i].chunk->Render();
	}
	_totalTime += 0.01;
}

void	VoxObject::Load(void)
{
	for (int i = 0; i < _parts.size(); i++)
	{
		_parts[i].chunk->Load();
	}
}

void	VoxObject::Unload(void)	
{
	for (int i = 0; i < _parts.size(); i++)
	{
		_parts[i].chunk->Unload();
	}
}

int	VoxObject::TotalParts(void)
{
	return _parts.size();
}

int	VoxObject::TotalAnima(int part)
{
	return _parts[part].animaTime.size();
}

void	VoxObject::Rotate(glm::vec3 axis, float angle, int part, int index)
{
	glm::mat4 &m = _parts[part].animaTransform[index];
	glm::vec4 p = m * glm::vec4(0, 0, 0, 1);	
	glm::mat4 translate = glm::translate(glm::vec3(p));
	glm::mat4 rotate = glm::rotate(glm::radians(angle), axis);

	m = translate * rotate * -translate * m;
}

void	VoxObject::Move(glm::vec3 amount, int part, int index)
{
	glm::mat4 &m = _parts[part].animaTransform[index];
	glm::mat4 translate = glm::translate(amount);

	m = translate * m;
}

void	VoxObject::ToFile(std::string filepath)
{
	
}

void	VoxObject::print(void)
{
	for (int i = 0; i < _parts.size(); i++)
	{
		_parts[i].chunk->print();
		std::cout << std::endl << std::endl << std::endl;
	}
}
