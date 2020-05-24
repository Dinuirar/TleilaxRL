#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <ncurses.h>
#include <unistd.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "lib/TimeOps/timeops.h"
#include "lib/Random/random.h"
#include "lib/Galaxy/galaxy.h"
#include "lib/NcursesTools/ncurses_tools.h"
#include "lib/Lua/lua_utils.h"

#define MS_PER_UPDATE_GRAPHICS 16
#define MS_PER_UPDATE_LOGIC 1000 

struct application {
	struct config Config; 
} Application;

/** 
 * Global variable determining if main loop should run 
 */
static volatile sig_atomic_t program_is_running = 1;

/** 
 * Stops the program from running 
 */
static void stop (int sig) {
	program_is_running = 0;
}

/**
 * Initializes the program instance
 */
int init() 
{
	return 0;
}

int move_galaxy_on_input(double *galaxy_offset_x, double *galaxy_offset_y, const float speed, const float elapsed_ms)
{
	if (Ncurses.kbhit()) {
		char ch = getch();
		if (ch == 'a') {
			*galaxy_offset_x -= speed * elapsed_ms;
		}
		if (ch == 's') {
			*galaxy_offset_y += speed * elapsed_ms;
		}
		if (ch == 'w') {
			*galaxy_offset_y -= speed * elapsed_ms;
		}
		if (ch == 'd') {
			*galaxy_offset_x += speed * elapsed_ms;
		}
	}		

	return 0;
}


/**
 * Draw all screen components
 */
int render_stars_on_screen(const int amount_sectors_x, const int amount_sectors_y) 
{
	for (int x = 0; x < amount_sectors_x; x++) {
		for (int y = 0; y < amount_sectors_y; y++) {

			Random.randomize_seed_xy( x + (int)Galaxy.offset_x, y + (int)Galaxy.offset_y );

			int randomNum = Random.rnd_int_range(0, Galaxy.CHANCE_OF_STAR);
			if (randomNum == 0) {
				randomNum = Random.rnd_int_range(0,100);
				
				if (randomNum < 10) {
					Ncurses.draw_char(x+5, y+5, 'O', 1);
				} else if (randomNum >= 10 && randomNum < 50) {
					Ncurses.draw_char(x+5, y+5, 'o', 2);
				} else {
					Ncurses.draw_char(x+5, y+5, '*', 3);
				}
			} else {
				mvwaddch(stdscr, y+5, x+5, ' ');
			}
		}
	}
	return 0;
}

/**
 * Main program
 * 
 * 1. Initialize state
 * 2. Run update-render loop
 * 3. On exit free memory & turn off OLED screen
 *
 */  
int main(int argc, char **argv)
{
	Ncurses.init_config();

	long previous_ms = 0, current_ms = 0, elapsed_ms = 0, lag_ms = 0, count_ms = 0;
	
	previous_ms = get_current_time();

	/* Stop program on CTRL+c */
	signal(SIGINT, stop);

	Application.Config = Lua.load_configuration("./lua/config.lua");

	char debug_galaxy_xy[20];

	/*
	 * Main program loop
	 */
	while(program_is_running)
	{
		current_ms = get_current_time();

		/* Update if enough time elapsed */
		if (count_ms > Application.Config.ms_per_update_logic) {
			count_ms = 0;
		}
		
		/* FPS calculations */
		elapsed_ms = current_ms - previous_ms;
		previous_ms = current_ms;
		count_ms += elapsed_ms;
		lag_ms += elapsed_ms;
		
		/* Update the background according to lag */
		while (lag_ms >= Application.Config.ms_per_update_graphics) 
		{
			lag_ms -= Application.Config.ms_per_update_graphics;
		}

		move_galaxy_on_input(&Galaxy.offset_x, &Galaxy.offset_y, Application.Config.scroll_speed, elapsed_ms);
		refresh();
		render_stars_on_screen(Application.Config.screen_width, Application.Config.screen_height); 
		
		wmove(stdscr, 0 ,0);
		sprintf(debug_galaxy_xy, "x=[%.02f] y=[%0.2f]", Galaxy.offset_x, Galaxy.offset_y);
		mvaddstr(3, Application.Config.screen_width >> 1, debug_galaxy_xy);
		mvaddstr(40, 0, "Press one of WSAD to move the screen.");
		mvaddstr(41, 0, "Press CTRL+c to exit.");
	}
	/* Exit program */
	endwin();
	
	/* Exit */	
	return 0;
}
