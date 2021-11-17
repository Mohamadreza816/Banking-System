#include "../header/customer.hpp"
#include "../header/functions.hpp"
#include "../header/banktransaction.hpp"
using namespace std;

int main()
{
    string request;
    vector<banktransaction>alltransaction;
    vector<customer>cus;
    getline(cin, request);
    while (request != "exit")
    {
        command(request,cus,alltransaction);
        cout << "in main" << endl;
        getline(cin, request);
    }
    
}