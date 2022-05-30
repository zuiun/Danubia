#include "game.hpp"

/*
 * Runs game
 * 
 * Pre: None
 * Post: None
 * Return: None
 */
int main (int argc, char* args[]) {
	Game* game = new Game ();

	while (game->get_is_running ()) {
		game->update ();
	}

	return 0;
}
