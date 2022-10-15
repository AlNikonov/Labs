#include <iostream>
#include <cmath>
#include <iomanip>

// Функция, отвечающая за ввод и проверку на корректность параметра x
// Возвращает параметр x, в случае если он корректный, иначе - просит ввести другое значение
double xParameterValidation() {
    double x;
    std::cin >> x;
    if (x < -1 || x >= 1 || std::cin.fail() || std::cin.bad() || std::cin.peek() != '\n') {
        std::cout << "Incorrect parameter x, please enter another one: ";
        std::cin.clear(); // Возвращение потока ввода в начальное состояние
        std::cin.ignore(32767, '\n'); // Очистка потока ввода
        xParameterValidation();
    }
    else {
        return x;
    }
}

// Функция, отвечающая за ввод и проверку на корректность параметра a
// Возвращает параметр а, в случае если он корректный, иначе - просит ввести другое значение
long double aParameterValidation() {
    long double a;
    std::cin >> a;
    if (std::cin.fail() || std::cin.bad() || std::cin.peek() != '\n') {
        std::cout << "Incorrect parameter a, please enter another one: ";
        std::cin.clear(); // Возвращение потока ввода в начальное состояние
        std::cin.ignore(32767, '\n'); // Очистка потока ввода
        aParameterValidation();
    }
    else {
        return a;
    }
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
        return answer;
    }
}

int main()
{
    bool exit_check = false;
    while (!exit_check) {

        std::cout << "Enter parameter x: ";
        double x = xParameterValidation();
        std::cout << "Enter parameter a: ";
        long double a = aParameterValidation();

        std::cout << "n" << std::setw(14) << "| An" << std::setw(20) << "| Sn" << std::setw(21) << " | En\n";
        long double An = 0; // Текущий элемент последовательности
        long double Sn = 0; // Сумма n элементов последовательности
        long double tempAn = 0; // Вспомогательная переменная для подсчета суммы n элементов ряда 1/n
        long double En = 0; // Текущая погрешность

        // Если параметр a - количество итераций
        if (a == long(a)) {
            for (int n = 1; n <= a; ++n) {
                tempAn += (1. / n);
                An = tempAn * std::pow(x, (n + 1)) / (n + 1); // Подсчет текущего элемента
                Sn += An; // Подсчет текущей суммы
                En = std::abs((tempAn + 1. / (n + 1)) * std::pow(x, (n + 2)) / (n + 2) / Sn); // Подсчет погрешности
                std::cout << "n = " << std::setw(6) << n << " | An = " << std::setw(12) << An << " | Sn = " << std::setw(12) << 2 * Sn << " | En = " << std::setw(12) << En << std::endl;
            }
        }
        // Если параметр а - необходимая погрешность
        else {
            int n = 1; // Номер элемента последовательности
            do {
                tempAn += (1. / n);
                An = tempAn * std::pow(x, (n + 1)) / (n + 1); // Подсчет текущего элемента
                Sn += An; // Подсчет текущей суммы
                En = std::abs((tempAn + 1. / (n + 1)) * std::pow(x, (n + 2)) / (n + 2) / Sn); // Подсчет погрешности
                std::cout << "n = " << std::setw(6) << n << " | An = " << std::setw(12) << An << " | Sn = " << std::setw(12) << 2 * Sn << " | En = " << std::setw(12) << En << std::endl;
                ++n;
            } while (En >= a);
        }

        // Вопрос о перезапуске программы
        std::cout << "Do you want to use the program again?\n";
        std::cout << "'0' = Yes\n'1' = No\n";
        exit_check = answerValidation();
        std::cout << "\n\n";
    }
    return 0;
}

