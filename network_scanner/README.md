Network Scanner - README
📌 Overview
A simple yet powerful multi-threaded network scanner written in C++ that discovers active devices on your local network by pinging IP addresses in a specified range.

✨ Features
Real-time results - Shows discovered devices as they're found

Multi-threaded - Scans multiple IPs simultaneously for faster results

Hostname resolution - Attempts to resolve hostnames for discovered devices

Progress tracking - Shows scanning progress and found devices count

Lightweight - No external dependencies beyond standard C++ libraries

🛠️ Requirements
Linux/Ubuntu system

g++ compiler

Basic network connectivity


Installation
Clone the repository or download the source file:

git clone https://github.com/amirhoseinnouri/network-scanner.git
cd network-scanner

Compile the program:

g++ -std=c++11 -pthread network_scanner.cpp -o network_scanner
Run the scanner with:

sudo ./network_scanner

You'll be prompted to enter:

Base IP (e.g., 192.168.1)

Start range (e.g., 1)

End range (e.g., 254)

Notes
Requires root privileges for some network operations

Scanning large ranges (e.g., 1-254) may take several seconds

Hostname resolution depends on your network's DNS configuration

The scanner uses ICMP ping packets which some firewalls may block

📜 License
This project is licensed under the MIT License - see the LICENSE file for details.

🤝 Contributing
Contributions are welcome! Please open an issue or submit a pull request.

---- 

🔍 Happy scanning! 

https://t.me/Nouri_AmirHosein
