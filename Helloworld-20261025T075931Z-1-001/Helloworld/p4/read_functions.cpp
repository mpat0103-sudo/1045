#include "splashkit.h"

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
        write_line("Please enter a whole number.");
        line = read_string(prompt);
    }

    return to_integer(line);
}

int read_integer(string prompt, int low, int high)
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
        write_line("Please enter a value between " + to_string(low) + " and " + to_string(high));
        input = read_integer(prompt);
    }

    return input;
}

double read_double(string prompt)
{
    string line = read_string(prompt);

    while (!is_double(line))
    {
        write_line("Please enter a number.");
        line = read_string(prompt);
    }

    return to_double(line);
}

double read_double(string prompt, double low, double high)
{
    if (low > high)
    {
        double temp = low;
        low = high;
        high = temp;
    }

    double input = read_double(prompt);

    while (input < low || input > high)
    {
        write_line("Please enter a value between " + to_string(low) + " and " + to_string(high));
        input = read_double(prompt);
    }

    return input;
}

int main()
{
    string name;
    int age, value;
    double height, score;

    name = read_string("enter your name: ");
    write_line("Hello " + name);

    age = read_integer("what is your age: ");
    write_line("You entered " + to_string(age));

    value = read_integer("Enter a value between 1 and 10: ", 1, 10);
    write_line("You entered " + to_string(value));

    height = read_double("Enter your height in metres: ");
    write_line("You entered " + to_string(height));

    score = read_double("Enter a score between 0 and 100: ", 0, 100);
    write_line("You entered " + to_string(score));

    return 0;
}