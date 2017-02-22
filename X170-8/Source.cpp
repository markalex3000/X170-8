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

// Start standard opening - test change

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

inline void keep_window_open() { char ch; cin >> ch; }

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



int main() {
	vector<int> number_list;
	int number_to_sum{ 0 };
	int val_count{ 0 };
	bool gp_return{ true };



	do {

		if (number_list.size() != 0) number_list.clear();
		
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
		cin >> temp;
		count += 1;
		nl.push_back(temp);
		cin >> test;
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
	for (int i = 0; i < c;++i) the_sum += nl[i];
	return the_sum;
}

