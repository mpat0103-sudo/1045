#include "splashkit.h"

int main()
{
    string user_input;
    double value;
    int count = 0;
    double total = 0;
    double average = 0;

    write_line("Welcome to the simple stats calculator:");

    do
    {
        write("Enter value: ");
        user_input = read_line();

        while (!is_double(user_input))
        {
            write_line("Please enter a number");
            write("Enter value: ");
            user_input = read_line();
        }

        value = to_double(user_input);
        count = count + 1;
        total = total + value;
        average = total / count;

        write_line("Count: " + to_string(count));
        write_line("Total: " + to_string(total));
        write_line("Average: " + to_string(average));

        write("Add another value: [y/n] ");
        user_input = read_line();
    } while (user_input != "n" && user_input != "N" && user_input != "no");

    write_line("I hope you got the information you are after!");

    return 0;
}