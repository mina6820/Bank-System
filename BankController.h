#pragma once
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "Account.h"
#include "vector"


using namespace std;

class BankController
{
public:
	

	void run() {
		while (true)
		{
			Menu();
		}
	}

private:

	vector <Account> Accounts;

	void StepBack()
	{
		cout << "\n\t\t\t\tPress Any Key To Get Back To Main Menu....";
		char end = _getche();
	}

	void Menu() {
		system("cls");
		cout << "================================ Bank System ================================\n\n"
			<< "\t\t\t\tPress <1> Create Account\n"
			<< "\t\t\t\tPress <2> Login\n"
			<< "\t\t\t\tEnter Your Choice [1-2] ";

		char choice = _getche();
		switch (choice) {
		case '1':
			system("cls");
			create_account();
			break;
		case '2':
			system("cls");
			login();
			break;
		default:
			break;
		}
	}

	void create_account()
	{

		string name;
		double balance;
		string pass;
		
		cout << "================================ Create Account ================================\n\n"
			 << "\t\t\t\tEnter Your Name: ";
		//getline(cin, name);
		cin >> name;
		bool validateBalance = true;
		while (validateBalance)
		{
			cout << "\t\t\t\tEnter Your Balance (At Least 3000$): ";
			cin >> balance;
			if (balance >= 3000)
			{
				validateBalance = false;
			}
		}


		bool validPassword = false;
		while (!validPassword) {
			cout << "\n\t\t\t\tEnter Your Password \n\t\t\t\t(8Chars with at least 1 Capital and 1 small Character): ";
			cin >> pass;

			validPassword = Account::validatePassword(pass);

			if (validPassword) {
		
				break;
			}

		}


		Account newAcc(name, pass, balance);
		Accounts.push_back(newAcc);
		cout << "\n\n\t\t\t\tAccount Created Successfully...";
		newAcc.DisplayAccountInfo();
		StepBack();
		Menu();
	}

	void login() {
		int id;
		string pass;
		bool isLoggedIn = false;

		while (!isLoggedIn) {
			system("cls");
			cout << "================================ Login To Your Account ================================\n\n"
				<< "\t\t\t\tEnter Your ID: ";
			cin >> id;
			cout << "\n\t\t\t\tEnter Your Password: ";
			cin >> pass;

			//Binary Search
			int start = 0;
			int end = Accounts.size() - 1;

			while (start <= end)
			{
				int mid = (start + end) / 2;
				if( Accounts[mid].GetAccountID() == id && Accounts[mid].CheckPassword(pass))
				{
					system("cls");
					operations(Accounts[mid]);
					isLoggedIn = true;
					break;
				}

				if (id > Accounts[mid].GetAccountID())
				{
					start = mid + 1;
				}
				else
				{
					end = mid - 1;
				}
			}


			if (!isLoggedIn) {
				cout << "\n\t\t\t\tInvalid ID (or/and) Password Click any key to try Again....";
				char end = _getche();
			}
		}
	}

	void operations(Account& Acc) {
		while (true) {
			system("cls");
			cout << "================================ Welcome " << Acc.GetAccountName() << " ================================\n\n"
				<< "\t\t\t\tPress <1> Account Information\n"
				<< "\t\t\t\tPress <2> Deposite\n"
				<< "\t\t\t\tPress <3> Withdraw\n"
				<< "\t\t\t\tPress <4> Send Money\n"
				<< "\t\t\t\tPress <5> Transactions History\n"
				<< "\t\t\t\tPress <6> Log out\n"
				<< "\t\t\t\tEnter Your Choice [1-5] ";


			char choice = _getche();

			if (choice == '1') {
				system("cls");
				Acc.DisplayAccountInfo();
				StepBack();
			}
			else if (choice == '2') {
				system("cls");
				double deposite;
				cout << "\t\t\t\tEnter The Amount You Want to Deposite: ";
				cin >> deposite;
				Acc.Deposite(deposite,0);
				cout << "\t\t\t\tAmount Adedd Successfuly...\n";
				StepBack();
			}
			else if (choice == '3') {
				system("cls");
				double amount;
				cout << "\t\t\t\tEnter The Amount You Want to Withdraw: ";
				cin >> amount;
				while (!Acc.Withdraw(amount,0)) {
					cout << "\n\t\t\t\tPlease Enter A valid Amount: ";
					cin >> amount;
				}
				cout << "\n\t\t\t\tThe Operation Done Successfully U Can Check Your New Balance..\n";
				StepBack();
			}
			else if (choice == '4')
			{
				system("cls");

				TransferMoney(Acc);
			}
			else if (choice == '5')
			{
				system("cls");

				Acc.DisplayTransactionHistory();
				StepBack();
			}
			else if (choice == '6') {
				break;
			}
		}
	}
	void TransferMoney(Account &sender)
	{

		int reciever_id;
		double amount;
		int index = 0;



		bool idFound = false;
		while (true)
		{
			cout << "\n\t\t\t\tEnter The ID of the Receiver Account: ";
			cin >> reciever_id;


			for (int Index = 0; Index < Accounts.size(); Index++)
			{
				if (Accounts[Index].GetAccountID() == reciever_id)
				{
					idFound = true;
					index = Index;
					break;
				}
			}


			if (!idFound)
			{
				cout << "\n\t\t\t\tInvalid ID. Try Again: ";
			}
			else
			{
				break;
			}
		}



		while (true)
		{

			cout << "\t\t\t\tEnter The Amount You Want to Send: ";
			cin >> amount;

			if (amount <= sender.GetAccountBalance())
			{
				break;
			}
			cout << "\t\t\t\tInvalid Amount!!!\n";
		}

		sender.Withdraw(amount,1);
		Accounts[index].Deposite(amount,1);


		sender.recordTransaction("Transfer", -amount);
		Accounts[index].recordTransaction("Transfer", amount);

		cout << "\n\t\t\t\tMoney Transfered Successfuly\n";
		StepBack();
		return;
	}
};