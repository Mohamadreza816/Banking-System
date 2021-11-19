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
//end of constructor
//-------------------------------------------
//set_source method
void banktransaction::set_source(string a)
{
    source = a;
}
//end of set_source method
//-------------------------------------------
//set_destination
void banktransaction::set_destination(string a)
{
    destination = a;
}
//end of set_destination
//-------------------------------------------
//set_status
void banktransaction::set_status(int e_arg)
{
    //e_parg = enum argumant
    status = e_arg;
} 
//end of set_status
//-------------------------------------------
//set_loan_status methos
void banktransaction::set_loan_status(int e_arg)
{
    loan_status = e_arg;
}
//end of loan status
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
int banktransaction::get_tr()
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
//get_loan_status method
int banktransaction::get_loan_status()
{
    return loan_status;
}
// end of get_loan_status method
//-------------------------------------------
//get_source method
string banktransaction::get_source()
{
    return source;
}
//end of get_source method
//-------------------------------------------
//get_destination
string banktransaction::get_destination()
{
    return destination;
}
//end of get_destination
//-------------------------------------------