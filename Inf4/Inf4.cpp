#include <iostream>
#include <fstream>
#include <string>

bool restartProgram() {
	std::cout << "Do you want to use the program again? (Yes/No)\n";
	std::cout << "Your answer: ";
	std::string answer;
	while (true) {
		std::getline(std::cin, answer);
		if (answer != "Yes" && answer != "No") {
			std::cout << "Incorrect answer, please enter another one: ";
		}
		else {
			std::cout << "\n\n";
			return answer == "Yes";
		}
	}
}

std::string getCorrectFilename() {
	std::cout << "Please enter a filename: ";
	while (true) {
		std::string filename;
		std::getline(std::cin, filename);
		if (filename.find_first_of("+=[]:*?;«,/\\<>|") != std::string::npos || filename.find(".txt") != filename.length() - 4) {
			std::cout << "Incorrect filename, please enter another one: ";
		}
		else {
			return filename;
		}
	}
}

void findSubstrInFile(std::fstream& file) {
	std::cout << "Input a string: ";
	std::string target;
	std::getline(std::cin, target);
	std::string current_string;
	int counter = 0;
	while (file.peek() != EOF) {
		std::getline(file, current_string);
		++counter;
		std::size_t index = current_string.find(target);
		if (index != std::string::npos) {
			std::cout << "Line #" << counter << ":\n" << current_string << '\n';
			return;
		}
	}
	std::cout << "The entered substring is not present in the file.\n";
}

int main() {
	do {
		std::fstream file;
		do {
			file.open(getCorrectFilename());
			if (!file.is_open()) { std::cout << "File can't be opened, please try again.\n"; };
		} while (!file.is_open());
		findSubstrInFile(file);
		file.close();
	} while (restartProgram());
	return 0;
}