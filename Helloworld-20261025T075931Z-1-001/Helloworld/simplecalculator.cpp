#include "splashkit.h"

int main()
{
    string line;
    int choice;

    do
    {
        write_line("1: Say Hello");
        write_line("2: Say Goodbye");
        write_line("3: Quit");
        write("Enter your choice: ");
        line = read_line();

        while (!is_integer(line))
        {
            write_line("Please enter a whole number");
            write("Enter your choice: ");
            line = read_line();
        }

        choice = to_integer(line);

        switch (choice)
        {
            case 1:
                write_line("Hello there!");
                break;
            case 2:
                write_line("Goodbye, see you next time!");
                break;
            case 3:
                write_line("Quitting the program...");
                break;
            default:
                write_line("Invalid choice");
                break;
        }
    } while (choice != 3);

    return 0;
}