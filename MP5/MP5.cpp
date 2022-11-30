#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

unsigned int getCorrectUInt();
double getCorrectDouble();
void printVector(std::vector<unsigned int> v);
bool chooseMethod();

class ProfitData {

private:

	// Поля класса
	unsigned int branch_number;
	unsigned int days_count;
	std::vector<double> profit_per_day;

public:

	// Сеттеры
	void setBranch(unsigned int branch) { branch_number = branch; }
	void setDays(unsigned int days) { days_count = days; }
	void setProfit(std::vector<double> profit) { profit_per_day = profit; }

	// Геттеры
	unsigned int getBranch() const { return branch_number; }
	unsigned int getDays() const { return days_count; }
	std::vector<double> getProfit() const { return profit_per_day; }

	// Конструкторы

	// Конструктор копирования
	ProfitData(const ProfitData& ref_data) {
		this->branch_number = ref_data.branch_number;
		this->days_count = ref_data.days_count;
		this->profit_per_day = ref_data.profit_per_day;
	}

	// Конструктор по умолчанию
	ProfitData(unsigned int branch = 0, unsigned int days = 0, std::vector<double> prof =  {}) {
		branch_number = branch;
		days_count = days;
		profit_per_day = prof;
	}

	// Деструктор
	~ProfitData () {}

	// Перегрузки операторов

	friend bool operator<(ProfitData& branch1, ProfitData& branch2) {
		double sum1 = 0, sum2 = 0;
		for (int i = 0; i < branch1.days_count; ++i) {
			sum1 += branch1.profit_per_day[i];
		}
		sum1 /= branch1.days_count;
		for (int i = 0; i < branch2.days_count; ++i) {
			sum2 += branch2.profit_per_day[i];
		}
		sum2 /= branch2.days_count;
		return sum1 < sum2;
	}

	// Чтение из обычного потока
	friend std::istream& operator>>(std::istream& in, ProfitData& ref) {
		std::cout << "Enter branch number (non-negative integer): ";
		ref.branch_number = getCorrectUInt();
		std::cout << "Enter days count (non-negative integer): ";
		ref.days_count = getCorrectUInt();
		std::cout << "Enter profit for each day.\n";
		for (int i = 0; i < ref.days_count; ++i) {
			double prof = getCorrectDouble();
			ref.profit_per_day.push_back(prof);
		}
		return in;
	}

	// Помещение в обычный поток
	friend std::ostream& operator<<(std::ostream& сout, const ProfitData& ref) {
		сout << "Branch: " << ref.branch_number << "\nDays: " << ref.days_count << "\nProfits per day: ";
		for (int i = 0; i < ref.days_count; ++i) {
			сout << ref.profit_per_day[i] << ' ';
		}
		сout << '\n';
		return сout;
	}

	// Чтение из файлового потока
	friend std::ifstream& operator>>(std::ifstream& in, ProfitData& ref) {
		try {
			in >> ref.branch_number;
			in.clear();
			in.ignore(32767, '\n');
			in >> ref.days_count;
			in.clear();
			in.ignore(32767, '\n');
			for (int i = 0; i < ref.days_count; ++i) {
				std::string prof;
				in >> prof;
				try {
					ref.profit_per_day.push_back(std::stod(prof));
				}
				catch (...) {
					ref.profit_per_day.push_back(0);
				}
			}
		}
		catch (...) {
			throw std::runtime_error("Incorrect input in file.");
		}
		return in;
	}

	// Помещение в файловый поток
	friend std::ofstream& operator<<(std::ofstream& out, const ProfitData& ref) {
		out << "Branch: " << ref.branch_number << "\nDays: " << ref.days_count << "\nProfits per day: ";
		for (int i = 0; i < ref.days_count; ++i) {
			out << ref.profit_per_day[i] << ' ';
		}
		out << '\n';
		return out;
	}

	// Функции

