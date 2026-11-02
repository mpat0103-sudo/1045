#include "utilities.h"
#include "splashkit.h"

/**
 * Draws a line like +------+ to the terminal.
 *
 * @param width the total width of the line
 */
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

/**
 * Draws a title inside a box, with a heading line above and below.
 *
 * @param title the text to show in the box
 * @param width the total width of the box
 */
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

/**
 * Shows a prompt and reads a line of text from the user.
 *
 * @param prompt the message to show the user
 * @returns the text the user entered
 */
string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

/**
 * Reads a whole number from the user, asking again until the input is valid.
 *
 * @param prompt the message to show the user
 * @returns the number the user entered
 */
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

/**
 * Reads a whole number between low and high (inclusive), asking again
 * until the input is valid.
 *
 * @param prompt the message to show the user
 * @param low the smallest value allowed
 * @param high the largest value allowed
 * @returns the number the user entered
 */
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

/**
 * Reads a y or n answer from the user, asking again until the input is valid.
 *
 * @param prompt the message to show the user
 * @returns true if the user entered y, false if they entered n
 */
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

/**
 * Reads a whole number between low and high (inclusive).
 *
 * @param prompt the message to show the user
 * @param low the smallest value allowed
 * @param high the largest value allowed
 * @returns the number the user entered
 */
int read_integer(string prompt, int low, int high)
{
    return read_integer_range(prompt, low, high);
}

/**
 * Reads a number (can have decimals) from the user, asking again until the input is valid.
 *
 * @param prompt the message to show the user
 * @returns the number the user entered
 */
double read_double(string prompt)
{
    string line = read_string(prompt);

    while (!is_double(line))
    {
        write_line("Please enter a number");
        line = read_string(prompt);
    }

    return to_double(line);
}
