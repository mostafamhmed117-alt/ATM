#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>

using namespace std;
string ClientsFileName = "Client.txt";

void ShowMainMenue(void);
void ShowLoginScreen(void);

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
};

stClient CurrentClient;

vector<string> Split(string S)
{
	string delim = "#//#";
	string sWord = "";
	short pos = 0;
	vector<string> vString;
	while ((pos = S.find(delim)) != std::string::npos)
	{
		sWord = S.substr(0, pos);
		if (sWord != " ")
		{
			vString.push_back(sWord);
		}
		S.erase(0, pos + delim.length());
	}
	if (S != " ")
	{
		vString.push_back(S);
	}
	return vString;
}

stClient ConvertLineToRecord(string Line)
{
	vector<string> vString = Split(Line);
	stClient Client;
	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccountBalance = stod(vString[4]);
	return Client;
}

string ConvertRecordToLine(stClient& Client)
{
	string S = "";
	S += Client.AccountNumber + "#//#";
	S += Client.PinCode + "#//#";
	S += Client.Name + "#//#";
	S += Client.Phone + "#//#";
	S += to_string(Client.AccountBalance);
	return S;
}

vector<stClient> LoadClientDateFromFile(string FileName)
{
	vector<stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in); // Read Mode.
	if (MyFile.is_open())
	{
		stClient Client;
		string Line;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

enum enTransaction
{
	eWithdraw = 1,
	eDeposit = 2
};

stClient UpdateBalance(stClient Client, short Amount, enTransaction Operation)
{
	switch (Operation)
	{
	case enTransaction::eWithdraw:
		Client.AccountBalance -= Amount;
		return Client;
	case enTransaction::eDeposit:
		Client.AccountBalance += Amount;
		return Client;
	}
}

void UpdateClientBalance(vector<stClient>& vClient, short Amount, enTransaction Operation)
{
	for (stClient& C : vClient)
	{
		if (CurrentClient.AccountNumber == C.AccountNumber)
		{
			C = UpdateBalance(C, Amount, Operation);
			CurrentClient = C;
		}
	}
}

void SaveClientUpdate(string FileName, vector<stClient> &vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		for (stClient& C : vClients)
		{
			MyFile << ConvertRecordToLine(C) << endl;
		}
		MyFile.close();
	}
}

void PerformTansaction(short Amount, enTransaction Operation)
{
	vector<stClient> vClients = LoadClientDateFromFile(ClientsFileName);
	char Answer = 'n';
	if (CurrentClient.AccountBalance >= Amount || Operation == enTransaction::eDeposit)
	{
		cout << "\nAre you sure you want to perform this transaction? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			UpdateClientBalance(vClients, Amount, Operation);
			SaveClientUpdate(ClientsFileName, vClients);
			cout << "\nDone Successfully.Newbalance is: " << CurrentClient.AccountBalance << endl;
		}
	}
	else
	{
		cout << "\nThe amount exceeds your balance, make another choice.\n";
	}
}

short GetWithdrawAmount(short Choice)
{
	switch (Choice)
	{
	case 1:
		return 20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;
	}
}

void QuickWithdraw()
{
	vector<stClient> vClients = LoadClientDateFromFile(ClientsFileName);
	short Choice = 0;
	cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
	cout << "Choose what to withdaw from[1] to [8] ? ";
	cin >> Choice;
	if (Choice == 9)
		return;
	PerformTansaction(GetWithdrawAmount(Choice), enTransaction::eWithdraw);
}

void ShowQucikWithdrawScreen()
{
	system("cls");
	cout << "=========================================\n";
	cout << "\t\tQuick Withdraw\n";
	cout << "=========================================\n";
	cout << "\t" << left << setw(15) << "[1] 20" << left << setw(10) << "[2] 50\n";
	cout << "\t" << left << setw(15) << "[3] 100" << left << setw(10) << "[4] 200\n";
	cout << "\t" << left << setw(15) << "[5] 400" << left << setw(10) << "[6] 600\n";
	cout << "\t" << left << setw(15) << "[7] 800" << left << setw(10) << "[8] 1000\n";
	cout << "\t" << left << setw(15) << "[9] Exit";
	cout << "\n=========================================\n";
	QuickWithdraw();
}

