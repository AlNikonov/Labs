#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

// Функция для чтения из файла в вектор символов
void readCharVector(std::fstream& fin, std::vector<char>& v) {
    while (!fin.eof() && fin.peek() != '\n') {
        v.push_back(fin.get());
    }
}

// Функция для вывода содержимого вектора
void printVector(std::vector<char>& v) {
    std::cout << "Vector read from file: ";
    if (v.size() < 40) {
        for (int i = 0; i < v.size(); ++i) std::cout << v[i];
    }
    else {
        for (int i = 0; i < 40; ++i) std::cout << v[i];
    }
    std::cout << '\n';
}

// Функция для подсчета количества символа в векторе
int countChar(std::vector<char>& v, char target) {
    int ans = 0;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == target) ++ans;
    }
    return ans;
}

// Функция для ввода и проверки на корректность ответа на вопрос о перезапуске программы
bool restartProgram() {
    std::cout << "\n\nDo you want to use the program again?\n";
    std::cout << "'0' = Yes\n'1' = No\n";
    std::cout << "Your answer: ";
    int answer;
    bool check = true;
    while (check) {
        std::cin >> answer;
        if (answer != 0 && answer != 1 || std::cin.fail() || std::cin.bad() || std::cin.peek() != '\n') {
            std::cout << "Incorrect answer, please enter another one: ";
            std::cin.clear(); // Возвращение потока ввода в начальное состояние
            std::cin.ignore(32767, '\n'); // Очистка потока ввода
        }
        else check = false;
    }
    std::cout << std::endl;
    return answer;
}

int main()
{
    bool exit = false;
    while (!exit) {
        std::fstream file("input.txt");
        // Проверка файла на существование
        if (!file) {
            std::cout << "File can't be opened!";
            return 0;
        }
        char target;

        std::vector<char> vec;
        readCharVector(file, vec);
        printVector(vec);
        file >> target;
        int char_time = 0;
        for (int i = 0; i < 10; ++i) {
            auto startChar = std::chrono::steady_clock::now(); // Время начала работы с массивом символов
            int ansChar = countChar(vec, target);
            std::ofstream foutChar("outputChar.txt");
            foutChar << ansChar;
            auto endChar = std::chrono::steady_clock::now(); // Время завершения работы с массивом символов
            auto diffChar = std::chrono::duration_cast<std::chrono::nanoseconds>(endChar - startChar);
            char_time += diffChar.count();
        }
        std::cout << "Average runtime: " << char_time/10 << " ns\n";


        file.seekp(std::ios_base::beg);

        std::string str;
        std::getline(file, str);
        std::cout << "\nString read from file: ";
        if (str.size() < 40) {
             std::cout << str << '\n';
        }
        else {
            for (int i = 0; i < 40; ++i) std::cout << str[i];
            std::cout << '\n';
        }
        file >> target;
        int string_time = 0;
        for (int i = 0; i < 10; ++i) {
            auto startStr = std::chrono::steady_clock::now(); // Время начала работы со строкой
            int ansStr = 0;
            for (int i = 0; i < str.size(); ++i) {
                if (str[i] == target) {
                    ++ansStr;
                }
            }
            std::ofstream foutString("outputString.txt");
            foutString << ansStr;
            auto endStr = std::chrono::steady_clock::now(); // Время завершения работы со строкой
            auto diffStr = std::chrono::duration_cast<std::chrono::nanoseconds>(endStr - startStr);
            string_time += diffStr.count();
        }
        std::cout << "Average runtime: " << string_time/10 << " ns\n\n";

        std::cout << "Ratio of char vector time to string time: " << double(char_time) / string_time;

        exit = restartProgram();
    }
    return 0;
}