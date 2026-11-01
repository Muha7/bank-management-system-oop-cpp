#pragma once
#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"

using namespace std;

class clsInputValidate
{


public:
    static int IsNumberBetween(int number, int from, int to)
    {
        if (from <= number <= to)
        {
            return true;
        }
        else
            return false;

    }

    static short IsNumberBetween(short number, short from, short to)
    {
        if (from <= number <= to)
        {
            return true;
        }
        else
            return false;

    }

    static float IsNumberBetween(float number, float from, float to)
    {
        if (from <= number <= to)
        {
            return true;
        }
        else
            return false;

    }

    static double IsNumberBetween(double number, double from, double to)
    {
        if (from <= number <= to)
        {
            return true;
        }
        else
            return false;

    }

    static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        short Number;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        short Number = ReadShortNumber();

        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadShortNumber();
        }
        return Number;
    }

  
    static bool IsDateBetween(clsDate Date, clsDate FromDate, clsDate ToDate)
    {
        if (clsDate::IsDate1AfterDate2(Date, FromDate) || clsDate::IsDate1EqualDate2(Date, FromDate)
            && clsDate::IsDate1BeforeDate2(Date, ToDate) || clsDate::IsDate1EqualDate2(Date, ToDate))
            return true;
        if (clsDate::IsDate1AfterDate2(Date, ToDate) || clsDate::IsDate1EqualDate2(Date, ToDate)
            && clsDate::IsDate1BeforeDate2(Date, FromDate) || clsDate::IsDate1EqualDate2(Date, FromDate))
            return true;
        else
            return false;
    }

    static int ReadIntNumber(string ErrorMessage = "Invalid Number")
    {
        int N;
        while (!(cin >> N)) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
         
        return N;


    }

    static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        float Number;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    static float ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        float Number = ReadFloatNumber();

        while (!IsNumberBetween(Number, From, To)) {
            cout << ErrorMessage;
            Number = ReadDblNumber();
        }
        return Number;
    }

    static double ReadDblNumber(string ErrorMessage = "Invalid Number")
    {
        double N;
        while (!(cin >> N))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }

        return N;


    }

    static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Invalid Number")
    {
        int N = ReadIntNumber();

        while (!(IsNumberBetween(N, From, To)))
        {
            cout << ErrorMessage;
            N = ReadIntNumber();
        }

        return N;
    }

    static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Invalid Number")
    {
        double N = ReadDblNumber();

        while (!(IsNumberBetween(N, From, To)))
        {
            cout << ErrorMessage;
            N = ReadIntNumber();
        }

        return N;
    }

    static bool IsValidDate(clsDate Date)
    {
        return clsDate::ValidateDate(Date);
    }

    static string ReadString()
    {
        string  S1 = "";
        // Usage of std::ws will extract allthe whitespace character
        getline(cin >> ws, S1);
        return S1;
    }

};

