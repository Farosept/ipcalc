#include "ipclc.h"

//Print
void print_wrong_arg()
{
    printf("\nipclc -a <ip-адрес> -m <маска>\n");
    printf("\nДоступные параметры:\n");
    printf("--broadcast		вывод широковещательного адреса\n");
    printf("--mbit		вывод количества бит маски\n");
    printf("--2ress		вывод адреса сети\n");
    printf("--class		вывод класса адреса\n");
    printf("--min		вывод минимального адреса\n");
    printf("--max		вывод максимального адреса\n");
    printf("--count		вывод количества хостов\n");
}
void print_mbit()
{
    printf("Bitmask: %d\n", get_bit_mask());
}
void print_count()
{
    printf("Hosts: %d\n", get_amount_hosts());
}
void print_network_address(char *ip, char *mask)
{
    char res[20];
    get_network_address(ip, mask, res, NULL);
    printf("Network address: %s\n", res);
}
void print_min_host(char *ip, char *mask)
{
    char res[20];
    get_min_host(ip, mask, res, NULL);
    printf("Min host: %s\n", res);
}
void print_broadcast(char *ip, char *mask)
{
    char res[20];
    get_broadcast(ip, mask, res, NULL);
    printf("Broadcast: %s\n", res);
}
void print_max_host(char *ip, char *mask)
{
    char res[20];
    get_max_host(ip, mask, res, NULL);
    printf("Max host: %s\n", res);
}
void print_class(char *ip)
{
    int class = get_class(ip);
    switch (class)
    {
    case 1:
        printf("Class: A\n");
        break;
    case 2:
        printf("Class: B\n");
        break;
    case 3:
        printf("Class: C\n");
        break;
    case 4:
        printf("Class: D\n");
        break;
    case 5:
        printf("Class: E\n");
        break;
    default:
        break;
    }
}

void to_dec(int *binary, char *res)
{
    int octets[] = {0, 0, 0, 0};
    int k = 0, p = 0;
    for (int i = 0; i < 32; i += 8)
    {
        p = 7;
        for (int j = i; j < i + 8; j++)
        {
            octets[k] += (power(2, p) * binary[j]);
            p--;
        }
        k++;
    }
    sprintf(res, "%d.%d.%d.%d", octets[0], octets[1], octets[2], octets[3]);
}
void to_digit(char *ch, int *binary)
{
    int octet1, octet2, octet3, octet4, i = 0;
    sscanf(ch, "%d.%d.%d.%d", &octet1, &octet2, &octet3, &octet4);
    int octets[] = {octet1, octet2, octet3, octet4};
    for (int j = 0; j < 32; j++)
    {
        binary[j] = 0;
    }
    for (int j = 0; j < 4; j++)
    {
        int n = octets[j];
        int k = 0;
        do
        {
            binary[i] = n % 2;
            n = n / 2;
            i++;
            k++;
        } while (n > 0 || k < 8);
    }
    for (int u = 0; u < 4; u++)
    {
        for (int i = 0; i < 4; i++)
        {
            int tmp = binary[(8 * u) + i];
            binary[(8 * u) + i] = binary[(7 + (8 * u)) - i];
            binary[(7 + (8 * u)) - i] = tmp;
        }
    }
}

