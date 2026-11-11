/* 🄯 2026 Code3x-Dev. Open Source under copyleft terms. Attribution
is legally required; failure to retain this credit constitutes a copyright violation. */

#define _CRT_SECURE_NO_WARNINGS  // Disable warnings for "unsafe" functions (like std::localtime)
#include <iostream>             // Input/output streams (std::cout)
#include <string>              // String data type
#include <cstdlib>            // General utilities (std::exit)
#include <chrono>            // Time durations
#include <thread>           // Thread support and sleeping
#include <ctime>           // C-style time functions
#include <fstream>
#include <limits>
#include <vector>        // Added for command history storage


//--Trigger CMDS--//

void showHelp();
void showTime();
void Calculator();
void Calcinfo();
void Exit();
void Clear();
void Pi();
void Ping();
void About();
void Logout();
void ShowHistory(const std::vector<std::string>& history);
void Print();
void Echo(const std::string& cmd);
void handleInvalidCommand(const std::string& cmd);
unsigned long hashPassword(const std::string& str);
void registerUser();
bool loginUser(std::string& loggedInUser);
void currentUser(const std::string& username);


const std::string REDtxt = "\033[31m";            // Color Red
const std::string ORANGEtxt = "\033[38;5;214m";  //Color Orange
const std::string BLUEtxt = "\033[34m";         // Color Blue
const std::string RESET = "\033[0m";           // Normal Color (white)
const std::string Yellowtxt = "\033[33m";

// A simple, classic cryptographic hashing function (DJB2) Used to hash password varibles
unsigned long hashPassword(const std::string& str) {
	unsigned long hash = 5381;
	for (char c : str) {
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	}
	return hash;
}

// Function to handle creating a new account and appending it to the file
void registerUser() {
	std::string username;
	std::string password;

	std::cout << "=== Register New Account ===\n";
	std::cout << "Enter a Username: ";
	std::cin >> username;

	std::cout << "Create a Password: ";
	std::cin >> password;

	unsigned long hashedPassword = hashPassword(password);
	std::ofstream outFile("users.txt", std::ios::app);

	if (outFile.is_open()) {
		outFile << username << " " << hashedPassword << "\n";
		outFile.close();
		std::cout << "\nAccount Saved Securely!\n\n";
	} else {
		std::cout << "\nError: Could not open file to save user.\n\n";
	}
}

// Function to handle logging in
bool loginUser(std::string& loggedInUser) {
	std::string tried_password;
	std::string fileUser;
	unsigned long fileHash;
	bool loginSuccessful = false;

	std::cout << "=== Login Screen ===\n";
	std::cout << "Enter Username: ";
	std::cin >> loggedInUser;


	std::cout << "Enter Password: ";
	std::cin >> tried_password;

	unsigned long triedHash = hashPassword(tried_password);
	std::ifstream inFile("users.txt");

	if (inFile.is_open()) {
		while (inFile >> fileUser >> fileHash) {
			if (fileUser == loggedInUser && fileHash == triedHash) {
				loginSuccessful = true;
				break;
			}
		}
		inFile.close();
	} else {
		std::cout << "\nNotice: No users found. Please register an account first.\n";
	}

	return loginSuccessful;
}

int main() {
	int choice = 0;

	std::cout << "1. Register a new user\n";
	std::cout << "2. Log in with an existing user\n";
	std::cout << "Choose an option (1 or 2): ";
	std::cin >> choice;
	std::cout << std::endl;

	if (choice == 1) {
		registerUser();
	}

	std::cout << "\033[2J\033[1;1H";

	// Create string in main to store who logged in
	std::string activeUser;

	// Loop until the user successfully logs in
	while (true) {
		if (loginUser(activeUser)) { // FIXED: Passed activeUser as the missing argument
			std::cout << "\033[2J\033[1;1H";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			
			std::cout << "\nLogin Successful! Welcome back, " << activeUser << "\n";
			break;
		} else {
			std::cout << "\nIncorrect Username or Password. Try again.\n\n";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << "\033[2J\033[1;1H";
		}
	}

	// FIXED: Clear the trailing '\n' out of the buffer so std::getline works next
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');



	std::string cmd;
	std::vector<std::string> cmdHistory;
	
	std::cout << ORANGEtxt << R"(
    _ _ _ _____ _     _____ _____ _____ _____   _____ _____   _____ _____ ____  __  __ ___ _   _     _    _
   | | | | ____| |   |     |     |     | ____| |_   _|     | |_   _| ____|  _ \|  \/  |_ _| \ | |   / \  | |
   | | | |  _| | |   |  ___|  |  | | | |  _| |   | | |  |  |   | | |  _| | |_) | |\/| || ||  \| |  / _ \ | |
   |     | |___| |---|  \__|  |  | | | | |___|   | | |  |  |   | | | |___|  _  | |  | || || |\  | / ___ \| |___
   |_____|_____|_____|_____|_____|_|_|_|_____|   |_| |_____|   |_| |_____|_| \_\_|  |_|___|_| \_\/_/   \_\_____|

)";
    
    std::cout << ORANGEtxt << "                                   >> Use  help for a list of Commands <<\n\n";  // radnom spaces to correcly line this up with "Welcome to Terminal"
    std::cout << ">";
    