void NormalWithdraw()
{
	int Amount = 0;
	do
	{
		cout << "\nEnter an amount multiple of 5's ? ";
		cin >> Amount;
	} while (Amount % 5 != 0);

	PerformTansaction(Amount, enTransaction::eWithdraw);
}

void ShowNormalWithdrawScreen()
{
	system("cls");
	cout << "=========================================\n";
	cout << "\t\tNormal Withdraw\n";
	cout << "=========================================\n";
	NormalWithdraw();
}

void Deposit()
{
	short Amount = 0;
	cout << "\nEnter a positive Deposit Amount? ";
	cin >> Amount;
	while (Amount < 0)
	{
		cout << "\nEnter a positive Deposit Amount? ";
		cin >> Amount;
	}
	PerformTansaction(Amount, enTransaction::eDeposit);
}

void ShowDepositScreen()
{
	system("cls");
	cout << "=========================================\n";
	cout << "\t\tDeposit Screen\n";
	cout << "=========================================\n";
	Deposit();
}

void ShowCheckBalanceScreen()
{
	system("cls");
	cout << "=========================================\n";
	cout << "\t\tCheck Balance Screen\n";
	cout << "=========================================\n";
	cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
}

void BackToMainMenue()
{
	cout << "\nPress any key to go back to main Menue...\n";
	system("pause>0");
	ShowMainMenue();
}

void Logout()
{
	ShowLoginScreen();
}

enum enMainTransaction
{
	enQuickWithdraw = 1,
	enNormalWithdraw = 2,
	enDeposit = 3,
	enCheckBalanace = 4,
	enLogout = 5
};

short ReadNumber()
{
	short Number;
	cout << "Choose what do you want to do? [1 to 5]? ";
	cin >> Number;
	return Number;
}

void PerformMainMenueChoice(enMainTransaction Op)
{
	switch (Op)
	{
	case enMainTransaction::enQuickWithdraw:
		ShowQucikWithdrawScreen();
		BackToMainMenue();
		break;
	case enMainTransaction::enNormalWithdraw:
		ShowNormalWithdrawScreen();
		BackToMainMenue();
		break;
	case enMainTransaction::enDeposit:
		ShowDepositScreen();
		BackToMainMenue();
		break;
	case enMainTransaction::enCheckBalanace:
		ShowCheckBalanceScreen();
		BackToMainMenue();
		break;
	case enMainTransaction::enLogout:
		Logout();
		BackToMainMenue();
		break;
	}
}

void ShowMainMenue()
{
	system("cls");
	cout << "=========================================\n";
	cout << "\t\tATM Main Screen\n";
	cout << "=========================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "=========================================\n";
	PerformMainMenueChoice(enMainTransaction(ReadNumber()));
}

bool FindClientByAccNumberAndPinCode(string& AccNumber, string& PinCode)
{
	vector<stClient> vClients = LoadClientDateFromFile(ClientsFileName);
	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccNumber && C.PinCode == PinCode)
		{
			CurrentClient = C;
			return true;
		}
	}
	return false;
}

bool GetClientLoginInfo(string& AccNumber, string& PinCode)
{
	return (FindClientByAccNumberAndPinCode(AccNumber, PinCode)) ? true : false;
}

void ShowLoginScreen()
{
	bool LoginFaild = false;
	string AccNumber, PinCode;
	do
	{
		system("cls");
		cout << "--------------------------------------\n";
		cout << "\tLogin Screen\n";
		cout << "--------------------------------------\n";
		if (LoginFaild)
		{
			cout << "Invalid Account Number/PinCode\n";
		}
		cout << "Enter Account Number? ";
		getline(cin >> ws, AccNumber);
		cout << "Enter Pin Code? ";
		getline(cin, PinCode);
		LoginFaild = !GetClientLoginInfo(AccNumber, PinCode);

	} while (LoginFaild);
	ShowMainMenue();
}

int main()
{
	ShowLoginScreen();
	return 0;
}