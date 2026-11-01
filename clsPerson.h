#pragma once
#include <iostream>
using namespace std;


class clsPerson
{
private:
 
    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;

public:
    clsPerson(string FirstName, string LastName, string Email, string Phone)
    {
        
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }


    void SetFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }
    string GetFirstName()
    {
        return _FirstName;
    }

    __declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;


    void SetLasttName(string LastName)
    {
        _LastName = LastName;
    }

    string GetLastName()
    {
        return _LastName;
    }

    __declspec(property(get = GetLastName, put = SetLasttName)) string LastName;


    string FullName()
    {
        return _FirstName + " " + _LastName;
    }

    void SetPhone(string Phone)
    {
        _Phone = Phone;
    }
    string GetPhone()
    {
        return _Phone;
    }

    __declspec(property(get = GetPhone, put = SetPhone)) string Phone;


    string GetEmail()
    {
        return _Email;
    }

    void SetEmail(string Email)
    {
        _Email = Email;
    }


    __declspec(property(get = GetEmail, put = SetEmail)) string Email;

    void print()
    {
        cout << "Info:\n\n";
        cout << "______________________________________\n";
        cout << "First Name:" << _FirstName << endl;
        cout << "Last Name :" << _LastName << endl;
        cout << "Full Name :" << FullName() << endl;
        cout << "Email     :" << _Email << endl;
        cout << "Phone     :" << _Phone << endl;
        cout << "________________________________________\n\n";
    }

    void SendEmail(string subject, string body)
    {
        cout << "\nThe following message sent successfully to email : " << _Email;
        cout << "\nSubject: " << subject;
        cout << "\nBody: " << body << endl;
    }

    void SendSMS(string message)
    {
        cout << "\nThe following SMS sent successfully to phone: " << _Phone;
        cout << "\n"
            << message << endl;
    }
};

