#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int MAX_VALUE = 100;
int *Order_list1 = new int[MAX_VALUE];		// an array to store the table number according to the order of different group of customers
int *Order_list2 = new int[MAX_VALUE];		// an array to store the order of different group of customers(who come earlier)
int *Table_Occupied = new int[MAX_VALUE];	//shows how many seats are occupied
int *Table_Available = new int[MAX_VALUE];	//shows how many seats are available
int *Waiting_list = new int[MAX_VALUE];		//construct a waiting list to see how many people waiting for a seat and thier number
int table_size = 5, num_of_table = 20,z=0,x=0;
ofstream fout;

/* This function shows a 2D picture of our restaurant which included the number of the table,
 the available seat of a table and the seat occupied for that table*/
void show_table() {
	cout << endl;
	fout << endl;

	cout << setw(50) << right << "***********************************************" << endl;
	fout << setw(50) << right << "***********************************************" << endl;

	cout << setw(10) << "* Table" << setw(20) << right << "(Available seat) " << setw(20) << right << "[Occupied seat] *" << endl;
	fout << setw(10) << "* Table" << setw(20) << right << "(Available seat) " << setw(20) << right << "[Occupied seat] *" << endl;

	cout << setw(50) << right << "***********************************************" << endl;
	fout << setw(50) << right << "***********************************************" << endl;

	cout << endl;
	fout << endl;

	cout << " +------------+------------+------------+------------+----------- +" << endl;
	fout << " +------------+------------+------------+------------+----------- +" << endl;

	for (int i = 0; i < num_of_table; i++) {
		if ((i + 1) % 5 == 0) {
			cout << " |" << setw(3) << right << (i + 1) << " (" << Table_Available[i] << ") [" << Table_Occupied[i] << "] |";
			fout << " |" << setw(3) << right << (i + 1) << " (" << Table_Available[i] << ") [" << Table_Occupied[i] << "] |";

			cout << endl;
			fout << endl;

			cout << " +------------+------------+------------+------------+----------- +" << endl;
			fout << " +------------+------------+------------+------------+----------- +" << endl;
		}
		else {
			cout << " |" << setw(3) << right << (i + 1) << " (" << Table_Available[i] << ") [" << Table_Occupied[i] << "]" << right;
			fout << " |" << setw(3) << right << (i + 1) << " (" << Table_Available[i] << ") [" << Table_Occupied[i] << "]" << right;
		}
	}
}
/*this function read an input of number of customer and print out a waiting list*/
/*void Waiting_lists(int &count_customer) {
	cout << endl;
	fout << endl;

	cout << "Waiting List: " << endl;
	fout << "Waiting List: " << endl;

	for (int i = count_customer; i < MAX_VALUE; i++) {
		if ((i + 1) % 10 == 0) {
			cout << setw(2) << right << Waiting_list[i] << endl;
			fout << setw(2) << right << Waiting_list[i] << endl;
		}
		else {
			cout << setw(2) << right << Waiting_list[i] << " ";
			fout << setw(2) << right << Waiting_list[i] << " ";
		}
	}
	cout << endl;
	fout << endl;
}*/

/*this function read the action that that user want to carry out,'I' or 'O' ,the number of the customers,the number of all available table
,number of full table ,the number of total available seat, and be reminded that these parameter are passed to reference.
this function will fout the output into the target file.It will automatically assign the customer to 
the available seat when it is in 'all_table occupied state'(all tables are occupied by at least one person), it will notice
them you have to share table with other and also tell the waiter we don't have enough seat when all available seats are occupied 
or the new coming customer number is larger than our available seat. It will let the waiter release the table occupied by earlest come customer*/

