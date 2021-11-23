#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int binary_mask[32], binary_ip[32];

void print_wrong_arg();
void to_digit(char *ch, int *binary);
int is_ip(char *ip);
int is_mask(char *mask);