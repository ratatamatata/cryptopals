#ifndef MAIN
#define MAIN

#endif // MAIN
#include <iostream>
#include <bitset>

using namespace std;

char bits_to_base64(bitset<6> base64_bset);
char int_to_base64(int dec);
string hexstr_to_base64(string hexstr);
string hexstr_to_ascii(string hexstr, char xorchar = 0);
int hex_to_decimal(char hex);
string ascii_to_hex(string str);
string repeating_key_xor(string str, string key);
