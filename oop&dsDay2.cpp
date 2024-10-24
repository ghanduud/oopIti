

#include <iostream>


using namespace std;

////////////////////////////////////////////////////////////////////// Task 3 //////////////////////////////////////////////////////////////////////////
struct Sword {
	int id;
	string type;
	double durability;
};

struct HealthPotion {
	int id;
	int hitPointRestore;
};

struct Armor {
	int id;
	string type;
	double durability;
};

struct Money {
	int id;
	string type;
};

struct Inventory {
	Sword sword;
	HealthPotion healthPotion[10];
	Armor armor;
	Money money[100];
	int potionCount = 0;
	int moneyCount = 0;
};

void addPotion(Inventory& inv) {
	if (inv.potionCount < 10) {
		inv.healthPotion[inv.potionCount].id = inv.potionCount + 1;
		inv.healthPotion[inv.potionCount].hitPointRestore = 50 + inv.potionCount * 10;
		inv.potionCount++;
		cout << "add potion current potion count: " << inv.potionCount << "\n";
	}
	else {
		cout << "no space\n";
	}
}

void getPotion(Inventory& inv) {
	if (inv.potionCount > 0) {
		inv.potionCount--;
		cout << "retrive potion Current potion count: " << inv.potionCount << "\n";
	}
	else {
		cout << "no potions\n";
	}
}

void addMoney(Inventory& inv) {
	if (inv.moneyCount < 100) {
		inv.money[inv.moneyCount].id = inv.moneyCount + 1;
		inv.money[inv.moneyCount].type = "Gold Coin";
		inv.moneyCount++;
		cout << "add money Current money count: " << inv.moneyCount << "\n";
	}
	else {
		cout << "no space\n";
	}
}

void getMoney(Inventory& inv) {
	if (inv.moneyCount > 0) {
		inv.moneyCount--;
		cout << "retrive money Current money count: " << inv.moneyCount << "\n";
	}
	else {
		cout << "no money\n";
	}
}

void displayInventory(const Inventory& inv) {
	cout << "\n--- Inventory Status ---\n";
	cout << "Current potions: " << inv.potionCount << "/10\n";
	cout << "Current money: " << inv.moneyCount << "/100\n";
}

////////////////////////////////////////////////////////////////////// Task 3 //////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////// Task 1 //////////////////////////////////////////////////////////////////////////
void timesTable(int x, int until) {
	if (until == 0) {
		cout << x << " * 0 =" << 0 * x << "\n";
		return;
	}
	cout << x << " * " << until << " = " << until * x << "\n";
	timesTable(x, until - 1);
}
////////////////////////////////////////////////////////////////////// Task 1 //////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////// Task 2 ///////////////////////////////////////////////////////////////////////////////

int factorialWithoutPointer(int n) {
	if (n <= 1 ) {
		return 1;
	}
	return n * factorialWithoutPointer(n - 1);
}

int powerWithOutRecursion(int x, int y) {
	if (y == 0) {
		return 1;
	}
	return x * powerWithOutRecursion(x, y - 1);
}

void factorialWithPointer(int* n, int iterator = 1) {
	if (*n <= 1) {
		*n = iterator;
		return;
	}
	*n -= 1;
	factorialWithPointer(n, iterator * (*n + 1));
}


void powerWithPointer(int* base, int* exponent, int iterator = 1) {
	if (*exponent == 0) {
		*base = iterator;
		return;
	}
	*exponent -= 1;
	powerWithPointer(base, exponent, iterator * (*base));
}
////////////////////////////////////////////////////////////////////////////// Task 2 ///////////////////////////////////////////////////////////////////////////////

int main()
{

	////////////////////////////////////////////////////////////////////////////// Task 2 ///////////////////////////////////////////////////////////////////////////////

	cout << "recursion factorial without pointer : 5! = " << factorialWithoutPointer(5) << endl;

	cout << "recursion factorial without power : 2^3 = " << powerWithOutRecursion(2, 3) << endl;





	int numberForFactorial = 5;
	factorialWithPointer(&numberForFactorial);
	cout << "recursion factorial with pointer: 5! = " << numberForFactorial << endl;

	int num1ForPower = 2;
	int exponentForPower = 3;
	powerWithPointer(&num1ForPower, &exponentForPower);
	cout << "recursion power with pointer: 2^3 = " << num1ForPower << endl;
	////////////////////////////////////////////////////////////////////////////// Task 2 ///////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////// Task3 //////////////////////////////////////////////////////////////////////////
	Inventory inventory;

	for (int i = 0; i < 5; i++) {
		addPotion(inventory);
		addMoney(inventory);
	}

	addPotion(inventory);
	getPotion(inventory);

	addMoney(inventory);
	getMoney(inventory);

	displayInventory(inventory);
	////////////////////////////////////////////////////////////////////// Task 3 //////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////// Task 1 //////////////////////////////////////////////////////////////////////////

	timesTable(5, 10);

	////////////////////////////////////////////////////////////////////// Task 1 //////////////////////////////////////////////////////////////////////////
}

