#include "splashkit.h"

const int PLAYER_RADIUS = 20;
const int PLAYER_SPEED = 4;
const int COIN_RADIUS = 10;

enum coin_kind
{
    BRONZE,
    SILVER,
    GOLD
};

struct coin_data
{
    double x;
    double y;
    coin_kind kind;
};

struct game_data
{
    double player_x;
    double player_y;
    coin_data coin;
    int score;
};

int coin_points(coin_kind kind)
{
    switch (kind)
    {
        case BRONZE: return 1;
        case SILVER: return 3;
        case GOLD:   return 5;
        default:     return 0;
    }
}

color coin_color(coin_kind kind)
{
    switch (kind)
    {
        case BRONZE: return COLOR_BROWN;
        case SILVER: return COLOR_SILVER;
        case GOLD:   return COLOR_GOLD;
        default:     return COLOR_BLACK;
    }
}

coin_data random_coin()
{
    coin_data result;
    result.x = rnd(COIN_RADIUS, screen_width() - COIN_RADIUS);
    result.y = rnd(COIN_RADIUS, screen_height() - COIN_RADIUS);
    result.kind = (coin_kind)rnd(3);
    return result;
}

void move_player(game_data &game)
{
    if (key_down(LEFT_KEY))  game.player_x -= PLAYER_SPEED;
    if (key_down(RIGHT_KEY)) game.player_x += PLAYER_SPEED;
    if (key_down(UP_KEY))    game.player_y -= PLAYER_SPEED;
    if (key_down(DOWN_KEY))  game.player_y += PLAYER_SPEED;
}

void draw_game(game_data game)
{
    clear_screen(COLOR_WHITE);
    fill_circle(coin_color(game.coin.kind), game.coin.x, game.coin.y, COIN_RADIUS);
    fill_circle(COLOR_BLUE, game.player_x, game.player_y, PLAYER_RADIUS);
    draw_text("Score: " + to_string(game.score), COLOR_BLACK, 10, 10);
    refresh_screen(60);
}

int main()
{
    open_window("Coin Collector", 800, 600);

    game_data game;
    game.player_x = 400;
    game.player_y = 300;
    game.coin = random_coin();
    game.score = 0;

    while (!quit_requested())
    {
        process_events();
        move_player(game);

        if (point_in_circle(game.coin.x, game.coin.y, game.player_x, game.player_y, PLAYER_RADIUS + COIN_RADIUS))
        {
            game.score += coin_points(game.coin.kind);
            game.coin = random_coin();
        }

        draw_game(game);
    }

    return 0;
}