// Bea Calma
// July 29, 2025
// Cargo Transport Transaction System (C++) (Mini Project 7)


#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
#include<ctime>
#include <sstream>
using namespace std;

// Struct for Container Info
struct Container {
	double height, length, width, volume, baseCost, premiumCost;
	string packageLabel, deliveryMethodLabel, deliveryShort;
	int deliveryMethod; // 1-std, 2-ground, 3-air
	string estDelivery; // Date or text
};

// Function Prototypes
double CalVolume(double length, double width, double height);
void ProcessPayment(double total);
bool isValidLicense(const string& s);
string getDeliveryString(int method, double volume);
string getDeliveryDate(int method, string startDate);


int main()
{
	// New Header
	cout << "****East County Cargo Transport****" << endl << endl;
	cout << "Cashiering system 2.0" << endl;
	string date;
	cout << "Starting Transactions - date - ";
	getline(cin, date);
	cout << endl << endl;
	cout << "Starting at Transaction #1" << endl << endl;

	// Customer Name
	string custName;
	cout << "Enter Customer's name: ";
	getline(cin, custName);
	cout << endl << "Customer - " << custName << endl << endl;

	// Store Container Info for Receipt (removed function)
	vector<Container> containers;
	double containerTotal = 0.0;
	double premiumTotal = 0.0;
	int containerNum = 1;
	char addAnother;

	do {
		double length, width, height, volume;
		do { // Loops until a valid package volume is entered
			cout << "Enter dimensions for container #" << containerNum << " (in feet):" << endl;
			cout << "Height: ";
			cin >> height;
			cout << endl << "Length: ";
			cin >> length;
			cout << endl << "Width:  ";
			cin >> width;
			cout << endl;

			volume = CalVolume(length, width, height);

			if (volume > 65) {
				cout << "This package exceeds the 65 cubic foot limit. Please input again." << endl << endl;
			}

			else {
				cout << "Volume of container #" << containerNum << " is " << setprecision(0) << fixed <<
					volume << " cu ft" << endl;
			}


		} while (volume > 65);
		double baseCost = 0.0;
		string packageLabel;
		if (volume >= 0 && volume <= 15) {
			baseCost = (volume * 1.50);
			packageLabel = "Small Package ($1.50 per cu ft):  ";
		}
		else if (volume > 15 && volume <= 45) {
			baseCost = (volume * 2.50);
			packageLabel = "Medium Package ($2.50 per cu ft):  ";
		}
		else if (volume > 45 && volume <= 65) {
			baseCost = (volume * 3.00);
			packageLabel = "Large Package ($3.00 per cu ft):  ";
		}
		cout << setprecision(2) << fixed;
		cout << packageLabel << "$" << baseCost << endl << endl;


		// Delivery Method 
		cout << "How is this container to be shipped:" << endl << endl;
		cout << "(1) Standard - (one to two weeks) - No change to the price" << endl;
		cout << "(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot" << endl;

		if (volume < 30) // Only displays if volume is less than 30 cubic feet
			cout << "(3) Air - (1 to 2 business days) - Only applies to packages under 30 cubic feet - Extra $3.00 per cubic foot" << endl;
		cout << endl;

		int deliveryMethod;
		bool validKey = false; // Flag to check if a valid key is pressed
		double premiumDeliveryCost = 0.0; // Variable to store premium delivery cost
		string deliveryMethodLabel; // Variable to store delivery method label
		string deliveryShort;

		do {
			cout << "Delivery: ";
			cin >> deliveryMethod;
			cout << endl;

			if (deliveryMethod == 1) {
				deliveryMethodLabel = "Standard:";
				deliveryShort = "STD";
				premiumDeliveryCost = 0.0; // No extra cost for standard delivery
				validKey = true; // Valid key pressed
			}
			else if (deliveryMethod == 2) {
				deliveryMethodLabel = "Fast Ground ($1.50 per cu ft):";
				deliveryShort = "FG";
				premiumDeliveryCost = volume * 1.50; // Extra $1.50 per cubic foot
				validKey = true; // Valid key pressed
			}
			else if (deliveryMethod == 3 && volume < 30) {
				deliveryMethodLabel = "Air ($3.00 per cu ft):";
				deliveryShort = "AIR";
				premiumDeliveryCost = volume * 3.00; // Extra $3.00 per cubic foot
				validKey = true; // Valid key pressed
			}
			else if (deliveryMethod == 3 && volume >= 30) {
				cout << "Air delivery is only available for packages under 30 cubic feet." << endl;
			}
			else {
				cout << "Invalid selection. Please choose a valid delivery method." << endl;
			}
		} while (!validKey); // Loop until a valid key is pressed

		cout << deliveryMethodLabel << "  $" << premiumDeliveryCost << endl << endl;


		containerTotal += baseCost;
		premiumTotal += premiumDeliveryCost;

		// Option 1: Create a Container object and store it in the vector
		Container c;
		c.height = height;
		c.length = length;
		c.width = width;
		c.volume = volume;
		c.baseCost = baseCost;
		c.premiumCost = premiumDeliveryCost;
		c.packageLabel = packageLabel;
		c.deliveryMethodLabel = deliveryMethodLabel;
		c.deliveryMethod = deliveryMethod;
		c.deliveryShort = deliveryShort;

		// Option 2: Calculate estimated date
		c.estDelivery = getDeliveryDate(deliveryMethod, date);
		containers.push_back(c);

		// Display estimated delivery date
		cout << "Another container (y/n): ";
		cin >> addAnother;
		cout << endl;
		containerNum++;

	} while (addAnother == 'y' || addAnother == 'Y');
	double subTotal = containerTotal + premiumTotal;
	double salesTax = subTotal * 0.0775;
	double total = subTotal + salesTax;

	// Display Customer Receipt
	cout << endl << endl;
	cout << setw(59) << left << "Subtotal" << "$" << setw(9) << right << subTotal << endl;
	cout << setw(59) << left << "Sales Tax - 7.75%" << "$" << setw(9) << right << salesTax << endl << endl;
	cout << setw(59) << left << "Total" << "$" << setw(9) << right << total << endl << endl;

	// Payment
	ProcessPayment(total);

	// Receipt Section
	cout << endl << endl << "________________________________________________________________________" << endl << endl;
	cout << "East County Cargo Transport" << endl << endl;
	cout << "123 First Street\nEl Cajon, CA  92071" << endl << endl;
	cout << "Customer Receipt - " << date << endl << endl;
	cout << "Customer Name: " << custName << endl << endl;

	// Each container
	for (int i = 0; i < containers.size(); ++i) {
		cout << "Container #" << (i + 1) << " - " << containers[i].volume << " cu ft";
		cout << setw(36 - to_string((int)containers[i].volume).length()) << right << "$" << setw(9) << right << fixed << setprecision(2) << containers[i].baseCost << endl;
		cout << "Shipping: " << containers[i].deliveryShort << " - Est. Delivery - " << containers[i].estDelivery;
		cout << setw(31 - containers[i].deliveryShort.length() - containers[i].estDelivery.length()) << right << "$" << setw(9) << right << fixed << setprecision(2) << containers[i].premiumCost << endl << endl;
	}
	cout << setw(59) << left << "Subtotal" << "$" << setw(9) << right << subTotal << endl;
	cout << setw(59) << left << "Sales Tax - 7.75%" << "$" << setw(9) << right << salesTax << endl << endl;
	cout << setw(59) << left << "Total" << "$" << setw(9) << right << total << endl << endl;

	return 0;
}

