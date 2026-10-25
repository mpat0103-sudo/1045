#include "splashkit.h"

const int MAX_NUMBER = 100;
const int MAX_GUESSES = 7;

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

void print_line(int length)
{
    int i = 0;
    while (i < length)
    {
        write("-");
        i++;
    }
    write_line();
}

bool perform_guess(int num_guess, int target)
{
    int guess;

    guess = read_integer("Guess " + to_string(num_guess) + ": ", 1, MAX_NUMBER);

    if (target < guess)
    {
        write_line("The number is less than " + to_string(guess));
    }
    else if (target > guess)
    {
        write_line("The number is larger than " + to_string(guess));
    }
    else
    {
        write_line("Well done... the number was " + to_string(guess));
    }

    return target == guess;
}

void play_game()
{
    int my_number, num_guess;
    bool got_it;

    my_number = rnd(MAX_NUMBER) + 1;
    num_guess = 0;
    got_it = false;

    write_line("I am thinking of a number between 1 and " + to_string(MAX_NUMBER));

    do
    {
        num_guess++;
        got_it = perform_guess(num_guess, my_number);
    } while (num_guess < MAX_GUESSES && !got_it);

    if (!got_it)
    {
        write_line("You ran out of guesses... the number was " + to_string(my_number));
    }
}

int main()
{
    string again = "";

    do
    {
        play_game();

        write_line();
        print_line(50);
        again = read_string("Do you want to play again [Y/n]? ");
    } while (again != "N" && again != "n");

    write_line("Bye");

    return 0;
}