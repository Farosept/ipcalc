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
void print_mbit(char *mask)
{
    printf("Bitmask: %d\n", get_bit_mask(mask));
}
void print_count(char *mask)
{
    printf("Hosts: %d\n", get_amount_hosts(mask));
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

void to_dec(unsigned char *binary, char *res)
{
    int octets[] = {0, 0, 0, 0};
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        octets[i] += (int)binary[i];
    }
    sprintf(res, "%d.%d.%d.%d", octets[0], octets[1], octets[2], octets[3]);
}
void to_digit(char *ch, unsigned char *binary)
{
    int octet1, octet2, octet3, octet4, i = 0;
    sscanf(ch, "%d.%d.%d.%d", &octet1, &octet2, &octet3, &octet4);
    int octets[] = {octet1, octet2, octet3, octet4};
    for (i = 0; i < 4; i++)
    {
        int n = octets[i];
        int k = 0;
        do
        {
            binary[i] |= (n % 2) << k;
            n = n / 2;
            k++;
        } while (n > 0 || k < 7);
    }
}

int is_ip(char *ip)
{
    int k = 0, j = 0;
    for (j = 0; j < 4; j++)
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

    int octet1 = 0, octet2 = 0, octet3 = 0, octet4 = 0;
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
    int k = 0, j = 0, i = 0;
    for (j = 0; j < 4; j++)
    {
        int z = 0;
        while ((mask[k] != '.') && (mask[k] != '\0'))
        {
            k++;
            z++;
            if (z > 3)
            {
                return 0;
            }
        }
        k++;
    }
    unsigned char m[4] = {0, 0, 0, 0};
    to_digit(mask, m);
    j = 6;
    for (i = 0; i < 4; i++)
    {
        for (j = 6; j > 0; j--)
        {
            if (((m[i] & (1 << (j + 1))) == 0) && ((m[i] & (1 << j)) > 0))
            {
                return 0;
            }
        }
    }
    int octet1 = 0, octet2 = 0, octet3 = 0, octet4 = 0;
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

int get_bit_mask(char *mask)
{
    unsigned char m[4] = {0, 0, 0, 0};
    to_digit(mask, m);
    int bits = 0, i = 0, j = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if ((m[i] & (1 << j)) > 0)
            {
                bits++;
            }
        }
    }
    return bits;
}

void get_network_address(char *ip, char *mask, char *res_char, unsigned char *res_mass)
{
    unsigned char address[4] = {0, 0, 0, 0};
    unsigned char m_bin[4] = {0, 0, 0, 0};
    unsigned char ip_bin[4] = {0, 0, 0, 0};
    to_digit(mask, m_bin);
    to_digit(ip, ip_bin);
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        address[i] = (ip_bin[i] & m_bin[i]);
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

void get_min_host(char *ip, char *mask, char *res_char, unsigned char *res_mass)
{
    unsigned char address[4] = {0, 0, 0, 0};
    get_network_address(ip, mask, NULL, address);
    address[3] |= 1 << 0;
    if (res_mass != NULL)
    {
        int i = 0;
        for (i = 0; i < 32; i++)
        {
            res_mass[i] = address[i];
        }
    }
    if (res_char != NULL)
    {
        to_dec(address, res_char);
    }
}

void get_broadcast(char *ip, char *mask, char *res_char, unsigned char *res_mass)
{
    unsigned char address[4] = {0, 0, 0, 0}, invert_mask[4] = {0, 0, 0, 0};
    unsigned char m_bin[4] = {0, 0, 0, 0};
    unsigned char ip_bin[4] = {0, 0, 0, 0};
    to_digit(mask, m_bin);
    to_digit(ip, ip_bin);
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        invert_mask[i] = ~m_bin[i];
    }
    i = 0;
    for (i = 0; i < 4; i++)
    {
        address[i] = ip_bin[i] | invert_mask[i];
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

void get_max_host(char *ip, char *mask, char *res_char, unsigned char *res_mass)
{
    unsigned char address[4] = {0, 0, 0, 0};
    get_broadcast(ip, mask, NULL, address);
    address[3] &= ~(1 << 0);
    if (res_mass != NULL)
    {
        int i = 0;
        for (i = 0; i < 4; i++)
        {
            res_mass[i] = address[i];
        }
    }
    if (res_char != NULL)
    {
        to_dec(address, res_char);
    }
}

int get_amount_hosts(char *mask)
{
    int bit_mask = get_bit_mask(mask);
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
    return 1;
}

int power(int x, int n)
{
    if (n == 0)
        return 1;
    return x * power(x, n - 1);
}