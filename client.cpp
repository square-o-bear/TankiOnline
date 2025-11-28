#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

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
    int x, y;
    char v;

    do {
        cin >> x;
        if (x == -1) {
            char msg[3] = {'-', '1', ' '};
            write(sockfd, msg, strlen(msg));
            break;
        }
        else {
            cin >> y >> v;
            char msg[3] = {IntToChar(x), IntToChar(y), v};
            write(sockfd, msg, strlen(msg));

            char buf[1024] = {0};
            read(sockfd, buf, sizeof(buf)-1);
            std::cout << buf << "\n\n";
        }

    } while(true);

    close(sockfd);
    return 0;
}