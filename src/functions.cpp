#include "../header/functions.hpp"
using namespace std;
//message function
void message()
{
     cout << "------------------------" << endl;
    cout << "1-Create account" << endl;
    cout << "------------------------" << endl;
    cout << "2-Deposit" << endl;
    cout << "------------------------" << endl;
    cout << "3-Withdraw" << endl;
    cout << "------------------------" << endl;
    cout << "4-Transfer" << endl;
    cout << "------------------------" << endl;
    cout << "5-Renewal" << endl;
    cout << "------------------------" << endl;
    cout << "6-Get loan" << endl;
    cout << "------------------------" << endl;
    cout << "7-Pay loan" << endl;
    cout << "------------------------" << endl;
    cout << "What do you want?---->";
}
// end of message function
//------------------------------------------------------
//separate command
bool command(string request, vector<customer> &v_customer, vector<banktransaction> &AT)
{
    int pos = request.find(' '); //separate first part
    if (request.substr(0, pos) == "create")
    {
        request = request.substr(pos + 1);
        int pos1 = request.find(':'); //separate entered username
        if (check_username(request.substr(0, pos1), v_customer) == false)
        {
            return false;
        }
        string name = request.substr(0, pos1); //store entered username
        if (check_ip(request.substr(pos1 + 1)) == false)
        {
            return false;
        }
        string ip = request.substr(pos1 + 1); //store entered IP
        for (auto item : v_customer)          // all IP must be unique
        {
            if (item.checkIP(ip))
            {
                cout << "this IP entered brfore!" << endl;
                return false;
            }
        }
        int c_num = card_number(v_customer);   //store card number
        make_obj(name, ip, c_num, v_customer); // making obj and store that in vector of constructor
        return true;
    }
    if (request.substr(0, pos) == "add_ip")
    {
        request = request.substr(pos + 1);
        add_ip(request, v_customer);
        return true;
    }
    if ((request.substr(0, pos) == "deposit") || (request.substr(0, pos) == "withdraw")) //deposit and withdraw
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
        return true;
    }
    if (request.substr(0, pos) == "get_loan")
    {
        get_loan(request, v_customer, AT);
        return true;
    }
    if (request.substr(0, pos) == "pay_loan")
    {
        pay_loan(request.substr(pos + 1), v_customer, AT);
        return true;
    }
    show(request,v_customer,AT);
    cout << "input command is incorrect!!!" << endl;
    return false;
}
//------------------------------------------------------
//check username for add new customer
bool check_username(string name, vector<customer> &v_customer)
{
    try
    {
        for (auto item : v_customer) // a loop for Check that the name has not been entered before
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
            if (a_ip[i] != '.' && a_ip[i] != '\0' && ((int)a_ip[i] < 48 || (int)a_ip[i] > 57)) //if ip has a word or other sign--> Error
            {
                throw out_of_range(" is invalid!!!");
            }
            if (a_ip[i] == '.') //separate IP partt from request and checck each number range
            {
                temp = stoi(a_ip.substr(k, i - k));
                if (temp < 0 || temp > 255)
                {
                    throw out_of_range(" is invalid!!!");
                }
                count++; //count of point
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
void make_obj(string username, string IP, int card, vector<customer> &v_customer) // making obj and store that in vector of constructor
{
    customer temp;
    temp.set_name(username);
    temp.set_ip(IP);
    temp.set_cadr_num(card);
    temp.set_borrow(0);
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
    srand(time(0)); // use for generate random number
    int card{0};
    int check = 1;
    while (true) //inf loop until generate a correct card number
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
    //this function can get more than on IP
    int check{0};
    int pos = request.find(':');
    try
    {
        int i{0};
        //check username
        for (i = 0; i < v_customer.size(); i++)
        {
            if (v_customer[i].get_username() == request.substr(0, pos)) //recognize object that we want add ip
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
        status = DEPOSIT; //enum transaction {DEPOSIT, WITHDRAW}
    }
    if (request.substr(0, pos) == "withdraw")
    {
        status = WITHDRAW;
    }
    request = request.substr(pos + 1); //seprate deposie or withdraw from request
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
        request = request.substr(pos1 + 1); //remove entered username from request
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
                    throw invalid_argument("This " + request.substr(0, j) + " dosen't exists!");
                }
                request = request.substr(j + 1); // remove ip from request after check and store money
            }
            if (request[j] == '\0')
            {
                int money = stoi(request); //convert string to int

                if (status == WITHDRAW)
                {
                    if (v_customer[i].transaction(-money, WITHDRAW, v_customer))
                    {
                        banktransaction temp(-money);                  // make new transaction
                        temp.set_source(v_customer[i].get_username()); //save source account name

                        AT.push_back(temp); //save withdraw transactions in bank list
                    }
                }
                else if (status == DEPOSIT)
                {
                    if (v_customer[i].transaction(money, DEPOSIT, v_customer))
                    {
                        banktransaction temp(money);                   // make new transaction
                        temp.set_source(v_customer[i].get_username()); //save source account name
                        AT.push_back(temp);                            //save deposit transactions in bank list
                    }
                }
                v_customer[i].save_transactions(AT); //save number of vector<banktransaction> in transaction list customer
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
    request = request.substr(pos + 1); //remove transfer word from request
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
        if (v_customer[i].transaction(-money, WITHDRAW, v_customer))
        {
            banktransaction temp(-money);                  // make new transaction
            temp.set_source(v_customer[i].get_username()); //save source account name
            AT.push_back(temp);                            //save withdraw transactions in bank list
            v_customer[i].save_transactions(AT);           //save number of vector<banktransaction> in transaction list customer
        }
        v_customer[j].transaction(money, DEPOSIT, v_customer);
        banktransaction temp(money);
        temp.set_destination(v_customer[j].get_username()); //save destination account name
        AT.push_back(temp);                                 //save deposit transactions in bank list
        v_customer[j].save_transactions(AT);                //save number of vector<banktransaction> in transaction list customer
        cout << "transfer from " << array[0] << " to " << array[2] << endl;
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
    request = request.substr(pos + 1); //remove renewal from request
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
            if (v_customer[i].transaction(-10000, WITHDRAW, v_customer))
            {
                banktransaction temp(-10000);                  // make new transaction
                temp.set_source(v_customer[i].get_username()); //save source account name
                AT.push_back(temp);                            //save withdraw transactions in bank list
                v_customer[i].save_transactions(AT);           ///save number of vector<banktransaction> in transaction list customer
                v_customer[i].set_date();                      //renewal the account
                cout << "Account successfully renewed" << endl;
            }
        }
        else
        {
            throw invalid_argument("This " + request + " dosen't exists!");
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what() << endl;
    }
}
//end of renewal function
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
            if (v_customer[i].get_username() == request) //recognize object that we wand add profit
            {
                check = 1;
                break;
            }
        }
        if (check == 0)
        {
            throw invalid_argument("This username dosen't exists!");
        }
        v_customer[i].take_profites(AT, v_customer);
    }
    catch (const invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}
