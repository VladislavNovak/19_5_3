#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream> // stringstream
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int getCalculatedSalary(const vector<vector<string>> &dataBase) {
    const int SALARY = 2;
    int totalSum = 0;

    for (auto record : dataBase) {
        if (record.size() >= (SALARY + 1)) {
            totalSum += stoi(record[SALARY]);
        }
    }

    return totalSum;
}

int getHighestSalaryPerson(const vector<vector<string>> &dataBase) {
    const int SALARY = 2;
    int highestSalaryPerson = 0;

    for (int i = 0; i < dataBase.size(); ++i) {
        auto record = dataBase[i];

        if (record.size() >= (SALARY + 1)) {
            if (stoi(dataBase[highestSalaryPerson][SALARY]) < stoi(record[SALARY])) {
                highestSalaryPerson = i;
            }
        }
    }

    return highestSalaryPerson;
}

void printData(const vector<vector<string>> &dataBase, int totalSalary, int highestSalaryPerson) {
    cout << "Полный список данных: " << endl;
    for (int i = 0; i < dataBase.size(); ++i) {
        auto record = dataBase[i];
        cout << i << ": ";
        for (const auto &item : record) cout << item << " ";

        cout << endl;
    }

    cout << endl;

    cout << "Заработный фонд: " << totalSalary << endl;
    cout << "Максимальная зарплата у: ";
    for (auto &item : dataBase[highestSalaryPerson]) {
        cout << item << " ";
    }

    cout << endl;
}

// Обрезаем с начала и с конца все НЕ символы
std::string trim(std::string const &str, std::string const &whitespace=" \r\n\t\v\f") {
    auto start = str.find_first_not_of(whitespace);
    auto end = str.find_last_not_of(whitespace);

    return str.substr(start, end - start + 1);
}

// Записывает в data данные из файла по принципу: массив строк.
// Возвращает true, если чтение прошло успешно
bool readFileToVector(const char* pathName, vector<string> &data) {
    bool isFileReadSuccessfully = false;
    std::ifstream in(pathName);

    if (in.is_open() && !in.bad()) {
        string textLine;

        while (std::getline(in, textLine)) {
            data.push_back(textLine);
        }

        in.clear();
        in.seekg(0, std::ios_base::beg);
        isFileReadSuccessfully = true;
    }

    in.close();

    return isFileReadSuccessfully;
}

// Записывает в data данные из файла по принципу: массив строк <- массив слов.
bool readFileToVectorOfVectors(const char* pathName, vector<vector<string>> &data) {
    vector<string> rows;
    bool isFileReadSuccessfully = readFileToVector(pathName, rows);

    if (isFileReadSuccessfully && !rows.empty()) {
        for (const auto &row : rows) {
            vector<string> words;
            string word;
            std::stringstream ss(row);

            // Делим строки на токены по запятой
            while (std::getline(ss, word, ' ')) {
                string retStr = trim(word);
                words.push_back(retStr);
            }

            data.push_back(words);
        }
    }

    return isFileReadSuccessfully;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const char* pathName = R"(..\test.txt)";

    vector<vector<string>> dataBase;

    bool isFileExist = readFileToVectorOfVectors(pathName, dataBase);

    if (!isFileExist) {
        printf("Неверное расположение файла (%s). Переместите в директорию с исполняемым файлом!", pathName);
        return 1;
    }

    printData(dataBase, getCalculatedSalary(dataBase), getHighestSalaryPerson(dataBase));
}