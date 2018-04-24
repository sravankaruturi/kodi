#define ENGINE_DEMO 1

#if !ENGINE_DEMO

#include "TetrisGame.h"

int main()
{

	printf("Tetris Game.. Loading ...");

	TetrisGame tetris("Tetris", 800, 600);

	while(!tetris.GetWindow()->IsClosed())
	{

		tetris.Update();

#if _DEBUG
		if (tetris.GetWindow()->IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			break;
		}
#endif

	}

	return 0;
}

#endif