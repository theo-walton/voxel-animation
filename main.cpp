
#include "voxGL.hpp"

int	main(int ac, char **av)
{

	if (ac == 1)
		return (1);
	
	Window window(X_DIM, Y_DIM, NAME);
	Camera camera;

        if (glGetError() !=GL_NO_ERROR)
                std::cerr << "FAIL\n";


	window.EventListen();
	
	window.ForwardAndBackKeys('W', 'S');
	window.LeftAndRightKeys('A', 'D');
	window.UpAndDownKeys('Z', 'X');
	
	camera.TrackEvents(&window);

	VoxRenderer renderer;

	glClearColor(0.20, 0.25, 0.29, 1);

	for (int i = 1; i < ac; i++)
	{
	
		VoxObject *test = new VoxObject(av[i]);
	
		test->Load();
		renderer.AttachObject(test);
	
		test->SetPos(glm::vec3((i - 1) * 20, 0, 100));
	}

	while (window.IsOpen())
	{
		window.Clear();
		camera.Update();
		if (camera.JustMoved())
		{
			renderer.NewPerspective(camera.Perspective());
		}
		renderer.Render();
		window.Update();

		GLenum err;

		if ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cerr << "OpenGL error: " << err << std::endl;
		}
	}
}
