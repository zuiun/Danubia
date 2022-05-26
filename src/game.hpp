#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL.h>
#include "time_manager.hpp"

class Game {
	public:
		Game (int width = 640, int height = 480, int frame_rate = 30);
		~Game ();
		void update ();
		bool get_is_running ();
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event event;
		TimeManager* time_manager;
		bool is_running;

		void handle_event ();
		void render ();
};

#endif
