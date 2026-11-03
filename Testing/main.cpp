/* WIP Username and Password System (adding in a later version) 
will include fully functioning local users and memory */


#include <iostream>
#include <string>
#include <chrono>
#include <thread>

    int main() {

    std::string username;
    std::string tried_username;
    
    std::string password;
    std::string tried_password;
    
    std::cout << "Enter a Username\n\n";
    std::cin >> username;
    std::cout << std::endl;
    
    
    std::cout << "Create a Password\n\n";
    std::cin >> password;
    std::cout << std::endl;
    
    std::cout << "\033[2J\033[1;1H"; 
    
while (true) {
    
    std::cout << "Enter Username\n\n";
    std::cin >> tried_username;
    std::cout << std::endl;
    
    std::cout << "Enter Password\n\n";
    std::cin >> tried_password;
    std::cout << std::endl;
        
    if (username == tried_username && password == tried_password) {
            break;
    }
    else {
        std::cout << "Incorect Username or Password\n\n";
    }
    
}

}
