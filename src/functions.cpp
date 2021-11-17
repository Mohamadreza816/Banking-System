#include "../header/functions.hpp"
using namespace std;
//separate command
bool command(string request, vector<customer> &v_customer, vector<banktransaction> &AT)
{
    int pos = request.find(' ');
    if (request.substr(0, pos) == "create")
    {
        request = request.substr(pos + 1);
        int pos1 = request.find(':');
        if (check_username(request.substr(0, pos1), v_customer) == false)
        {
            return false;
        }
        string name = request.substr(0, pos1);
        if (check_ip(request.substr(pos1 + 1)) == false)
        {
            return false;
        }
        string ip = request.substr(pos1 + 1);
        int c_num = card_number(v_customer);
        make_obj(name, ip, c_num, v_customer);
        return true;
    }
    if (request.substr(0, pos) == "add_ip")
    {
        request = request.substr(pos + 1);
        add_ip(request, v_customer);
        return true;
    }
    if ((request.substr(0, pos) == "deposit") || (request.substr(0, pos) == "withdraw"))
    {
        customer_transaction(request, v_customer, AT);
        return true;
    }
    if (request.substr(0, pos) == "transfer")
    {
        transfer(request, v_customer, AT);
        return true;
    }
    if (request.substr(0, pos) == "renewal")
    {
        renewal(request, v_customer, AT);
        return true;
    }
    if (request.substr(0, pos) == "add_profits")
    {
        profits(request.substr(pos + 1), v_customer, AT);
        cout << "yes" << endl;
        return true;
    }

    return false;
}
//------------------------------------------------------
//check username for add new customer
bool check_username(string name, vector<customer> &v_customer)
{
    try
    {
        for (auto item : v_customer)
        {
            if (item.get_username() == name)
            {
                throw invalid_argument("This username already exists");
            }
        }
        // username = (number)+.... ----> Error
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
    catch (const invalid_argument &e)
    {
        cerr << e.what() << '\n';
        return false;
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
    int count = 0; // for counting Point
    int k = 0;
    int temp{0}; //a var for converting string to int
    try
    {
        for (size_t i = 0; i <= a_ip.length(); i++)
        {
            cout << a_ip[i] << endl;
            if (a_ip[i] == '.')
            {
                temp = stoi(a_ip.substr(k, i - k));
                if (temp < 0 || temp > 255)
                {
                    throw out_of_range(" is invalid!!!");
                }
                count++;
                k = i + 1;
            }
            if (a_ip[i] == '\0')
            {
                temp = stoi(a_ip.substr(k, i - k));
                if (temp < 0 || temp > 255)
                {
                    throw out_of_range(" is invalid!!!");
                }
            }
            
        }
    }
    catch (const out_of_range &e)
    {
        std::cerr << a_ip << e.what() << '\n';
        return false;
    }
    if (count == 3)
    {
        return true;
    }
    cout << a_ip << " is invalid!" << endl;
    return false;
}
//end of check ip function
//------------------------------------------------------
//make new customer object
void make_obj(string username, string IP, int card, vector<customer> &v_customer)
{
    customer temp;
    temp.set_name(username);
    temp.set_ip(IP);
    temp.set_cadr_num(card);
    temp.set_stock();
    temp.set_date();
    v_customer.push_back(temp);
    cout << temp.get_username() << " was added successfully" << endl;
}
//end of make_obj
//------------------------------------------------------
//make card_number
int card_number(vector<customer> &v_customer)
{
    srand(time(0));
    int card{0};
    int check = 1;
    while (true)
    {
        for (size_t i = 0; i < 4; i++)
        {
            card = (card * 10) + (rand() % 10);
        }
        for (auto item : v_customer)
        {
            if (item.get_card_num() == card)
            {
                card = 0;
                check = -1;
            }
        }
        if (check == 1)
        {
            break;
        }
    }
    return card;
}
//End of make card_number
//------------------------------------------------------
//add_ip
bool add_ip(string request, vector<customer> &v_customer)
{
    int check{0};
    int pos = request.find(':');
    try
    {
        int i{0};
        //check username
        for (i = 0; i < v_customer.size(); i++)
        {
            if (v_customer[i].get_username() == request.substr(0, pos))
            {
                check = 1;
                break;
            }
        }
        if (check == 0)
        {
            throw invalid_argument("This username dosen't exists!");
        }
        int j = 0;
        //separate command by (':') for read ip
        while (true)
        {
            if (request[j] == '\0')
            {
                //if input ip was correct then we add that to ip list
                if (check_ip(request) == true)
                {
                    v_customer[i].set_ip(request);
                }
                else
                {
                    return false;
                }
                break;
            }
            if (request[j] == ':')
            {
                if (isdigit(request[j + 1]))
                {
                    request = request.substr(j + 1); //remove (another) from request

                    j = 0;
                    // if (check_ip(request.substr(0, pos1)) == true)
                    // {
                    //     v_customer[i].set_ip(request.substr(0, pos1));
                    // }
                    // else
                    // {
                    //     return false;
                    // }
                }
                else
                {
                    //sent ip to check ip
                    if (check_ip(request.substr(0, j)) == true)
                    {
                        v_customer[i].set_ip(request.substr(0, j));
                        cout << request.substr(0, j) << " was added successfully" << endl;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            j++;
        }
    }
    catch (const invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}
//end of add_ip
//------------------------------------------------------
//customer_transaction function
void customer_transaction(string request, vector<customer> &v_customer, vector<banktransaction> &AT) //AT = all transaction
{
    int pos = request.find(' ');
    int status;
    if (request.substr(0, pos) == "deposit")
    {
        status = DEPOSIT;
    }
    if (request.substr(0, pos) == "withdraw")
    {
        status = WITHDRAW;
    }
    request = request.substr(pos + 1);
    int pos1 = request.find(':');
    int i = 0;
    int check = 0;
    try
    {
        for (i = 0; i < v_customer.size(); i++)
        {
            if (v_customer[i].get_username() == request.substr(0, pos1)) //check input username in list of all customers, and select customer
            {
                check = 1;
                break;
            }
        }
        if (check == 0)
        {
            throw invalid_argument("This username dosen't exists!");
        }
        request = request.substr(pos1 + 1);

        int j = 0;
        while (true)
        {
            if (request[j] == ':')
            {
                if (v_customer[i].checkIP(request.substr(0, j)) == true) //check input ip in the ip list for the customer
                {
                }
                else
                {
                    throw invalid_argument("This username dosen't exists!");
                }
                request = request.substr(j + 1); // remove ip from request after check and store money
            }
            if (request[j] == '\0')
            {
                long long int money = stoi(request);
                if (v_customer[i].transaction(money, status))
                {
                    if (status == WITHDRAW)
                    {
                        banktransaction temp(-money);
                        AT.push_back(temp); //save withdraw transactions in bank list
                    }
                    else
                    {
                        banktransaction temp(money);
                        AT.push_back(temp); //save deposit transactions in bank list
                    }
                    v_customer[i].save_transactions(AT); //save transaction in customer list
                }
                break;
            }
            j++;
        }
    }
    catch (const invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}
//end of customer_transaction function
//------------------------------------------------------
//transfer function
void transfer(string request, vector<customer> &v_customer, vector<banktransaction> &AT)
{
    int pos = request.find(' ');
    request = request.substr(pos + 1);
    pos = request.find(':');
    int check = 0;
    string array[4]; //store different parts of request in array
    int i = 0;
    try
    {
        for (i = 0; i < v_customer.size(); i++)
        {
            if (v_customer[i].get_username() == request.substr(0, pos))
            {
                array[0] = request.substr(0, pos); //store sender username
                request = request.substr(pos + 1); //remove sender username from request
                check = 1;
                break;
            }
        }
        if (check == 0)
        {
            throw invalid_argument("This username dosen't exists!");
        }
        pos = request.find(':');
        if (v_customer[i].checkIP(request.substr(0, pos)))
        {
            array[1] = request.substr(0, pos); //store sender_ip
            request = request.substr(pos + 1); //remove sender ip from request
        }
        else
        {
            throw invalid_argument("This IP dosen't exists!");
        }
        pos = request.find(':');
        int j = 0;
        check = 0;
        for (j = 0; j < v_customer.size(); j++)
        {
            if (v_customer[j].get_username() == request.substr(0, pos))
            {
                array[2] = request.substr(0, pos);  //store receiver username
                array[3] = request.substr(pos + 1); //store money in array
                check = 1;
                break;
            }
            if (check == 0)
            {
                throw invalid_argument("This username dosen't exists!");
            }
        }
        int money = stoi(array[3]);
        if (v_customer[i].transaction(money, WITHDRAW))
        {
            banktransaction temp(-money);
            AT.push_back(temp);                  //save withdraw transactions in bank list
            v_customer[i].save_transactions(AT); //save transaction in customer list
        }
        v_customer[j].transaction(money, DEPOSIT);
        banktransaction temp(money);
        AT.push_back(temp);                  //save deposit transactions in bank list
        v_customer[j].save_transactions(AT); //save transaction in customer list
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
//end of transfer function
//------------------------------------------------------
//renewal function
void renewal(string request, vector<customer> &v_customer, vector<banktransaction> &AT)
{
    int pos = request.find(' ');
    request = request.substr(pos + 1);
    pos = request.find(':');
    int i = 0;
    int check = 0;
    try
    {
        for (i = 0; i < v_customer.size(); i++)
        {
            if (v_customer[i].get_username() == request.substr(0, pos)) //check input username in list of all customers, and select customer
            {
                check = 1;
                request = request.substr(pos + 1); //remove username from request
                break;
            }
        }
        if (check == 0)
        {
            throw invalid_argument("This username dosen't exists!");
        }
        if (v_customer[i].checkIP(request) == true) //check input ip in the ip list for the customer
        {
            if (v_customer[i].transaction(10000, WITHDRAW))
            {
                banktransaction temp(-10000);
                AT.push_back(temp);
                v_customer[i].save_transactions(AT);
                v_customer[i].set_date(); //renewal the account
            }
            else
            {
                //for extra mark
            }
        }
        else
        {
            throw invalid_argument("This username dosen't exists!");
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what() << endl;
    }
}
//renewal function
//------------------------------------------------------
//profits function
void profits(string request, vector<customer> &v_customer, vector<banktransaction> &AT)
{
    try
    {
        int check = 0;
        int i = 0;
        for (i = 0; i < v_customer.size(); i++)
        {
            if (v_customer[i].get_username() == request)
            {
                check = 1;
                break;
            }
        }
        if (check == 0)
        {
            throw invalid_argument("This username dosen't exists!");
        }
        v_customer[i].take_profites(AT);
    }
    catch (const invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}
//end of profits function
//------------------------------------------------------