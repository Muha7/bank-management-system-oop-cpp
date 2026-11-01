#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include "Global.h"
#include <vector>
#include <fstream>
#include <filesystem>
using namespace std;


class clsBankClient : public clsPerson
{
private:
	enum eMode{EmptyMode = 0, UpdateMode = 1, AddNewMode = 3};
	
    eMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
    bool _MarkForDelete = false;


    static clsBankClient _ConvertLineToClientObject(string Line, string seperator = "#//#")
    {
        vector <string> vClientData;

        vClientData = clsString::Split(Line, "#//#");

        return clsBankClient(eMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
            vClientData[4], vClientData[5], stof(vClientData[6]));
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(eMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static vector <clsBankClient> _LaodClientDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Client.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLineToClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;
    }

    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Client.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C._MarkForDelete == false)
                {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }


            }

            MyFile.close();

        }

    }

    void  _Update()
    {
        vector <clsBankClient> _vClient;
        _vClient = _LaodClientDataFromFile();

        for (clsBankClient& C: _vClient)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
            }
        }

        _SaveCleintsDataToFile(_vClient);
    }

    void _AddNew()
    {
        _AddLineDataToFile(_ConverClientObjectToLine(*this));
    }

    void _AddLineDataToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Client.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    string _prepareTransferRecord(clsBankClient DestinationClient, float Amount, string UserName, string s = "#//#")
    {
        string TransferRecord = "";

        TransferRecord += clsDate::GetSystemDateTimeString() + s;
        TransferRecord += AccountNumber() + s;
        TransferRecord += DestinationClient.AccountNumber() + s;
        TransferRecord += to_string(Amount) + s;
        TransferRecord += to_string(AccountBalance) + s;
        TransferRecord += to_string(DestinationClient.AccountBalance) + s;
        TransferRecord += UserName;

        return TransferRecord;
    }

    void _RegisterTransfer(clsBankClient Client, float Amount, string UserName)
    {
        string DataLine = _prepareTransferRecord(Client, Amount, UserName);
        fstream MyFile;

        MyFile.open("TransferLog.txt", ios::app | ios::in);

        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;

            MyFile.close();
        }
    }
    struct stTransferLog;

    static clsBankClient::stTransferLog _ConverTransferLogLineToRecord(string Line)
    {
        clsBankClient::stTransferLog TransferLog;

        vector <string> vTransferLogLine = clsString::Split(Line, "#//#");

        TransferLog.DateTime = vTransferLogLine[0];
        TransferLog.sAcct = vTransferLogLine[1];
        TransferLog.dAcct = vTransferLogLine[2];
        TransferLog.Amount = stof(vTransferLogLine[3]);
        TransferLog.sBalance = stof(vTransferLogLine[4]);
        TransferLog.dBalance = stof(vTransferLogLine[5]);
        TransferLog.User = vTransferLogLine[6];

        return TransferLog;

    }


public:
	clsBankClient(eMode Mode, string FirstName, string LastName,
		string Email, string Phone, string AccountNumber, string PinCode,
		float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;

	}

    struct stTransferLog{

        string DateTime;
        string sAcct;
        string dAcct;
        float Amount;
        float sBalance;
        float dBalance;
        string User;
        
    
    };

	bool IsEmpty()
	{
		return (_Mode == eMode::EmptyMode);
	}

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;



    static clsBankClient Find(string AccountNumber)
    {
 

        fstream MyFile;
        MyFile.open("Client.txt", ios::in);


        string Line;
        if(MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                clsBankClient Client1 = _ConvertLineToClientObject(Line);

                if (Client1.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client1;
                }
            }

            MyFile.close();
        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {


        fstream MyFile;
        MyFile.open("Client.txt", ios::in);


        string Line;
        
        if (MyFile.is_open())
        {
            
            while (getline(MyFile, Line))
            {
                clsBankClient Client1 = _ConvertLineToClientObject(Line);

                if (Client1.AccountNumber() == AccountNumber && Client1.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client1;
                }
            }

            MyFile.close();
        }

        return _GetEmptyClientObject();
    }

    static bool IsClientExists(string AccountNumber)
    {
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        return (!Client.IsEmpty());
    }

    static clsBankClient GetAddNewClientObject(string accountNumber)
    {
        return clsBankClient(eMode::AddNewMode, "", "", "", "", accountNumber, "", 0);
    }
    
    enum eSaveResult { svFailedEmptyObject = 0, svSucceeded = 1, svFailedACexists = 3 };

    eSaveResult Save()
    {
        switch (_Mode)
        {
        case eMode::EmptyMode:
        {
            return eSaveResult::svFailedEmptyObject;
        }
        case eMode::UpdateMode:
        {
            _Update();

            return eSaveResult::svSucceeded;
            break;
        }

        case eMode::AddNewMode:
        {
            

            if (clsBankClient::IsClientExists(_AccountNumber))
            {
                return eSaveResult::svFailedACexists;
            }
            else 
            {
                _AddNew();

                _Mode = eMode::UpdateMode;
                return eSaveResult::svSucceeded;
                
            }

        }
            
        }
    }

    bool Delete()
    {
        vector <clsBankClient> _vClient;
        _vClient = _LaodClientDataFromFile();

        for (clsBankClient& C : _vClient)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C._MarkForDelete = true;
                break;
            }
        }

        _SaveCleintsDataToFile(_vClient);
        *this = _GetEmptyClientObject();

        return true;
    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LaodClientDataFromFile();
    }

    static double GetTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;

        for (clsBankClient Client : vClients)
        {

            TotalBalances += Client.AccountBalance;
        }

        return TotalBalances;

    }

     void Deposite(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

     bool Withdraw(double Amount)
     {
         if (Amount > _AccountBalance)
         {
             return false;
         }
         else
         {
             _AccountBalance -= Amount;
             Save();

             return true;
         }
  
     }

     bool Transfer(float Amount, clsBankClient& DestinationClient, string UserName)
     {
         if (Amount > AccountBalance)
         {
             return false;
         }

         Withdraw(Amount);
         DestinationClient.Deposite(Amount);
         _RegisterTransfer(DestinationClient, Amount, UserName);
         return true;
     }

     static vector <stTransferLog> GetTransferLogList()
     {
         vector <clsBankClient::stTransferLog> vTransferLogRecord;

         fstream Myfile;
         Myfile.open("TransferLog.txt", ios::in);
         string Line;

         if (Myfile.is_open())
         {
             while (getline(Myfile, Line))
             {
                 clsBankClient::stTransferLog TransferLogLine = _ConverTransferLogLineToRecord(Line);
                 vTransferLogRecord.push_back(TransferLogLine);

             }

             Myfile.close();
         }

         return vTransferLogRecord;
     }

};

