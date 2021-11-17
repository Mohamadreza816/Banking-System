#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include <iostream>
#include <vector>
#include <stdbool.h>
#include "banktransaction.hpp"
using namespace std;
// enum for diffrent type of transaction
enum transaction
{
    //transactions
    DEPOSIT,
    WITHDRAW
};
class customer
{
private:
    string username;
    int card_number;
    struct date
    {
        int year;
        int month;
        int day;
    };
    struct date array[2]; //arrayy[0] : store opening date-------array[1] : store expiration date
    int stock;
    vector<int> transactions; //store transaction for each customer
    vector<string> ip;        //store ip(or ips) for each customer
public:
    customer();
    //setters
    void set_name(string);
    void set_cadr_num(int);
    void set_stock();
    bool set_ip(string);
    void set_date();
    //setters

    //getters
    string get_username();
    int get_card_num();
    double get_stock();
    string get_ip(); //return the last IP
    string get_opening_date();
    string get_expiration_date();
    int get_size_transactions();
    //getters

    //other methods
    bool transaction(int, int);
    bool checkIP(string);
    void save_transactions(vector<banktransaction> &);
    bool take_profites(vector<banktransaction> &);
};

#endif