	// Возвращает вектор с номерами дней, в которых была нулевая прибыль
	std::vector<unsigned int> zeroProfDays() const {
		std::vector<unsigned int> result;
		for (int i = 0; i < days_count; ++i) {
			if (!profit_per_day[i]) {
				result.push_back(i+1);
			}
		}
		return result;
	}
};

void inputInConsole(std::vector<ProfitData>& ref);

// Проверка на корректность неотрицательных целых чисел
unsigned int getCorrectUInt() {
	std::string input;
	while (true) {
		std::getline(std::cin, input);
		if (input.find_first_not_of("0123456789") != std::string::npos || input.empty()) {
			std::cout << "Incorrect value, please enter another one: ";
		}
		else {
			return std::stoul(input);
		}
	}
}

// Проверка на корректность вещественного числа
double getCorrectDouble() {
	std::string input;
	while (true) {
		std::getline(std::cin, input);
		if (input.find_first_not_of("0123456789-.") != std::string::npos || input.empty()) {
			std::cout << "Incorrect value, please enter another one: ";
		}
		else {
			try {
				return std::stod(input);
			}
			catch (...) {
				std::cout << "Incorrect value, please enter another one: ";
			}
		}
	}
}

// Функция для вывода элементов вектора
void printVector(std::vector<ProfitData> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		inputInConsole(vec);
	}
}

void printVector(const std::vector<unsigned int> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << ' ';
	}
	std::cout << '\n';
}

void inputInFile(std::ofstream& out, std::vector<ProfitData> &ref) {
	for (ProfitData i : ref) {
		out << i;
		std::vector<unsigned int> v = i.zeroProfDays();
		out << "Number of days with zero profit: " << v.size() << '\n';
		out << "Days with zero profit: ";
		for (unsigned int i : v) {
			out << i << ' ';
		}
		out << '\n';
	}
}

void inputInConsole(std::vector<ProfitData>& ref) {
	for (ProfitData i : ref) {
		std::cout << i;
		std::vector<unsigned int> v = i.zeroProfDays();
		std::cout << "Number of days with zero profit: " << v.size() << '\n';
		std::cout << "Days with zero profit: ";
		printVector(v);
	}
}

// Выбор метода ввода/вывода
bool chooseMethod() {
	std::string ans;
	std::cout << "Your answer: ";
	while (true) {
		std::getline(std::cin, ans);
		if (ans == "0" || ans == "1") {
			return ans == "0";
		}
		else {
			std::cout << "Incorrect value, please enter another one: ";
		}
	}
}

// Функция для перезапуска программы
bool restartProgram() {
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
			return answer == "Yes";
		}
	}
}

int main()
{
	do {
		std::vector<ProfitData> all_data;
		std::cout << "Choose input:\n0-keyboard\n1-file\n";
		bool method = chooseMethod();
		if (method) {
			std::cout << "Enter the number of branches: ";
			unsigned int size = getCorrectUInt();
			for (int i = 0; i < size; ++i) {
				ProfitData temp;
				std::cin >> temp;
				all_data.push_back(temp);
			}
		}
		else {
			bool flag = true;
			while (flag) {
				std::string name;
				std::cout << "Enter file name: ";
				std::getline(std::cin, name);
				std::ifstream in(name);
				if (!in.is_open()) {
					std::cout << "File can't be opened, try again.\n";
				}
				else {
					try {
						while (in.peek()!= EOF) {
							ProfitData temp;
							in >> temp;
							all_data.push_back(temp);
						}
						flag = false;
					}
					catch (...) {
						flag = false;
						std::cout << "Something goes wrong! Try again!";
					}
				}
			}

		}
		std::cout << "Choose output:\n0-console\n1-file\n";
		method = chooseMethod();
		if (method) {
			inputInConsole(all_data);
		}
		else {
			bool flag = true;
			while (flag) {
				try {
					std::string name;
					std::cout << "Enter file name: ";
					std::getline(std::cin, name);
					std::ofstream out(name);
					inputInFile(out, all_data);
					flag = false;
				}
				catch (...) {
					std::cout << "Something goes wrong! Try again!";
				}
			}
		}
	} while (restartProgram());
	return 0;
}
