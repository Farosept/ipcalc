#include <stdlib.h>
#include "ctest.h"
#include "ipclc.h"

//to_digit
CTEST(to_digit, test_mask_1)
{
    // Given
    char ip[] = "255.255.255.254";

    // When
    unsigned char binary[4] = {0, 0, 0, 0};
    to_digit(ip, binary);

    // Then
    const unsigned char expected[] = {255, 255, 255, 254};

    ASSERT_DATA(expected, 4, binary, 4);
}
CTEST(to_digit, test_mask_2)
{
    // Given
    char ip[] = "255.255.252.0";

    // When
    unsigned char binary[4] = {0, 0, 0, 0};
    to_digit(ip, binary);

    // Then
    const unsigned char expected[] = {255, 255, 252, 0};

    ASSERT_DATA(expected, 4, binary, 4);
}
CTEST(to_digit, test_mask_3)
{
    // Given
    char ip[] = "255.255.0.0";

    // When
    unsigned char binary[4] = {0, 0, 0, 0};
    to_digit(ip, binary);

    // Then
    const unsigned char expected[] = {255, 255, 0, 0};

    ASSERT_DATA(expected, 4, binary, 4);
}
CTEST(to_digit, test_mask_4)
{
    // Given
    char ip[] = "255.0.0.0";

    // When
    unsigned char binary[4] = {0, 0, 0, 0};
    to_digit(ip, binary);

    // Then
    const unsigned char expected[] = {255, 0, 0, 0};

    ASSERT_DATA(expected, 4, binary, 4);
}
CTEST(to_digit, test_ip_1)
{
    // Given
    char ip[] = "192.168.0.0";

    // When
    unsigned char binary[4] = {0, 0, 0, 0};
    to_digit(ip, binary);

    // Then
    const unsigned char expected[] = {192, 168, 0, 0};

    ASSERT_DATA(expected, 4, binary, 4);
}
CTEST(to_digit, test_ip_2)
{
    // Given
    char ip[] = "192.168.0.2";

    // When
    unsigned char binary[4] = {0, 0, 0, 0};
    to_digit(ip, binary);

    // Then
    const unsigned char expected[] = {192, 168, 0, 2};

    ASSERT_DATA(expected, 4, binary, 4);
}
CTEST(to_digit, test_ip_3)
{
    // Given
    char ip[] = "11.0.0.2";

    // When
    unsigned char binary[4] = {0, 0, 0, 0};
    to_digit(ip, binary);

    // Then
    const unsigned char expected[] = {11, 0, 0, 2};

    ASSERT_DATA(expected, 4, binary, 4);
}

