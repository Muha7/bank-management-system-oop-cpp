#pragma once
#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


class clsWithdrawScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        return AccountNumber;
    }

public:
    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t  Withdraw Client Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExists(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        double Amount;
        cout << "Withdraw Amount: ";
        cin >> Amount;

        cout << "Are you sure u want to Withdraw Amount? y or n: ";
        char answer = 'y';
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            if (Client1.Withdraw(Amount))
            {
                cout << "\Amount withrawed Successfully :-)\n";
                cout << "\New balance: " << Client1.GetAccountBalance();
            }
            else
            {
                cout << "\nInsufficint amount, please go to your home\n";
                cout << "\Amount to withdraw: " << Amount << endl;
                cout << "\current balance : " << Client1.GetAccountBalance();
            }
        }
        else {
            cout << "Operation was cancelled";
        }
       
    }
};

