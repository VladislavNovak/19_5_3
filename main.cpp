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

bool isFileExist(const char* fileName) {
    bool isExist = false;
    std::ifstream fileReader;
    fileReader.open(fileName);
    if (fileReader.is_open() && !fileReader.bad()) isExist = true;
    fileReader.close();

    return isExist;
}

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

void readFileToData(const char* pathName, vector<vector<string>> &dataBase) {
    string textLine;

    std::ifstream fileReader;
    fileReader.open(pathName);

    while (std::getline(fileReader, textLine)) {
        std::stringstream ss(textLine);
        vector<string> words;
        string word;

        while (ss >> word) words.push_back(word);

        dataBase.push_back(words);
    }

    fileReader.close();
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const char* pathName = R"(..\test.txt)";

    if (!isFileExist(pathName)) {
        printf("Неверное расположение файла (%s). Переместите в директорию с исполняемым файлом!", pathName);
        return 0;
    }

    vector<vector<string>> dataBase;

    readFileToData(pathName, dataBase);

    printData(dataBase, getCalculatedSalary(dataBase), getHighestSalaryPerson(dataBase));
}