// CalVolume function (definition)
double CalVolume(double length, double width, double height) {
	return length * width * height;
}

// ProcessPayment function (definition) 
void ProcessPayment(double total)
{
	int paymentMethod;
	double accepted = 0.0;
	string driversLicense; // Variable to store driver's license number
	char VMchoice; // Variable for Visa or Mastercard choice
	string cardpin; // Variable to store last four digits of card pin


	cout << "Payment (1. Cash, 2. Check, 3. Credit): ";
	cin >> paymentMethod;
	cout << endl;

	if (paymentMethod < 1 || paymentMethod > 3) {
		cout << "Invalid payment method. Please try again." << endl;
		return;
	}

	switch (paymentMethod) {
	case 1:
		// Cash
		cout << setw(59) << left << "Accepted:" << "$   ";
		cin >> accepted;

		if (accepted >= total) {
			double change = accepted - total;
			cout << setw(59) << left << "Change:" << "$" << setw(9) << right << fixed << setprecision(2) << change << endl;
		}
		else {
			cout << "Insufficient cash. Please try again." << endl;
		}
		break;

	case 2:
		// Check
		cout << setw(59) << left << "Enter Driver License No:"; // prompt and input on same line
		cin >> driversLicense;

		while (!isValidLicense(driversLicense)) {
			cout << "Invalid format. Please try again." << endl;
			cout << setw(59) << left << "Enter Driver License No:";
			cin >> driversLicense;
		}
		cout << setw(59) << left << "Accepted Check Payment:" << "$" << setw(9) << right << fixed << setprecision(2) << total << endl;
		break;

	case 3:
		// Credit Card
		cout << setw(59) << left << "Enter V for Visa or M for MasterCard: ";
		cin >> VMchoice;

		if (VMchoice == 'V' || VMchoice == 'v' || VMchoice == 'M' || VMchoice == 'm') {
			cout << setw(59) << left << "Enter Last Four Digits of Card:";
			cin >> cardpin;
			string cardType = (VMchoice == 'V' || VMchoice == 'v') ? "Visa" : "MasterCard";
			cout << setw(59) << left << "Accepted " + cardType + " ending in " + cardpin + " for the amount of:" << "$" << setw(9) << right << fixed << setprecision(2) << total << endl;
		}
		else {
			cout << "Invalid card type selection." << endl;
		}
		break;
	default:
		cout << "Invalid selection. Please try again." << endl;
		break;
	}
}

