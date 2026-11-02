#include "splashkit.h"
#include "utilities.h"

const int MIN_SIDES = 2;
const int MAX_SIDES = 100;

enum menu_option
{
    ROLL_DIE = 1,
    NEW_DIE = 2,
    QUIT = 3
};

class die
{
    /**
     * The number of sides on the die. This is only set in the constructor,
     * and there is no method to change it, so it cannot change after creation.
     */
    int sides;

    /**
     * The value currently showing on top of the die.
     */
    int value;

public:
    /**
     * Creates a die with the given number of sides, and rolls it
     * so it starts with a valid value.
     *
     * @param sides_ the number of sides on the die
     */
    die(int sides_)
    {
        sides = sides_;
        roll();
    }

    /**
     * Rolls the die, setting the value to a random number between 1 and sides.
     */
    void roll()
    {
        value = rnd(sides) + 1;
    }

    /**
     * Returns the value currently showing on top of the die.
     *
     * @returns the current value
     */
    int get_value()
    {
        return value;
    }

    /**
     * Outputs the number of sides and the current value to the terminal.
     */
    void print()
    {
        write_line(to_string(sides) + " sides: value is " + to_string(value));
    }
};

/**
 * Prints the menu options.
 */
void print_menu()
{
    write_line("1: Roll die");
    write_line("2: Get new die");
    write_line("3: Quit");
}

int main()
{
    die my_die(read_integer_range("Sides: ", MIN_SIDES, MAX_SIDES));
    menu_option option;

    do
    {
        print_menu();
        option = (menu_option)read_integer_range("> ", 1, 3);

        switch (option)
        {
            case ROLL_DIE:
                my_die.roll();
                my_die.print();
                write_line();
                break;
            case NEW_DIE:
                my_die = die(read_integer_range("Sides: ", MIN_SIDES, MAX_SIDES));
                write_line();
                break;
            case QUIT:
                break;
        }
    } while (option != QUIT);

    return 0;
}