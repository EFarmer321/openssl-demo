#include <cstdlib>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "utils.h"
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <windows.h>

int main() {
    WSAData wsa_data;

    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
      std::cerr << "WSAStartup failed to run\n";
      WSACleanup();
      return EXIT_FAILURE;
    }

    std::cout << "Enter a port number\n";
    int port_num;
    std::cin >> port_num;

    struct sockaddr_in socket_name = {};
    socket_name.sin_family = AF_INET;
    socket_name.sin_port = htons(port_num);
    socket_name.sin_addr.s_addr = inet_addr("127.0.0.1");

    const SSL_METHOD *method = TLS_client_method();
    SSL_CTX *context = SSL_CTX_new(method);
    SSL_CTX_use_PrivateKey_file(context, "server.pem", SSL_FILETYPE_PEM);

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(server_socket, (sockaddr*) &socket_name, sizeof(struct sockaddr_in));

    SSL *ssl_object = SSL_new(context);
    SSL_set_fd(ssl_object, server_socket);
    SSL_connect(ssl_object);

    std::cout << "Handshake.\n";

    while (true)
    {
      std::cout << "Type in a message to send to the server. Type `quit` to quit: ";
      std::string message = Utils::read_string();

      if (message == "quit") {
        break;
      }
      else {
        if (SSL_write(ssl_object, message.c_str(), strlen(message.c_str())) <= 0) {
          std::cerr << "SSWL_write failed!";
          break;
        }
      }
    }

    closesocket(server_socket);
    WSACleanup();
    
    return EXIT_SUCCESS;
}