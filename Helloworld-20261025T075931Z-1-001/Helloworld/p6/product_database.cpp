#include "splashkit.h"
#include "splashkit-arrays.h"
#include "utilities.h"

const int NO_CHOICE = -1;
const int LOW_STOCK = 10;

enum menu_option
{
    ADD_PRODUCT = 1,
    DELETE_PRODUCT = 2,
    UPDATE_PRODUCT = 3,
    SELL_PRODUCT = 4,
    PRINT_STATUS = 5,
    LIST_PRODUCTS = 6,
    QUIT = 7
};

enum update_product_option
{
    UPDATE_NAME = 1,
    UPDATE_COST_PRICE = 2,
    UPDATE_SALE_PRICE = 3,
    UPDATE_STOCK = 4,
    UPDATE_QUIT = 5
};

struct product_data
{
    string name;
    double cost_price;
    double sale_price;
    int stock;
};

struct store_data
{
    dynamic_array<product_data> products;
    double total_sales;
    double total_profits;
};

/**
 * Print the main menu options
 */
void print_main_menu()
{
    write_line();
    write_line("Main Menu");
    write_line("1. Add a new product");
    write_line("2. Delete a product");
    write_line("3. Update a product");
    write_line("4. Sell a product");
    write_line("5. Print status");
    write_line("6. List products");
    write_line("7. Quit");
}

/**
 * Print the update menu options
 */
void print_update_menu()
{
    write_line("Update Menu");
    write_line("1. Update name");
    write_line("2. Update cost price");
    write_line("3. Update sale price");
    write_line("4. Update number in stock");
    write_line("5. Quit update");
}

/**
 * Print details of a single product.
 *
 * @param product the product to print
 */
void print_product(const product_data &product)
{
    write_line("Name:        " + product.name);
    write_line("Cost Price:  $" + to_string(product.cost_price, 2));
    write_line("Sale Price:  $" + to_string(product.sale_price, 2));
    write_line("In Stock:    " + to_string(product.stock));
}

/**
 * Read in product details from the user, making sure the name is not empty.
 *
 * @returns the product the user entered
 */
product_data read_product()
{
    product_data result;

    do
    {
        result.name = read_string("Enter product name: ");
        if (trim(result.name) == "")
        {
            write_line("Name cannot be empty. Please try again.");
        }
    } while (trim(result.name) == "");

    result.cost_price = read_double("Enter cost price: ");
    result.sale_price = read_double("Enter sale price: ");
    result.stock = read_integer("Enter amount in stock: ");

    return result;
}

/**
 * Add a new product to the store.
 *
 * @param store the store to add the product to
 */
void add_product(store_data &store)
{
    product_data new_product = read_product();
    add(store.products, new_product);
    write_line("Product added successfully!");
}

/**
 * List all products in the store.
 *
 * @param store the store containing the products
 */
void list_products(const store_data &store)
{
    if (length(store.products) == 0)
    {
        write_line("No products currently in the store.");
        return;
    }

    write_line("== Product Listing ==");
    for (int i = 0; i < length(store.products); i++)
    {
        write_line("[" + to_string(i + 1) + "]");
        print_product(store.products[i]);
        write_line("--------------------");
    }
    write_line("Total Products: " + to_string(length(store.products)));
}

/**
 * Search for a product by name and let the user pick one of the matches.
 *
 * @param store the store to search
 * @returns the index of the chosen product, or NO_CHOICE if none was found
 */
int find_product(const store_data &store)
{
    if (length(store.products) == 0)
    {
        write_line("No products available in the store.");
        return NO_CHOICE;
    }

    string search_text = to_lowercase(read_string("Enter search term: "));
    dynamic_array<int> matches;

    for (int i = 0; i < length(store.products); i++)
    {
        if (contains(to_lowercase(store.products[i].name), search_text))
        {
            add(matches, i);
            write_line(to_string(length(matches)) + ". " + store.products[i].name);
        }
    }

    if (length(matches) == 0)
    {
        write_line("No matching products found.");
        return NO_CHOICE;
    }

    int choice = read_integer("Select a product (1-" + to_string(length(matches)) + "): ", 1, length(matches));

    return matches[choice - 1];
}

