#pragma once
#include <iostream>
using namespace std;

class Transaction
{
private:
	string operationType;
	double amount;

public:

	void setAmount(double amount)
	{
		this->amount = amount;
	}

	void setOperationType(string type)
	{
		operationType = type;
	}

	double getAmount()
	{
		return this->amount;
	}

	string getOerationType()
	{
		return this->operationType;
	}
};

