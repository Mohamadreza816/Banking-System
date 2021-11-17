#include <iostream>
#include <string>
#include <ctime>
#ifndef BANKTRANSACTION_HPP
#define BANKTRANSACTION_HPP
using namespace std;
enum check
{
    //profit
    PROFIT,
    NOPROFIT
};
class banktransaction
{
private:
    int day;   //use for date
    int month; //use for date
    int year;  //use for date
    int status;
    long long int tr; //transaction

public:
    banktransaction(int); //constructor
    void set_status(int);
    int get_day();          //return day
    int get_month();        //return month
    int get_year();         //return year
    long long int get_tr(); //return amount of transaction
    int get_status();       //return status PROFIT or NOPROFIT
};
#endif