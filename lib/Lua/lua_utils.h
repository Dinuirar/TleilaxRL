#ifndef _LUA_UTILS_H_
#define _LUA_UTILS_H_

typedef struct lua_State lua_State;

struct config {
	int screen_width;
	int screen_height;
	int scroll_speed;
	int ms_per_update_logic;
	int ms_per_update_graphics;
};

struct lua {
	/* -- public  -- */
	struct config (*load_configuration) (const char*);
	int (*randomize_seed) (const char *, const int x, const int y);
	void (*draw_galaxy) (lua_State *, const int, const int);

	/* -- private -- */
	/* pointer to a randomize_seed(x,y) function used by Lua scripts */
	unsigned int (*p_randomize_seed_xy_function) (const int, const int);
	int (*p_rnd_int_range_function) (const int, const int);
	int (*p_rnd_double_range_function) (const double, const double);
	int (*p_draw_char_function) (const int, const int, const char *, const int);
};

lua_State *lua_load_galaxy_script(const char *);
int close_galaxy_script(lua_State *);

/* Export as a "namespaced" global variable */
extern struct lua Lua;
#endif
