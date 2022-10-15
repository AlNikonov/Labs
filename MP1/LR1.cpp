// Оценка характеристик последовательности чисел (12 вариант)
// Выполнил Никонов Алексей

#include <iostream> // Подключение стандартной библиотеки для ввода/вывода
#include <ctype.h> // Для констант DBL_MAX и DBL_MIN
#include <string> // Для работы со строками


// Проверяет что строка состоит только из цифр и точки
bool IsNumeric(std::string const& str)
{
    auto it = str.begin();
    while (it != str.end() && (std::isdigit(*it) || *it == '.')) {
        it++;
    }
    return !str.empty() && it == str.end();
}


// Ввод чисел последовательности и проверка введенных данных на корректность, возвращает введенное число
double NumInputAndValidation() {
    while (true) {
        double num;
        std::string input_str;
        std::cin >> input_str;
        if (!IsNumeric(input_str)) { // Проверка, что пользователь ввел число, а не набор символов
            std::cin.clear(); // Очистка буфера ввода
            std::cin.ignore(32767, '\n');
            std::cout << "Некорректное значение, введите другое: " << std::endl;
        }
        else {
            num = std::stod(input_str); // Перевод строки в число с плавающей точкой
            if (num < 0) { // Проверка, что пользователь ввел отрицательное число
                std::cin.clear(); // Очистка буфера ввода
                std::cin.ignore(32767, '\n');
                std::cout << "Некорректное значение, введите другое: " << std::endl;
            }
            else {
                return num;
            }
        }
    }
}


// Ввод ответа и проверка его на корректность, возвращает 0(Да) или 1(Нет)
int AnswerInputAndValidation() {
    while (true) {
        int answer;
        std::cin >> answer;
        if (std::cin.fail() || (answer != 0 && answer != 1)) { // Проверка ответа на некорректность
            std::cin.clear(); // Очистка буфера ввода
            std::cin.ignore(32767, '\n');
            std::cout << "Некорректное значение, введите другое: " << std::endl;
        }
        else {
            return answer;
        }
    }
}


int main() {
    while (true) {
        std::setlocale(LC_ALL, "Russian"); // Для русского языка в консоли
        std::setlocale(LC_NUMERIC, "eng"); // Чтобы разделителем целой и дробной части была точка, а не запятая
        std::cout << "Введите последовательность положительных чисел (для завершения ввода последовательности введите 0): " << std::endl;

        double sum = 0; // Переменная, в которой хранится сумма последовательности
        double min_num = DBL_MAX; // Переменная, в которой хранится значение минимального элемента последовательности
        double max_num = DBL_MIN; // Переменная, в которой хранится значение максимального элемента последовательности
        int count = 0; // Счетчик элементов последовательности

        bool flag = true;
        while (flag) {
            double current_num = NumInputAndValidation(); // Текущее число последовательности
            if (current_num == 0) {
                flag = false;
            }
            else {
                sum += current_num;
                ++count;
                if (current_num > max_num) { // Проверка на максимальное число в последовательности
                    max_num = current_num;
                }
                if (current_num < min_num) { // Проверка на минимальное число в последовательности
                    min_num = current_num;
                }
            }
        }

        if (count == 0) { // Проверка на пустую последовательность
            std::cout << "Вы ввели пустую последовательность" << std::endl;
        }
        else { // Вывод характеристик последовательности
            std::cout << "Сумма последовательности: " << sum << std::endl;
            std::cout << "Среднее значение: " << sum / count << std::endl;
            std::cout << "Минимальный элемент последовательности: " << min_num << std::endl;
            std::cout << "Максимальный элемент последовательности: " << max_num << std::endl;
        }

        std::cout << "\nЗапустить программу еще раз?" << std::endl;
        std::cout << "0 - Да" << std::endl;
        std::cout << "1 - Нет" << std::endl;
        std::cout << "Ваш ответ: ";

        char answer = AnswerInputAndValidation();
        if (answer) { // Завершение программы в случае отрицательного ответа
            return 0;
        }
        else {
            std::cout << "\nОчистить консоль?" << std::endl;
            std::cout << "0 - Да" << std::endl;
            std::cout << "1 - Нет" << std::endl;
            std::cout << "Ваш ответ: ";

            answer = AnswerInputAndValidation();
            if (answer) { // Продолжение работы программы без очистки консоли
                std::cout << std::endl;
                continue;
            }
            else { // Продолжение работы программы с очисткой консоли
                system("cls");
            }
        }
    }
    return 0;
}
