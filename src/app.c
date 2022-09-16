#include "app.h"

void swap(int *p_a, int *p_b) {
	int tmp = *p_a;
	*p_a = *p_b;
	*p_b = tmp;
}

void app_init(app_t *p_app) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("%s", SDL_GetError());

		exit(EXIT_FAILURE);
	}

	p_app->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                                 SCREEN_W * SCALE, SCREEN_H * SCALE, SDL_WINDOW_RESIZABLE);
	if (p_app->window == NULL) {
		SDL_Log("%s", SDL_GetError());

		exit(EXIT_FAILURE);
	}

	p_app->renderer = SDL_CreateRenderer(p_app->window, -1, SDL_RENDERER_ACCELERATED);
	if (p_app->renderer == NULL) {
		SDL_Log("%s", SDL_GetError());

		exit(EXIT_FAILURE);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	if (SDL_RenderSetLogicalSize(p_app->renderer, SCREEN_W, SCREEN_H) != 0) {
		SDL_Log("%s", SDL_GetError());

		exit(EXIT_FAILURE);
	}

	p_app->screen = SDL_CreateTexture(p_app->renderer, SDL_PIXELFORMAT_RGBA8888,
	                                  SDL_TEXTUREACCESS_TARGET, SCREEN_W, SCREEN_H);
	if (p_app->screen == NULL) {
		SDL_Log("%s", SDL_GetError());

		exit(EXIT_FAILURE);
	}

	p_app->screen_rect.x = 0;
	p_app->screen_rect.y = 0;
	p_app->screen_rect.w = SCREEN_W;
	p_app->screen_rect.h = SCREEN_H;

	p_app->key_states = SDL_GetKeyboardState(NULL);

	time_t random = rand();
	srand(time(&random));

	app_shuffle_list(p_app);
}

void app_finish(app_t *p_app) {
	SDL_DestroyTexture(p_app->screen);
	SDL_DestroyRenderer(p_app->renderer);
	SDL_DestroyWindow(p_app->window);

	SDL_Quit();
}

void app_set_it(app_t *p_app, size_t p_i) {
	p_app->i = p_i;
	p_app->j = -1;
}

void app_set_its(app_t *p_app, size_t p_i, size_t p_j) {
	p_app->i = p_i;
	p_app->j = p_j;
}

void app_shuffle_list(app_t *p_app) {
	p_app->idle = false;

	for (size_t i = 0; i < SIZE_OF(p_app->list); ++ i) {
		p_app->list[i] = rand() % SCREEN_H;

		app_set_it(p_app, i);

		app_render(p_app);
		app_events(p_app);
		if (p_app->idle) {
			p_app->idle = true;

			return;
		}

		SDL_Delay(1000 / 120);
	}

	p_app->idle   = true;
	p_app->sorted = false;
}

void app_bubblesort(app_t *p_app) {
	if (p_app->sorted)
		return;

	p_app->idle = false;

	bool sorted;
	do {
		sorted = true;

		for (size_t i = 0; i < SIZE_OF(p_app->list) - 1; ++ i) {
			if (p_app->list[i] > p_app->list[i + 1]) {
				sorted = false;

				swap(&p_app->list[i], &p_app->list[i + 1]);
			}

			app_set_it(p_app, i);

			app_render(p_app);
			app_events(p_app);
			if (p_app->idle) {
				p_app->idle = true;

				return;
			}

			SDL_Delay(1000 / BUBBLESORT_FPS);
		}
	} while (!sorted);

	p_app->idle   = true;
	p_app->sorted = true;
}

int app_quicksort_partition(app_t *p_app, int p_first, int p_last) {
	int i = p_first, pivot = p_app->list[p_last];

	for (int j = p_first; (int)j < p_last; ++ j) {
		if (p_app->list[j] < pivot) {
			swap(&p_app->list[j], &p_app->list[i]);

			++ i;
			app_set_its(p_app, p_first, j);

			app_render(p_app);
			app_events(p_app);
			if (p_app->idle)
				return - 1;

			SDL_Delay(1000 / QUICKSORT_FPS);
		}
	}

	swap(&p_app->list[i], &p_app->list[p_last]);

	return i;
}

