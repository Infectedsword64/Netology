#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <atomic>

using namespace std::chrono_literals;
int maxClients = 5;
std::atomic_int clientCounter = 0;

void clientThread()
{
    while (clientCounter < maxClients)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        clientCounter += 1;
        std::cout << "Client joined, total clients: " << clientCounter << std::endl;
    }
}

void operatorThread()
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (clientCounter > 0)
        {
            clientCounter -= 1;
            std::cout << "The operator served the client. Number of clients: " << clientCounter << std::endl;
        }
        else
        {
            std::cout << "The operator has finished his work. Number of clients: " << clientCounter << std::endl;
            break;
        }
    }
}

int main() {
    std::thread client(clientThread);
    std::thread operatorT(operatorThread);

    client.join();
    operatorT.join();

    return 0;
}