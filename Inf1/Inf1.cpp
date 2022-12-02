#include <iostream>
#include <string>

// Вариант 8

unsigned int getYear() {
    std::string year;
    while (true) {
        std::getline(std::cin, year);
        if (year.find_first_not_of("0123456789") != std::string::npos || year.empty()) {
            std::cout << "Incorrect year, please enter another one: ";
        } else {
            return std::stoul(year);
        }
    }
}

bool isLeap(unsigned int year) {
    return !(year % 4) && (year % 100) || !(year % 400);
}

unsigned int numberOfLeap(unsigned int start, unsigned int final) {
    unsigned int num = 0;
    for (start; start <= final; ++start) {
        if (isLeap(start)) {
            ++num;
        }
    }
    return num;
}

std::string restartProgram() {
    std::cout << "Do you want to use the program again?\n";
    std::cout << "Yes/No\n";
    std::cout << "Your answer: ";
    std::string answer;
    while (true) {
        std::getline(std::cin, answer);
        if (answer != "Yes" && answer != "No") {
            std::cout << "Incorrect answer, please enter another one: ";
        } else {
            std::cout << '\n';
            return answer;
        }
    }
}

int main() {
    std::cout << "The number of leap years on a time interval.\n";
    std::string restart_check = "Yes";
    while (restart_check == "Yes") {
        std::cout << "Enter a start year: ";
        unsigned int start_year = getYear();
        std::cout << "Enter a final year: ";
        unsigned int final_year = getYear();
        std::cout << "The number of leap years: " << numberOfLeap(start_year, final_year) << '\n';
        restart_check = restartProgram();
    }
    return 0;
}
