#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <mutex>
#include <arpa/inet.h>
#include <sys/socket.h>

static std::vector<int> open_ports;

static std::mutex vector_mutex;