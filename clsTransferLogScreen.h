#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsString.h"

class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintTransferLogRecordLine(clsBankClient::stTransferLog TransferLog)
	{

		cout << setw(10) << left << "" << "| " << setw(20) << left << TransferLog.DateTime;
		cout << "| " << setw(13) << left << TransferLog.sAcct;
		cout << "| " << setw(13) << left << TransferLog.dAcct;
		cout << "| " << setw(13) << left << TransferLog.Amount;
		cout << "| " << setw(13) << left << TransferLog.sBalance;
		cout << "| " << setw(13) << left << TransferLog.dBalance;
		cout << "| " << setw(13) << left << TransferLog.User << endl;


	}
	
public:
	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stTransferLog> vTransferLogRecord = clsBankClient::GetTransferLogList();
		
		_DrawScreenHeader("\Transfer Log Screen", to_string(vTransferLogRecord.size()) + " Records");

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "___________________________________________________\n" << endl;

		cout << setw(10) << left << "" << "| " << left << setw(20) << "Date / Timing";
		cout << "| " << left << setw(13) << "s.Acct";
		cout << "| " << left << setw(13) << "d.Acct";
		cout << "| " << left << setw(13) << "Amount";
		cout << "| " << left << setw(13) << "s.Balance";
		cout << "| " << left << setw(13) << "d.Balance";
		cout << "| " << left << setw(13) << "User";

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "____________________________________________________\n" << endl;

		if (vTransferLogRecord.size() == 0)
			cout << "\t\t\t\tNo Transfer logs Available In the System!";
		else
			for (clsBankClient::stTransferLog T : vTransferLogRecord)
			{
				_PrintTransferLogRecordLine(T);
			}


	}

};




