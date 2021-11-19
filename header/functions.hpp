#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "customer.hpp"
#include "banktransaction.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

//function prototype
void message();                                                                   //show abilty og program
bool command(string, vector<customer> &, vector<banktransaction> &);              //function for read the command
bool check_username(string, vector<customer> &);                                  //username is correct or not?(add new user)
bool add_ip(string, vector<customer> &);                                          //add new_ip
bool check_ip(string);                                                            //is ip correct or not?
void make_obj(string, string, int, vector<customer> &);                           //set class members
int card_number(vector<customer> &);                                              //generate random number
void customer_transaction(string, vector<customer> &, vector<banktransaction> &); //deposit and withdraw
void transfer(string, vector<customer> &, vector<banktransaction> &);             //transfer money
void renewal(string, vector<customer> &, vector<banktransaction> &);              //renewal the customer account
void profits(string, vector<customer> &, vector<banktransaction> &);              //add profits for customers
void get_loan(string, vector<customer> &, vector<banktransaction> &);             //get loan to the customers
void pay_loan(string, vector<customer> &, vector<banktransaction> &);             //pay loan to the bank
bool show(string, vector<customer> &, vector<banktransaction> &);                 //show bank and customers info
#endif