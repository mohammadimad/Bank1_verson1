#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
//#include "Bank.h"
//using namespace Bank;
using namespace std;
const string ClientsFileName = "Clients2.txt";

struct sClient {
	string AccountNumber;
	string AccountName;
	string PinCode;
	string PhoneNumber;
	double AccountBalance;
	bool MarkForDelete = false;
};
string ReadString(string Message) {
	string Account;
	cout << Message;
	getline(cin, Account);
	return Account;
}
vector <string> SplitString(string S1, string delim) {

	//cout << "\nYour string wrords are: \n\n";
	string sWord;
	vector <string> vString;
	short pos = 0;
	// Hello Mohammad imad wasd Abdelfattah
	while ((pos = S1.find(delim)) != string::npos) {
		sWord = S1.substr(0, pos);
		if (sWord != "")
			vString.push_back(sWord);
		S1.erase(0, pos + delim.length());
	}
	if (S1 != "")
		vString.push_back(S1);
	return vString;
}
sClient ConvertLineToRecord(string Line, string Seperator = "#//#") {
	string stClientRecord = "";
	sClient Clinet;
	vector <string> vString;
	vString = SplitString(Line, Seperator);
	Clinet.AccountNumber = vString[0];
	Clinet.PinCode = vString[1];
	Clinet.AccountName = vString[2];
	Clinet.PhoneNumber = vString[3];
	Clinet.AccountBalance = stod(vString[4]);//casting from string to double
	return Clinet;
}

vector <sClient>LoadClientsDataFromFile(string FileName) {
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open()) {
		string Line;
		sClient Client;
		while (getline(MyFile, Line)) {
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}
void AddDateLineToFile(string FileName, string sDataLine) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << sDataLine << endl;
		MyFile.close();
	}
}
sClient ReadNewClient() {
	sClient Client;
	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);

	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.AccountName);

	cout << "Enter Phone? ";
	getline(cin, Client.PhoneNumber);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.AccountName + Seperator;
	stClientRecord += Client.PhoneNumber + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
bool FindClientByAccountNumber(sClient& Clients, string AccountNumber, vector <sClient> vClients) {
	for (sClient C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			Clients = C;
			return true;
		}
	}
	return false;
}
void AddNewClient() {
	sClient Client;
	Client = ReadNewClient();
	AddDateLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}
void AddClients(vector<sClient> vClients) {
	sClient Clients;
	string AccountNumber;
	bool findAccount = true;
	bool freind = false;
	do {

		cout << "Enter account number: ";
		cin >> AccountNumber;
		findAccount = FindClientByAccountNumber(Clients, AccountNumber, vClients);
		if (findAccount == true) {
			freind = true;
			cout << "Clients with [" << AccountNumber << "] already exits, Enter another Account Number? \n";
		}
	} while (freind);
	char AddMore = 'Y';
	do {
		system("cls");
		cout << "Adding New Client: \n\n";

		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
void PrintClientRecord(sClient Client) {
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.AccountName;
	cout << "| " << left << setw(12) << Client.PhoneNumber;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}
void ShowClientsList(vector <sClient>vClinets) {
	cout << "\n\t\t\t\tClients List ( " << vClinets.size() << ") Client(s).";
	cout << "\n________________________________________________________";
	cout << "__________________________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sClient Client : vClinets) {
		PrintClientRecord(Client);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void ShowMainMenue() {
	
	system("cls");
	cout << "=======================================\n";
	cout << "\t\tMain Screen\n";
	cout << "=======================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client.\n";
	cout << "\t[5] Show Client Info.\n";
	cout << "\t[6] Exit.\n";
	cout << "=======================================\n";
	
}

void PrintRecord(sClient clinet) {

	cout << " Account Number: ";
	cout << clinet.AccountNumber << endl;

	cout << " PinCode: ";
	cout << clinet.PinCode << endl;

	cout << " Name: ";
	cout << clinet.AccountName << endl;

	cout << " Phone: ";
	cout << clinet.PhoneNumber << endl;

	cout << " AccountBalance: ";
	cout << clinet.AccountBalance << endl;

}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients) {

	for (sClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients) {
	fstream MyFile;
	string DataLine;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		for (sClient C : vClients) {
			if (C.MarkForDelete == false) {
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}

		}
		MyFile.close();
	}
	return vClients;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
	sClient Clients;
	char x = 'n';
	if (FindClientByAccountNumber(Clients, AccountNumber, vClients) == true) {
		PrintRecord(Clients);
		cout << "Are you sure you want to delete this client? y/n ";
		cin >> x;
		if (towupper(x) == 'Y') {
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);
			vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else {
		cout << "Client with Account Number (" << AccountNumber << ") is Not Found!\n";
		return false;
	}
}
sClient ChangeClinetRecord(string AccountNumber) {
	sClient Client;
	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.AccountName);

	cout << "Enter Phone? ";
	getline(cin, Client.PhoneNumber);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
	sClient Clients;
	char x = 'n';
	if (FindClientByAccountNumber(Clients, AccountNumber, vClients) == true) {
		PrintRecord(Clients);
		cout << "Are you sure you want to update this client? y/n ";
		cin >> x;
		if (towupper(x) == 'Y') {
			for (sClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {
					C = ChangeClinetRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Update Successfully.";
			return true;
		}
	}
	else {
		cout << "Client with Account Number (" << AccountNumber << ") is Not Found!\n";
		return false;
	}
}
bool PrintlientByAccountNumber(sClient& Clients, string AccountNumber, vector <sClient> vClients) {
	for (sClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			Clients = C;
			return true;
		}
	}
	return false;
}
void StartProgramming();
void GoBackToMainMenu()
{
	int x;
	cout << "\n\nPress Any Key To Go Back To Main Menu Screen..";
	system("pause>0");
	StartProgramming();

}
void StartProgramming() {
	
	int x;
	string AccountNumber;
	sClient Clinet;
	vector <sClient> vClient = LoadClientsDataFromFile(ClientsFileName);
	ShowMainMenue();
	cout << "Choose what do you want to do [1 to 6]? ";
	cin >> x;
	switch (x) {
	case 1:
		ShowClientsList(vClient);
		GoBackToMainMenu();
		//cout << "Press any key to go  back Main Menue...";
		//system("pause");
		break;
	case 2:
		AddClients(vClient);
		GoBackToMainMenu();
		break;
	case 3:
		cout << "Enter Account Number: ";
		cin >> AccountNumber;
		DeleteClientByAccountNumber(AccountNumber, vClient);
		GoBackToMainMenu();
		break;
	case 4:
		cout << "Enter Account Number: ";
		cin >> AccountNumber;
		UpdateClientByAccountNumber(AccountNumber, vClient);
		GoBackToMainMenu();
		break;
	case 5:
		cout << "Enter Account Number: ";
		cin >> AccountNumber;

		if (PrintlientByAccountNumber(Clinet, AccountNumber, vClient) == true)
			PrintRecord(Clinet);
		else
			cout << "Client with Account Number (" << AccountNumber << ") is Not Found!\n";
		GoBackToMainMenu();
		break;
	case 6:
		cout << "-------------------------------\n";
		cout << "\tProgram Ends\n";
		cout << "-------------------------------";
		system("pause>0");
		break;
	}
}
int main()
{ 
  //  ShowMainMenue();
    StartProgramming();
}

