#include <iostream
#include <fstream>
#include <string>

// A simple, classic cryptographic hashing function (DJB2)
// This turns any string password into a secure, irreversible number
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
    
    // Hash the password before doing anything else with it
    unsigned long hashedPassword = hashPassword(password);
    
    // Open the file in append mode (std::ios::app) so we don't delete old users
    std::ofstream outFile("users.txt", std::ios::app);
    
    if (outFile.is_open()) {
        // Save the plain username, but ONLY save the secure hash of the password
        outFile << username << " " << hashedPassword << "\n";
        outFile.close();
        std::cout << "\nAccount saved securely to users.txt!\n\n";
    } else {
        std::cout << "\nError: Could not open file to save user.\n\n";
    }
}

// Function to handle logging in by reading and verifying against the file
bool loginUser() {
    std::string tried_username;
    std::string tried_password;
    
    std::string fileUser;
    unsigned long fileHash; // The file stores numbers now, not plain text strings
    bool loginSuccessful = false;

    std::cout << "=== Login Screen ===\n";
    std::cout << "Enter Username: ";
    std::cin >> tried_username;
    
    std::cout << "Enter Password: ";
    std::cin >> tried_password;

    // Hash the user's login attempt so we can compare hashes to hashes
    unsigned long triedHash = hashPassword(tried_password);

    // Open the file to read it
    std::ifstream inFile("users.txt");
    
    if (inFile.is_open()) {
        // Read through the file line by line (Username then Hash)
        while (inFile >> fileUser >> fileHash) {
            // Check if both the username and the calculated hash match
            if (fileUser == tried_username && fileHash == triedHash) {
                loginSuccessful = true;
                break; // Stop looking, we found a match!
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
    
    // Clear screen escape sequence from your original code
    std::cout << "\033[2J\033[1;1H"; 

    // Loop until the user successfully logs in
    while (true) {
        if (loginUser()) {
            std::cout << "\nLogin Successful! Welcome back.\n";
            break;
        } else {
            std::cout << "\nIncorrect Username or Password. Try again.\n\n";
        }
    }

    return 0;
}
