#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

// Структура, хранящая в себе результаты вычислений на определнной итерации
struct result {
    long double An = 0;
    long double Sn = 0;
    long double En = 0;
    long double tempAn = 0;
};

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
        std::cin.clear();
        std::cin.ignore(32767, '\n');
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
        std::cin.clear();
        std::cin.ignore(32767, '\n');
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
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        return answer;
    }
}

int main()
{
    bool exit_check = false;
    std::vector<result> previous_iteration;
    double previous_x = -5;
    while (!exit_check) {

        result current_iteration;

        std::cout << "Enter parameter x: ";
        double x = xParameterValidation();
        if (x == previous_x) {

            std::cout << "Enter parameter a: ";
            long double a = aParameterValidation();

            if (a == long(a)) {
                int size = previous_iteration.size();
                if (a >= size) {


                    std::cout << "The following values are taken from previous calculations.\n";
                    std::cout << "n" << std::setw(14) << "| An" << std::setw(20) << "| Sn" << std::setw(21) << " | En\n";
                    for (int i = 0; i < size; ++i) {
                        std::cout << "n = " << std::setw(6) << i+1 << " | An = " << std::setw(12) << previous_iteration[i].An
                                  << " | Sn = " << std::setw(12) << 2 * previous_iteration[i].Sn << " | En = " << std::setw(12)
                                  << previous_iteration[i].En << std::endl;
                    }


                    std::cout << "The following values are new.\n";
                    std::cout << "n" << std::setw(14) << "| An" << std::setw(20) << "| Sn" << std::setw(21) << " | En\n";
                    current_iteration.tempAn = previous_iteration[size-1].tempAn;


                    for (int n = size; n < a; ++n) {
                        current_iteration.tempAn += (1. / n);
                        current_iteration.An = current_iteration.tempAn * std::pow(x, (n + 1)) / (n + 1); // Подсчет текущего элемента
                        current_iteration.Sn += current_iteration.An; // Подсчет текущей суммы
                        current_iteration.En = std::abs((current_iteration.tempAn + 1. / (n + 1)) * std::pow(x, (n + 2)) / (n + 2) /
                                                        current_iteration.Sn); // Подсчет погрешности
                        previous_iteration.push_back(current_iteration);
                        std::cout << "n = " << std::setw(6) << n+1 << " | An = " << std::setw(12) << current_iteration.An
                                  << " | Sn = " << std::setw(12) << 2 * current_iteration.Sn << " | En = " << std::setw(12)
                                  << current_iteration.En << std::endl;
                    }
                } else {
                    std::cout << "The following values are taken from previous calculations.\n";
                    std::cout << "n" << std::setw(14) << "| An" << std::setw(20) << "| Sn" << std::setw(21) << " | En\n";
                    for (int i = 0; i < a; ++i) {
                        std::cout << "n = " << std::setw(6) << i+1 << " | An = " << std::setw(12) << previous_iteration[i].An
                                  << " | Sn = " << std::setw(12) << 2 * previous_iteration[i].Sn << " | En = " << std::setw(12)
                                  << previous_iteration[i].En << std::endl;
                    }
                }



            } else { // Старый параметр х и новый ДРОБНЫЙ параметр а
                int size = previous_iteration.size();


                if (previous_iteration[size-1].En >= a) { // Если введенная погрешность еще не достигнута

                    std::cout << "The following values are taken from previous calculations.\n";
                    std::cout << "n" << std::setw(14) << "| An" << std::setw(20) << "| Sn" << std::setw(21) << " | En\n";


                    for (int i = 0; i < size; ++i) {
                        std::cout << "n = " << std::setw(6) << i+1 << " | An = " << std::setw(12) << previous_iteration[i].An
                                  << " | Sn = " << std::setw(12) << 2 * previous_iteration[i].Sn << " | En = " << std::setw(12)
                                  << previous_iteration[i].En << std::endl;
                    }

                    std::cout << "The following values are new.\n";
                    std::cout << "n" << std::setw(14) << "| An" << std::setw(20) << "| Sn" << std::setw(21) << " | En\n";
                    current_iteration.tempAn = previous_iteration[size-1].tempAn;

                    int n = size - 1;
                    do {
                        current_iteration.tempAn += (1. / n);
                        current_iteration.An = current_iteration.tempAn * std::pow(x, (n + 1)) / (n + 1); // Подсчет текущего элемента
                        current_iteration.Sn += current_iteration.An; // Подсчет текущей суммы
                        current_iteration.En = std::abs((current_iteration.tempAn + 1. / (n + 1)) * std::pow(x, (n + 2)) / (n + 2) /
                                                        current_iteration.Sn); // Подсчет погрешности
                        previous_iteration.push_back(current_iteration);
                        std::cout << "n = " << std::setw(6) << size+1 << " | An = " << std::setw(12) << current_iteration.An
                                  << " | Sn = " << std::setw(12) << 2 * current_iteration.Sn << " | En = " << std::setw(12)
                                  << current_iteration.En << std::endl;
                        ++n;
                    } while (previous_iteration[previous_iteration.size()-1].En >= a);


                } else { // Если введенная погрешность уже посчитана

                    std::cout << "The following values are taken from previous calculations.\n";
                    std::cout << "n" << std::setw(14) << "| An" << std::setw(20) << "| Sn" << std::setw(21) << " | En\n";

                    int i = 0;
                    do {
                        std::cout << "n = " << std::setw(6) << i+1 << " | An = " << std::setw(12) << previous_iteration[i].An
                                  << " | Sn = " << std::setw(12) << 2 * previous_iteration[i].Sn << " | En = " << std::setw(12)
                                  << previous_iteration[i].En << std::endl;
                        ++i;
                    } while (previous_iteration[i-1].En >= a);

                }
            }
        }
        else {
            std::cout << "Enter parameter a: ";
            long double a = aParameterValidation();

            std::cout << "n" << std::setw(14) << "| An" << std::setw(20) << "| Sn" << std::setw(21) << " | En\n";

            // Если параметр a - количество итераций
            if (a == long(a)) {
                for (int n = 1; n <= a; ++n) {
                    current_iteration.tempAn += (1. / n);
                    current_iteration.An = current_iteration.tempAn * std::pow(x, (n + 1)) / (n + 1); // Подсчет текущего элемента
                    current_iteration.Sn += current_iteration.An; // Подсчет текущей суммы
                    current_iteration.En = std::abs((current_iteration.tempAn + 1. / (n + 1)) * std::pow(x, (n + 2)) / (n + 2) /
                                                    current_iteration.Sn); // Подсчет погрешности
                    previous_iteration.push_back(current_iteration);
                    std::cout << "n = " << std::setw(6) << n << " | An = " << std::setw(12) << current_iteration.An
                              << " | Sn = " << std::setw(12) << 2 * current_iteration.Sn << " | En = " << std::setw(12)
                              << current_iteration.En << std::endl;
                }
            }
                // Если параметр а - необходимая погрешность
            else {
                int n = 1; // Номер элемента последовательности
                do {
                    current_iteration.tempAn += (1. / n);
                    current_iteration.An = current_iteration.tempAn * std::pow(x, (n + 1)) / (n + 1); // Подсчет текущего элемента
                    current_iteration.Sn += current_iteration.An; // Подсчет текущей суммы
                    current_iteration.En = std::abs((current_iteration.tempAn + 1. / (n + 1)) * std::pow(x, (n + 2)) / (n + 2) /
                                                    current_iteration.Sn); // Подсчет погрешности
                    previous_iteration.push_back(current_iteration);
                    std::cout << "n = " << std::setw(6) << n << " | An = " << std::setw(12) << current_iteration.An
                              << " | Sn = " << std::setw(12) << 2 * current_iteration.Sn << " | En = " << std::setw(12)
                              << current_iteration.En << std::endl;
                    ++n;
                } while (current_iteration.En >= a);
            }
        }
        previous_x = x;

        // Вопрос о перезапуске программы
        std::cout << "Do you want to use the program again?\n";
        std::cout << "'0' = Yes\n'1' = No\n";
        exit_check = answerValidation();
        std::cout << "\n\n";
    }
    return 0;
}