void auto_assign_table(char move, int customer, int &count_customer, int &all_available_table, int &full_table, int &all_available_seat) {
	int table_num;
	show_table();

	cout << "Number of available table: " << all_available_table - full_table << endl;
	cout << "Number of full table: " << full_table << endl;
	cout << "Number of available seat: " << all_available_seat << endl;
	cout << "Number of occupied seat: " << num_of_table * table_size - all_available_seat << endl;

	fout << "Number of available table: " << all_available_table - full_table << endl;
	fout << "Number of full table: " << full_table << endl;
	fout << "Number of available seat: " << all_available_seat << endl;
	fout << "Number of occupied seat: " << num_of_table * table_size - all_available_seat << endl;

	cout << endl;
	cout << "  * Input E to exit   " << endl;
	cout << "  * Input I to occupy a table   " << endl;
	cout << "  * Input O to release a table   " << endl;
	cout << endl;
	cout << "What action? (I/O) ";

	fout << endl;
	fout << "  * Input E to exit   " << endl;
	fout << "  * Input I to occupy a table   " << endl;
	fout << "  * Input O to release a table   " << endl;
	fout << endl;
	fout << "What action? (I/O) ";

	cin >> move;
	fout << move << endl;

	if (move == 'I') {
		if (all_available_seat == 0) {
			cout << "********* The restaurant is now full *********" << endl;
			fout << "********* The restaurant is now full *********" << endl;

			cout << Order_list2[x] << " customer(s) in Table " << Order_list1[x] << " may occupy the table for too long !" << endl;
			fout << Order_list2[x] << " customer(s) in Table " << Order_list1[x] << " may occupy the table for too long !" << endl;

			cout << endl;
			fout << endl;

			x++;
			move = 'O';
		}

		else if (all_available_seat >= customer) {
			cout << " ********* All tables in the restaurant are occupied *********" << endl;
			cout << "You have to share the table with others!" << endl;
			cout << "Number of customer(s): ";

			fout << " ********* All tables in the restaurant are occupied *********" << endl;
			fout << "You have to share the table with others!" << endl;
			fout << "Number of customer(s): ";

			// cout << customer << endl;
			cin >> customer;
			fout << customer << endl;

			for (int i = 0; i < num_of_table; i++) {
				if (customer <= Table_Available[i]) {
					Table_Available[i] -= customer;
					Table_Occupied[i] += customer;
					cout << customer << " Customer(s) have been assigned to Table " << i + 1 << endl;
					fout << customer << " Customer(s) have been assigned to Table " << i + 1 << endl;
					Order_list1[z] = i+1;
					Order_list2[z] = customer;
					z++;
					break;
				}

				else if (customer > Table_Available[i] && Table_Available[i] != 0) {
					int temp = customer;

					while (Table_Available[i] > 0) {
						Table_Available[i] -= 1;
						Table_Occupied[i] += 1;
						customer -= 1;
					}

					cout << temp - customer << " Customer(s) have been assigned to Table " << i + 1 << endl;
					fout << temp - customer << " Customer(s) have been assigned to Table " << i + 1 << endl;

					Order_list1[z] = i + 1;
					Order_list2[z] = temp-customer;
					z++;
				}

				else if (all_available_seat < customer) {

					cout << "We don't have enoguh seats."<<endl;
					cout << Order_list2[x] << " customer(s) in Table " << Order_list1[x] << " may occupy the table for too long !";
					cout << endl;

					fout << "We don't have enoguh seats."<<endl;
					fout << Order_list2[x] << " customer(s) in Table " << Order_list1[x] << " may occupy the table for too long !";
					fout << endl;

					x++;
					move = 'O';
					return;
				}

				else if (Table_Available[i] == 0) {
					continue;
				}
			}
		}

		else if (all_available_seat < customer) {

			cout << "We don't have enoguh seats." << endl;
			cout << Order_list2[x] << " customer(s) in Table " << Order_list1[x] << " may occupy the table for too long !";
			cout << endl;

			fout << "We don't have enoguh seats." << endl;
			fout << Order_list2[x] << " customer(s) in Table " << Order_list1[x] << " may occupy the table for too long !";
			fout << endl;

			x++;
			move = 'O';
			return;
		}
		count_customer++;
	}

	if (move == 'O') {

		cout << "Which table need to be released? ";
		fout << "Which table need to be released? ";

		cin >> table_num;
		fout << table_num << endl;

		cout << "How many customer(s) out? ";
		fout << "How many customer(s) out? ";

		cin >> customer;
		fout << customer << endl;

		while (customer > Table_Occupied[table_num - 1]) {

			cout << "Error! Enter again. ";
			cout << "How many customer(s) out? ";

			fout << "Error! Enter again. ";
			fout << "How many customer(s) out? ";

			cin >> customer;
			fout << customer << endl;
		}
		Table_Available[table_num - 1] += customer;
		Table_Occupied[table_num - 1] -= customer;
	}

	if (move == 'E'){
		return;
	}

	for (int i = 0; i < all_available_table; i++) {
		all_available_seat += Table_Available[i];
		if (Table_Available[i] == 0) {
			full_table += 1;
		}
	}
}

