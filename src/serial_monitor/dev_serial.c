#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <termios.h>
#include <unistd.h>

int main (int argc, char **argv)
{
        if (argc < 2) {
                fprintf (stderr, "must specify serial port!\n");
                exit (EXIT_FAILURE);
        }

        int fd = open (argv[1], O_RDWR | O_NOCTTY | O_NDELAY);

        if (fd < 0) {
                perror ("open");
                exit (EXIT_FAILURE);
        }

        struct termios config;
        tcgetattr(fd, &config);

        speed_t input_baud = cfgetispeed(&config);
        speed_t output_baud = cfgetospeed(&config);

        printf("Input Baud: %lu\n", input_baud);
        printf("Output Baud: %lu\n", output_baud);

        return 0; 

}