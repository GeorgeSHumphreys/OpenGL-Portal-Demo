// Includes
#include "GLUTCallbacks.h"
#include "Game.h"

// Namespace implementation
namespace GLUTCallbacks
{
	namespace
	{
		// Initialise to a null pointer to begin
		Game* game = nullptr;
	}

	void Init(Game* gl)
	{
		game = gl;
	}

	void Display()
	{
		if (game != nullptr)
		{
			game->Display();
		}
	}

	
	void Timer(int preferredRefresh)
	{
		if (game != nullptr)
		{
			int updateTime = glutGet(GLUT_ELAPSED_TIME);
			game->Update();
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
			glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
		}
	}

	
	void Keyboard(unsigned char key, int x, int y)
	{
		if (game != nullptr)
		{
			game->Keyboard(key, x, y);
		}
	}
	
	void KeyboardUp(unsigned char key, int x, int y)
	{
		if (game != nullptr)
		{
			game->KeyboardUp(key, x, y);
		}
	}
	
	void mouse_callback(int x, int y)
	{
		if (game != nullptr)
		{
			game->MouseMove(x, y);
		}
	}
}