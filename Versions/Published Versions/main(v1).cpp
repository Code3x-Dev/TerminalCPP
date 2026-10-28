/* 🄯 2026 Code 3-Dev. Open Source under copyleft terms. Attribution 
is legally required; failure to retain this credit constitutes a copyright violation. */


#define _CRT_SECURE_NO_WARNINGS  // Disable warnings for unsafe functions (like std::localtime)
#include <iostream>             // Input/output streams (std::cout)
#include <string>              // String data type
#include <cstdlib>            // General utilities (std::exit)
#include <chrono>            // Time durations
#include <thread>           // Thread support and sleeping
#include <ctime>           // C-style time functions


//--Trigger CMDS--//

void showHelp();
void showTime();
void Exit();
void Clear();
void Pi();
void Ping();
void About();
void Echo(const std::string& cmd);
void handleInvalidCommand(const std::string& cmd);

const std::string REDtxt = "\033[31m";            // Color Red
const std::string ORANGEtxt = "\033[38;5;214m";  //Color Orange
const std::string BLUEtxt = "\033[34m";         // Color Blue
const std::string RESET = "\033[0m";           // Normal Color
const std::string Yellowtxt = "\033[33m";


//--Text Color--//

//---Word Trigger--//

int main() {



	std::string cmd;
	std::cout << ORANGEtxt << R"(
    _ _ _ _____ _     _____ _____ _____ _____   _____ _____   _____ _____ ____  __  __ ___ _   _     _    _
   | | | | ____| |   |     |     |     | ____| |_   _|     | |_   _| ____|  _ \|  \/  |_ _| \ | |   / \  | |
   | | | |  _| | |   |  ___|  |  | | | |  _| |   | | |  |  |   | | |  _| | |_) | |\/| || ||  \| |  / _ \ | |
   |     | |___| |---|  \__|  |  | | | | |___|   | | |  |  |   | | | |___|  _  | |  | || || |\  | / ___ \| |___
   |_____|_____|_____|_____|_____|_|_|_|_____|   |_| |_____|   |_| |_____|_| \_\_|  |_|___|_| \_\/_/   \_\_____|

)";
	std::cout << ORANGEtxt << "                                   >> Use /help for a list of Commands <<\n\n";  // radnom spaces to correcly line this up with "Welcome to Terminal"
/* All Command Triggers made using a slash or /. Accual Command Functions below int main().
 Some Commands use void<VaribleHere>(const std::string& cmd) thats so you can connect functions utside of int main()*/
  while (true) {

		std::getline(std::cin, cmd);

		// FIX: If the user just pressed Enter, skip everything else and start the loop over
		if (cmd.empty()) {
			continue;
		}

		if (cmd == "/help" || cmd == "/Help") {
			showHelp();
		}
		else if (cmd == "/ping" || cmd == "/Ping") {
			Ping();
		}
		else if (cmd == "/time" || cmd == "/Time") {
			showTime();
		}
		else if (cmd == "/clear" || cmd == "/Clear" || cmd == "/clr" || cmd == "/Clr") {
			Clear();
		}
		else if (cmd == "exit" || cmd == "Exit") {
			Exit();
		}
		else if (cmd == "/pi" || cmd == "/Pi") {
			Pi();
		}
		else if (cmd.rfind("/echo ", 0) == 0 || cmd.rfind("/Echo ", 0) == 0) { // 0 makes sure that the first word is echo
			Echo(cmd);
		}
		else if (cmd == "/about" || cmd == "/About") {
			About();
		}
		else {
			handleInvalidCommand(cmd);
		}

	}

}

//--CMD Functions--//
/* All Command Functions Once Trigger. Some use void<VaribleHere>(const std::string& cmd) 
to connect functions under int main */

void showHelp() {
	std::cout << "\n--- Available Commands ---\n";
	std::cout << "/help - Shows this help menu\n\n";
	std::cout << "/ping - Is the Terminal Responding?\n\n";
	std::cout << "/time - Shows your device's current time\n\n";
	std::cout << "/pi - Shows some Digits of Pi\n\n";
	std::cout << "/echo <Words Here> - Repeats your text to the Terminal (You don't use <>)\n\n";
	std::cout << "/clear | /clr - Clears the Termianl\n\n";
	std::cout << "/about - Shows info about the Terminal\n\n";
	std::cout << "exit - exits the terminal\n\n";

}

void Ping() {
	std::cout << "Pong!\n";
}

void showTime() {
	std::time_t currentTime = std::time(nullptr);
	std::cout << "Current Time: \n" << std::asctime(std::localtime(&currentTime));
}

void Echo(const std::string& cmd) {
	std::string message = cmd.substr(6); // Removes /echo and just prints what you type.
	std::cout << message << "\n";
}

void Clear() {
	std::cout << "Clearing Termianl...\n";

	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cout << "\033[2J\033[1;1H";

	std::cout << ORANGEtxt << R"(
    _ _ _ _____ _     _____ _____ _____ _____   _____ _____   _____ _____ ____  __  __ ___ _   _     _    _
   | | | | ____| |   |     |     |     | ____| |_   _|     | |_   _| ____|  _ \|  \/  |_ _| \ | |   / \  | |
   | | | |  _| | |   |  ___|  |  | | | |  _| |   | | |  |  |   | | |  _| | |_) | |\/| || ||  \| |  / _ \ | |
   |     | |___| |---|  \__|  |  | | | | |___|   | | |  |  |   | | | |___|  _  | |  | || || |\  | / ___ \| |___
   |_____|_____|_____|_____|_____|_|_|_|_____|   |_| |_____|   |_| |_____|_| \_\_|  |_|___|_| \_\/_/   \_\_____|

)";
	std::cout << ORANGEtxt << "                                 >> Use /help for a list of Commands <<\n\n"; //Reprint for when you clear Terminal
}

void Pi() {
	std::cout << "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091\n";
}

void About() {
	std::cout << REDtxt << "Made by Code3x-Dev" << RESET << ORANGEtxt;
	std::cout << Yellowtxt << "||Click \033]8;;https://github.com/Code3x-Dev/TerminalCPP\033\\Here\033]8;;\033\\ For Github Page||"; // Link to Github Page (only works on some devices)
	std::cout << BLUEtxt << "Version 0.3\n" << RESET << ORANGEtxt;
}

void Exit() {
	std::cout << "Exiting in 3\n";

	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::cout << "2\n";

	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::cout << "1\n";

	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::exit(0);
}

void handleInvalidCommand(const std::string& cmd) {  // Used to copy what you invalid command you wrote and say <invalidCommand> is not a know command
	std::cout << cmd << " Is Not a known Command\n";
	std::cout << "Use /help for a List of Commands\n\n";
}
