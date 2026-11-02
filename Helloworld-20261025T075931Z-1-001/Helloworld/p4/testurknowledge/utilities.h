#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
using std::string;

/**
 * Draws a line like +------+ to the terminal.
 *
 * @param width the total width of the line
 */
void draw_heading_line(int width);

/**
 * Draws a title inside a box, with a heading line above and below.
 *
 * @param title the text to show in the box
 * @param width the total width of the box
 */
void draw_title(string title, int width);

/**
 * Shows a prompt and reads a line of text from the user.
 *
 * @param prompt the message to show the user
 * @returns the text the user entered
 */
string read_string(string prompt);

/**
 * Reads a whole number from the user, asking again until the input is valid.
 *
 * @param prompt the message to show the user
 * @returns the number the user entered
 */
int read_integer(string prompt);

/**
 * Reads a whole number between low and high (inclusive), asking again
 * until the input is valid.
 *
 * @param prompt the message to show the user
 * @param low the smallest value allowed
 * @param high the largest value allowed
 * @returns the number the user entered
 */
int read_integer_range(string prompt, int low, int high);

/**
 * Reads a y or n answer from the user, asking again until the input is valid.
 *
 * @param prompt the message to show the user
 * @returns true if the user entered y, false if they entered n
 */
bool read_boolean(string prompt);

#endif