/* All Command Triggers made using a slash or /. Accual Command Functions below int main().
 Some Commands use void<VaribleHere>(const std::string& <otherVarible>) thats so you 
                can connect functions outside and or in int main() */
  
  while (true) {

		std::getline(std::cin, cmd);
		std::cout << ">";

		// FIX: If the user just pressed Enter, skip everything else and start the loop over
		if (cmd.empty()) {
		    continue;
		}
		
		if (cmdHistory.empty() || cmdHistory.back() != cmd) {
            cmdHistory.push_back(cmd);
        }

		if (cmd == "help" || cmd == "Help") {
			showHelp();
		}
		else if (cmd == "ping" || cmd == "Ping") {
			Ping();
		}
		else if (cmd == "user" || cmd == "User" || cmd == "usr" || cmd == "Usr") {
		    currentUser(activeUser);
		}
		else if (cmd == "register" || cmd == "Register" || cmd == "rgsr" || cmd == "Rgsr") {
		    registerUser();
		}
		else if (cmd == "logout" || cmd == "Logout") {
		    Logout();
		}
		else if (cmd == "history" || cmd == "History") {
            ShowHistory(cmdHistory);
        }
        else if (cmd == "clearhistory" || cmd == "Clearhistory" || cmd == "clrhistory") {
            cmdHistory.clear();
            std::cout << Yellowtxt << "Command History Cleared.\n";
            std::cout << ">";
        }
		else if (cmd == "time" || cmd == "Time") {
			showTime();
		}
		else if (cmd == "calculator" || cmd == "Calculator" || cmd == "calc" || cmd == "Calc") {
		    Calculator();
		}
		else if (cmd == "calcinfo" || cmd == "Calcinfo") {
		    Calcinfo();
		}
		else if (cmd == "clear" || cmd == "Clear" || cmd == "clr" || cmd == "Clr") {
			Clear();
		}
		else if (cmd == "exit" || cmd == "Exit") {
			Exit();
		}
		else if (cmd == "pi" || cmd == "Pi") {
			Pi();
		}
		else if (cmd.rfind("echo ", 0) == 0 || cmd.rfind("Echo ", 0) == 0) { // 0 makes sure that the first word is echo
			Echo(cmd);
		}
		else if (cmd == "about" || cmd == "About") {
			About();
		}
		else {
			handleInvalidCommand(cmd);
		}

	}

}

//--CMD Functions--//
/* All Command Functions Once Triggered. Some use void<VaribleHere>(const std::string& <otherVarible>) 
                                        to connect functions*/

void showHelp() {
	std::cout << "\n--- Available Commands ---\n";
	std::cout << "help - Shows this help menu\n\n";
	std::cout << "ping - Is the Terminal Responding?\n\n";
	std::cout << "time - Shows your device's current time\n\n";
	std::cout << "calculator | calc - Do some Math!\n\n";
	std::cout << "calcinfo - Shows what each calculator symbol means\n\n";
	std::cout << "history - Show you Command History\n\n";
	std::cout << "clearhistory | clrhistory - Clears your Command History\n\n";
	std::cout << "pi - Shows some Digits of Pi\n\n";
	std::cout << "echo <Words Here> - Repeats your text to the Terminal (You don't use <>)\n\n";
	std::cout << "clear | clr - Clears the Termianl\n\n";
	std::cout << "user | usr Displays the Current User\n\n";
	std::cout << "register | rgsr creates a new user\n\n";
	std::cout << "logout - Logout of the current session\n\n";
	std::cout << "about - Shows info about the Terminal\n\n";
	std::cout << "exit - exits the terminal\n\n";
	std::cout << ">";


}

void Ping() {
	std::cout << "Pong!\n";
	std::cout << ">";

}

void currentUser(const std::string& username) {
    std::cout << "Current user: " << username << "\n";
    std::cout << ">";

}

void showTime() {
	std::time_t currentTime = std::time(nullptr);
	std::cout << "Current Time: \n" << std::asctime(std::localtime(&currentTime));
    std::cout << ">";
}

void Echo(const std::string& cmd) {
	std::string message = cmd.substr(5); // Removes echo and just prints what you type.
	std::cout << message << "\n";
	std::cout << ">";

}

