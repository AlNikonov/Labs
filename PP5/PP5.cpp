#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

// Проверка на корректность вещественного числа
long double getCorrectDouble() {
	std::string input;
	while (true) {
		std::getline(std::cin, input);
		if (input.find_first_not_of("0123456789.") != std::string::npos || input.empty()) {
			std::cout << "Incorrect value, please enter another one: ";
		}
		else {
			try {
				return std::stold(input);
			}
			catch (...) {
				std::cout << "Incorrect value, please enter another one: ";
			}
		}
	}
}

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

class WorkTime {

private:

	// Поля класса

	std::string date;
	std::string start_time;
	std::string end_time;

	// Проверка корректности даты
	bool checkDate()
	{
		if (date.size() != 5 || !isdigit(date[0]) || !isdigit(date[1]) || date[2] != '.' || !isdigit(date[3]) || !isdigit(date[4])) {
			return false;
		}
		int day = stoi(date.substr(0, 2)); 
		int month = stoi(date.substr(3, 2));
		if (month < 1 || month > 12) {
			return false;
		}
		int days_in_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (day < 1 || day > days_in_month[month - 1]) {
			return false;
		}
		return true;
	}

	// Проверка корректности начального времени
	bool checkStartTime() {
		if (start_time.size() != 5 || !isdigit(start_time[0]) || !isdigit(start_time[1]) || start_time[2] != ':' || !isdigit(start_time[3]) || !isdigit(start_time[4])) {
			return false;
		}
		int start_hour = std::stoi(start_time.substr(0, 2));
		int start_minute = std::stoi(start_time.substr(3, 2));
		if (start_hour < 0 || start_hour > 23 || start_minute < 0 || start_minute > 59) {
			return false;
		}
	}

	// Проверка корректности конечного времени
	bool checkEndTime() {
		if (end_time.size() != 5 || !isdigit(end_time[0]) || !isdigit(end_time[1]) || end_time[2] != ':' || !isdigit(end_time[3]) || !isdigit(end_time[4])) {
			return false;
		}
		int start_hour = std::stoi(start_time.substr(0, 2));
		int end_hour = std::stoi(end_time.substr(0, 2));
		int start_minute = std::stoi(start_time.substr(3, 2));
		int end_minute = std::stoi(end_time.substr(3, 2));
		if (end_hour < 0 || end_hour > 23 || end_minute < 0 || end_minute > 59) {
			return false;
		}
		if (start_hour > end_hour || (start_hour == end_hour && start_minute > end_minute)) {
			return false;
		}
	}

public:

	// Конструкторы

	WorkTime() {
		date = "01.01";
		start_time = "00:00";
		end_time = "23:59";
	}

	WorkTime(std::string d, std::string start, std::string end) {
		date = d;
		start_time = start;
		end_time = end;
	}

	WorkTime(const WorkTime& ref) {
		this->date = ref.date;
		this->start_time = ref.start_time;
		this->end_time = ref.end_time;
	}

	// Деструктор

	~WorkTime() {}

	// Геттеры

	std::string getDate() const { return date; }
	std::string getStartTime() const { return start_time; }
	std::string getEndTime() const { return end_time; }

	// Сеттеры

	void setDate(std::string new_d) { date = new_d; }
	void setStartTime(std::string start) { start_time = start; }
	void setEndTime(std::string end) { end_time = end; }

	// Перегрузки операторов

	friend std::ostream& operator<<(std::ostream&, WorkTime&);
	friend std::istream& operator>>(std::istream&, WorkTime&);
	friend std::ofstream& operator<<(std::ofstream&, WorkTime&);
	friend std::ifstream& operator>>(std::ifstream&, WorkTime&);

	// Функции

