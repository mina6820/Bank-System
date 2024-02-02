#include <iostream>
#include "Account.h"
#include "BankController.h"

int Account::account_id_counter = 1000;

using namespace std;

int main()
{

    BankController bank;
    bank.run();

}