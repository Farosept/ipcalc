#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int binary_mask[32], binary_ip[32];

int power(int x, int n);
void print_wrong_arg();
void print_mbit(int bits);
void print_network_address(char * ip, char * mask);
void to_dec(int *binary,char *res);
void to_digit(char *ch, int *binary);
int is_ip(char *ip);
int is_mask(char *mask);
int get_bit_mask();
void get_network_address(char *ip, char *mask,char * res);