void start_func() {
	int customer = 0, count_customer = 0;
	char YorN, move = ' ';

	for (int i = 0; i < MAX_VALUE; i++) {
		Table_Available[i] = table_size;
		Table_Occupied[i] = 0; // Original = 0;
	}

	//Waiting_lists(count_customer);

	while (move != 'E') {
		int table_num, /*customer = 0, */all_available_table = num_of_table, full_table = 0, all_available_seat = 0, total = 0;

		for (int i = 0; i < num_of_table; i++) {
			if (Table_Occupied[i] > 0) {
				total += 1;
			}
		}

		customer = Waiting_list[count_customer];
		// Waiting_list[count_customer] = NULL;

		for (int i = 0; i < all_available_table; i++) {
			all_available_seat += Table_Available[i];
			if (Table_Available[i] == 0) {
				full_table += 1;
			}
		}

		if (total == num_of_table && move != 'O') {
			auto_assign_table(move, customer, count_customer, all_available_table, full_table, all_available_seat);    // Assign the table if all tables are occupied
			continue;
		}

		cout << "Number of available table: " << all_available_table - full_table << endl;
		cout << "Number of full table: " << full_table << endl;
		cout << "Number of available seat: " << all_available_seat << endl;
		cout << "Number of occupied seat: " << num_of_table * table_size - all_available_seat << endl;

		fout << "Number of available table: " << all_available_table - full_table << endl;
		fout << "Number of full table: " << full_table << endl;
		fout << "Number of available seat: " << all_available_seat << endl;
		fout << "Number of occupied seat: " << num_of_table * table_size - all_available_seat << endl;

		show_table();

		cout << endl;
		fout << endl;

		cout << "  * Input E to exit   " << endl;
		cout << "  * Input I to occupy a table   " << endl;
		cout << "  * Input O to release a table   " << endl;
		cout << endl;
		cout << "What action? (I/O) ";

		fout << "  * Input E to exit   " << endl;
		fout << "  * Input I to occupy a table   " << endl;
		fout << "  * Input O to release a table   " << endl;
		fout << endl;
		fout << "What action? (I/O) ";

		cin >> move;
		fout << move << endl;

		if (move == 'I') {

			cout << "Number of customer(s): ";
			fout << "Number of customer(s): ";

			cin >> customer;
			//cout << customer << endl;
			fout << customer << endl;

			if (all_available_seat < customer) {

				cout << "We don't have enoguh seats." << endl;
				cout << Order_list2[x] << " customer(s) in Table " << Order_list1[x] << " may occupy the table for too long !" << endl;

				fout << "We don't have enoguh seats." << endl;
				fout << Order_list2[x] << " customer(s) in Table " << Order_list1[x] << " may occupy the table for too long !" << endl;

				x++;
				move = 'O';
			}
			else if (all_available_seat >= customer) {
				while (customer != 0) {
					cout << "Tables you can choose: ";
					fout << "Tables you can choose: ";

					for (int i = 0; i < num_of_table; i++) {
						if (Table_Occupied[i] == 0) {
							cout << i + 1 << " ";
							fout << i + 1 << " ";
						}
					}

					cout << endl;
					cout << "Table(s) you would like to occupy: ";

					fout << endl;
					fout << "Table(s) you would like to occupy: ";

					cin >> table_num;
					fout << table_num << endl;

					if (Table_Occupied[table_num - 1] != 0) {

						cout << " Table is occupied already " << endl;
						cout << " Please try again" << endl;

						fout << " Table is occupied already " << endl;
						fout << " Please try again" << endl;

						break;
					}

					else {
						if (Table_Available[table_num - 1] >= customer) {
							Order_list1[z] = table_num;
							Order_list2[z] = customer;
							z++;
							Table_Available[table_num - 1] -= customer;
							Table_Occupied[table_num - 1] += customer;
							customer -= customer;
						}

						if (Table_Available[table_num - 1] < customer) {
							Order_list1[z] = table_num;
							Order_list2[z] = table_size;
							z++;
							Table_Available[table_num - 1] -= table_size;
							Table_Occupied[table_num - 1] += table_size;
							customer -= table_size;
							show_table();

							cout << "You have to assign tables for " << customer << " more customers" << endl;
							fout << "You have to assign tables for " << customer << " more customers" << endl;
						}
					}
				}
			}
		}
		 if (move == 'O') {
			cout << "Which table need to be released? ";
			fout << "Which table need to be released? ";

			cin >> table_num;
			fout << table_num << endl;

			cout << "How many customer(s) out? ";
			fout << "How many customer(s) out? ";

			cin >> customer;
			fout << customer << endl;

			while (customer > Table_Occupied[table_num - 1]) {

				cout << "Error! Enter again. ";
				cout << "How many customer(s) out? ";
				fout << "Error! Enter again. ";
				fout << "How many customer(s) out? ";

				cin >> customer;
				fout << customer << endl;
			}
			Table_Available[table_num - 1] += customer;
			Table_Occupied[table_num - 1] -= customer;
		}

		cout << "===========================================================================" << endl;
		cout << endl;
		fout << "===========================================================================" << endl;
		fout << endl;

		count_customer++;
		//cout << "Waiting List: " << endl;
		//Waiting_lists(count_customer);
		
		cout << endl;
		fout << endl;
	}
}


