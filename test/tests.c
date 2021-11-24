#include <stdlib.h>
#include "ctest.h"
#include "ipclc.h"


//to_digit
CTEST(to_digit, test_255_255_255_0){
    // Given
    char ip[] = "255.255.255.0";

    // When
    int binary[32];
    to_digit(ip,binary);

    // Then
    const int expected[] = {1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0};

    ASSERT_DATA(expected,32, binary,32);
}
CTEST(to_digit, test_255_255_252_0){
    // Given
    char ip[] = "255.255.252.0";

    // When
    int binary[32];
    to_digit(ip,binary);

    // Then
    const int expected[] = {1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,0,0, 0,0,0,0,0,0,0,0};

    ASSERT_DATA(expected,32, binary,32);
}

CTEST(to_digit, test_192_168_0_2){
    // Given
    char ip[] = "192.168.0.2";

    // When
    int binary[32];
    to_digit(ip,binary);

    // Then
    const int expected[] = {1,1,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};

    ASSERT_DATA(expected,32, binary,32);
}
CTEST(to_digit, test_192_0_1_2){
    // Given
    char ip[] = "192.0.1.2";

    // When
    int binary[32];
    to_digit(ip,binary);

    // Then
    const int expected[] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0};

    ASSERT_DATA(expected,32, binary,32);
}

//is_ip
CTEST(is_ip, test_192_0_1_2_TRUE){
    // Given
    char ip[] = "192.0.1.2";

    // When
    const int real = is_ip(ip);

    // Then
    const int expected = 1;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_ip, test_192_0_0_0_TRUE){
    // Given
    char ip[] = "192.0.1.2";

    // When
    const int real = is_ip(ip);

    // Then
    const int expected = 1;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_ip, test_asd_FALSE){
    // Given
    char ip[] = "asd";

    // When
    const int real = is_ip(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_ip, test_11111_1111_222_333_FALSE){
    // Given
    char ip[] = "11111.1111.222.333";

    // When
    const int real = is_ip(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_ip, test_192_168_0_FALSE){
    // Given
    char ip[] = "192.168.0";

    // When
    const int real = is_ip(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}

//is_mask
CTEST(is_mask, test_255_255_255_0_TRUE){
    // Given
    char ip[] = "255.255.255.0";

    // When
    const int real = is_mask(ip);

    // Then
    const int expected = 1;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_mask, test_255_252_0_0_TRUE){
    // Given
    char ip[] = "255.252.0.0";

    // When
    const int real = is_mask(ip);

    // Then
    const int expected = 1;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_mask, test_asd_FALSE){
    // Given
    char ip[] = "asd";

    // When
    const int real = is_mask(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_mask, test_11111_1111_222_333_FALSE){
    // Given
    char ip[] = "11111.1111.222.333";

    // When
    const int real = is_mask(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}
CTEST(is_mask, test_255_255_33_0_FALSE){
    // Given
    char ip[] = "255.255.33.0";

    // When
    const int real = is_mask(ip);

    // Then
    const int expected = 0;

    ASSERT_EQUAL(expected, real);
}