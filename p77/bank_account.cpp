#include "splashkit.h"

class account
{
    /**
     * The balance of the account in cents.
     */
    int balance;

public:
    /**
     * The name of the account holder.
     */
    string name;

    /**
     * Creates an account with the given name and balance.
     *
     * @param name_ the name of the account
     * @param balance_ the starting balance in cents
     */
    account(string name_, int balance_)
    {
        // Initialises the account
        // We've added _ to the end of the parameters, to differentiate them from the class fields
        name = name_;
        balance = balance_;
    }

    /**
     * Creates an account with a default name and a balance of 0.
     */
    account()
    {
        // A default constructor lets you initialise the value when no parameters are passed
        name = "Account Holder Unknown";
        balance = 0;
    }

    /**
     * Outputs the account name and balance to the terminal.
     */
    void print()
    {
        write_line(name + " : $" + to_string(balance / 100.0));
    }

    /**
     * Increases the balance by the given amount, if it is positive.
     *
     * @param amount the amount to deposit in cents
     */
    void deposit(int amount)
    {
        if (amount > 0)
        {
            balance += amount;
        }
    }

    /**
     * Decreases the balance by the given amount, if it is positive.
     *
     * @param amount the amount to withdraw in cents
     */
    void withdraw(int amount)
    {
        if (amount > 0)
        {
            balance -= amount;
        }
    }

    /**
     * Returns the current balance.
     *
     * @returns the balance in cents
     */
    int get_balance()
    {
        return balance;
    }
};

int main()
{
    // Create 5 accounts objects on the stack
    account a1("Atabak", 100);
    account a2("Sheena", 734231);
    account a3("Azadeh", 90210);
    account a4("Jo", -1000);
    account a5;

    // Print the accounts
    a1.print();
    a2.print();
    a3.print();
    a4.print();
    a5.print();

    // Perform deposits and withdrawals
    a1.deposit(5000);
    a2.withdraw(1000);

    // Negative amounts should be ignored
    a3.deposit(-500);
    a3.withdraw(-500);

    // Print updated states and test get_balance
    write_line("\nUpdated accounts:");
    a1.print();
    a2.print();
    a3.print();
    write_line("a1 balance via get_balance: " + to_string(a1.get_balance()));

    return 0;
}