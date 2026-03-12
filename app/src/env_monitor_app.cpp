#include "display_data.h"
#include <iostream>
#include <csignal>
#include <unistd.h>

volatile sig_atomic_t keep_running = 1;

void sigint_handler(int sig) {
    (void)sig;
    keep_running = 0;
}

int main(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigint_handler);
    
    std::cout << "Starting sensor monitoring..." << std::endl;
    
    while (keep_running) {
        // Đọc và hiển thị dữ liệu
        display_data();
        
        // In ra console để debug
        const char *data = get_ssd1306_buffer();
        std::cout << "Data: " << data << std::endl;
        
        sleep(5);
    }
    
    std::cout << "\nExiting..." << std::endl;
    return 0;
}
