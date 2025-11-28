#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

using namespace std;

int charToInt (char diggital) {
    return diggital - '0';
}

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

    bind(sockfd, (sockaddr*)&addr, sizeof(addr));
    listen(sockfd, 2);

    int client = accept(sockfd, nullptr, nullptr);
    cout << "Connected to client\n";

    vector<vector<char>> matrix(3, vector<char>(3, '.'));
    do {

        char buf[1024] = {0};
        read(client, buf, sizeof(buf)-1);
        std::cout << "read: [" << buf << "]\n";

        if (buf[0]=='-' && buf[1]=='1') {
            char reply[12] = {'G', 'o', 'o', 'd', 'b', 'y', 'e', ' ', '!', ' ', ' ', ' '};
            write(client, reply, strlen(reply));
            break;
        } else {
            matrix[charToInt(buf[0])][charToInt(buf[1])] = buf[2];
        }

        char reply[12] = {'\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n'};
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                reply[4*i+j] = matrix[i][j];
            }
        }
        write(client, reply, strlen(reply));

    } while(true);

    close(client);
    close(sockfd);
    return 0;
}
