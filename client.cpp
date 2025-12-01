#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "classes.h"

using namespace std;

char IntToChar (int diggital) {
    return diggital + '0';
}

int main () {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    std::cout << "start\n";

    connect(sockfd, (sockaddr*)&addr, sizeof(addr));
    cout << "Connected to server!\n";
    
    char line[1024]={0};

    do {

        do {
            read(sockfd, line, sizeof(line)-1);
            sleep(10);
        } while(line[0] == 0);

        if (line[2] == ':') break;
        cout << line << "\nWrite your action: ";
        cin >> line;

        
        write(sockfd, line, sizeof(line)-1);

    } while(true);

    close(sockfd);
    return 0;
}