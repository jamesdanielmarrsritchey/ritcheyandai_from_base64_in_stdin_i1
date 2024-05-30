#include <iostream>
#include <string>
#include <vector>

/*
To compile and install the program on Debian, you can follow these steps:

1. Install the g++ compiler if it's not already installed. You can do this by running the following command in your terminal:
   sudo apt-get install g++

2. Navigate to the directory containing the source code file (let's call it base64_decode.cpp) using the cd command.

3. Compile the source code file using the g++ compiler. You can do this by running the following command in your terminal:
   g++ -o base64_decode base64_decode.cpp

4. Now, you can run the program using the following command:
   echo -n "Your Base64 string here" | ./base64_decode

Please replace "Your Base64 string here" with the Base64 string you want to decode. The -n option with echo command is used to prevent adding a newline at the end of the string.
*/

const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

int pos(char c) {
    return base64_chars.find(c);
}

std::string base64_decode(const std::string &input) {
    std::string ret;
    std::vector<int> T(256,-1);
    for (int i=0; i<64; i++) T[base64_chars[i]] = i;

    int val=0, valb=-8;
    for (char c : input) {
        if (T[c] == -1) break;
        val = (val<<6) + T[c];
        valb += 6;
        if (valb>=0) {
            ret.push_back(char((val>>valb)&0xFF));
            valb -= 8;
        }
    }
    return ret;
}

int main() {
    std::string input;
    char buffer[4];
    while (std::cin.read(buffer, sizeof(buffer))) {
        input.append(buffer, sizeof(buffer));
    }
    // Handle remaining bytes
    input.append(buffer, std::cin.gcount());
    std::cout << base64_decode(input);

    return 0;
}