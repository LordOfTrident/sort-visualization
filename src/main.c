#include "app.h"

int main(void) {
	app_t app = {0};

	app_init(&app);
	app_run(&app);
	app_finish(&app);

	return 0;
}
