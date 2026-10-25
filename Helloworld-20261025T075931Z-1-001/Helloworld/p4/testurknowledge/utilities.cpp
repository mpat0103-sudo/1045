#include "utilities.h"
#include "splashkit.h"

void draw_heading_line(int width)
{
    write("+");
    int i = 0;
    while (i < width - 2)
    {
        write("-");
        i++;
    }
    write_line("+");
}

void draw_title(string title, int width)
{
    int spaces = width - 3 - length_of(title);

    draw_heading_line(width);

    write("| " + title);
    int i = 0;
    while (i < spaces)
    {
        write(" ");
        i++;
    }
    write_line("|");

    draw_heading_line(width);
}

string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

int read_integer(string prompt)
{
    string line = read_string(prompt);

    while (!is_integer(line))
    {
        write_line("Please enter a whole number");
        line = read_string(prompt);
    }

    return to_integer(line);
}

int read_integer_range(string prompt, int low, int high)
{
    if (low > high)
    {
        int temp = low;
        low = high;
        high = temp;
    }

    int input = read_integer(prompt);

    while (input < low || input > high)
    {
        write_line("Please enter a number between " + to_string(low) + " and " + to_string(high));
        input = read_integer(prompt);
    }

    return input;
}

bool read_boolean(string prompt)
{
    string line = read_string(prompt);

    while (line != "y" && line != "Y" && line != "n" && line != "N")
    {
        write_line("Please enter y or n");
        line = read_string(prompt);
    }

    return line == "y" || line == "Y";
}