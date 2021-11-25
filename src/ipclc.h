#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int power(int x, int n);

void print_wrong_arg();
void print_mbit();
void print_count(char *mask);
void print_network_address(char * ip, char * mask);
void print_min_host(char *ip, char *mask);
void print_broadcast(char *ip, char *mask);
void print_max_host(char *ip, char *mask);
void print_class(char *ip);

void to_dec(unsigned char *binary,char *res);
void to_digit(char *ch, unsigned char *binary);

int is_ip(char *ip);
int is_mask(char *mask);

int get_bit_mask(char *mask);
int get_amount_hosts(char *mask);
void get_network_address(char *ip, char *mask, char *res_char, unsigned char *res_mass);
void get_min_host(char *ip, char *mask, char *res_char, unsigned char *res_mass);
void get_broadcast(char *ip, char *mask, char *res_char, unsigned char *res_mass);
void get_max_host(char *ip, char *mask, char *res_char, unsigned char *res_mass);
int get_class(char *ip);