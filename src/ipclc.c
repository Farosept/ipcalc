#include "ipclc.h"

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
