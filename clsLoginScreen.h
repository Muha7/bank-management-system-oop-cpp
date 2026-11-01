#pragma once
#include "Global.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsScreen.h"
#include <iostream>


class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
		
		string UserName, Password;
		bool LoginFailed = false;
		short LoginFailedCount = 0;

		do
		{
			if (LoginFailed)
			{
				LoginFailedCount++;


				cout << "Invalid login credentionals, try again!\n";
				cout << "You have " << (3 - LoginFailedCount) << " trails left\n";

			}
			if (LoginFailedCount == 3)
			{
				cout << " you are locked!";
				return false;
			}

			cout << "Enter userName: ";
			cin >> UserName;

			cout << "Enter Password: ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFailed = CurrentUser.IsEmpty();


		} while (LoginFailed);


		
		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		return true;
	}
public:
	static bool LoginScreen()
	{
		//System("pause")
		_DrawScreenHeader("Login Screen");
		return _Login();
		
			
	}
};

