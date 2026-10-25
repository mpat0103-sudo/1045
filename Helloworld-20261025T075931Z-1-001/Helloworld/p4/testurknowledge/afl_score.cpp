#include "utilities.h"
#include "splashkit.h"

const int WIDTH = 26;
const int GOAL_POINTS = 6;
const int BEHIND_POINTS = 1;

int calculate_score(int goals, int behinds)
{
    return goals * GOAL_POINTS + behinds * BEHIND_POINTS;
}

void print_score(int goals, int behinds)
{
    write_line("Current Score: " + to_string(calculate_score(goals, behinds)));
}

void print_details(string name, int goals, int behinds)
{
    write_line(name + ": " + to_string(goals) + " Goals " + to_string(behinds) + " Behinds " + to_string(calculate_score(goals, behinds)));
}

void print_menu()
{
    write_line();
    draw_title("Main Menu", WIDTH);
    write_line("1: Update goals");
    write_line("2: Update behinds");
    write_line("3: Print details");
    write_line("4: Quit");
    draw_heading_line(WIDTH);
}

int main()
{
    string name;
    int goals, behinds, option;
    bool quit = false;

    draw_title("Score Calculator", WIDTH);
    write_line("Welcome to the AFL score calculator!");
    write_line();

    name = read_string("Enter team name: ");
    goals = read_integer("Enter goals: ");
    behinds = read_integer("Enter behinds: ");
    print_score(goals, behinds);

    do
    {
        print_menu();
        option = read_integer_range("Enter Option: ", 1, 4);

        if (option == 1)
        {
            write_line();
            write_line("Current goals: " + to_string(goals));
            goals = read_integer("Enter new goals: ");
            print_score(goals, behinds);
        }
        else if (option == 2)
        {
            write_line();
            write_line("Current behinds: " + to_string(behinds));
            behinds = read_integer("Enter new behinds: ");
            print_score(goals, behinds);
        }
        else if (option == 3)
        {
            print_details(name, goals, behinds);
        }
        else
        {
            quit = read_boolean("Are you sure you want to quit? [Y/n]: ");
        }
    } while (!quit);

    write_line("Bye!");

    return 0;
}