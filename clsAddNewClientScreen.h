#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsAddNewClientScreen : protected clsScreen
{
private:
     static void ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

     static void PrintClient(clsBankClient Client)
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

public:
    static void AddNewClient()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }

        _DrawScreenHeader("\t  Add New Client Screen");


        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExists(AccountNumber))
        {
            cout << "\nAccount number is exists, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::GetAddNewClientObject(AccountNumber);

        ReadClientInfo(Client);

        clsBankClient::eSaveResult SaveResult;

        SaveResult = Client.Save();

        switch (SaveResult)
        {
        case clsBankClient::eSaveResult::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            PrintClient(Client);
            break;
        }
        case clsBankClient::eSaveResult::svFailedEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }
        case clsBankClient::eSaveResult::svFailedACexists:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }


        }
    }
};

