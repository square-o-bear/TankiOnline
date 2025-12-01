#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

#include "classes.h"

using namespace std;

int charToInt (char diggital) {
    return diggital - '0';
}

int main () {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    std::cout << "start\n";

    bind(sockfd, (sockaddr*)&addr, sizeof(addr));
    listen(sockfd, 2);

    Pole pole (10);
    char line[1024];
    char *reply;

    int client = accept(sockfd, nullptr, nullptr);
    cout << "Connected to client\n";

    while(pole.isContinue() == 0) {
        reply = pole.draw();

        write(client, reply, strlen(reply));
        system("clear");
        cout << reply << "\nWrite your action: ";
        
        cin >> line;
        if (line == "exit") break;

        pole.movePlrServak(line);

        do {
            read(client, line, sizeof(line)-1);
            sleep(10);
        } while(line[0] == 0);
        pole.movePlrClientosina(line);
        
        write(client, reply, strlen(reply));
    }

    reply = {0};
    reply[0] = charToInt(pole.isContinue());

    close(client);
    close(sockfd);
    return 0;
}
