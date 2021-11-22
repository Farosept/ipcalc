#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
int main(int argc, char **argv)
{

    long int c;
    int digit_optind = 0;
    int option_index = 0;

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
            printf("параметр %s", long_options[option_index].name);
            if (optarg)
                printf(" с аргументом %s", optarg);
            printf("\n");
            break;
        case 2:
            printf("параметр %s", long_options[option_index].name);
            if (optarg)
                printf(" с аргументом %s", optarg);
            printf("\n");
            break;
        case 3:
            printf("параметр %s", long_options[option_index].name);
            if (optarg)
                printf(" с аргументом %s", optarg);
            printf("\n");
            break;
        case 4:
            printf("параметр %s", long_options[option_index].name);
            if (optarg)
                printf(" с аргументом %s", optarg);
            printf("\n");
            break;
        case 5:
            printf("параметр %s", long_options[option_index].name);
            if (optarg)
                printf(" с аргументом %s", optarg);
            printf("\n");
            break;
        case 6:
            printf("параметр %s", long_options[option_index].name);
            if (optarg)
                printf(" с аргументом %s", optarg);
            printf("\n");
            break;
        case 7:
            printf("параметр %s", long_options[option_index].name);
            if (optarg)
                printf(" с аргументом %s", optarg);
            printf("\n");
            break;
        case 'a':
            printf(" a");
            printf(" с аргументом %s", optarg);
            break;
        case 'm':
            printf(" m");
            printf(" с аргументом %s", optarg);
            break;
        case '?':
            printf("\nipclc -a <ip-адрес> -m <маска>\n");
            printf("\nДоступные параметры:\n");
            printf("--broadcast		вывод широковещательного адреса\n");
            printf("--mbit		вывод количества бит маски\n");
            printf("--address		вывод адреса сети\n");
            printf("--class		вывод класса адреса\n");
            printf("--min		вывод минимального адреса\n");
            printf("--max		вывод максимального адреса\n");
            printf("--count		вывод количества хостов\n");
        default:
            abort();
        }
    }
    return 0;
}