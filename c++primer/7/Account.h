#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using std::string;
class Account {
    public:
        Account() = default;
        Account(const string &s, double amt) : owners(s), amount(amt) { };

        void calculate() {
            amount += amount * interestRate;
        }

        double balance() {
            return amount;
        }

    public:
        static double rate() {
            return interestRate;
        }

        static void rate(double);

    private:
        string owner;
        double amount = 0.0;
        static double interestRate;
        static double initRate() {
            return .0225;
        }

        static const string accountType;
        static constexpr int period = 30;
        double daily_tbl[period];

};
