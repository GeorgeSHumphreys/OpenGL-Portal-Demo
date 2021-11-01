#pragma once
class Game;

namespace GLUTCallbacks
{
	void Init(Game* gl);

	void Display();

	void Timer(int preferredRefresh);

	void Keyboard(unsigned char key, int x, int y);

	void KeyboardUp(unsigned char key, int x, int y);

	void mouse_callback(int x, int y);
}