/**
 * Remove a product from the store after searching for it.
 *
 * @param store the store to remove the product from
 */
void delete_product(store_data &store)
{
    int index = find_product(store);
    if (index == NO_CHOICE) return;

    string product_name = store.products[index].name;
    remove(store.products, index);

    write_line("Removed " + product_name + " from the store database.");
}

/**
 * Sell some of a product and update the store's sales and profits.
 *
 * @param store the store to update
 */
void sell_product(store_data &store)
{
    int index = find_product(store);
    if (index == NO_CHOICE) return;

    product_data &product = store.products[index];

    if (product.stock == 0)
    {
        write_line(product.name + " is out of stock.");
        return;
    }

    write_line("Selected: " + product.name + " (Stock: " + to_string(product.stock) + ")");
    int quantity = read_integer("Enter quantity to sell: ", 1, product.stock);

    product.stock -= quantity;

    store.total_sales += product.sale_price * quantity;
    store.total_profits += (product.sale_price - product.cost_price) * quantity;

    write_line("Successfully sold " + to_string(quantity) + " unit(s) of " + product.name + "!");
}

/**
 * Let the user update the details of a product.
 *
 * @param store the store containing the product
 */
void update_product(store_data &store)
{
    int index = find_product(store);
    if (index == NO_CHOICE) return;

    update_product_option option;

    do
    {
        write_line("Current details:");
        print_product(store.products[index]);
        write_line();
        print_update_menu();

        option = (update_product_option)read_integer("Enter an option: ", 1, 5);

        switch (option)
        {
            case UPDATE_NAME:
                store.products[index].name = read_string("Enter new name: ");
                write_line("Updated name.");
                break;
            case UPDATE_COST_PRICE:
                store.products[index].cost_price = read_double("Enter new cost price: ");
                write_line("Updated cost price.");
                break;
            case UPDATE_SALE_PRICE:
                store.products[index].sale_price = read_double("Enter new sale price: ");
                write_line("Updated sale price.");
                break;
            case UPDATE_STOCK:
                store.products[index].stock = read_integer("Enter new amount in stock: ");
                write_line("Updated amount of stock.");
                break;
            case UPDATE_QUIT:
                break;
        }
    } while (option != UPDATE_QUIT);
}

/**
 * Print the store's total sales, profit, stock value and low stock count.
 *
 * @param store the store to report on
 */
void print_status(const store_data &store)
{
    double stock_value = 0;
    int low_stock = 0;

    for (int i = 0; i < length(store.products); i++)
    {
        stock_value += store.products[i].cost_price * store.products[i].stock;
        if (store.products[i].stock < LOW_STOCK)
        {
            low_stock++;
        }
    }

    write_line("== Store Report ==");
    write_line("Total sales:     $" + to_string(store.total_sales, 2));
    write_line("Total profit:    $" + to_string(store.total_profits, 2));
    write_line("Products:        " + to_string(length(store.products)));
    write_line("Stock value:     $" + to_string(stock_value, 2));
    write_line("Low stock (<10): " + to_string(low_stock));
}

int main()
{
    store_data store;
    store.total_sales = 0;
    store.total_profits = 0;

    menu_option option;

    write_line("Product Database!");

    do
    {
        print_main_menu();
        option = (menu_option)read_integer("Please choose an option: ", 1, 7);

        switch (option)
        {
            case ADD_PRODUCT:
                add_product(store);
                break;
            case DELETE_PRODUCT:
                delete_product(store);
                break;
            case UPDATE_PRODUCT:
                update_product(store);
                break;
            case SELL_PRODUCT:
                sell_product(store);
                break;
            case PRINT_STATUS:
                print_status(store);
                break;
            case LIST_PRODUCTS:
                list_products(store);
                break;
            case QUIT:
                break;
        }
    } while (option != QUIT);

    write_line("Thank you for using our service. Program Quitting....");
    return 0;
}