void app_quicksort(app_t *p_app, int p_first, int p_last) {
	if (p_first < p_last) {
		int idx = app_quicksort_partition(p_app, p_first, p_last);

		app_quicksort(p_app, p_first, idx - 1);
		if (p_app->idle)
			return;

		app_quicksort(p_app, idx + 1, p_last);
		if (p_app->idle)
			return;
	}
}

void app_quicksort_start(app_t *p_app) {
	if (p_app->sorted)
		return;

	p_app->idle = false;

	app_quicksort(p_app, 0, SIZE_OF(p_app->list) - 1);
	if (p_app->idle) {
		p_app->idle = true;

		return;
	}

	p_app->idle   = true;
	p_app->sorted = true;
}

void app_run(app_t *p_app) {
	app_render(p_app);

	do {
		app_events(p_app);

		SDL_Delay(1000 / 60);
	} while (!p_app->quit);
}

void app_render(app_t *p_app) {
	SDL_SetRenderDrawColor(p_app->renderer, 13, 43, 69, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(p_app->renderer);

	SDL_SetRenderTarget(p_app->renderer, p_app->screen);
	SDL_SetRenderDrawColor(p_app->renderer, 32, 60, 86, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(p_app->renderer);

	SDL_Rect rect = {.w = 1};
	for (size_t i = 0; i < SIZE_OF(p_app->list); ++ i) {
		if (p_app->list[i] == 0)
			continue;

		if (i % 2 == 0)
			SDL_SetRenderDrawColor(p_app->renderer, 208, 129, 89, SDL_ALPHA_OPAQUE);
		else
			SDL_SetRenderDrawColor(p_app->renderer, 141, 105, 122, SDL_ALPHA_OPAQUE);

		rect.h = p_app->list[i];
		rect.y = SCREEN_H - p_app->list[i];
		rect.x = i;

		SDL_RenderFillRect(p_app->renderer, &rect);
	}

	if (!p_app->idle) {
		SDL_SetRenderDrawColor(p_app->renderer, 255, 234, 214, SDL_ALPHA_OPAQUE);

		rect.x = p_app->i;
		rect.h = SCREEN_H;
		rect.y = 0;

		SDL_RenderFillRect(p_app->renderer, &rect);

		if (p_app->j != (size_t)-1) {
			rect.x = p_app->j;

			SDL_RenderFillRect(p_app->renderer, &rect);
		}
	}

	SDL_SetRenderTarget(p_app->renderer, NULL);
	SDL_RenderCopy(p_app->renderer, p_app->screen, NULL, &p_app->screen_rect);
	SDL_RenderPresent(p_app->renderer);
}

void app_events(app_t *p_app) {
	while (SDL_PollEvent(&p_app->event)) {
		switch (p_app->event.type) {
		case SDL_QUIT:        p_app->quit = true; break;
		case SDL_WINDOWEVENT: app_render(p_app);  break;
		case SDL_KEYDOWN:
			switch (p_app->event.key.keysym.sym) {
			case SDLK_ESCAPE:
				if (p_app->idle)
					p_app->quit = true;
				else
					p_app->idle = true;

				break;

			case SDLK_r:
				if (p_app->idle) {
					app_shuffle_list(p_app);
					app_render(p_app);
				}

				break;

			case SDLK_b:
				if (p_app->idle) {
					app_bubblesort(p_app);
					app_render(p_app);
				}

				break;

			case SDLK_q:
				if (p_app->idle) {
					app_quicksort_start(p_app);
					app_render(p_app);
				}

				break;

			default: break;
			}

			break;

		default: break;
		}
	}
}
