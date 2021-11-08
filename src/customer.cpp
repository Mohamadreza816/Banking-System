#include "../header/customer.hpp"
#include <ctime>
#include <stdexcept>
#include <string>
//constructor
customer::customer()
{
}
// End of constructo
//--------------------------------

//setters
void customer::set_name(string a_name)
{
    username = a_name;
}

void customer::set_cadr_num(int a_card)
{
    card_number = a_card;
}

bool customer::set_ip(string a_ip)
{
    try
    {
      for(auto item: ip)
    {
        if (item == a_ip)
        {
            throw invalid_argument("This IP alredy exists!!!");
        }
    }  

    }
    catch(invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    ip.push_back(a_ip);
    return true;
}

void customer::set_stock()
{
    stock = 0.0;
}

void customer::set_opening_date(struct opening_date* OD)
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    OD->year = ltm->tm_year + 1900;
    OD->month = 1 + ltm->tm_mon;
    OD->day = ltm->tm_mday;
}

void customer::set_expiration_date(struct expiration_date* ED)
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    ED->year = ltm->tm_year + 1900 + 2;
    ED->month = 1 + ltm->tm_mon;
    ED->day = ltm->tm_mday;
}
//End of setters
//--------------------------------

//getters
string customer::get_username()
{
    return username;
}

int customer::get_card_num()
{
    return card_number;
}

double customer::get_stock()
{
    return stock;
}

string customer::get_ip()
{
    return ip.back();
}

string customer::get_opening_date(struct opening_date* OD)
{
    string temp = ""; 
    temp = to_string(OD->month) + "/" + to_string(OD->day) + "/" + to_string(OD->year);
    return temp;
}

string customer::get_expiration_date(struct expiration_date* ED)
{
    string temp = ""; 
    temp = to_string(ED->month) + "/" + to_string(ED->day) + "/" + to_string(ED->year);
    return temp;
}
// end of getters