//is_ip
CTEST(is_ip, test_1_ok)
{
    // Given
    char ip[] = "192.0.1.2";

    // When
    const int real = is_ip(ip);

    // Then
    const int expected = 1;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_ip, test_2_no)
{
    // Given
    char ip[] = "192.0.1.";

    // When
    const int real = is_ip(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_ip, test_3_no)
{
    // Given
    char ip[] = "asd";

    // When
    const int real = is_ip(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_ip, test_4_no)
{
    // Given
    char ip[] = "11111.1111.222.333";

    // When
    const int real = is_ip(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_ip, test_5_no)
{
    // Given
    char ip[] = "192.168.0";

    // When
    const int real = is_ip(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}

//is_mask
CTEST(is_mask, test_1_ok)
{
    // Given
    char ip[] = "255.255.255.0";

    // When
    const int real = is_mask(ip);

    // Then
    const int expected = 1;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_mask, test_2_no)
{
    // Given
    char ip[] = "255.252.0";

    // When
    const int real = is_mask(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_mask, test_3_no)
{
    // Given
    char ip[] = "asd";

    // When
    const int real = is_mask(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_mask, test_4_no)
{
    // Given
    char ip[] = "2555.255.255.0";

    // When
    const int real = is_mask(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_mask, test_5_no)
{
    // Given
    char ip[] = "255.255.33.0";

    // When
    const int real = is_mask(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_mask, test_6_no)
{
    // Given
    char ip[] = "255.255.255.";

    // When
    const int real = is_mask(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}

//get_bits
CTEST(get_bits, test_1)
{
    // Given
    char ip[] = "255.255.255.0";

    // When
    const int real = get_bit_mask(ip);

    // Then
    const int expected = 24;

    ASSERT_EQUAL(expected, real);
}
CTEST(get_bits, test_2)
{
    // Given
    char ip[] = "255.255.252.0";

    // When
    const int real = get_bit_mask(ip);

    // Then
    const int expected = 22;

    ASSERT_EQUAL(expected, real);
}
CTEST(get_bits, test_3)
{
    // Given
    char ip[] = "255.255.0.0";

    // When
    const int real = get_bit_mask(ip);

    // Then
    const int expected = 16;

    ASSERT_EQUAL(expected, real);
}

//to_dec
CTEST(to_dec, test_1)
{
    // Given
    unsigned char ip[] = {255,255,255,0};
    // When
    char res[13];
    to_dec(ip,res);
    
    const char expected[] = "255.255.255.0";

    ASSERT_DATA(expected, 13, res, 13);
}
CTEST(to_dec, test_2)
{
    // Given
    unsigned char ip[] = {192,168,0,0};
    // When
    char res[11];
    to_dec(ip,res);
    
    const char expected[] = "192.168.0.0";

    ASSERT_DATA(expected, 11, res, 11);
}
CTEST(to_dec, test_3)
{
    // Given
    unsigned char ip[] = {192,0,3,20};
    // When
    char res[10];
    to_dec(ip,res);
    
    const char expected[] = "192.0.3.20";

    ASSERT_DATA(expected, 10, res, 10);
}
CTEST(to_dec, test_4)
{
    // Given
    unsigned char ip[] = {11,0,0,2};
    // When
    char res[8];
    to_dec(ip,res);
    
    const char expected[] = "11.0.0.2";

    ASSERT_DATA(expected, 8, res, 8);
}

//get_network_address(char *ip, char *mask, char *res_char, unsigned char *res_mass)
CTEST(get_network_address, test_1)
{
    // Given
    char ip[] = "192.168.3.5";
    char mask[] = "255.255.252.0";
    // When
    unsigned char real[] = {0,0,0,0};
    get_network_address(ip, mask, NULL, real);
    
    // Then
    const unsigned char expected[] = {192,168,0,0};

    ASSERT_DATA(expected, 4, real, 4);
}
CTEST(get_network_address, test_2)
{
    // Given
    char ip[] = "192.168.3.5";
    char mask[] = "255.255.255.0";
    // When
    unsigned char real[] = {0,0,0,0};
    get_network_address(ip, mask, NULL, real);
    
    // Then
    const unsigned char expected[] = {192,168,3,0};

    ASSERT_DATA(expected, 4, real, 4);
}

//void get_min_host(char *ip, char *mask, char *res_char, unsigned char *res_mass)
CTEST(get_min_host, test_1)
{
    // Given
    char ip[] = "192.168.3.5";
    char mask[] = "255.255.255.0";
    // When
    unsigned char real[] = {0,0,0,0};
    get_min_host(ip, mask, NULL, real);
    
    // Then
    const unsigned char expected[] = {192,168,3,1};

    ASSERT_DATA(expected, 4, real, 4);
}
CTEST(get_min_host, test_2)
{
    // Given
    char ip[] = "192.168.3.5";
    char mask[] = "255.255.252.0";
    // When
    unsigned char real[] = {0,0,0,0};
    get_min_host(ip, mask, NULL, real);
    
    // Then
    const unsigned char expected[] = {192,168,0,1};

    ASSERT_DATA(expected, 4, real, 4);
}

//void get_broadcast(char *ip, char *mask, char *res_char, unsigned char *res_mass)
CTEST(get_broadcast, test_1)
{
    // Given
    char ip[] = "192.168.3.5";
    char mask[] = "255.255.252.0";
    // When
    unsigned char real[] = {0,0,0,0};
    get_broadcast(ip, mask, NULL, real);
    
    // Then
    const unsigned char expected[] = {192,168,3,255};

    ASSERT_DATA(expected, 4, real, 4);
}
CTEST(get_broadcast, test_2)
{
    // Given
    char ip[] = "192.168.3.5";
    char mask[] = "255.255.255.0";
    // When
    unsigned char real[] = {0,0,0,0};
    get_broadcast(ip, mask, NULL, real);
    
    // Then
    const unsigned char expected[] = {192,168,3,255};

    ASSERT_DATA(expected, 4, real, 4);
}
CTEST(get_broadcast, test_3)
{
    // Given
    char ip[] = "192.168.1.10";
    char mask[] = "255.255.255.0";
    // When
    unsigned char real[] = {0,0,0,0};
    get_broadcast(ip, mask, NULL, real);
    
    // Then
    const unsigned char expected[] = {192,168,1,255};

    ASSERT_DATA(expected, 4, real, 4);
}
CTEST(get_broadcast, test_4)
{
    // Given
    char ip[] = "192.168.1.10";
    char mask[] = "255.255.0.0";
    // When
    unsigned char real[] = {0,0,0,0};
    get_broadcast(ip, mask, NULL, real);
    
    // Then
    const unsigned char expected[] = {192,168,255,255};

    ASSERT_DATA(expected, 4, real, 4);
}

//void get_max_host(char *ip, char *mask, char *res_char, unsigned char *res_mass)
CTEST(get_max_host, test_1)
{
    // Given
    char ip[] = "192.168.1.10";
    char mask[] = "255.255.255.0";
    // When
    unsigned char real[] = {0,0,0,0};
    get_max_host(ip, mask, NULL, real);
    
    // Then
    const unsigned char expected[] = {192,168,1,254};

    ASSERT_DATA(expected, 4, real, 4);
}
CTEST(get_max_host, test_2)
{
    // Given
    char ip[] = "192.168.1.10";
    char mask[] = "255.255.252.0";
    // When
    unsigned char real[] = {0,0,0,0};
    get_max_host(ip, mask, NULL, real);
    
    // Then
    const unsigned char expected[] = {192,168,3,254};

    ASSERT_DATA(expected, 4, real, 4);
}

//int get_amount_hosts(char *mask)
CTEST(get_amount_hosts, test_1)
{
    // Given
    char mask[] = "255.255.255.0";
    // When
    int real = get_amount_hosts(mask);
    
    // Then
    const int expected = 254;

     ASSERT_EQUAL(expected, real);
}
CTEST(get_amount_hosts, test_2)
{
    // Given
    char mask[] = "255.255.252.0";
    // When
    int real = get_amount_hosts(mask);
    
    // Then
    const int expected = 1022;

     ASSERT_EQUAL(expected, real);
}
CTEST(get_amount_hosts, test_3)
{
    // Given
    char mask[] = "255.255.0.0";
    // When
    int real = get_amount_hosts(mask);
    
    // Then
    const int expected = 65534;

     ASSERT_EQUAL(expected, real);
}