#include "splashkit.h"
#include "utilities.h"
#include <vector>
using std::vector;

const int MIN_GRADE = 0;
const int MAX_GRADE = 100;
const int PASS_MARK = 50;
const int HD_MARK = 80;

/**
 * Asks how many grades to enter, then reads each one from the user.
 *
 * @returns the grades the user entered
 */
vector<int> read_grades()
{
    vector<int> grades;
    int count = read_integer_range("How many grades? ", 1, 100);

    for (int i = 0; i < count; i++)
    {
        grades.push_back(read_integer_range("Enter grade " + to_string(i + 1) + ": ", MIN_GRADE, MAX_GRADE));
    }

    return grades;
}

/**
 * Calculates the average of the grades.
 *
 * @param grades the grades to average
 * @returns the average grade
 */
double average(const vector<int> &grades)
{
    int count = grades.size();
    double total = 0;

    for (int i = 0; i < count; i++)
    {
        total += grades[i];
    }

    return total / count;
}

/**
 * Calculates the percentage of grades that are a pass (50 or more).
 *
 * @param grades the grades to check
 * @returns the pass rate as a percentage
 */
double pass_rate(const vector<int> &grades)
{
    int count = grades.size();
    int passes = 0;

    for (int i = 0; i < count; i++)
    {
        if (grades[i] >= PASS_MARK)
        {
            passes++;
        }
    }

    return passes * 100.0 / count;
}

/**
 * Counts how many grades are a high distinction (80 or more).
 *
 * @param grades the grades to check
 * @returns the number of high distinctions
 */
int count_hd(const vector<int> &grades)
{
    int count = grades.size();
    int hds = 0;

    for (int i = 0; i < count; i++)
    {
        if (grades[i] >= HD_MARK)
        {
            hds++;
        }
    }

    return hds;
}

int main()
{
    write_line("Student Grade Analyser");

    vector<int> grades = read_grades();

    write_line();
    write_line("Average grade: " + to_string(average(grades)));
    write_line("Pass rate: " + to_string(pass_rate(grades)) + "%");
    write_line("High distinctions: " + to_string(count_hd(grades)));

    return 0;
}