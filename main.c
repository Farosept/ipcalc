#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

void print_wrong_arg()
{
    printf("\nipclc -a <ip-адрес> -m <маска>\n");
    printf("\nДоступные параметры:\n");
    printf("--broadcast		вывод широковещательного адреса\n");
    printf("--mbit		вывод количества бит маски\n");
    printf("--address		вывод адреса сети\n");
    printf("--class		вывод класса адреса\n");
    printf("--min		вывод минимального адреса\n");
    printf("--max		вывод максимального адреса\n");
    printf("--count		вывод количества хостов\n");
}

int main(int argc, char **argv)
{
    int c, digit_optind = 0, option_index = 0;
    int args[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    char *arg_a, *arg_m;
    static struct option long_options[] = {
        {"broadcast", 0, 0, 1},
        {"mbit", 0, 0, 2},
        {"address", 0, 0, 3},
        {"class", 0, 0, 4},
        {"min", 0, 0, 5},
        {"max", 0, 0, 6},
        {"count", 0, 0, 7},
        {0, 0, 0, 0}};
    if (argc == 1)
    {
        printf("\nipclc -a <ip-адрес> -m <маска>\n");
        printf("\nДоступные параметры:\n");
        printf("--broadcast		вывод широковещательного адреса\n");
        printf("--mbit		вывод количества бит маски\n");
        printf("--address		вывод адреса сети\n");
        printf("--class		вывод класса адреса\n");
        printf("--min		вывод минимального адреса\n");
        printf("--max		вывод максимального адреса\n");
        printf("--count		вывод количества хостов\n");
    }
    while ((c = getopt_long(argc, argv, "a:m:", long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case 1:
            args[2] = 1;
            break;
        case 2:
            args[3] = 1;
            break;
        case 3:
            args[4] = 1;
            break;
        case 4:
            args[5] = 1;
            break;
        case 5:
            args[6] = 1;
            break;
        case 6:
            args[7] = 1;
            break;
        case 7:
            args[8] = 1;
            break;
        case 'a':
            arg_a = optarg;
            args[0] = 1;
            break;
        case 'm':
            arg_m = optarg;
            args[1] = 1;
            break;
        case '?':
            print_wrong_arg();
        default:
            abort();
        }
    }
    if (args[0] == 1 && args[1] == 1)
    {
        printf("\n a");
        printf(" с аргументом %s\n", arg_a);
        printf("\n m");
        printf(" с аргументом %s\n", arg_m);
    }
    else
    {
        print_wrong_arg();
    }
    return 0;
}