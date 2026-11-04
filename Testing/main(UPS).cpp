/* 🄯 2026 Code3x-Dev. Open Source under copyleft terms. Attribution 
is legally required; failure to retain this credit constitutes a copyright violation. */


#define _CRT_SECURE_NO_WARNINGS  // Disable warnings for unsafe functions (like std::localtime)
#include <iostream>             // Input/output streams (std::cout)
#include <string>              // String data type
#include <cstdlib>            // General utilities (std::exit)
#include <chrono>            // Time durations
#include <thread>           // Thread support and sleeping
#include <ctime>           // C-style time functions
#include <fstream>
#include <limits>


unsigned long hashPassword(const std::string& str);
void registerUser();
bool loginUser(std::string& loggedInUser); 
void currentUser(const std::string& username);


const std::string REDtxt = "\033[31m";            // Color Red
const std::string ORANGEtxt = "\033[38;5;214m";  //Color Orange
const std::string BLUEtxt = "\033[34m";         // Color Blue
const std::string RESET = "\033[0m";           // Normal Color
const std::string Yellowtxt = "\033[33m";

// A simple, classic cryptographic hashing function (DJB2)
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
        std::cout << "\nAccount saved securely to users.txt!\n\n";
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
            std::cout << "\nLogin Successful! Welcome back, " << activeUser << "\n";
            break;
        } else {
            std::cout << "\nIncorrect Username or Password. Try again.\n\n";
        }
    }

    // FIXED: Clear the trailing '\n' out of the buffer so std::getline works next
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
}
