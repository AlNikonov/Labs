#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <string>

// Функция для ввода и проверки на корректность размера вектора
int getVectorSize() {
    std::cout << "Enter vector size: ";
    std::string size;
    while (true) {
        std::getline(std::cin, size);
        if (size.find_first_not_of("0123456789") != std::string::npos || size.empty() || std::stoi(size) < 2) {
            std::cout << "Incorrect vector size, please enter another one: ";
        }
        else {
            return stoi(size);
        }
    }
}

// Функция для ввода и проверки на корректность количества выводимых элементов
int getOutputSize() {
    std::cout << "How many first elements of the vector should be output? ";
    std::string size;;
    while (true) {
        std::getline(std::cin, size);
        if (size.find_first_not_of("0123456789") != std::string::npos || size.empty() || std::stoi(size) < 1) {
            std::cout << "Incorrect number of elements, please enter another one: ";
        }
        else {
            return stoi(size);
        }
    }
}

// Функция для ввода и проверки способа заполнения вектора
int getMethod() {
    std::cout << "Choose how to fill the vector.\n";
    std::cout << "1 - Random values.\n2 - Reverse sorted random values.\n3 - Manual filling.\n";
    std::cout << "Your answer: ";
    std::string method;
    while (true) {
        std::getline(std::cin, method);
        if (method != "1" && method != "2" && method != "3") {
            std::cout << "Incorrect method, please enter another one: ";
        }
        else {
            return std::stoi(method);
        }
    }
}

// Функция для ввода и проверки на корректность элементов вектора при ручном заполнении
int getNum(int i) {
    std::cout << "Enter " << i+1 << " element: ";
    std::string num;
    while (true) {
        std::getline(std::cin, num);
        if (num.find_first_not_of("0123456789") != std::string::npos || num.empty()) {
            std::cout << "Incorrect vector size, please enter another one: ";
        }
        else {
            return stoi(num);
        }
    }
}

// Функция для вывода элементов вектора в консоль
void printVectorElements(std::vector<int>& vec, int num, int size) {
    for (int i = 0; i < ((num <= size) ? (num) : (size)); ++i) {
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';
}

// Функция для сортировки вектора пузырьком
void bubbleSort(std::vector<int>& vec, int size, int num, double& bubble_time) {
    std::cout << "\nBubble sort.\n";
    std::cout << "Before sort: ";
    printVectorElements(vec, num, size); // Выводим вектор до сортировки
    auto start = std::chrono::steady_clock::now(); // Время начала сортировки
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                int temp = vec[j + 1];
                vec[j + 1] = vec[j];
                vec[j] = temp;
            }
        }
    }
    auto end = std::chrono::steady_clock::now(); // Время завершения сортировки
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    bubble_time = diff.count();
    std::cout << "After sort:  ";
    printVectorElements(vec, num, size); // Выводим вектор после сортировки
    std::cout << "Runtime: " << bubble_time << " ns\n";
}

// Функция для сортировки библиотечным алгоритмом
void libSort(std::vector<int>& vec, int size, int num, double& lib_time) {
    std::cout << "\nLibrary sort.\n";
    std::cout << "Before sort: ";
    printVectorElements(vec, num, size); // Выводим вектор до сортировки
    auto start = std::chrono::steady_clock::now(); // Время начала сортировки
    std::sort(vec.begin(), vec.end());
    auto end = std::chrono::steady_clock::now(); // Время завершения сортировки
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    lib_time = diff.count();
    std::cout << "After sort:  ";
    printVectorElements(vec, num, size); // Выводим вектор после сортировки
    std::cout << "Runtime: " << lib_time << " ns\n";
}

// Функция для заполнения вектора рандомными числами
void fillVector(std::vector<int>& vec, int size, int method) {
    switch (method) {
    case 1:
        for (int i = 0; i < size; ++i) {
            vec.push_back(std::rand() % 100);
        }
        break;
    case 2:
        for (int i = 0; i < size; ++i) {
            vec.push_back(std::rand() % 100);
        }
        std::sort(vec.begin(), vec.end(), std::greater<int>());
        break;
    case 3:
        for (int i = 0; i < size; ++i) {
            int num = getNum(i);
            vec.push_back(num);
        }
        break;
    }
}

// Функция для ввода и проверки на корректность ответа на вопрос о перезапуске программы
std::string restartProgram() {
    std::cout << "Do you want to use the program again?\n";
    std::cout << "Yes/No\n";
    std::cout << "Your answer: ";
    std::string answer;
    while (true) {
        std::getline(std::cin, answer);
        if (answer != "Yes" && answer != "No") {
            std::cout << "Incorrect answer, please enter another one: ";
        }
        else {
            std::cout << "\n\n";
            return answer;
        }
    }
}

// Функция для сравнения времени сортировок
void compareSorts (double bubble_time, double lib_time) {
    if (bubble_time > lib_time) {
        std::cout << "\nLibrary sort is " << bubble_time / lib_time << " times faster.\n\n";
    }
    else if (lib_time > bubble_time) {
        std::cout << "\nBubble sort is " << lib_time / bubble_time << " times faster.\n\n";
    }
    else {
        std::cout << "\nSorting time is the same.\n\n";
    }
}

int main() {
    std::srand(std::time(nullptr));
    std::string exit_check = "Yes";
    while (exit_check == "Yes") {
        int size = getVectorSize(); // Вводим размер вектора
        int num = getOutputSize(); // Вводим количество элементов для вывода
        std::vector<int> vec1;
        int vector_fill_method = getMethod();
        fillVector(vec1, size, vector_fill_method); // Заполняем вектор
        std::vector<int> vec2(vec1); // Создаем копию заполненного вектора
        double bubble_time = 0;
        bubbleSort(vec1, size, num, bubble_time); // Сортировка пузырьком
        double lib_time = 0;
        libSort(vec2, size, num, lib_time); // Сортировка библиотечным алгоритмом
        compareSorts(bubble_time, lib_time); // Сравнение времени работы алгоритмов
        exit_check = restartProgram(); // Вопрос о перезапуске программы
    }
}