#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/fcntl.h>
#include <sys/termios.h>
#include <termios.h>
#include <unistd.h>

enum PARITY_SETTING { EVEN, ODD, DISABLED };

int main (int argc, char **argv)
{
        struct option long_opts[] = {
                { .name = "device", .has_arg = required_argument, .flag = NULL, .val = 'f' },
                { .name = "stopbits", .has_arg = required_argument, .flag = NULL, .val = 's' },
                { .name = "databits", .has_arg = required_argument, .flag = NULL, .val = 'd' },
                { .name = "paritybits", .has_arg = required_argument, .flag = NULL, .val = 'p' },
                { 0 }
        };

        int stopbits = -1, databits = -1;
        char *device_file = NULL;
        enum PARITY_SETTING paritybits;

        int opt_idx = 0;
        char choice;
        while ((choice = getopt_long (argc, argv, "", long_opts, &opt_idx)) != -1) {
                switch (choice) {
                case 'f': device_file = optarg; break;
                case 's': stopbits = strtol (optarg, NULL, 10); break;
                case 'd': databits = strtol (optarg, NULL, 10); break;
                case 'p':
                        if (strcmp (optarg, "even") == 0) {
                                paritybits = EVEN;
                        } else if (strcmp (optarg, "odd")) {
                                paritybits = ODD;
                        } else if (strcmp (optarg, "disabled")) {
                                paritybits = DISABLED;
                        }
                        break;
                case '?': exit (EXIT_FAILURE);
                default: break;
                }
        }

        if (!device_file) {
                fprintf (stderr, "ERROR: You must specify a device! Use --device path/to/device\n");
                exit (EXIT_FAILURE);
        }

        int fd = open (device_file, O_RDWR | O_NOCTTY);

        if (fd < 0) {
                perror ("open");
                exit (EXIT_FAILURE);
        }

        struct termios config;

        cfmakeraw (&config);

        switch (paritybits) {
        case EVEN:
                config.c_cflag &= ~(PARODD);
                config.c_cflag |= PARENB;
                break;
        case ODD:
                config.c_cflag |= PARODD;
                config.c_cflag |= PARENB;
                break;
        case DISABLED: config.c_cflag &= ~(PARENB); break;
        default:
                fprintf (stderr, "ERROR: invalid paritybits flag value\n");
                exit (EXIT_FAILURE);
                break;
        }

        switch (stopbits) {
        case 1: config.c_cflag &= ~(CSTOPB); break;
        case 2: config.c_cflag |= (CSTOPB); break;
        default:
                fprintf (stderr, "ERROR: invalid stopbits flag value, must be either 1 or 2.\n");
                exit (EXIT_FAILURE);
                break;
        }

        config.c_cflag |= (CLOCAL | CREAD);
        config.c_iflag &= ~(IXOFF | IXANY);
        config.c_cc[VMIN] = 0;  // you likely don't want to change this
        config.c_cc[VTIME] = 0; // or this
        cfsetispeed (&config, 9600);
        cfsetospeed (&config, 9600);

        if (tcsetattr (fd, TCSANOW, &config) < 0) {
                perror ("tcsetattr");
                exit (EXIT_FAILURE);
        }

        char buf[255];

        if (read (fd, buf, 254) < 0) {
                perror ("read");
                exit (EXIT_FAILURE);
        }

        buf[254] = '\0';
        printf ("%s", buf);

        return 0;
}