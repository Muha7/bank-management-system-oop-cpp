#pragma once
#include "Global.h"
#include "clsScreen.h"
#include "clsDate.h"
class clsRegisterLoginScreen : protected clsScreen
{
private:
    static void PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginUser)
    {

        cout << setw(10) << left << "" << "| " << setw(15) << left << LoginUser.DateTime;
        cout << "| " << setw(20) << left << LoginUser.UserName;
        cout << "| " << setw(20) << left << LoginUser.Password;
        cout << "| " << setw(20) << left << LoginUser.Permission;
        

    }


public:

    static void ShowRegisterLoginList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
        {
            return;
        }

        vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();

        string Title = "\t Login Register Users List Screen";
        string SubTitle = "\t    (" + to_string(vLoginRegisterRecord.size()) + ") Client(s).";

        clsScreen::_DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(10) << left << "" << "| " << left << setw(20) << "Date / Timing";
        cout << "| " << left << setw(20) << "User Name";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(20) << "Permissions";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUser::stLoginRegisterRecord LoginUser : vLoginRegisterRecord)
            {

                PrintLoginRegisterRecordLine(LoginUser);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }



};