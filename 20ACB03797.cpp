/* Important notices for the A2 template:
A. You will need to use this template to work on the Assignment 2 (A2)
B. You are not allowed to change the whole structure of template including adding additional functions or remove any existing functions
C. You will only need to fill in the codes with the parts that indicated with numbers and its descriptions
D. You will need to ensure all the COUT are exactly the same as shown in A2 doc as the codes are auto marked by a system. LOW marks or ZERO
   mark will be awarded if the system is unable to detect the correct COUT.
E. No extra decorations are allowed as you will be using the template to work on A2
F. You will need to define the parameters accordingly (including its datatype) as described below:
   P1 = parameter to store the day
   P2 = parameter to store the date
   P3 = array to store the name of the items
   P4 = array to store the code of the items
   P5 = array to store the price of the items per kilogram
   P6 = array to store the purchasing weight provided by the user
   P7 = parameter to store the number of items available in the list
*/

//Only these libraries are allowed to be defined and used
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

#define SIZE 100 //global definition to determine the size of the array in A2
//1. Define the FUNCTION PROTOTYPE for all the listed functions
void readItemList(string&, string&, string[], string[], double[], double[], int&);
void writeItemList(string&, string&, string[], string[], double[], double[], int&);
void addItemList(string[], string[], double[], double[], int&);
void modifyItemList(string[], string[], double[], double[], int&);
void displayItemList(string[], string[], double[], double[], int&);
void printInvoice(string&, string&, string[], string[], double[], double[], int&);
double calculateGrandTotal(double[], double[], int&);

int main() {
	//2. Define all the necessary variables
	double goods_price[SIZE], goods_weight[SIZE];
	string purchase_day, purchase_date, goods_name[SIZE], goods_code[SIZE];
	int select, cont, number_goods = 0;

	//Call readItemList with the required parameters
	readItemList(purchase_day, purchase_date, goods_name, goods_code, goods_price, goods_weight, number_goods);

	do {//do...while iteration is implemented to repeat the selection menu as below
		cout << "1. Display Item List" << endl;
		cout << "2. Add Item List" << endl;
		cout << "3. Modify Item List" << endl;
		cout << "4. Print Invoice" << endl;
		cout << "5. Quit" << endl;

		//User will key in and select one of the functions available
		cout << "Choice: ";
		cin >> select;

		//"cls" stand for clear screen which refreshes the screen, placing the cursor on original place.
		//For more information, refer to https://www.quora.com/What-is-system-CLS-for-in-c++
		system("cls");

		//cin.ignore() is to ignore or clear one or more characters from the input buffer
		//For more information, refer to https://www.tutorialspoint.com/what-is-the-use-of-cin-ignore-in-cplusplus
		cin.ignore();

		//3. if...else is implemented to select the function according to the user input
		if (select == 1)
			displayItemList(goods_name, goods_code, goods_price, goods_weight, number_goods);
		else if (select == 2)
			addItemList(goods_name, goods_code, goods_price, goods_weight, number_goods);
		else if (select == 3)
			modifyItemList(goods_name, goods_code, goods_price, goods_weight, number_goods);
		else if (select == 4)
			printInvoice(purchase_day, purchase_date, goods_name, goods_code, goods_price, goods_weight, number_goods);
		else if (select == 5)
			break;
		else
			cout << "Not available" << endl;

		//Update the items in the text file whatever function is carried out
		writeItemList(purchase_day, purchase_date, goods_name, goods_code, goods_price, goods_weight, number_goods);

		//To check whether user wants to continue to perform these functions or not
		cout << "Continue? (1-yes, 2-no): ";
		cin >> cont;

		system("cls");
	} while (cont == 1); //the do...while will stop if the condition is false (user choose to stop the program)

	/*4. Grand total of the items is calculated through the RETURN function */
	cout << "Grand Total of the bill = RM" << fixed << setprecision(2) << calculateGrandTotal(goods_price, goods_weight, number_goods) << endl;

	return 0;
}

//5. Function readItemList --> read (ifstream) all the items listed in "itemList.txt" 
//   and store the data into the respective parameters.
//   Hint: P1, P2 and P7 should be reference parameters in this function
void readItemList(string& purchase_day, string& purchase_date,
	string goods_name[], string goods_code[], double goods_price[], double goods_weight[], int& number_goods) {

	int index = 0;

	ifstream readfile;
	readfile.open("itemList.txt");

	getline(readfile, purchase_day);
	getline(readfile, purchase_date);

	while (!readfile.eof()) {
		getline(readfile, goods_name[index]);
		getline(readfile, goods_code[index]);
		readfile >> goods_price[index] >> goods_weight[index];
		readfile.ignore();
		index++;
	}
	number_goods = index;
	readfile.close();
}

//6. Function writeItemList --> write / update (ofstream) all the items to "itemList.txt"
void writeItemList(string& purchase_day, string& purchase_date,
	string goods_name[], string goods_code[], double goods_price[], double goods_weight[], int& number_goods) {

	ofstream writefile;
	writefile.open("itemList.txt");

	writefile << purchase_day << endl;
	writefile << purchase_date << endl;

	for (int i = 0; i < number_goods; i++) {
		writefile << goods_name[i] << endl;
		writefile << goods_code[i] << endl;
		writefile << showpoint << fixed << setprecision(2);
		writefile << goods_price[i] << " " << goods_weight[i];
		if (i != (number_goods - 1))
			writefile << endl;
	}
	writefile.close();
}

