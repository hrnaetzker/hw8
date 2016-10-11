#include <iostream>
#include <string>
#include "game.h"
#include "checkers.h"
#include "piece.h"
#include "colors.h"

using namespace main_savitch_14;

int main()
{
	game* game1;
	game1 = new Checkers;
	game::who winner;

	winner = game1 -> play();

	return 0;
}