void setting_func() {
	int prog_choice;
	do {
		cout << endl;
		cout << "What time is it?" << endl;
		cout << "------------------------------------------" << endl;
		cout << "                      Summer Time" << endl;
		cout << "(1) 07:00 - 11:30 - Number of table: 10 Table size: 4" << endl;
		cout << "(2) 12:00 - 14:30 - Number of table: 20 Table size: 5" << endl;
		cout << "(3) 15:00 - 18:00 - Number of table: 10 Table size: 4" << endl;
		cout << "(4) 18:00 - 21:30 - Number of table: 20 Table size: 5" << endl;
		cout << "                      Winter Time" << endl;
		cout << "(5) 07:00 - 11:30 - Number of table: 15 Table size: 5" << endl;
		cout << "(6) 12:00 - 14:30 - Number of table: 20 Table size: 6" << endl;
		cout << "(7) 15:00 - 18:00 - Number of table: 15 Table size: 5" << endl;
		cout << "(8) 18:00 - 21:30 - Number of table: 25 Table size: 6" << endl;
		cout << endl;
		cout << "(9) Exit" << endl;
		cout << "Enter the choice: ";
		
		fout << endl;
		fout << "What time is it?" << endl;
		fout << "------------------------------------------" << endl;
		fout << "                      Summer Time" << endl;
		fout << "(1) 07:00 - 11:30 - Number of table: 10 Table size: 4" << endl;
		fout << "(2) 12:00 - 14:30 - Number of table: 20 Table size: 5" << endl;
		fout << "(3) 15:00 - 18:00 - Number of table: 10 Table size: 4" << endl;
		fout << "(4) 18:00 - 21:30 - Number of table: 20 Table size: 5" << endl;
		fout << "                      Winter Time" << endl;
		fout << "(5) 07:00 - 11:30 - Number of table: 15 Table size: 5" << endl;
		fout << "(6) 12:00 - 14:30 - Number of table: 20 Table size: 6" << endl;
		fout << "(7) 15:00 - 18:00 - Number of table: 15 Table size: 5" << endl;
		fout << "(8) 18:00 - 21:30 - Number of table: 25 Table size: 6" << endl;
		fout << endl;
		fout << "(9) Exit" << endl;
		fout << "Enter the choice: ";
		
		cin >> prog_choice;
		fout << prog_choice << endl;

		switch (prog_choice) {
		case 1: table_size = 4, num_of_table = 10;
			prog_choice = 9;
			break;
		case 2: table_size = 5, num_of_table = 20;
			prog_choice = 9;
			break;
		case 3: table_size = 4, num_of_table = 10;
			prog_choice = 9;
			break;
		case 4:  table_size = 5, num_of_table = 20;
			prog_choice = 9;
			break;
		case 5: table_size = 5, num_of_table = 15;
			prog_choice = 9;
			break;
		case 6: table_size = 6, num_of_table = 20;
			prog_choice = 9;
			break;
		case 7: table_size = 5, num_of_table = 15;
			prog_choice = 9;
			break;
		case 8: table_size = 6, num_of_table = 25;
			prog_choice = 9;
			break;
		default:
			cout << "Please enter choice 1 - 8 only." << endl;
			break;
		}
	} while (prog_choice != 9);
}

