#include "display_data.h"
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

#define OLED_FILE_PATH   "/dev/oled_ssd1306"
#define BH1750_FILE_PATH "/dev/bh1750_sensor"
#define SHT30_FILE_PATH  "/dev/sht30_sensor"

// Buffers to store sensor readings and OLED display content
static char buf_bh1750[64];
static char buf_sht30[64];
static char buf_ssd1306[128];

/*********************************
 * LOW-LEVEL HARDWARE ACCESS
 *********************************/

/* Read data from BH1750 sensor via its device file */
static int read_bh1750(void)
{
    int fd = open(BH1750_FILE_PATH, O_RDONLY);
    if (fd < 0) {
        std::cerr << "open " << BH1750_FILE_PATH << ": " << strerror(errno) << std::endl;
        return -1;
    }

    int ret = read(fd, buf_bh1750, sizeof(buf_bh1750) - 1);
    close(fd);  
    
    if (ret < 0) {
        std::cerr << "read " << BH1750_FILE_PATH << ": " << strerror(errno) << std::endl;
        return -1;
    }
    
    if (ret == 0) {
        std::cerr << "read " << BH1750_FILE_PATH << ": no data available" << std::endl;
        return -1;
    }

    buf_bh1750[ret] = '\0';
    return 0;
}

/* Read data from SHT30 sensor via its device file */
static int read_sht30(void)
{
    int fd = open(SHT30_FILE_PATH, O_RDONLY);
    if (fd < 0) {
        std::cerr << "open " << SHT30_FILE_PATH << ": " << strerror(errno) << std::endl;
        return -1;
    }

    int ret = read(fd, buf_sht30, sizeof(buf_sht30) - 1);
    close(fd); 
    
    if (ret < 0) {
        std::cerr << "read " << SHT30_FILE_PATH << ": " << strerror(errno) << std::endl;
        return -1;
    }
    
    if (ret == 0) {
        std::cerr << "read " << SHT30_FILE_PATH << ": no data available" << std::endl;
        return -1;
    }

    buf_sht30[ret] = '\0';
    return 0;
}

/* Write a string to the SSD1306 OLED display via its device file */
static int write_oled(const char *str_display)
{
    int fd = open(OLED_FILE_PATH, O_WRONLY);
    if (fd < 0) {
        std::cerr << "open " << OLED_FILE_PATH << ": " << strerror(errno) << std::endl;
        return -1;
    }

    int ret = write(fd, str_display, strlen(str_display));
    close(fd);  
    
    if (ret < 0) {
        std::cerr << "write " << OLED_FILE_PATH << ": " << strerror(errno) << std::endl;
        return -1;
    }

    return 0;
}

/********************************************
 * HIGH-LEVEL FUNCTION: READ DATA AND DISPLAY
 ********************************************/

/* Read all sensor data, format it, and send to OLED display */
void display_data(void) 
{
    if (read_sht30() != 0) {
        snprintf(buf_sht30, sizeof(buf_sht30), "ERROR");
    }

    if (read_bh1750() != 0) {
        snprintf(buf_bh1750, sizeof(buf_bh1750), "ERROR");
    }

    // Format data to display on OLED
    snprintf(buf_ssd1306, sizeof(buf_ssd1306), "%s-%s", buf_sht30, buf_bh1750);
    
    if (write_oled(buf_ssd1306) != 0) {
        std::cerr << "write_oled failed" << std::endl;
    }
}

/* Return the current OLED display buffer */
const char* get_ssd1306_buffer(void)
{
    return buf_ssd1306;
}