//end of profits function
//------------------------------------------------------
//get_loan function
void get_loan(string request, vector<customer> &v_customer, vector<banktransaction> &AT)
{
    int pos = request.find(' ');
    request = request.substr(pos + 1); //remove get_loan word from request
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
        if (v_customer[i].get_borrow() < 0)
        {
            throw out_of_range("sorry...you can't get another loan!(you must pay last loan!)");
        }

        request = request.substr(pos1 + 1); //remove entered username from request
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
                    throw invalid_argument("This " + request.substr(0, j) + " dosen't exists!");
                }
                request = request.substr(j + 1); // remove ip from request after check and store money
            }
            if (request[j] == '\0')
            {
                int amount_loan = stoi(request);
                if ((static_cast<double>(amount_loan) * 0.75) > (static_cast<double>(v_customer[i].get_stock()))) //check condition one
                {
                    long long int a = (v_customer[i].get_stock() * 4) / 3;
                    string temp = to_string(a);
                    throw out_of_range("sorry...you can't get loan!!\nmaximmum amount that you can get is " + temp);
                }
                int bank_balance{0};
                for (auto item : v_customer) //check condition two
                {
                    if (item.get_username() == v_customer[i].get_username())
                    {
                    }
                    else
                    {
                        bank_balance = item.get_stock() + item.get_borrow() + bank_balance;
                    }
                }
                if (bank_balance > amount_loan)
                {
                    amount_loan = -((amount_loan * 0.2) + amount_loan);
                    v_customer[i].set_borrow(amount_loan);
                    v_customer[i].transaction(-amount_loan, DEPOSIT, v_customer); //deposit amoutn of loan in accuont
                    banktransaction temp(-amount_loan);                           // make new banktransaction obj
                    temp.set_source(v_customer[i].get_username());                //save source account name
                    temp.set_loan_status(BORROW);                                 //get loan to the customer
                    AT.push_back(temp);                                           //save deposit transactions in bank list
                    v_customer[i].save_transactions(AT);                          //save number of vector<banktransaction> in transaction list customer
                    cout << v_customer[i].get_username() << "get loan" << -amount_loan << endl;
                }
                else
                {
                    throw out_of_range("sorry...you can't get loan!!!\nbalance of the bank isn't enough!!!");
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
    catch (const out_of_range &e)
    {
        cerr << e.what() << endl;
    }
}
//end of get_loan function
//------------------------------------------------------
//pay_loan function
void pay_loan(string request, vector<customer> &v_customer, vector<banktransaction> &AT)
{
    int pos = request.find(':'); //remove pay_loan from user
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
        if (v_customer[i].get_borrow() >= 0)
        {
            throw invalid_argument("you don't have loan!");
        }

        int money = stoi(request); //convert string to int
        int sum = v_customer[i].get_borrow() + money;
        //payment is equal borrow
        if (sum == 0)
        {
            v_customer[i].set_borrow(0);
            banktransaction temp{money};                   //make new banktransaction obj
            temp.set_source(v_customer[i].get_username()); //save source account name
            temp.set_loan_status(NOBORROW);                //pay loan
            AT.push_back(temp);                            //save deposit transactions in bank list
            v_customer[i].save_transactions(AT);           //save number of vector<banktransaction> in transaction list customer
            cout << "You have no debt to the bank" << endl;
        }
        //payment is less than borrow
        if (sum < 0)
        {
            v_customer[i].set_borrow(sum);
            banktransaction temp{money};                   //make new banktransaction obj
            temp.set_source(v_customer[i].get_username()); //save source account name
            temp.set_loan_status(BORROW);                  //pay loan(not complete)
            AT.push_back(temp);                            //save deposit transactions in bank list
            v_customer[i].save_transactions(AT);           //save number of vector<banktransaction> in transaction list customer
            cout << "You have " << -sum << " debt to the bank" << endl;
        }
        //payment is more than borrow
        if (sum > 0)
        {
            v_customer[i].set_borrow(0);
            banktransaction temp{money};                   //make new banktransaction obj
            temp.set_source(v_customer[i].get_username()); //save source account name
            temp.set_loan_status(NOBORROW);                //pay loan
            AT.push_back(temp);                            //save deposit transactions in bank list
            v_customer[i].save_transactions(AT);           //save number of vector<banktransaction> in transaction list customer
            cout << "You have no debt to the bank" << endl;
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what() << endl;
    }
}
//------------------------------------------------------
//end of pay_loan function
//------------------------------------------------------
//shoe function
bool show(string request, vector<customer> &v_customer, vector<banktransaction> &AT)
{
    int check{0}; //input command for show is user name
    if (request == "bank")
    {
        check = 3; // show bank info
    }

    if (isdigit(request[0]))
    {
        if (request[1] == '.')
        {
            check = 1; //input command for show is IP
        }
        else
        {
            check = 2; //input command for show is card number
        }
    }
    try
    {
        switch (check)
        {
        case 0: // username
        {
            for (auto item : v_customer)
            {
                if (item.get_username() == request)
                {
                    cout << "Username: " << item.get_username() << endl;
                    item.get_ip();
                    cout << "Card Number: " << item.get_card_num() << endl;
                    cout << "Balance: " << item.get_stock() << endl;
                    cout << "The amount of debt to the bank: " << item.get_borrow() << endl;
                    cout << "Account opening date: " << item.get_opening_date() << endl;
                    cout << "Account expiration date: " << item.get_expiration_date() << endl;
                    return true;
                }
            }
            throw invalid_argument("This username dosen't exists!");
            break;
        }
        case 1: //IP
        {
            for (auto item : v_customer)
            {
                if (item.checkIP(request))
                {
                    cout << "Username: " << item.get_username() << endl;
                    item.get_ip();
                    cout << "Card Number: " << item.get_card_num() << endl;
                    cout << "Balance: " << item.get_stock() << endl;
                    cout << "The amount of debt to the bank: " << item.get_borrow() << endl;
                    cout << "Account opening date: " << item.get_opening_date() << endl;
                    cout << "Account expiration date: " << item.get_expiration_date() << endl;
                    return true;
                }
            }
            throw invalid_argument("This IP dosen't exists!");
        }
        case 2: //Card Number
        {
            int card = stoi(request);
            for (auto item : v_customer)
            {
                if (item.get_card_num() == card)
                {
                    cout << "Username: " << item.get_username() << endl;
                    item.get_ip();
                    cout << "Card Number: " << item.get_card_num() << endl;
                    cout << "Balance: " << item.get_stock() << endl;
                    cout << "The amount of debt to the bank: " << item.get_borrow() << endl;
                    cout << "Account opening date: " << item.get_opening_date() << endl;
                    cout << "Account expiration date: " << item.get_expiration_date() << endl;
                    return true;
                }
            }
            throw invalid_argument("This Cardnumber dosen't exists!");
        }
        case 3:
        {
            cout << "number of customer: " << v_customer[0].get_count() << endl;
            int current_balance{0};
            int pure_balance{0};
            int loan{0};
            for (auto item : v_customer)
            {
                current_balance = item.get_stock() + item.get_borrow() + current_balance;
                pure_balance = item.get_stock() + pure_balance;
                loan = item.get_borrow() + loan;
            }
            cout << "current balance: " << current_balance << endl;
            cout << "pure balance: " << pure_balance << endl;
            cout << "loan amount: " << loan << endl;
        }
        default:
            break;
        }
    }
    catch (const invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return false;
}

//------------------------------------------------------
//end of show function