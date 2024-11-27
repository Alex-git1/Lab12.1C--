#include <iostream>
#include <fstream>
using namespace std;

void CreateBIN(char* fname) {
    ofstream fout(fname, ios::binary); // відкриваємо файл для запису
    char ch;
    double number;

    do {
        cout << "Enter a number: ";
        cin >> number;
        fout.write((char*)&number, sizeof(number)); // записуємо число у файл
        cout << "Continue? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fout.close();
}

void PrintBIN(char* fname) {
    ifstream fin(fname, ios::binary); // відкриваємо файл для читання
    double number;

    cout << "Contents of " << fname << ":\n";
    while (fin.read((char*)&number, sizeof(number))) {
        cout << number << " ";
    }
    cout << endl;
    fin.close();
}

void ProcessBIN(char* fname, char* gname) {
    ifstream fin(fname, ios::binary); // відкриваємо вхідний файл
    ofstream fout(gname, ios::binary); // відкриваємо вихідний файл

    double number;
    double maxValue, minValue;
    bool firstRead = true;

    // Знаходимо максимальне та мінімальне значення
    while (fin.read((char*)&number, sizeof(number))) {
        if (firstRead) {
            maxValue = minValue = number; // Ініціалізуємо першим числом
            firstRead = false;
        }
        else {
            if (number > maxValue) {
                maxValue = number;
            }
            if (number < minValue) {
                minValue = number;
            }
        }
    }

    // Записуємо результати у вихідний файл
    if (!firstRead) { // якщо дані були прочитані
        fout.write((char*)&maxValue, sizeof(maxValue));
        fout.write((char*)&minValue, sizeof(minValue));
    }

    fin.close();
    fout.close();
}

int main() {
    char fname[100]; // ім'я вхідного файлу
    char gname[100]; // ім'я вихідного файлу

    cout << "Enter input file name: ";
    cin >> fname;
    CreateBIN(fname); // створюємо вхідний бінарний файл

    PrintBIN(fname); // виводимо вміст вхідного файлу

    cout << "Enter output file name: ";
    cin >> gname;
    ProcessBIN(fname, gname); // обробляємо файл

    PrintBIN(gname); // виводимо вміст вихідного файлу

    return 0;
}
