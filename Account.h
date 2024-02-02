#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <vector>
#include "Transaction.h"
using namespace std;

class Account
{
private:
	vector <Transaction> TransactionHistory;
	static int account_id_counter;
	int account_id;
	string account_name;
	string account_password;
	double account_balance;

public:


	Account(string name, string pass, double balance)
	{
		account_id_counter += 20;
		account_id = account_id_counter;

		SetAccountName(name);
		SetAccountPassword(pass);
		SetAccountBalance(balance);
	}

	//Getters

	bool CheckPassword(string pass)
	{
		return this->account_password == pass;
	}

	string GetAccountName()
	{
		return account_name;
	}

	int GetAccountID()
	{
		return account_id;
	}

	int GetAccountBalance()
	{
		return account_balance;
	}

	//Setters
	void SetAccountName(string name)
	{
		account_name = name;
	}

	static bool validatePassword(const string& pass)
	{
		if (pass.length() < 8)
		{
			cout << "\n\t\t\t\tPassword must be at least 8 characters.\n";
			return false;
		}

		bool hasUppercase = false;
		bool hasLowercase = false;
		bool hasDigit = false;

		for (int index = 0; index < pass.length(); index++)
		{
			if (isupper(pass[index])) hasUppercase = true;
			if (islower(pass[index])) hasLowercase = true;
			if (isdigit(pass[index])) hasDigit = true;
		}

		if (!(hasUppercase && hasLowercase && hasDigit))
		{
			cout << "\n\t\t\t\tPassword must contain at least 1 uppercase letter, 1 lowercase letter, and 1 digit.\n";
			return false;
		}

		return true;
	}

	void SetAccountPassword(string pass)
	{
		account_password = pass;
	}


	void SetAccountBalance(double balance)
	{
		account_balance = balance;
	}



	void Deposite(double amount, int flag)
	{
		account_balance += amount;

		if(flag == 0)
			recordTransaction("Deposite", amount);
	}

	bool Withdraw(double amount, int flag )
	{
		if (amount > account_balance || amount < 0)
		{
			return false;
		}

		else
		{
			account_balance -= amount;
			if (flag == 0)
			{
				recordTransaction("Withdraw", amount);
			}
			return true;
		}
	}

	void DisplayAccountInfo()
	{
		cout << "\n\t\t\t\tAccount ID: " << account_id << endl
			<< "\t\t\t\tAccount Owner: " << account_name << endl
			<< "\t\t\t\tAccount Balance: " << account_balance << endl;
	}

	void DisplayTransactionHistory()
	{
		cout << "================================ Transactions History ================================\n\n";
		for (int index = 0; index < TransactionHistory.size(); index++)
		{
			cout << "\t\t\t\t " << TransactionHistory[index].getOerationType() << " : " << TransactionHistory[index].getAmount() << endl;
		}

	}
	
	void recordTransaction(string type, double amount)
	{
		Transaction newTransact;
		newTransact.setAmount(amount);
		newTransact.setOperationType(type);
		TransactionHistory.push_back(newTransact);
	}

};