	// Возвращает время работы в минутах
	int workMinutes()
	{
		int start_hour = std::stoi(start_time.substr(0, 2)); 
		int end_hour = std::stoi(end_time.substr(0, 2));
		int start_minute = std::stoi(start_time.substr(3, 2));
		int end_minute = std::stoi(end_time.substr(3, 2));
		int minute_result, hour_result;
		if (end_minute - start_minute >= 0) { 
			minute_result = end_minute - start_minute;
			hour_result = end_hour - start_hour;
		}
		else { 
			minute_result = end_minute - start_minute + 60;
			hour_result = end_hour - start_hour - 1;
		}
		return hour_result * 60 + minute_result;
	}

};

//  Чтение из консоли
std::istream& operator>>(std::istream& in, WorkTime& ref)
{
	std::cout << "Input date in format (dd.mm): ";
	while (!(in >> ref.date) || in.peek() != '\n' || !ref.checkDate()) {
		std::cout << "Incorrect date format. Enter date again: ";
		in.clear();
		in.ignore(32767, '\n');
	}
	std::cout << "Input start time in format (hh:mm): ";
	while (!(in >> ref.start_time) || in.peek() != '\n' || !ref.checkStartTime()) {
		std::cout << "Incorrect time format. Enter start time again: ";
		in.clear();
		in.ignore(32767, '\n');
	}
	std::cout << "Input end time in format (hh:mm): ";
	while (!(in >> ref.end_time) || in.peek() != '\n' || !ref.checkEndTime()) {
		std::cout << "Incorrect time format. Enter end time again: ";
		in.clear();
		in.ignore(32767, '\n');
	}
	return in;
}

// Вывод в консоль
std::ostream& operator<<(std::ostream& out, WorkTime& ref)
{
	out << ref.date << ' ' << ref.start_time << ' ' << ref.end_time << '\n';
	return out;
}

// Чтение из файла
std::ifstream& operator>>(std::ifstream& in, WorkTime& ref)
{
	std::getline(in, ref.date);
	std::getline(in, ref.start_time);
	std::getline(in, ref.end_time);
	if (!ref.checkDate()) {
		ref.date = "01.01";
	}
	if (!ref.checkStartTime()) {
		ref.start_time = "00:00";
	}
	if (!ref.checkEndTime()) {
		ref.end_time = "23:59";
	}
	return in;
}

// Запись в файл
std::ofstream& operator<<(std::ofstream& out, WorkTime& ref)
{
	out << ref.date << ' ' << ref.start_time << ' ' << ref.end_time << '\n';
	return out;
}

class Worker {

private:

	// Поля класса
	std::string full_name;
	long double wage_rate;
	WorkTime work_time;

public:

	// Конструкторы

	Worker() {
		full_name = "Ivanov I.I.";
		wage_rate = 0;
		work_time = WorkTime();
	}

	Worker(std::string name, long double rate, WorkTime t) {
		full_name = name;
		wage_rate = rate;
		work_time = t;
	}

	Worker(const Worker& ref) {
		this->full_name = ref.full_name;
		this->wage_rate = ref.wage_rate;
		this->work_time = ref.work_time;
	}

	// Деструктор

	~Worker() {}

	// Геттеры

	std::string getFullname() const { return full_name; }
	long double getWageRate() const { return wage_rate; }
	WorkTime getWorkTime() const { return work_time; }

	// Сеттеры

	void setFullname(std::string name) { full_name = name; }
	void setWageRate(long double rate) { wage_rate = rate; }
	void setWorkTime(WorkTime t) { work_time = t; }

	// Перегрузки операторов

	friend std::ostream& operator<<(std::ostream&, Worker&);
	friend std::istream& operator>>(std::istream&, Worker&);
	friend std::ofstream& operator<<(std::ofstream&, Worker&);
	friend std::ifstream& operator>>(std::ifstream&, Worker&);

	// Функции

	// Возвращает зарплату, которую необходимо выплатить работнику за его рабочее время
	long double calculateSalary() {
		return work_time.workMinutes() * (wage_rate / 60);
	}
};

// Вывод в консоль
std::ostream& operator<<(std::ostream& out, Worker& ref) {
	out << ref.full_name << ' ' << ref.wage_rate << ' ' << ref.work_time;
	return out;
}

