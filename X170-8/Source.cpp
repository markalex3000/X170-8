// X170-8	Mark R. Alexieff	2/20/2017
// Programs reads and stores a series of integers and then computes the sum of the first N integeres
// Input: Ask for the number of inetgers to sum
// Input: a series of input values - '|' indicates end of input
//
// Output: "The sum of the first N integers (num1, num2, num3) is SUM.
// Repeat until user says no mas
//
// Error conditions to check for:
// 1. User tries to input non-integers
// 2. User asks to sum more numbers than there are in the vector.
// 3. Add if the SUM cannot be represented as an int.  MAX_INT = 2147483647  MIN_INT = -2147483648

// Start standard opening - test change

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <exception>

using namespace std;

inline void keep_window_open() { 
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	char ch; cin >> ch; }

inline void simple_error(string s)	// write ``error: s and exit program
{
	cerr << "error: " << s << '\n';
	keep_window_open();		// for some Windows environments
	exit(1);
}

bool yes_no(string s) {
	char response{ 'X' };
	cout << s << " (y/n): ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin >> response;
	switch (response)
	{
	case 'y':
		return true;
	case 'n':
		return false;
	default:
		return false;
	}
};

//Functions
int get_number_list(vector<int> & nl);
bool out_number_list(vector<int> & nl);
int do_the_sum(vector<int> & nl, int c);
class Addition_overflow {};


int main() {
	vector<int> number_list;
	int number_to_sum{ 0 };
	int val_count{ 0 };
	bool gp_return{ true };

	
	do {

		if (number_list.size() != 0) number_list.clear();

		try {
			cin.exceptions(ios_base::badbit | ios_base::failbit);

			cout << "\nPlease enter the numbers of values you want to sum: ";
			cin >> number_to_sum;

			cout << "\nEnter the values, '|' to end: ";
			val_count = get_number_list(number_list);
			gp_return = out_number_list(number_list);

			if (number_to_sum > number_list.size()) cout << "\nmain: number to sum is too large.\n";
			else {
				cout << "\nThe sum of the first " << number_to_sum << " numbers " << "( ";
				for (int i = 0; i < number_to_sum; ++i) cout << number_list[i] << " ";
				cout << ") is: " << do_the_sum(number_list, number_to_sum) << "\n";
			}
		}
		catch (exception& e) {
			cerr << "error: " << e.what() << "\n";
			simple_error("Caught the exception");
			return 1;
		}
		catch (Addition_overflow) {
			cerr << "error: Caught Addition_overflow\n";
			simple_error("Caught another exception");

		}
	
	} while (yes_no("\nWould you like to go again? "));
}

int get_number_list(vector<int>& nl)
{
	int count{ 0 };
	int temp{ 0 };
	char test{ ' ' };
	cin >> test;
	while (test != '|') {
		cin.putback(test);
		if (cin >> temp) {
			count += 1;
			nl.push_back(temp);
			cin >> test;
		}
		else simple_error("get_number_list: bad input...");
	}
	return count;
}

bool out_number_list(vector<int>& nl)
{
	if (nl.size() == 0) {
		cout << "out_number_list: There are not numbers in the list. \n";
		return false;
	}
	else {
		for (int i = 0; i < nl.size(); ++i) {
			if (i % 10 == 0) cout << "\n";
			cout << nl[i] << "\t";
		}
		return true;
	}
}

int do_the_sum(vector<int>& nl, int c)    // assumes c <= number of elements in nl - caller must check
{
	int the_sum{ 0 };
	float test{ 0 };
	bool okay_to_add{ false };

	for (int i = 0; i < c;++i) {
		// case 0: sum is 0 and nl[i] is positive
		// case 02: sum is O and nl[i] is negative  (both are okay cuz number list only has good numbers in it)
		okay_to_add = false;

		if (the_sum == 0) okay_to_add = true;

		// case 1: sum is positive and nl[i] is positive
		if (the_sum > 0 && nl[i] >= 0) {
			cout << INT_MAX << " the_sum = " << the_sum << "nl[i] = " << nl[i] << "\n";
			cout << "INT_MAX - the sum = " << INT_MAX - the_sum << "\n";
			if ((INT_MAX - the_sum) >= nl[i])  okay_to_add = true;
		}
		
		// case 2: sum is positive and nl[i] is negative (okay cux any nl[i] is within limits for ints
		if (the_sum > 0 && nl[i] < 0) okay_to_add = true;

		// case 3: sum is negative and nl[i] is negative
		if (the_sum < 0 && nl[i] < 0) {
			if (INT_MIN - the_sum <= nl[i]) okay_to_add = true;
		}

		// case 4: sum is negative and nl[i] is positive
		if (the_sum < 0 && nl[i] > 0) okay_to_add = true;

		if (okay_to_add) {
			the_sum += nl[i];
			cout << "\n--- Int sum is: " << the_sum << "\n";
		}
		else throw(Addition_overflow{});
	}
	return the_sum;
}

