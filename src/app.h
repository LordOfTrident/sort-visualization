#ifndef APP_H__HEADER_GUARD__
#define APP_H__HEADER_GUARD__

#include <stdlib.h>  /* exit, EXIT_FAILURE, rand, srand */
#include <time.h>    /* time */
#include <stdbool.h> /* bool, true, false */

#include <SDL2/SDL.h>

#define TITLE "Sort visualization"

#define SCREEN_W 64
#define SCREEN_H 48

#define SCALE    10
#define BUBBLESORT_FPS 120
#define QUICKSORT_FPS  60

#define SIZE_OF(p_arr) (sizeof(p_arr) / sizeof(p_arr[0]))

typedef struct {
	SDL_Window   *window;
	SDL_Renderer *renderer;
	SDL_Texture  *screen;
	SDL_Rect      screen_rect;

	SDL_Event    event;
	const Uint8 *key_states;

	bool   quit, idle, sorted;
	size_t i, j;

	int list[SCREEN_W];
} app_t;

void swap(int *p_a, int *p_b);

void app_init(app_t *p_app);
void app_finish(app_t *p_app);
void app_run(app_t *p_app);

void app_set_it(app_t *p_app,  size_t p_i);
void app_set_its(app_t *p_app, size_t p_i, size_t p_j);

void app_shuffle_list(app_t *p_app);

void app_bubblesort(app_t *p_app);

int  app_quicksort_partition(app_t *p_app, int p_first, int p_last);
void app_quicksort(app_t *p_app, int p_first, int p_last);
void app_quicksort_start(app_t *p_app);

void app_render(app_t *p_app);
void app_events(app_t *p_app);

#endif
