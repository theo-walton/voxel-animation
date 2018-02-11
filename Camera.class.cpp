
#include "voxGL.hpp"

glm::vec3 const	Camera::Pos;
glm::vec3 const	Camera::Up;
glm::vec3 const	Camera::Forward;
glm::vec3 const	Camera::Right;

Camera::Camera(void) : _cameraShouldMove(true)
{
	auto timestamp = std::chrono::high_resolution_clock::now();
//	_time = std::chrono::time_point<double, std::nano>(timestamp).count();
}

glm::mat4	Camera::Perspective(void)
{
	glm::mat4 look = glm::lookAt(glm::vec3(_transform * glm::vec4(Pos, 1)),
				     glm::vec3(_transform * glm::vec4(Forward, 1)),
				     Up);

	float width, height;

	_window->GetSize(width, height);

	glm::mat4 perspective = glm::perspective(glm::radians(45.0f), width/height, 0.1f, 1000.0f);

	return perspective * look;
}

void	Camera::Move(glm::vec3 amount)
{
	_transform = glm::translate(_transform, amount);
	_cameraShouldMove = true;
}

void	Camera::Rotate(glm::vec3 axis, float degrees)
{
	_transform = glm::rotate(_transform, glm::radians(degrees), axis);
	_cameraShouldMove = true;	
}

void	Camera::TrackEvents(Window *window)
{
	_window = window;
}

void	Camera::Update(void)
{
	auto timestamp = std::chrono::high_resolution_clock::now();
	
	double time = 0;//std::chrono::time_point_cast<std::chrono::seconds>(timestamp);
	double deltaTime = 0.1;//time - _time;


	if (_window->IsForward())
	{
		Move(Forward * deltaTime);
	}
	if (_window->IsBackward())
	{
		Move(-Forward * deltaTime);
	}
	if (_window->IsLeft())
	{
		Move(-Right * deltaTime);
	}
	if (_window->IsRight())
	{
		Move(Right * deltaTime);
	}
	if (_window->IsUp())
	{
		Move(Up * deltaTime);		
	}
	if (_window->IsDown())
	{
		Move(-Up * deltaTime);
	}
	if (_window->KeyOn('N'))
	{
		Rotate(glm::vec3(0, 0, -1), 0.5);
	}
	if (_window->KeyOn('M'))
	{
		Rotate(glm::vec3(0, 0, 1), 0.5);
	}
	if (_window->KeyOn('J'))
	{
		Rotate(glm::vec3(0, -1, 0), 0.5);
	}
	if (_window->KeyOn('K'))
	{
		Rotate(glm::vec3(0, 1, 0), 0.5);
	}
	
	if (_cameraShouldMove)
	{
		
	}
	
	_time = time;
}

bool	Camera::JustMoved(void)
{
	bool out = _cameraShouldMove;
	_cameraShouldMove = false;
	return out;
}
