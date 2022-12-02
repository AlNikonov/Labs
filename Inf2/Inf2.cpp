#include <iostream>
#include <string>

// Вариант 28

unsigned int getDays() {
    std::cout << "Enter the number of days: ";
    std::string days;
    while (true) {
        std::getline(std::cin, days);
        if (days.find_first_not_of("0123456789") != std::string::npos || days.empty()) {
            std::cout << "Incorrect number of days, please enter another one: ";
        } else {
            return std::stoul(days);
        }
    }
}

void numberTarSpoons(unsigned int days) {
    std::cout << "Total number of eaten tar spoons: ";
    double eaten_tar = 0;
    double tar_in_pot = 1;
    for (int i = 0; i < days; ++i) {
        tar_in_pot /= 2;
        eaten_tar += tar_in_pot;
        ++tar_in_pot;
    }
    std::cout << eaten_tar << '\n';
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
    std::cout << "Winnie-the-Pooh problem.\n";
    std::string restart_check = "Yes";
    while (restart_check == "Yes") {
        unsigned int days = getDays();
        numberTarSpoons(days);
        restart_check = restartProgram();
    }
    return 0;
}