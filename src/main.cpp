#include "../header/customer.hpp"
#include "../header/functions.hpp"
#include "../header/banktransaction.hpp"
using namespace std;

int main()
{
    string request;                         //input by user
    vector<banktransaction> alltransaction; //list for save transactions for each customer
    vector<customer> cus;                   //list of customer class.
    message();                              //show abilty og program
    getline(cin, request);
    cout << "========================" << endl;
    while (request != "exit")
    {
        command(request, cus, alltransaction);
        message();
        getline(cin, request);
        cout << "========================" << endl;
    }
    cout << "*********************" << endl;
    cout << "End of program!" << endl;
    cout << "*********************" << endl;
    return 0;
}