// Вывод в файл
std::ofstream& operator<<(std::ofstream& out, Worker& ref) {
	out << ref.full_name << ' ' << ref.wage_rate << ' ' << ref.work_time;
	return out;
}

// Ввод из консоли
std::istream& operator>>(std::istream& in, Worker& ref) {
	std::regex r("[A-Z][a-z]+\\s+[A-Z]\\.\\s*[A-Z]\\.");
	std::cout << "Enter fullname in format \"Ivanov I.I.\": ";
	std::string name;
	bool flag = true;
	while (flag) {
		std::getline(in, name);
		if (!std::regex_match(name, r)) {
			std::cout << "Incorrect fullname format, please try again: ";
		}
		else {
			flag = false;
			ref.full_name = name;
		}
	}
	std::cout << "Enter wage rate (non-negative double): ";
	ref.wage_rate = getCorrectDouble();
	in >> ref.work_time;
	in.ignore(32767, '\n');
	return in;
}

// Ввод из файла
std::ifstream& operator>>(std::ifstream& in, Worker& ref) {
	std::regex r("[A-Z][a-z]+\\s+[A-Z]\\.\\s*[A-Z]\\.");
	std::string temp;
	std::getline(in, temp);
	if (std::regex_match(temp, r)) {
		ref.full_name = temp;
	}
	else {
		ref.full_name = "Ivanov I.I.";
	}
	try {
		std::getline(in, temp);
		if (temp.find_first_not_of("0123456789.") != std::string::npos || temp.empty()) {
			ref.wage_rate = 0;
		}
		else {
			ref.wage_rate = std::stold(temp);
		}
	}
	catch (...) {
		ref.wage_rate = 0;
	}
	in >> ref.work_time;
	return in;
}

// Вывод в консоль
void outputInConsole(std::vector<Worker>& ref) {
	for (Worker i : ref) {
		std::cout << i << "Salary: " << i.calculateSalary() << '\n';
	}
}

// Вывод в файл
void outputInFile(std::ofstream& out, std::vector<Worker>& ref) {
	for (Worker i : ref) {
		out << i << "Salary: " << i.calculateSalary() << '\n';
	}
}

// Проверка на корректность имени файла
std::string getCorrectFilename() {
	std::cout << "Please enter a filename: ";
	while (true) {
		std::string filename;
		std::getline(std::cin, filename);
		if (filename.find_first_of("+=[]:*?;«,/\\<>|") != std::string::npos || filename.length() < 5 || filename.find(".txt") != filename.length() - 4) {
			std::cout << "Incorrect filename, please enter another one: ";
		}
		else {
			return filename;
		}
	}
}

// Зацикливание программы
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

int main()
{
	do {
		std::vector<Worker> all_data;
		std::cout << "Choose input:\n0 - Keyboard\n1 - File\n";
		bool method = chooseMethod();
		if (method) {
			std::cout << "Enter the number of workers: ";
			unsigned int size = getCorrectUInt();
			for (int i = 0; i < size; ++i) {
				Worker temp;
				std::cin >> temp;
				all_data.push_back(temp);
			}
		}
		else {
			bool flag = true;
			while (flag) {
				std::ifstream file;
				do {
					file.open(getCorrectFilename());
					if (!file.is_open()) { std::cout << "File can't be opened, please try again.\n"; };
				} while (!file.is_open());
				try {
					while (file.peek() != EOF) {
						Worker temp;
						file >> temp;
						all_data.push_back(temp);
					}
					flag = false;
				}
				catch (...) {
					flag = false;
					std::cout << "Something goes wrong! Try again!";
				}
				file.close();
			}
		}
		std::cout << "Choose output:\n0 - Console\n1 - File\n";
		method = chooseMethod();
		if (method) {
			outputInConsole(all_data);
		}
		else {
			bool flag = true;
			while (flag) {
				try {
					std::ofstream file(getCorrectFilename());
					outputInFile(file, all_data);
					flag = false;
				}
				catch (...) {
					std::cout << "Something goes wrong! Try again!";
				}
			}
		}
	} while (restartProgram());
}