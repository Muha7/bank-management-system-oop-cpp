#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


class clsShowTotalBalancesScreen : protected clsScreen
{
private:
    static void _PrintClientRecordLine(clsBankClient Client)
    {

        cout << setw(25) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(40) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.AccountBalance;

    }
public:
    static void ShowTotalBalancesScreen()
    {
        vector <clsBankClient> vClient = clsBankClient::GetClientsList();

        string Title = "Total balances Screen";
        string SubTitle = "Total Clients  (" + to_string(vClient.size()) + " ) Client(s)";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(25) << left << "" << "\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;



        double TotalBlances = clsBankClient::GetTotalBalances();

        if (vClient.size() == 0)
        {
            cout << " No Clients found!!";
        }
        else 
        {
            for (clsBankClient C : vClient)
            {
                _PrintClientRecordLine(C);
                cout << endl;
            }

            cout << setw(70) << left << "" << "total balance : " << TotalBlances;
            //cout << setw(25) << left << clsBankClient::

        }


    }
};

