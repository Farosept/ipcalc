#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int binary_mask[32], binary_ip[32];

int power(int x, int n);

void print_wrong_arg();
void print_mbit();
void print_count();
void print_network_address(char * ip, char * mask);
void print_min_host(char *ip, char *mask);
void print_broadcast(char *ip, char *mask);
void print_max_host(char *ip, char *mask);
void print_class(char *ip);

void to_dec(int *binary,char *res);
void to_digit(char *ch, int *binary);

int is_ip(char *ip);
int is_mask(char *mask);

int get_bit_mask();
int get_amount_hosts();
void get_network_address(char *ip, char *mask, char *res_char, int *res_mass);
void get_min_host(char *ip, char *mask, char *res_char, int *res_mass);
void get_broadcast(char *ip, char *mask, char *res_char, int *res_mass);
void get_max_host(char *ip, char *mask, char *res_char, int *res_mass);
int get_class(char *ip);