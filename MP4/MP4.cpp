#include <iostream>
#include <fstream>
#include <vector>

// Функция для чтения из файла в вектор символов
void readCharVector(std::fstream& fin, std::vector<char>& v) {
    while (!fin.eof() && fin.peek() != '\n') {
        v.push_back(fin.get());
    }
}

// Функция для аккуратного вывода содержимого вектора
void printVector(std::vector<char>& v) {
    if (v.size() < 40) {
        std::cout << "Vector read from file: ";
        for (int i = 0; i < v.size(); ++i) std::cout << v[i];
    }
    else {
        std::cout << "Vector is too big (" << v.size() << " elements), first 40 elements of vector: ";
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
        std::fstream file("input2.txt");
        // Проверка файла на существование
        if (!file) {
            std::cout << "File can't be opened!";
        }
        else {
            std::vector<char> vec;
            readCharVector(file, vec);
            printVector(vec);

            char target;
            file >> target;

            int ans = countChar(vec, target);
            std::cout << target << " : " << ans;

            std::ofstream fout("output.txt");
            fout << ans;
        }
        exit = restartProgram();
    }
    return 0;
}