//7. Function addItemList --> add new items into the existing list 
//   Hint: P7 should be a reference parameter as the number of items should be updated
void addItemList(string goods_name[], string goods_code[], double goods_price[], double goods_weight[], int& number_goods) {

	char select[20];
	int number = 0, alphabet = 0, unknown = 0;
	bool not_correct = true;

	//8. This part is to confirm whether user want to key in new item or not.
	//   If yes, user will need to enter 1. Else, user will need to enter 2.
	//   An evaluation is carried out to ensure user only key in 1 or 2.
	//   However, the current evaluation is only able to check on numbers.
	//   Additional marks will be awarded to those who are able to check on the input other than numbers such as "abc" or "1abc".
	//   Tips: isdigit and stoi can be used. If you are using stoi with dev c++, you may face c++ 11 problem and please
	//	       refer to https://stackoverflow.com/questions/13613295/how-can-i-compile-c11-code-with-orwell-dev-c

	do {
		cout << "Add new item? (1-yes, 2-no): ";
		cin.getline(select, 20);

		for (int i = 0; i < strlen(select); i++) {

			if (isdigit(select[i]))
				number++;
			else if (isalpha(select[i]))
				alphabet++;
			else
				unknown++;
		}

		for (int i = 0; i < strlen(select); i++) {
			if ((number == 1) && (alphabet == 0) && (unknown == 0)) {
				switch (select[0]) {
				case '1':
					not_correct = false;
					break;
				case '2':
					not_correct = false;
					break;
				default:
					number = 0;
					alphabet = 0;
					unknown = 0;
					not_correct = true;
				}
			}
			else {
				number = 0;
				alphabet = 0;
				unknown = 0;
				not_correct = true;
			}
		}
	} while (not_correct);

	if (select[0] == '1') {
		//9. User will key in the details of the new items
		//   The COUT of add item for this module is shown in the A2 doc
		//   Marks will not be awarded if your COUT different from the sample COUT
		for (int i = 0; i <= number_goods; i++) {
			if (i == number_goods) {
				cout << "New item's name: ";
				getline(cin, goods_name[number_goods]);
				cout << "New item's code: ";
				getline(cin, goods_code[number_goods]);
				cout << "Price of new item per KG (RM): ";
				cin >> goods_price[number_goods];
				cout << "Purchasing Weight (KG): ";
				cin >> goods_weight[number_goods];
			}
		}
		number_goods++;
	}
}

//10. Function modifyItemList --> modify the details of any existing items in the list
void modifyItemList(string goods_name[], string goods_code[], double goods_price[], double goods_weight[], int& number_goods) {
	int found_code = 0, select = 0, index_found = 0;
	string modify_code;

	//Evaluation is not required in this function
	do {
		cout << "Modify item? (1-yes, 2-no): ";
		cin >> select;

	} while (select <= 0 || select >= 3);

	if (select == 1) {
		//11. User will key in the item to be modified through item code and find its match from the existing list
		//    If item is detected, all the details are to be keyed in 
		//    Else, it will have to cout "Item is not available." as shown in the A2 doc
		//    The COUT of modification for this module is shown in the A2 doc
		//    Marks will not be awarded if your COUT different from the sample COUT

		cin.ignore();
		cout << "Key in item code: ";
		getline(cin, modify_code);

		for (int i = 0; i < number_goods; i++) {
			if (goods_code[i] == modify_code) {
				found_code = 1;
				index_found = i;
			}
		}

		if (found_code == 1) {
			cout << "Item found!" << endl;
			cout << "New item's name: ";
			getline(cin, goods_name[index_found]);
			cout << "New item's code: ";
			getline(cin, goods_code[index_found]);
			cout << "Price per KG (RM): ";
			cin >> goods_price[index_found];
			cout << "Purchasing Weight (KG): ";
			cin >> goods_weight[index_found];
		}
		else
			cout << "Item is not available." << endl;
		found_code = 0;
	}
}

//12. Function displayItemList --> display the details of all the items in the list
//    The COUT of display items is shown in the A2 doc
//    Marks will not be awarded if your COUT different from the sample COUT
void displayItemList(string goods_name[], string goods_code[], double goods_price[], double goods_weight[], int& number_goods) {
	for (int i = 0; i < number_goods; i++) {
		cout << "Item " << i + 1 << endl;
		cout << "Name: " << goods_name[i] << endl;
		cout << "Code: " << goods_code[i] << endl;
		cout << showpoint << fixed << setprecision(2);
		cout << "Price per KG: RM" << goods_price[i] << endl;
		cout << "Purchasing Weight: " << goods_weight[i] << "KG" << endl << endl;
	}
}

//13. Function printInvoice --> print out an invoice named "invoice.txt"
//    The output of the invoice is shown in the A2 doc
//    Marks will not be awarded if the output of your invoice is different from the sample invoice
void printInvoice(string& purchase_day, string& purchase_date,
	string goods_name[], string goods_code[], double goods_price[], double goods_weight[], int& number_goods) {

	double total = 0;

	ofstream writefile;
	writefile.open("invoice.txt");

	writefile << "Date: " << purchase_date << endl;
	writefile << "Day: " << purchase_day << endl;
	writefile << "List of Items:" << endl;
	for (int i = 0; i < number_goods; i++) {
		writefile << i + 1 << ". " << goods_name[i] << " = " << showpoint << fixed << setprecision(2) << goods_weight[i] << "KG"
			<< " * RM" << goods_price[i] << " = RM" << (goods_weight[i] * goods_price[i]) << endl;
		total += (goods_weight[i] * goods_price[i]);
	}
	writefile << "Grand Total of the bill = RM" << total;
	writefile.close();
}

//14. Function calculateGrandTotal --> calculate the grand total of the items purchase and RETURN the grand total to the calling function
double calculateGrandTotal(double goods_price[], double goods_weight[], int& number_goods) {
	double total = 0;
	for (int i = 0; i < number_goods; i++)
		total += (goods_weight[i] * goods_price[i]);
	return total;
}
