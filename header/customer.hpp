#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <vector>
using namespace std;
class customer{
private:
    string username;
    int card_number;
    struct opening_date
    {
        int year;
        int month;
        int day;
    };
    struct expiration_date
    {
        int year;
        int month;
        int day;
    };
    double stock;
    vector<double>*transaction;//store transaction for each customer
    vector<string> ip;//store ip(or ips) for each customer
public:
    customer(string, string, int);
    //setters
    void set_opening_date(struct opening_date*);
    void set_opening_date(struct expiration_date*);
    //setters

    
};




#endif