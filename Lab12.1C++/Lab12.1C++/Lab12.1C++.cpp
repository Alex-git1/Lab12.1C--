#include <iostream>
#include <fstream>
using namespace std;

void CreateBIN(char* fname) {
    ofstream fout(fname, ios::binary); // ��������� ���� ��� ������
    char ch;
    double number;

    do {
        cout << "Enter a number: ";
        cin >> number;
        fout.write((char*)&number, sizeof(number)); // �������� ����� � ����
        cout << "Continue? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fout.close();
}

void PrintBIN(char* fname) {
    ifstream fin(fname, ios::binary); // ��������� ���� ��� �������
    double number;

    cout << "Contents of " << fname << ":\n";
    while (fin.read((char*)&number, sizeof(number))) {
        cout << number << " ";
    }
    cout << endl;
    fin.close();
}

void ProcessBIN(char* fname, char* gname) {
    ifstream fin(fname, ios::binary); // ��������� ������� ����
    ofstream fout(gname, ios::binary); // ��������� �������� ����

    double number;
    double maxValue, minValue;
    bool firstRead = true;

    // ��������� ����������� �� �������� ��������
    while (fin.read((char*)&number, sizeof(number))) {
        if (firstRead) {
            maxValue = minValue = number; // ���������� ������ ������
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

    // �������� ���������� � �������� ����
    if (!firstRead) { // ���� ��� ���� ��������
        fout.write((char*)&maxValue, sizeof(maxValue));
        fout.write((char*)&minValue, sizeof(minValue));
    }

    fin.close();
    fout.close();
}

int main() {
    char fname[100]; // ��'� �������� �����
    char gname[100]; // ��'� ��������� �����

    cout << "Enter input file name: ";
    cin >> fname;
    CreateBIN(fname); // ��������� ������� ������� ����

    PrintBIN(fname); // �������� ���� �������� �����

    cout << "Enter output file name: ";
    cin >> gname;
    ProcessBIN(fname, gname); // ���������� ����

    PrintBIN(gname); // �������� ���� ��������� �����

    return 0;
}
