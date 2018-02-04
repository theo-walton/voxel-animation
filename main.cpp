
#include "voxGL.hpp"

int	chunkFun(int index, int size)
{
	int x = index % 10 - 5;
	index /= 10;
	int y = index % 10 - 5;
	index /= 10;
	int z = index % 10 - 5;

	if (x * x + y * y + z * z < 4 * 4)
		return 1;
	return 0;
}

int	main(void)
{
	
	Window window(X_DIM, Y_DIM, NAME);
	ShadingProgram program("vertex.glsl",
			       "geom.glsl",
			       "frag.glsl");
	Camera camera;

	program.Use();


        if (glGetError() !=GL_NO_ERROR)
                std::cerr << "FAIL\n";


	window.EventListen();
	
	window.ForwardAndBackKeys('W', 'S');
	window.LeftAndRightKeys('A', 'D');
	window.UpAndDownKeys('Z', 'X');
	
	camera.TrackEvents(&window);
	
	VoxelChunk chunk(chunkFun);
	VoxelMap map(program);

	chunk.Load();
	map.AddChunk(&chunk);
	
	while (window.IsOpen())
	{
		window.Clear();
		camera.Update();
		if (camera.JustMoved())
		{
			map.NewPerspective(camera.Perspective());
			map.UsePerspective();
		}
		map.Render();
		window.Update();

		GLenum err;

		if ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cerr << "OpenGL error: " << err << std::endl;
		}
	}


}
