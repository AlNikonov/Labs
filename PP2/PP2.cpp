#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

// Структура, хранящая в себе результаты вычислений на определнной итерации
struct iteration { long double An = 0, Sn = 0, En = 0, tempAn = 0; };

double getParameterX() {
    std::cout << "Enter parameter x: ";
    double x;
    bool check = true;
    while (check) {
        std::cin >> x;
        if (x < -1 || x >= 1 || std::cin.fail() || std::cin.bad() || std::cin.peek() != '\n') {
            std::cout << "Incorrect parameter x, please enter another one: ";
            std::cin.clear(); // Возвращение потока ввода в начальное состояние
            std::cin.ignore(32767, '\n'); // Очистка потока ввода
        }
        else check = false;
    }
    return x;
}

long double getParameterA() {
    std::cout << "Enter parameter a: ";
    long double a;
    bool check = true;
    while (check) {
        std::cin >> a;
        if (std::cin.fail() || std::cin.bad() || std::cin.peek() != '\n') {
            std::cout << "Incorrect parameter a, please enter another one: ";
            std::cin.clear(); // Возвращение потока ввода в начальное состояние
            std::cin.ignore(32767, '\n'); // Очистка потока ввода
        }
        else check = false;
    }
    return a;
}

// Функция, отвечающая за ввод и проверку на корректность ответа пользователя на вопрос о перезапуске
// Возвращает ответ, в случае если он корректный, иначе - просит ввести другое значение
bool answerValidation() {
    int answer;
    std::cin >> answer;
    if (answer != 0 && answer != 1 || std::cin.fail() || std::cin.bad() || std::cin.peek() != '\n') {
        std::cout << "Incorrect answer, please enter another one: ";
        std::cin.clear(); // Возвращение потока ввода в начальное состояние
        std::cin.ignore(32767, '\n'); // Очистка потока ввода
        answerValidation();
    }
    else {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        return answer;
    }
}

iteration calculateIteration(std::vector<iteration>& v, int n, double x) {
    iteration current_iteration;
    int i = v.size() - 1;
    current_iteration.tempAn = v[i].tempAn + (1. / n);
    current_iteration.An = current_iteration.tempAn * std::pow(x, (n + 1)) / (n + 1); // Подсчет текущего элемента
    current_iteration.Sn = v[i].Sn + current_iteration.An; // Подсчет текущей суммы
    current_iteration.En = std::abs((current_iteration.tempAn + 1. / (n + 1)) * std::pow(x, (n + 2)) / (n + 2) / current_iteration.Sn); // Подсчет погрешности
    v.push_back(current_iteration);
    return current_iteration;
}

void printIteration(iteration& current_iteration, int n) {
    std::cout << "n = " << std::setw(6) << n << " | An = " << std::setw(12) << current_iteration.An << " | Sn = " << std::setw(12) << 2 * current_iteration.Sn << " | En = " << std::setw(12) << current_iteration.En << std::endl;
}

void printHeader(bool f) {
    if (f) std::cout << "The following values are taken from previous calculations.\n" << "n" << std::setw(14) << "| An" << std::setw(20) << "| Sn" << std::setw(21) << " | En\n";
    else std::cout << "The following values are new.\n" << "n" << std::setw(14) << "| An" << std::setw(20) << "| Sn" << std::setw(21) << " | En\n";
}

int main()
{
    bool exit_check = false;
    double previous_x = -5;
    std::vector<iteration> calculated_iterations;
    while (!exit_check) {
        iteration current_iteration;
        double x = getParameterX();
        if (x == previous_x) {
            long double a = getParameterA();
            if (a == long(a)) {
                int size = calculated_iterations.size();
                if (a >= size) {
                    printHeader(true);
                    for (int i = 1; i < size; ++i) printIteration(calculated_iterations[i], i);
                    printHeader(false);
                    current_iteration.tempAn = calculated_iterations[size - 1].tempAn;
                    for (int n = size; n - 1 < a; ++n) {
                        current_iteration = calculateIteration(calculated_iterations, n, x);
                        printIteration(current_iteration, n);
                    }
                }
                else {
                    printHeader(true);
                    for (int i = 1; i <= a; ++i) printIteration(calculated_iterations[i], i);
                }
            }
            else { // Старый параметр х и новый ДРОБНЫЙ параметр а
                int size = calculated_iterations.size();
                if (calculated_iterations[size - 1].En >= a) { // Если введенная погрешность еще не достигнута
                    printHeader(true);
                    for (int i = 1; i < size; ++i) printIteration(calculated_iterations[i], i);
                    printHeader(false);
                    current_iteration.tempAn = calculated_iterations[size - 1].tempAn;
                    int n = size;
                    do {
                        current_iteration = calculateIteration(calculated_iterations, n, x);
                        printIteration(current_iteration, n);
                        ++n;
                    } while (calculated_iterations[calculated_iterations.size() - 1].En >= a);
                }
                else { // Если введенная погрешность уже посчитана
                    printHeader(true);
                    int i = 1;
                    do {
                        printIteration(calculated_iterations[i], i);
                        ++i;
                    } while (calculated_iterations[i - 1].En >= a);
                }
            }
        } else {
            calculated_iterations.clear();
            iteration zero_iteration;
            calculated_iterations.push_back(zero_iteration);
            long double a = getParameterA();
            std::cout << "n" << std::setw(14) << "| An" << std::setw(20) << "| Sn" << std::setw(21) << " | En\n";
            // Если параметр a - количество итераций
            if (a == long(a)) {
                for (int n = 1; n <= a; ++n) {
                    current_iteration = calculateIteration(calculated_iterations, n, x);
                    printIteration(current_iteration, n);
                }
            }
            else { // Если параметр а - необходимая погрешность
                int n = 1; // Номер элемента последовательности
                do {
                    current_iteration = calculateIteration(calculated_iterations, n, x);
                    printIteration(current_iteration, n);
                    ++n;
                } while (current_iteration.En >= a);
            }
        }
        previous_x = x;
        // Вопрос о перезапуске программы
        std::cout << "Do you want to use the program again?\n" << "'0' = Yes\n'1' = No\n";
        exit_check = answerValidation();
        std::cout << "\n\n";
    }
    return 0;
}