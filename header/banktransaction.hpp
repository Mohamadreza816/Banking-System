#include <iostream>
#include <string>
#include <ctime>
#ifndef BANKTRANSACTION_HPP
#define BANKTRANSACTION_HPP
using namespace std;
enum check
{
    //profits
    PROFIT,
    BORROW,
    NOBORROW
};
class banktransaction
{
private:
    int day;                        //use for date
    int month;                      //use for date
    int year;                       //use for date
    int status{-1};                 //PROFIT or NOPROFIT
    int loan_status{-1};            //NOBORROW
    int tr;                         //transaction
    string source{"Unkown"};        //save source account name
    string destination { "Unkown" }; //save Destination account name

public:
    banktransaction(int); //constructor
    void set_source(string);
    void set_destination(string);
    void set_status(int);
    void set_loan_status(int);
    int get_day();         //return day
    int get_month();       //return month
    int get_year();        //return year
    int get_tr();          //return amount of transaction
    int get_status();      //return status PROFIT or NOPROFIT
    int get_loan_status(); //return loan status
    string get_source();    
    string get_destination();
};
#endif