void Staffs_func() {

	cout << "Name: Chan Kam Chuen\tUID: 3035558197" << endl;
	cout << "Name: Ho Sui Ting\tUID: 3035569330" << endl;
	// ************************************************************
	fout << "Name: Chan Kam Chuen\tUID: 3035558197" << endl;
	fout << "Name: Ho Sui Ting\tUID: 3035569330" << endl;
	// ************************************************************
}

int main()
{
	int prog_choice, num;
	
/*	ifstream fin;
	fin.open("random_array.txt");
	if (fin.fail()) {
		cout << "Error! random_array.txt";
		exit(1);
	}*/

/*	for (int i = 0; i < MAX_VALUE; i++) {
		fin >> num;
		Waiting_list[i] = num;
	}
	fin.close();*/

	fout.open("Output.txt");
	if (fout.fail()) {
		cout << "Error! Output.txt";
		exit(1);
	}
	/*for (int i = 0; i < MAX_VALUE; i++) {
		Waiting_list[i] = (rand() % 6) + 1;
	}*/

	do {
		cout << endl;
		cout << "XYZ Restaurant -- Table management system" << endl;
		cout << "------------------------------------------" << endl;
		cout << "(1) Start" << endl;
		cout << "(2) Setting" << endl;
		cout << "(3) Staffs" << endl;
		cout << "(4) Exit" << endl;
		cout << "Enter the choice: ";
		// ************************************************************
		fout << "XYZ Restaurant -- Table management system" << endl;
		fout << "------------------------------------------" << endl;
		fout << "(1) Start" << endl;
		fout << "(2) Setting" << endl;
		fout << "(3) Staffs" << endl;
		fout << "(4) Exit" << endl;
		fout << "Enter the choice: ";
		// ************************************************************
		cin >> prog_choice;
		fout << prog_choice << endl;

		switch (prog_choice) {
		case 1: start_func(); break;
		case 2: setting_func(); break;
		case 3: Staffs_func(); break;
		case 4: break;
		default:
			cout << "Please enter choice 1 - 4 only." << endl;
			// ************************************************************
			fout << "Please enter choice 1 - 4 only." << endl;
			// ************************************************************
			break;
		}
	} while (prog_choice != 4);

	cout << "Program terminates. Good bye!" << endl;
	// ************************************************************
	fout << "Program terminates. Good bye!" << endl;
	// ************************************************************
	fout.close();
	delete Table_Occupied, Table_Available, Waiting_list;
	return 0;
}