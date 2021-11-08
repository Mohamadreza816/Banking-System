#include "../header/functions.hpp"
using namespace std;
//separate command
bool command(string request, vector<customer> a_customer)
{
    int pos = request.find(' ');
    if (request.substr(0, pos) == "create")
    {
        request = request.substr(pos+1);
        int pos1 = request.find(':');
        check_username(request.substr(0,pos1));
        check_ip(request.substr(pos1 + 1));
    }
}
//------------------------------------------------------
//check username
bool check_username(string name)
{
    try
    {
        if (isdigit(name[0]))
        {
            throw out_of_range("numbers can not coming in the first of username!!!");
        }
        // use ascii code for checking that name is English or not
        for (size_t i = 0; i < name.length(); i++)
        {
            if (((int)name[i] >= 48 && (int)name[i] <= 57) || ((int)name[i] >= 65 && (int)name[i] <= 90) || ((int)name[i] >= 97 && (int)name[i] <= 122))
            {
            }
            else
            {
                throw out_of_range("username must contains numbers and words!!!");
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
//end of check username function
//------------------------------------------------------

//check ip function
bool check_ip(string a_ip)
{
    int count = 1; // for counting Point
    int k = 0;
    try
    {
        for (size_t i = 0; count < 3 && i < a_ip.length(); i++)
        {
            if (a_ip[i] == '.')
            {
                int temp{0};
                cout << a_ip.substr(k, i - k) << endl;
                temp = stoi(a_ip.substr(k, i - k));
                if (temp < 0 || temp > 255)
                {
                    throw out_of_range("IP is invalid!!!");
                }
                count++;
                k = i + 1;
            }
        }
    }
    catch (const out_of_range& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    if (count == 3)
    {
        cout << "ip is correct" << endl;
        return true;
    }
    
}