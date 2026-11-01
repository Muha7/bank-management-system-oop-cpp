#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsTransferScreen : protected clsScreen
{
private:
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

	static string _ReadAccount()
	{
		string AccountName = "";

		cout << "Enter account number to transfer from: ";
		AccountName = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExists(AccountName))
		{
			cout << "Client not exisit , Please enter correct account number: ";
			AccountName = clsInputValidate::ReadString();
		}

		return AccountName;
	}

	static float _ReadAmount(clsBankClient SourceClient)
	{
		float Amount = 0;
		cout << "\nEnter Amout to transfer:";
		cin >> Amount;

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "Amount exceeds account balance, please enter another amount: ";
			cin >> Amount;
		}

		return Amount;
	}
public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccount());
		PrintClient(SourceClient);

		
		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccount());
		PrintClient(DestinationClient);

		float Amount = _ReadAmount(SourceClient);

		cout << "\nAre you sure you want to do this operation y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
			{
				cout << "Transfer done succesfully";
			}
			else
			{
				cout << "Transaction failed";
			}
		}

		PrintClient(SourceClient);
		PrintClient(DestinationClient);
	}
};

