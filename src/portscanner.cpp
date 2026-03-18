#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>



int main(int argc, char* argv[]){

    std::vector<int> open_ports;

    const char* ip_to_check = "127.0.0.1";

    sockaddr_in target{}; //create target address of type sockaddr_in (struct that holds IP address, port, and address type)
    
    target.sin_family = AF_INET; //specify target has IPv4 address

    for (int i = 0; i < 65535; i++){
        int sock = socket(AF_INET, SOCK_STREAM, 0); //create a TCP socket using IPv4

        if (sock < 0){
            std::cerr << "Failed to create socket\n";
            continue;
        }


        target.sin_port = htons(i); //set port to i
        inet_pton(AF_INET, ip_to_check, &target.sin_addr); //set IP address of target

        timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

        int result = connect(sock, (sockaddr*)&target, sizeof(target));

        if (result == 0){
            open_ports.push_back(i);
        }

        close(sock);
    }

    if (open_ports.size() == 0){
        std::cout << "No open ports on " << ip_to_check << "\n";
    }

    else{
        std::cout << "Open ports on " << ip_to_check << ":\n";

        for (int i = 0; i < open_ports.size(); i++){
            std::cout << open_ports[i] << "\n";
        }
    }


    return 0;
}