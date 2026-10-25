#include "splashkit.h"

int main()
{
    string target;
    double target_amount;
    double time_weeks;
    double current_savings;
    double weekly_savings;
    
    double dollars_per_week;
    double weeks_needed;

    write("What are you saving for? Enter title: ");
    target = read_line();

    write("How much do you need to save? Enter dollars: ");
    target_amount = to_double(read_line());

    write("How long before the purchase? Enter weeks: ");
    time_weeks = to_double(read_line());

    write("How much do you have already? Enter dollars: ");
    current_savings = to_double(read_line());

    write("How much can you save each week? Enter dollars: ");
    weekly_savings = to_double(read_line());

    write_line(); 

    dollars_per_week = (target_amount - current_savings) / time_weeks;
    weeks_needed = (target_amount - current_savings) / weekly_savings;

    write_line("For the " + target + ", you need to save " + to_string(dollars_per_week) + " dollars a week");
    write_line("Based on current savings you will need " + to_string(weeks_needed) + " weeks to save $" + to_string(target_amount));

    return 0;
}