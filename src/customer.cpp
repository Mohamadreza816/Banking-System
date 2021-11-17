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
        for (auto item : ip)
        {
            if (item == a_ip)
            {
                throw invalid_argument("This IP alredy exists!!!");
            }
        }
        ip.push_back(a_ip);
        cout << "push back IP" << endl;
        return true;
    }
    catch (invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

void customer::set_stock()
{
    stock = 0;
}

void customer::set_date()
{

    time_t now = time(0);
    tm *ltm = localtime(&now);
    //set opening date in array[0]
    array[0].year = ltm->tm_year + 1900;
    array[0].month = 1 + ltm->tm_mon;
    array[0].day = ltm->tm_mday;
    //set expiration date in array[1]
    array[1].year = ltm->tm_year + 1900 + 2;
    array[1].month = 1 + ltm->tm_mon;
    array[1].day = ltm->tm_mday;
}
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

string customer::get_opening_date()
{
    string temp = "";
    temp = to_string(array[0].month) + "/" + to_string(array[0].day) + "/" + to_string(array[0].year);
    return temp;
}

string customer::get_expiration_date()
{
    string temp = "";
    temp = to_string(array[1].month) + "/" + to_string(array[1].day) + "/" + to_string(array[1].year);
    return temp;
}
// end of getters
//--------------------------------
//transaction method
bool customer::transaction(int amount, int status)
{
    //status == 0 --------->deposit
    //status == 1 --------->whitdraw
    //status == 2 --------->transfer
    time_t now = time(0);
    tm *ltm = localtime(&now);
    try
    {
        //check curent year with expiration year
        if ((ltm->tm_year + 1900) > array[1].year)
        {
            cout << "1" << endl;
            throw out_of_range("you can't do transaction!you must renewal account");
        }
        //check curent month with expiration month if(curent year == expiration year)
        if (((ltm->tm_year + 1900) == array[1].year) && ltm->tm_mon + 1 > array[1].month)
        {
            cout << "2" << endl;
            throw out_of_range("you can't do transaction!you must renewal account");
        }
        //check curent day with expiration day if(curent year == expiration year &&  curent month == expiration month)
        if (((ltm->tm_year + 1900) == array[1].year) && (ltm->tm_mon + 1 == array[1].month) && ltm->tm_mday > array[1].day)
        {
            cout << "3" << endl;
            throw out_of_range("you can't do transaction!you must renewal account");
        }
        if (status == DEPOSIT)
        {
            stock = stock + amount;
        }
        if (status == WITHDRAW)
        {
            if (stock >= amount)
            {
                stock = stock - amount;
                return true;
            }
            else
            {
                throw out_of_range("threr is not enough stock for withdraw!!");
            }
        }
    }
    catch (const out_of_range &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}
//end of transaction method
//--------------------------------
//checkIP
bool customer::checkIP(string ip_a)
{
    for (auto item : ip)
    {
        if (item == ip_a)
        {
            return true;
        }
    }
    return false;
}
//end of check_ip
//--------------------------------
//save transactions
void customer::save_transactions(vector<banktransaction> &AT) //AT = all transaction
{
    //push element number of AT in the customer::transactions(vector)
    transactions.push_back(AT.size());
}
//end of save transactions
//--------------------------------
//get_size_transactios
int customer::get_size_transactions()
{
    return transactions.size(); //return size of vector
}
//end of get_size_transaction
//--------------------------------
//take_profits method
bool customer::take_profites(vector<banktransaction> &AT)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int sum{0};
    int DAY{0};
    int MONTH{0};
    int YEAR{0};
    try
    {
        for (int j = 0; j < transactions.size(); j++)
        {
            DAY = (ltm->tm_mday) - AT[transactions[j]].get_day();
            if (DAY < 0) //for correct in number---> 5 - 29 = -24 but in date-----> 5 - 29 = 5
            {
                DAY += 30;
            }
            if (AT[transactions[j]].get_status() == PROFIT)
            {
                YEAR = (ltm->tm_year + 1900) - AT[transactions[j]].get_year();
                if (YEAR == 0)
                {
                    MONTH = 1 + ltm->tm_mon - AT[transactions[j]].get_month();
                    if (MONTH < 0)
                    {
                        MONTH += 12;
                    }
                    if (MONTH * DAY < 30)
                    {
                        throw out_of_range("you can't add another profit!");
                    }
                }
            }
            if (DAY <= 7)
            {
                sum = sum + AT[transactions[j]].get_tr();
            }
        }
        sum = static_cast<double>(((stock - sum) + stock) / 2) * 0.1; //average of stock in 7 days = (stock of 7 days ago + stock today / 2)
        if (sum <= 0)
        {
            throw invalid_argument("This user can not take profit!");
        }
        this->transaction(DEPOSIT, sum);
        banktransaction temp(sum);
        temp.set_status(PROFIT);
        AT.push_back(temp);
        this->save_transactions(AT);
    }
    catch (const invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    catch(const out_of_range& e)
    {
        cerr << e.what() << endl;
        return false;
    }
    return true;
}
//end of take_profits
//--------------------------------