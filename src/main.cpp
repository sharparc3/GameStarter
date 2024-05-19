#include "Game.h"

int main(int argc, char** argv)
{
	Game::Construct();
	Game::GetInstance()->Run();
	Game::GetInstance()->Destruct();
	return 0;
}