void Logout() {
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "\033[2J\033[1;1H";	
    	int choice = 0;

	std::cout << "1. Register a new user\n";
	std::cout << "2. Log in with an existing user\n";
	std::cout << "Choose an option (1 or 2): ";
	std::cin >> choice;
	std::cout << std::endl;

	if (choice == 1) {
		registerUser();
	}

	std::cout << "\033[2J\033[1;1H";

	// Create string in main to store who logged in
	std::string activeUser;

	// Loop until the user successfully logs in
	while (true) {
		if (loginUser(activeUser)) { // FIXED: Passed activeUser as the missing argument
			std::cout << "\033[2J\033[1;1H";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			
			std::cout << "\nLogin Successful! Welcome back, " << activeUser << "\n";
			Print();
			break;
		} else {
			std::cout << "\nIncorrect Username or Password. Try again.\n\n";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << "\033[2J\033[1;1H";
		}
	}
}

void Clear() {
	std::cout << "Clearing Termianl...\n";

	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cout << "\033[2J\033[1;1H";
    Print();

}

void Print() {

	std::cout << ORANGEtxt << R"(
    _ _ _ _____ _     _____ _____ _____ _____   _____ _____   _____ _____ ____  __  __ ___ _   _     _    _
   | | | | ____| |   |     |     |     | ____| |_   _|     | |_   _| ____|  _ \|  \/  |_ _| \ | |   / \  | |
   | | | |  _| | |   |  ___|  |  | | | |  _| |   | | |  |  |   | | |  _| | |_) | |\/| || ||  \| |  / _ \ | |
   |     | |___| |---|  \__|  |  | | | | |___|   | | |  |  |   | | | |___|  _  | |  | || || |\  | / ___ \| |___
   |_____|_____|_____|_____|_____|_|_|_|_____|   |_| |_____|   |_| |_____|_| \_\_|  |_|___|_| \_\/_/   \_\_____|

)";
	std::cout << ORANGEtxt << "                                   >> Use  help for a list of Commands <<\n\n"; //Random spaces to line up with "Welcome to Terminal" probably and easier way to do this ``\_(ツ)_/``
	std::cout << ">";
}

void Pi() {
	std::cout << "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091\n";
	std::cout << ">";

}

void Calculator() {
    
    double num1, num2;
    char op;

    std::cout << "Enter first number: ";
    std::cin >> num1;

    std::cout << "Enter operator (+, -, *, /): ";
    std::cin >> op;

    std::cout << "Enter second number: ";
    std::cin >> num2;

    std::cout << "\nResult: ";
    switch (op) {
        case '+':
            std::cout << num1 << " + " << num2 << " = " << (num1 + num2) << "\n";
            break;
        case '-':
            std::cout << num1 << " - " << num2 << " = " << (num1 - num2) << "\n";
            break;
        case '*':
            std::cout << num1 << " * " << num2 << " = " << (num1 * num2) << "\n";
            break;
        case '/':
            // Prevent division by zero
            if (num2 == 0) {
                std::cout << "Error! Division by zero is undefined.\n";
            } else {
                std::cout << " " << num1 << " / " << num2 << " = " << (num1 / num2) << "\n";
            }
            break;
        default:
            std::cout << "Error! Invalid operator standard.\n";
            break;
    }
}

void Calcinfo() {
    std::cout << "* Multiplying\n\n";
    std::cout << "/ Dividing\n\n";
    std::cout << "+ Adding\n\n";
    std::cout << "- Subtracting\n\n";
    std::cout << ">";

}

void About() {
	std::cout << REDtxt << "Made by Code3x-Dev" << RESET << ORANGEtxt;
	std::cout << Yellowtxt << "||Click \033]8;;https://github.com/Code3x-Dev/TerminalCPP\033\\Here\033]8;;\033\\ For Github Page||"; // Link to Github Page (only works on some devices)
	std::cout << BLUEtxt << "Version 3.3\n" << RESET << ORANGEtxt;
	std::cout << ">";
}

void ShowHistory(const std::vector<std::string>& history) {
    std::cout << BLUEtxt << "--- Command History ---\n" << ORANGEtxt;
    for (size_t i = 0; i < history.size(); ++i) {
        std::cout << "  " << (i + 1) << ": " << history[i] << "\n";
    }
    std::cout << ">";
}

void Exit() {
	std::cout << "Exiting...\n";
	
	std::this_thread::sleep_for(std::chrono::seconds(3));

	std::exit(0);
}

void handleInvalidCommand(const std::string& cmd) {  // Used to copy what invalid command you wrote and say <invalidCommand> is not a know command
	std::cout << cmd << " Is Not a known Command\n";
	std::cout << "Use  help for a List of Commands\n\n";
	std::cout << ">";
}
