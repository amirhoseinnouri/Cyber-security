#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <sstream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <iomanip>

using namespace std;

mutex mtx;

bool ping_host(const string& ip) {
    string command = "ping -c 1 -W 1 " + ip + " > /dev/null 2>&1";
    int result = system(command.c_str());
    return (result == 0);
}

string get_hostname(const string& ip) {
    struct sockaddr_in sa;
    char hostname[NI_MAXHOST];
    
    sa.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &sa.sin_addr);
    
    if (getnameinfo((struct sockaddr*)&sa, sizeof(sa), 
                    hostname, NI_MAXHOST, NULL, 0, 0) != 0) {
        return "Unknown";
    }
    return string(hostname);
}

void scan_ip(const string& ip, int& devices_found) {
    if (ping_host(ip)) {
        string hostname = get_hostname(ip);
        lock_guard<mutex> lock(mtx);
        devices_found++;
        cout << "[" << devices_found << "] ";
        cout << "IP: " << left << setw(15) << ip;
        cout << " Hostname: " << hostname << endl;
    }
}

int main() {
    string base_ip;
    int start_range, end_range;
    
    cout << "Enter base IP (e.g., 192.168.1): ";
    cin >> base_ip;
    
    cout << "Enter start range (e.g., 1): ";
    cin >> start_range;
    
    cout << "Enter end range (e.g., 254): ";
    cin >> end_range;
    
    cout << "\nScanning network from " << base_ip << "." << start_range 
         << " to " << base_ip << "." << end_range << "..." << endl;
    cout << "------------------------------------------------" << endl;
    
    vector<thread> threads;
    int devices_found = 0;
    int total_ips = end_range - start_range + 1;
    int ips_scanned = 0;
    
    auto start_time = chrono::steady_clock::now();
    
    for (int i = start_range; i <= end_range; i++) {
        string ip = base_ip + "." + to_string(i);
        threads.emplace_back(scan_ip, ip, ref(devices_found));
        ips_scanned++;
        
        {
            lock_guard<mutex> lock(mtx);
            cout << "\rProgress: " << ips_scanned << "/" << total_ips 
                 << " IPs scanned | Found: " << devices_found << " devices" << flush;
        }
        
        if (threads.size() >= 50) {
            for (auto& t : threads) {
                t.join();
            }
            threads.clear();
        }
    }
    
    
    for (auto& t : threads) {
        t.join();
    }
    
    auto end_time = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time);
    
    cout << "\n\nScan completed in " << duration.count() << " seconds." << endl;
    cout << "Total devices found: " << devices_found << endl;
    
    return 0;
}
