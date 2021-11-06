#include "../header/customer.hpp"
#include <ctime>
//constructor
customer::customer(string A_usrename, string A_ip, int A_card)
 :username{A_usrename},card_number{A_card},stock{0.0}
{
    ip.push_back(A_ip);

}
// End of constructo
