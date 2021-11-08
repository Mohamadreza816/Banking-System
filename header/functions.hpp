#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "customer.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//function prototype
bool command(string, vector<customer>);//function for read the command
bool check_username(string);           //is correct or not?
bool check_ip(string);                 //is ip correct or not?
#endif