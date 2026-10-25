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

#endif