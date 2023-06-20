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

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const char* pathName = R"(..\test.txt)";

    if (!isFileExist(pathName)) {
        printf("Неверное расположение файла (%s). Переместите в директорию с исполняемым файлом!", pathName);
        return 0;
    }

    string textLine;
    int totalSum = 0;
    int nameOfWinner = 0;
    vector<vector<string>> dataBase;

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

    for (int i = 0; i < dataBase.size(); ++i) {
        auto record = dataBase[i];
        int recordSize = (int)record.size();

        if (recordSize >= 3) {
            totalSum += stoi(record[2]);

            if (stoi(dataBase[nameOfWinner][2]) < stoi(record[2])) {
                nameOfWinner = i;
            }
        }
    }

    cout << "Полный список данных: " << endl;
    for (auto &record : dataBase) {
        int recordSize = (int)record.size();
        cout << recordSize << ": ";
        for (auto &item : record) {
            cout << item << " ";
        }
        cout << endl;
    }

    cout << "Заработный фонд: " << totalSum << endl;
    cout << "Максимальная зарплата у: " << dataBase[nameOfWinner][0] << " " << dataBase[nameOfWinner][1] << " " << dataBase[nameOfWinner][2] << endl;
}