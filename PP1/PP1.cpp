#include <iostream> // Подключение стандартной библиотеки ввода/вывода

using namespace std; // Использование пространства имен std

// Функция, отвечающая за ввод и проверку на корректность размеров массива
// Возвращает размер, в случае если он корректный, иначе - просит ввести другое значение
int sizeValidation() {
    int size;
    cin >> size;
    if (size <= 1 || cin.fail() || cin.bad() || cin.peek() != '\n') {
        cout << "Incorrect array size, please enter another one: ";
        cin.clear(); // Возвращение потока ввода в начальное состояние
        cin.ignore(32767, '\n');
        sizeValidation();
    }
    else {
        return size;
    }
}

// Функция, отвечающая за ввод и проверку на корректность элементов массива
// Возвращает элемент, в случае если он корректный, иначе - просит ввести другое значение
double elementValidation() {
    double element;
    cin >> element;
    if (cin.fail() || cin.bad() || cin.peek() != '\n') {
        cout << "Incorrect array element, please enter another one: ";
        cin.clear(); // Возвращение потока ввода в начальное состояние
        cin.ignore(32767, '\n');
        elementValidation();
    }
    else {
        return element;
    }
}

// Функция, отвечающая за ввод и проверку на корректность ответа пользователя на вопрос о перезапуске
// Возвращает ответ, в случае если он корректный, иначе - просит ввести другое значение
bool answerValidation() {
    int answer;
    cin >> answer;
    if (answer != 0 && answer != 1 || cin.fail() || cin.bad() || cin.peek() != '\n') {
        cout << "Incorrect answer, please enter another one: ";
        cin.clear(); // Возвращение потока ввода в начальное состояние
        cin.ignore(32767, '\n');
        answerValidation();
    }
    else {
        return answer;
    }
}

int main()
{
    bool exit = false;
    while (!exit) {
        cout << "Enter the number of rows: ";
        int rows; // Количество строк в массиве
        rows = sizeValidation();
        cout << "Enter the number of columns: ";
        int columns; // Количество столбцов в массиве
        columns = sizeValidation();

        // Выделение памяти для динамического массива
        double **arr = new double* [rows];
        for (int i = 0; i < rows; ++i) {
            arr[i] = new double [columns];
        }

        // Заполнение массива элементами
        for (int i = 0; i < rows; ++i) { 
            for (int j = 0; j < columns; ++j) {
                cout << "Enter element of the " << i+1 << " row " << j+1 << " column: ";
                arr[i][j] = elementValidation();
            }
        }
        cout << "Matrix" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << arr[i][j] << '\t';
            }
            cout << endl;
        }

        // Проход по элементам массива и поиск минимального и максимального значений
        double max_value = -1.7e+308, min_value = 1.7e+308;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (arr[i][j] > max_value) {
                    max_value = arr[i][j];
                }
                if (arr[i][j] < min_value) {
                    min_value = arr[i][j];
                }
            }
        }

        // Освобождение памяти
        for (int i = 0; i < rows; ++i) {
            delete[] arr[i];
        }
        delete[] arr;

        // Вывод полученных значений
        cout << "Maximum value: " << max_value << endl;
        cout << "Minimum value: " << min_value << endl;

        // Вопрос о перезапуске программы
        cout << "Do you want to use the program again?\n";
        cout << "'0' = Yes\n'1' = No\n";
        exit = answerValidation();
        cout << "\n\n";
    }
    return 0;
}
