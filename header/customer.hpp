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
    static int count_of_customer;
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
    int borrow;
    vector<int> transactions; //store transaction for each customer
    vector<string> ip;        //store ip(or ips) for each customer
public:
    customer();
    //setters
    void set_name(string);
    void set_cadr_num(int);
    void set_stock();
    void set_borrow(int);
    bool set_ip(string);
    void set_date();
    //setters

    //getters
    string get_username();
    int get_card_num();
    int get_stock();
    int get_borrow();
    int get_count(); //return count of customer
    void get_ip(); //return the IP
    string get_opening_date();
    string get_expiration_date();
    int get_size_transactions();
    //getters

    //other methods
    bool transaction(int, int, vector<customer> &);
    bool checkIP(string);
    void save_transactions(vector<banktransaction> &);
    bool take_profites(vector<banktransaction> &, vector<customer> &);
};

#endif