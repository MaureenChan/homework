#include "Account.h"

const string Account::accountType("Savings Account");
double Account::interestRate = initRate();

void Account::rate(double newRate) {
    interestRate = newRate;
}
