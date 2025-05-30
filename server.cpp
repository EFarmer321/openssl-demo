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

  if (!OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS, NULL)) {
    std::cerr << "Failed to initialize OpenSSL!\n";
    WSACleanup();
    return EXIT_FAILURE;
  };

  std::cout << "Enter a port number\n";
  int port_num;
  std::cin >> port_num;

  struct sockaddr_in socket_name = {};
  socket_name.sin_family = AF_INET;
  socket_name.sin_port = htons(port_num);
  socket_name.sin_addr.s_addr = inet_addr("127.0.0.1");

  SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (bind(server_socket, (sockaddr *)&socket_name,
           sizeof(struct sockaddr_in)) == -1) {
    std::cout << "Failed to bind!\n";
    WSACleanup();
    while (true) {

    }
    return EXIT_FAILURE;
  };

  listen(server_socket, 1);

  std::cout << "Server is now listening on port " << port_num << ".\n";

  sockaddr_in client_address = {};

  int client_addr_size = sizeof(client_address);
  SOCKET client_socket =
      accept(server_socket, (sockaddr *)&client_address, &client_addr_size);

  const SSL_METHOD *method = TLS_server_method();
  SSL_CTX *context = SSL_CTX_new(method);

  if (!context) {
    std::cerr << "Failed to create server context!\n";
    SSL_CTX_free(context);
    exit(EXIT_FAILURE);
  }

  SSL_CTX_use_certificate_file(context, "server.crt", SSL_FILETYPE_PEM);
  SSL_CTX_use_PrivateKey_file(context, "server.pem", SSL_FILETYPE_PEM);

  if (!SSL_CTX_check_private_key(context)) {
    std::cerr << "Private key is not the same as the certificate!";
    WSACleanup();
    exit(EXIT_FAILURE);
  }

  SSL *ssl_object = SSL_new(context);
  SSL_set_fd(ssl_object, client_socket);
  SSL_accept(ssl_object);
  std::cout << "Accepted the handshake!\n";

  while (true) {
    char buffer[500] = {};

    if (SSL_read(ssl_object, buffer, sizeof(buffer)) > 0)
    {
      std::cout << "Client message: " << std::string(buffer) << "\n";
    }
    else
    {
      std::cerr << "Failed to call SSL_read!\n";
      break;
    }
  }


  SSL_shutdown(ssl_object);
  SSL_free(ssl_object);
  SSL_CTX_free(context);


  closesocket(server_socket);
  closesocket(client_socket);
  WSACleanup();

  return EXIT_SUCCESS;
}
