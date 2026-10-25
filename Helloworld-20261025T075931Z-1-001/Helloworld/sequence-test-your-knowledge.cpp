#include "splashkit.h"

int main()
{
 open_window("Traffic Light", 800, 600);
    clear_screen(COLOR_LIGHT_GRAY);

    fill_rectangle(COLOR_BLACK, 325, 100, 150, 400);

    fill_circle(COLOR_RED, 400, 170, 45);
    fill_circle(COLOR_YELLOW, 400, 300, 45);
    fill_circle(COLOR_GREEN, 400, 430, 45);

    refresh_screen();
    delay(5000);

    return 0;
}