// bankManagementSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

class account
{
	int accNo;
	char name[50];
	int deposit;
	char type;

public:
	void createAccount();	//function to get data from user
	void showAccount() const;	//function to show data on screen
	void modify();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int retAccNo() const;	//function to return account number
	int retDeposit() const;	//function to return balance amount
	char retAccType() const;	//function to return type of account
};         //class ends here

void account::createAccount() {
	std::cout << "Enter The account No. :\n";
	std::cin >> accNo;
	std::cout << "Enter The Name of The account Holder :\n";
	std::cin.ignore();
	std::cin.getline(name, 50);
	std::cout << "Enter Type of The account: For Current Account (C) For Savings Account (S) :\n";
	std::cin >> type;
	type = toupper(type);
	std::cout << "Enter The Initial amount(More than or equal to 500 for Saving Account\n\n and \nMore than or equal to 1000 for Current Account ) : \n";
	std::cin >> deposit;
	std::cout << "Account Successfully created\n";
}

void account::showAccount()const {
	std::cout << "Account No. : " << accNo;
	std::cout << "Account Holder Name : " << accNo;
	std::cout << name;
	std::cout << "Type of Account : " << type;
	std::cout << "Balance amount : " << deposit;
}

void account::modify() {
	std::cout << "Account No. : " << accNo;
	std::cout << "Modify Account Holder Name : ";
	std::cin.ignore();
	std::cin.getline(name, 50);
	std::cout << "Modify Account Type: ";
	std::cin >> type;
	type = toupper(type);
	std::cout << "Modify Account Balance : ";
	std::cin >> deposit;
}

void account::dep(int x) {
	deposit += x;
}

void account::draw(int x) {
	deposit -= x;
}

void account::report()const {
	std::cout << accNo << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::retAccNo()const {
	return accNo;
}

int account::retDeposit()const {
	return deposit;
}

char account::retAccType()const {
	return type;
}


void writeAccount();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modifyAccount(int);	//function to modify record of file
void deleteAccount(int);	//function to delete record of file
void displayAll();		//function to display all account details
void deposit_withdraw(int, int); // function to deposit/withdraw amount for given account

int main()
{
	char ch;
	int num;
	do
	{
		std::cout << "\n\tWelcome to OASIS BANK,ONLINE BANKING SYSTEM\n";
		std::cout << "\n\tMENU\n";
		std::cout << "\t1. NEW ACCOUNT\n";
		std::cout << "\t2. DEPOSIT AMOUNT\n";
		std::cout << "\t3. WITHDRAW AMOUNT\n";
		std::cout << "\t4. BALANCE ENQUIRY\n";
		std::cout << "\t5. ALL ACCOUNT HOLDER LIST\n";
		std::cout << "\t6. CLOSE AN ACCOUNT\n";
		std::cout << "\t7. MODIFY AN ACCOUNT\n";
		std::cout << "\t8. EXIT\n";
		std::cout << "\n\tTo proceed, Please choose an option between 1-8:";
		std::cin >> ch;
		switch (ch)
		{
		case '1':
			writeAccount();
			break;
		case '2':
			std::cout << "\n\n\tEnter The account No. : ";
			std::cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			std::cout << "\n\n\tEnter The account No. : ";
			std::cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			std::cout << "\n\n\tEnter The account No. : ";
			std::cin >> num;
			display_sp(num);
			break;
		case '5':
			displayAll();
			break;
		case '6':
			std::cout << "\n\n\tEnter The account No. : ";
			std::cin >> num;
			deleteAccount(num);
			break;
		case '7':
			std::cout << "\n\n\tEnter The account No. : ";
			std::cin >> num;
			modifyAccount(num);
			break;
		case '8':
			std::cout << "\n\n\tThanks for using Bank management system";
			break;
		default:std::cout << "\a";
		}
		std::cin.ignore();
		std::cin.get();
	} while (ch != '8');
	return 0;
}


void writeAccount() {
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.createAccount();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();

}

void display_sp(int n) {
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		std::cout << "File could not be open !! Press any Key...";
		return;
	}
	std::cout << "\nBALANCE DETAILS\n";

	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retAccNo() == n)
		{
			ac.showAccount();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		std::cout << "\n\nAccount number does not exist";
}

void modifyAccount(int n) {
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		std::cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retAccNo() == n)
		{
			ac.showAccount();
			std::cout << "\n\nEnter The New Details of account" << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			std::cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		std::cout << "\n\n Record Not Found ";
}

void deleteAccount(int n) {
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		std::cout << "File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retAccNo() != n)
		{
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	std::cout << "Record Deleted ..\n";

}

void displayAll() {
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		std::cout << "File could not be open !! Press any Key...";
		return;
	}
	std::cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	std::cout << "====================================================\n";
	std::cout << "A/c no.      NAME           Type  Balance\n";
	std::cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();

}

void deposit_withdraw(int n, int option) {
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		std::cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retAccNo() == n)
		{
			ac.showAccount();
			if (option == 1)
			{
				std::cout << "\n\n\tTO DEPOSIT AMOUNT ";
				std::cout << "\n\nEnter The amount to be deposited";
				std::cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				std::cout << "\n\n\tTO WITHDRAW AMOUNT ";
				std::cout << "\n\nEnter The amount to be withdraw";
				std::cin >> amt;
				int bal = ac.retDeposit() - amt;
				if ((bal < 500 && ac.retAccType() == 'S') || (bal < 1000 && ac.retAccType() == 'C'))
					std::cout << "Insufficient balance";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			std::cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		std::cout << "\n\n Record Not Found ";
}



