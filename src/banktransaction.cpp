#include "../header/banktransaction.hpp"
//constructor
banktransaction::banktransaction(int amount)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    //set opening date in array[0]
    year = ltm->tm_year + 1900;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;
    tr = amount;
}
//constructor
//-------------------------------------------
//set_status
void banktransaction::set_status(int e_profit)
{
    //e_profit = enum profit
    status = e_profit;
} 
//-------------------------------------------
//get_day method
int banktransaction::get_day()
{
    return day;
}
//end of get_day
//-------------------------------------------
//get_month method
int banktransaction::get_month()
{
    return month;
}
//end of get_month method
//-------------------------------------------
//get_year method
int banktransaction ::get_year()
{
    return year;
}
//end of get_year method
//-------------------------------------------
//banktransaction method
long long int banktransaction::get_tr()
{
    return tr;
}
//end of banktransaction
//-------------------------------------------
//get_status method use for checking profit customers
int banktransaction::get_status()
{
    return status;
}
//end of get_status
//-------------------------------------------