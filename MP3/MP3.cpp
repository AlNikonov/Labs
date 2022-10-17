#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Функция для ввода и проверки на корректность размера вектора
int getVectorSize() {
    std::cout << "Enter vector size: ";
    int n;
    bool check = true;
    while (check) {
        std::cin >> n;
        if (n < 1 || std::cin.fail() || std::cin.bad() || std::cin.peek() != '\n') {
            std::cout << "Incorrect vector size, please enter another one: ";
            std::cin.clear(); // Возвращение потока ввода в начальное состояние
            std::cin.ignore(32767, '\n'); // Очистка потока ввода
        }
        else check = false;
    }
    return n;
}

// Функция для ввода и проверки на корректность количества выводимых элементов
int getOutputSize() {
    std::cout << "How many first elements of the vector should be output? ";
    int n;
    bool check = true;
    while (check) {
        std::cin >> n;
        if (n < 1 || std::cin.fail() || std::cin.bad() || std::cin.peek() != '\n') {
            std::cout << "Incorrect number of elements, please enter another one: ";
            std::cin.clear(); // Возвращение потока ввода в начальное состояние
            std::cin.ignore(32767, '\n'); // Очистка потока ввода
        }
        else check = false;
    }
    return n;
}

// Функция для сортировки вектора пузырьком
void bubbleSort(std::vector<int>& vec, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                int temp = vec[j + 1];
                vec[j + 1] = vec[j];
                vec[j] = temp;
            }
        }
    }
}

// Функция для заполнения вектора рандомными числами
void fillVector(std::vector<int>& vec, int size) {
    for (int i = 0; i < size; ++i) {
        vec.push_back(std::rand() % 100);
    }
}

// Функция для вывода элементов вектора в консоль
void printVectorElements(std::vector<int>& vec, int num, int size) {
    for (int i = 0; i < ((num <= size) ? (num) : (size)); ++i) {
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';
}

// Функция для ввода и проверки на корректность ответа на вопрос о перезапуске программы
bool restartProgram() {
    std::cout << "Do you want to use the program again?\n";
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

int main() {
    std::srand(std::time(nullptr));
    bool exit_check = false;
    while (!exit_check) {
        int size = getVectorSize(); // Вводим размер вектора
        int num = getOutputSize(); // Вводим количество элементов для вывода
        std::vector<int> vec;
        fillVector(vec, size); // Заполняем вектор
        std::cout << "Before sort: ";
        printVectorElements(vec, num, size); // Выводим вектор до сортировки
        bubbleSort(vec, size); // 
        std::cout << "After sort:  ";
        printVectorElements(vec, num, size); // Выводим вектор после сортировки
        exit_check = restartProgram(); // Вопрос о перезапуске программы
    }
}
