#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

string generatePasswordFromWord(const string& word, int length) {
    const string chars = "0123456789!@#$%^&*()";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, chars.size() - 1);
    
    string password = word;
    while (password.length() < length) {
        password += chars[distribution(generator)];
    }
    return password;
}

void savePasswordsToFile(const string& word, int count, int length) {
    string folder = "passwords";
    filesystem::create_directory(folder);
    string filePath = folder + "/passwords.txt";
    ofstream file(filePath);
    
    if (!file) {
        cerr << "Error creating file!" << endl;
        return;
    }
    
    for (int i = 0; i < count; i++) {
        file << generatePasswordFromWord(word, length) << endl;
    }
    file.close();
    cout << "1000 passwords saved to " << filePath << endl;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "Password Generator");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Error loading font!" << endl;
        return -1;
    }

    string userWord;
    cout << "Enter a word to generate passwords: ";
    cin >> userWord;
    
    sf::Text text("Password: ", font, 24);
    text.setPosition(50, 100);
    text.setFillColor(sf::Color::White);
    
    string password = generatePasswordFromWord(userWord, 12);
    sf::Text passwordText(password, font, 24);
    passwordText.setPosition(50, 150);
    passwordText.setFillColor(sf::Color::Green);
    
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setPosition(50, 250);
    button.setFillColor(sf::Color::Blue);
    
    sf::Text buttonText("Generate New Password", font, 20);
    buttonText.setPosition(70, 260);
    buttonText.setFillColor(sf::Color::White);
    
    sf::RectangleShape saveButton(sf::Vector2f(250, 50));
    saveButton.setPosition(300, 250);
    saveButton.setFillColor(sf::Color::Red);
    
    sf::Text saveButtonText("Save 1000 Passwords", font, 20);
    saveButtonText.setPosition(320, 260);
    saveButtonText.setFillColor(sf::Color::White);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (button.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        password = generatePasswordFromWord(userWord, 12);
                        passwordText.setString(password);
                    }
                    if (saveButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        savePasswordsToFile(userWord, 1000, 12);
                    }
                }
            }
        }
        window.clear();
        window.draw(text);
        window.draw(passwordText);
        window.draw(button);
        window.draw(buttonText);
        window.draw(saveButton);
        window.draw(saveButtonText);
        window.display();
    }
    return 0;
}

