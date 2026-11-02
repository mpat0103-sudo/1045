#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
using std::string;

void draw_heading_line(int width);
void draw_title(string title, int width);
string read_string(string prompt);
int read_integer(string prompt);
int read_integer_range(string prompt, int low, int high);
bool read_boolean(string prompt);

/**
 * Reads a whole number between low and high (inclusive).
 *
 * @param prompt the message to show the user
 * @param low the smallest value allowed
 * @param high the largest value allowed
 * @returns the number the user entered
 */
int read_integer(string prompt, int low, int high);

/**
 * Reads a number (can have decimals) from the user, asking again until the input is valid.
 *
 * @param prompt the message to show the user
 * @returns the number the user entered
 */
double read_double(string prompt);

#endif