// Valid License function (definition)
bool isValidLicense(const string& s) {
	if (s.length() != 8) return false;
	if (!isupper(s[0])) return false;
	for (int i = 1; i < 8; ++i)
		if (!isdigit(s[i])) return false;
	return true;
}

// Delivery string for receipt
string getDeliveryString(int method, double volume) {
	if (method == 1)
		return "STD - Est. Delivery - 14 business days";
	else if (method == 2)
		return "FG - Est. Delivery - 5 business days";
	else if (method == 3 && volume < 30)
		return "AIR - Est. Delivery - 2 business days";
	return "";
}

// Calculate estimated delivery date (Option 2)
string getDeliveryDate(int method, string startDate) {
	int month = 0, day = 0, year = 0;
	char sep;
	istringstream iss(startDate);
	iss >> month >> sep >> day >> sep >> year;
	if (iss.fail() || month < 1 || month > 12 || day < 1 || day > 31 || year < 1900)
		return "Invalid Date";

	tm t = {};
	t.tm_year = year - 1900;
	t.tm_mon = month - 1;
	t.tm_mday = day;

	int daysToAdd = 0;
	if (method == 1)
		daysToAdd = 14;
	else if (method == 2)
		daysToAdd = 5;
	else if (method == 3)
		daysToAdd = 2;

	time_t raw = mktime(&t);
	if (raw == -1)
		return "Invalid Date";

	raw += daysToAdd * 86400; // 86400 seconds in a day

	tm f;
	localtime_s(&f, &raw); // Safe version for MSVC

	char buf[11];
	strftime(buf, sizeof(buf), "%m/%d/%Y", &f);
	return string(buf);
}


/*

****East County Cargo Transport****

Cashiering system 2.0
Starting Transactions - date - 05/28/2022


Starting at Transaction #1

Enter Customer's name: Jerry Lewis

Customer - Jerry Lewis

Enter dimensions for container #1 (in feet):
Height: 3

Length: 4

Width: 2

Volume of container #1 is 24 cu ft
Medium Package ($2.50 per cu ft):  $60.00

How is this container to be shipped:

(1) Standard - (one to two weeks) - No change to the price
(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot
(3) Air - (1 to 2 business days) - Only applies to packages under 30 cubic feet - Extra $3.00 per cubic foot

Delivery: 2

Fast Ground ($1.50 per cu ft):  $36.00

Another container (y/n): y

Enter dimensions for container #2 (in feet):
Height: 9

Length: 2

Width:  3

Volume of container #2 is 54 cu ft
Large Package ($3.00 per cu ft):  $162.00

How is this container to be shipped:

(1) Standard - (one to two weeks) - No change to the price
(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot

Delivery: 1

Standard:  $0.00

Another container (y/n): y

Enter dimensions for container #3 (in feet):
Height: 1

Length: 2

Width:  4

Volume of container #3 is 8 cu ft
Small Package ($1.50 per cu ft):  $12.00

How is this container to be shipped:

(1) Standard - (one to two weeks) - No change to the price
(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot
(3) Air - (1 to 2 business days) - Only applies to packages under 30 cubic feet - Extra $3.00 per cubic foot

Delivery: 3

Air ($3.00 per cu ft):  $24.00

Another container (y/n): n



Subtotal                                                   $   294.00
Sales Tax - 7.75%                                          $    22.79

Total                                                      $   316.79

Payment (1. Cash, 2. Check, 3. Credit): 1

Accepted:                                                  $   320.00
Change:                                                    $     3.21


________________________________________________________________________

East County Cargo Transport

123 First Street
El Cajon, CA  92071

Customer Receipt - 05/28/2022

Customer Name: Jerry Lewis

Container #1 - 24.00 cu ft                                 $    60.00
Shipping: FG - Est. Delivery - 06/02/2022                  $    36.00

Container #2 - 54.00 cu ft                                 $   162.00
Shipping: STD - Est. Delivery - 06/11/2022                 $     0.00

Container #3 - 8.00 cu ft                                  $    12.00
Shipping: AIR - Est. Delivery - 05/30/2022                 $    24.00

Subtotal                                                   $   294.00
Sales Tax - 7.75%                                          $    22.79

Total                                                      $   316.79

*/