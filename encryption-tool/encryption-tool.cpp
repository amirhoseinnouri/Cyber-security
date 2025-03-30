#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


void processFile(const string& inputFile, const string& outputFile, const string& key) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);

    if (!inFile) {
        cerr << "Error: Could not open input file!" << endl;
        return;
    }

    if (!outFile) {
        cerr << "Error: Could not create output file!" << endl;
        return;
    }

    char ch;
    size_t keyIndex = 0;
    while (inFile.get(ch)) {
        ch ^= key[keyIndex % key.length()];
        outFile.put(ch);
        keyIndex++;
    }

    inFile.close();
    outFile.close();

    cout << "Operation completed successfully!" << endl;
}

int main() {
    cout << "Simple File Encryption Tool" << endl;
    cout << "--------------------------" << endl;

    int choice;
    string inputFile, outputFile, key;

    cout << "1. Encrypt File" << endl;
    cout << "2. Decrypt File" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice != 1 && choice != 2) {
        cerr << "Invalid choice!" << endl;
        return 1;
    }

    cout << "Enter input filename: ";
    cin >> inputFile;
    cout << "Enter output filename: ";
    cin >> outputFile;
    cout << "Enter encryption key: ";
    cin >> key;

    if (key.empty()) {
        cerr << "Error: Key cannot be empty!" << endl;
        return 1;
    }

    processFile(inputFile, outputFile, key);

    if (choice == 1) {
        cout << "File encrypted successfully!" << endl;
    } else {
        cout << "File decrypted successfully!" << endl;
    }

    return 0;
}