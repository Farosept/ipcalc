#include "ipclc.h"

int main(int argc, char **argv)
{
    int c, option_index = 0;
    int args[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    char *arg_a, *arg_m;
    static struct option long_options[] = {
        {"broadcast", 0, 0, 1}, //+
        {"mbit", 0, 0, 2},      //+
        {"address", 0, 0, 3},   //+
        {"class", 0, 0, 4},     //+
        {"min", 0, 0, 5},       //+
        {"max", 0, 0, 6},       //+
        {"count", 0, 0, 7},     //+
        {0, 0, 0, 0}};
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
    if ((args[0] == 1 && args[1] == 1) || (args[1] == 1 && args[3] == 1))
    {
        if (((is_ip(arg_a) == 0) && args[3] == 0) || (is_mask(arg_m) == 0))
        {
            print_wrong_arg();
        }
        else
        {
            if (args[2] == 1)
            {
                print_broadcast(arg_a, arg_m);
            }
            if (args[3] == 1)
            {
                print_mbit(arg_m);
            }
            if (args[4] == 1)
            {
                print_network_address(arg_a, arg_m);
            }
            if (args[5] == 1)
            {
                print_class(arg_a);
            }
            if (args[6] == 1)
            {
                print_min_host(arg_a, arg_m);
            }
            if (args[7] == 1)
            {
                print_max_host(arg_a, arg_m);
            }
            if (args[8] == 1)
            {
                print_count(arg_m);
            }
            if (args[2] == 0 && args[3] == 0 && args[4] == 0 && args[5] == 0 && args[6] == 0 && args[7] == 0 && args[8] == 0)
            {
                print_network_address(arg_a, arg_m);
                print_mbit(arg_m);
                print_min_host(arg_a, arg_m);
                print_max_host(arg_a, arg_m);
                print_broadcast(arg_a, arg_m);
                print_count(arg_m);
                print_class(arg_a);
            }
        }
    }
    else
    {
        print_wrong_arg();
    }
    return 0;
}