int is_ip(char *ip)
{
    int k = 0;
    for (int j = 0; j < 4; j++)
    {
        int i = 0;
        while ((ip[k] != '.') && (ip[k] != '\0'))
        {
            k++;
            i++;
            if (i > 3)
            {
                return 0;
            }
        }
        k++;
    }

    int octet1, octet2, octet3, octet4;
    int res = sscanf(ip, "%d.%d.%d.%d", &octet1, &octet2, &octet3, &octet4);
    if (res != 4)
    {
        return 0;
    }
    if ((octet1 > 0 && octet1 < 255) && (octet2 >= 0 && octet2 < 255) && (octet3 >= 0 && octet3 < 255) && (octet4 >= 0 && octet4 < 255))
    {
        return 1;
    }
    return 0;
}
int is_mask(char *mask)
{
    int k = 0;
    for (int j = 0; j < 4; j++)
    {
        int i = 0;
        while ((mask[k] != '.') && (mask[k] != '\0'))
        {
            k++;
            i++;
            if (i > 3)
            {
                return 0;
            }
        }
        k++;
    }
    to_digit(mask, binary_mask);
    for (int j = 1; j < 32; j++)
    {
        if (binary_mask[j] == 1 && binary_mask[j - 1] == 0)
        {
            return 0;
        }
    }
    int octet1, octet2, octet3, octet4;
    int res = sscanf(mask, "%d.%d.%d.%d", &octet1, &octet2, &octet3, &octet4);
    if (res != 4)
    {
        return 0;
    }
    if ((octet1 >= 0 && octet1 <= 255) && (octet2 >= 0 && octet2 <= 255) && (octet3 >= 0 && octet3 <= 255) && (octet4 >= 0 && octet4 <= 255))
    {
        return 1;
    }
    return 0;
}

int get_bit_mask()
{
    int bits = 0;
    for (int i = 0; i < 32; i++)
    {
        if (binary_mask[i] == 1)
        {
            bits++;
        }
    }
    return bits;
}

void get_network_address(char *ip, char *mask, char *res_char, int *res_mass)
{
    int address[32];
    for (int i = 0; i < 32; i++)
    {
        address[i] = (binary_ip[i] * binary_mask[i]);
        if (res_mass != NULL)
        {

            res_mass[i] = address[i];
        }
    }
    if (res_char != NULL)
    {
        to_dec(address, res_char);
    }
}

void get_min_host(char *ip, char *mask, char *res_char, int *res_mass)
{
    int address[32];
    get_network_address(ip, mask, NULL, address);
    address[31] = 1;
    if (res_mass != NULL)
    {
        for (int i = 0; i < 32; i++)
        {
            res_mass[i] = address[i];
        }
    }
    if (res_char != NULL)
    {
        to_dec(address, res_char);
    }
}

void get_broadcast(char *ip, char *mask, char *res_char, int *res_mass)
{
    int address[32], invert_mask[32];

    for (int i = 0; i < 32; i++)
    {
        if (binary_mask[i] == 1)
        {
            invert_mask[i] = 0;
        }
        else
        {
            invert_mask[i] = 1;
        }
    }
    for (int i = 0; i < 32; i++)
    {
        address[i] = invert_mask[i] | binary_ip[i];
        if (res_mass != NULL)
        {

            res_mass[i] = address[i];
        }
    }

    if (res_char != NULL)
    {
        to_dec(address, res_char);
    }
}

void get_max_host(char *ip, char *mask, char *res_char, int *res_mass)
{
    int address[32];
    get_broadcast(ip, mask, NULL, address);
    address[31] = 0;
    if (res_mass != NULL)
    {
        for (int i = 0; i < 32; i++)
        {
            res_mass[i] = address[i];
        }
    }
    if (res_char != NULL)
    {
        to_dec(address, res_char);
    }
}

int get_amount_hosts()
{
    int bit_mask = get_bit_mask();
    return power(2, 32 - bit_mask) - 2;
}

int get_class(char *ip)
{
    int octet1, octet2, octet3, octet4;
    sscanf(ip, "%d.%d.%d.%d", &octet1, &octet2, &octet3, &octet4);
    if (octet1 >= 1 && octet1 <= 127)
    {
        return 1;
    }
    if (octet1 >= 128 && octet1 <= 191)
    {
        return 2;
    }
    if (octet1 >= 192 && octet1 <= 223)
    {
        return 3;
    }
    if (octet1 >= 224 && octet1 <= 239)
    {
        return 4;
    }
    if (octet1 >= 240 && octet1 <= 254)
    {
        return 5;
    }
}

int power(int x, int n)
{
    if (n == 0)
        return 1;
    return x * power(x, n - 1);
}