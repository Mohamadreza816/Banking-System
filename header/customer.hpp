#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <vector>
#include <stdbool.h>
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
    customer();
    //setters
    void set_name(string);
    void set_cadr_num(int);
    void set_stock();
    bool set_ip(string);
    void set_opening_date(struct opening_date*);
    void set_expiration_date(struct expiration_date*);
    //setters
    
    //getters
    string get_username();
    int get_card_num();
    double get_stock();
    string get_ip();//return the last IP
    string get_opening_date(struct opening_date*);
    string get_expiration_date(struct expiration_date*);
    //getters
};




#endif