#include "splashkit.h"
#include "utilities.h"

enum menu_option
{
    ENTER_BOOK,
    PRINT_BOOK,
    QUIT
};

struct book_data
{
    string name;
    string location;
    int pages;
};

book_data read_book()
{
    book_data result;
    result.name = read_string("Enter the name of the book: ");
    result.location = read_string("Enter book location: ");
    result.pages = read_integer("Enter number of pages: ");
    return result;
}

void print_book(book_data book)
{
    write_line();
    write_line("Book details:");
    write_line("Title: " + book.name);
    write_line("Location: " + book.location);
    write_line("Pages: " + to_string(book.pages));
}

menu_option read_menu_option()
{
    int choice;

    write_line();
    write_line("Menu:");
    write_line("1 - Enter book details");
    write_line("2 - Print book");
    write_line("3 - Quit");

    choice = read_integer_range("Option: ", 1, 3);

    return (menu_option)(choice - 1);
}

int main()
{
    book_data book;
    menu_option option;

    write_line("Book entry system:");
    book = read_book();

    do
    {
        option = read_menu_option();

        if (option == ENTER_BOOK)
        {
            book = read_book();
        }
        else if (option == PRINT_BOOK)
        {
            print_book(book);
        }
    } while (option != QUIT);

    return 0;
}