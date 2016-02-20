#include <iostream>
#include <main.h>
#include <bitset>
#include <cstring>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <iterator>
#include <stdlib.h> //itoa
#include <iomanip> // setw

using namespace std;

int main()
{
//    bitset<hex_lenght> bits('aa');
//    int to_base64_bset = ((bits.to_ulong() << 58) >> 58);
//    bitset<6> base64_bset(to_base64_bset);
    constexpr auto str = "abcd12"; //11af61
    string nm_str = "abcd12";
    string base64_final;
    char hex = 'a';
    int dec = hex_to_decimal(hex);
    bitset<6> base64_bset(dec);
    bitset<strlen(str)*4> sbase64_bset,ibase64_bset;

    for(size_t i=0; i<strlen(str); i++){
        int char_value = hex_to_decimal(str[i]);
        sbase64_bset = sbase64_bset << 4;
        cout << "Current value of char_value is " << char_value << endl;
        ibase64_bset = char_value;
        cout << "Current value of ibase64_bset is " << ibase64_bset << endl;
        sbase64_bset = sbase64_bset | ibase64_bset;
        cout << "Current value of bitset is " << sbase64_bset << endl;
    }

    for(auto i=(strlen(str)*4)/6; i>0; i--){
        for(size_t i=0; i<6; i++){
            base64_bset[i] = sbase64_bset[i];
        }
        cout << "Current value of base64_bset is " << base64_bset << endl;
        sbase64_bset = sbase64_bset >> 6;
        cout << "Current value of base64_bset is " << bits_to_base64(base64_bset) << endl;
        base64_final.push_back(bits_to_base64(base64_bset));
    }

    cout << "BASE64:  "
         //<< bits_to_base64(base64_bset)
         << base64_final
         << endl;
    cout << "New method: " << hexstr_to_base64(nm_str) << endl;

    //second
    string hex1("1c0111001f010100061a024b53535009181c"), hex2("686974207468652062756c6c277320657965"), xor_result;
    for(auto i = 0; i < hex1.length(); i++){
        auto hex1_value = hex_to_decimal(hex1.at(i));
        auto hex2_value = hex_to_decimal(hex2.at(i));
        xor_result.push_back(hex1_value ^ hex2_value);

    }
    cout << "XOR result: " << xor_result << endl;

    //third
    cout << "Decoded string: " << hexstr_to_ascii("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", 'X') << endl;

    //fourth

    ifstream file_in("4.txt", ifstream::in);
    ofstream file_out("file_o.txt", ifstream::out);

    map<char,double> KnownFrequency;

    KnownFrequency['e']=12.702;KnownFrequency['t']=9.056;KnownFrequency['a']=8.167;KnownFrequency['o']=7.507;
    KnownFrequency['i']=6.966; KnownFrequency['n']=6.749;KnownFrequency['s']=6.327;KnownFrequency['h']=6.094;
    KnownFrequency['r']=5.987; KnownFrequency['d']=4.253;KnownFrequency['l']=4.025;KnownFrequency['c']=2.782;
    KnownFrequency['u']=2.758; KnownFrequency['m']=2.406;KnownFrequency['w']=2.360;KnownFrequency['f']=2.228;
    KnownFrequency['g']=2.015; KnownFrequency['y']=1.974;KnownFrequency['b']=1.492;KnownFrequency['k']=0.772;
    KnownFrequency['p']=1.929; KnownFrequency['v']=0.978;KnownFrequency['j']=0.153;KnownFrequency['x']=0.150;
    KnownFrequency['q']=0.095; KnownFrequency['z']=0.074;KnownFrequency[' ']=16.667;

    string str_file_in, decode_str, best_str;
    char xor_char, best_xor_char = 0;
    int correct_char, incorrect_car;
    double max_score = 0, current_score = 0;

    while(getline(file_in,str_file_in)){
        for(xor_char = 31; xor_char < 127; xor_char++){
            map<char, int> FrequencyTally;
            map<char, int>::iterator it;
            current_score = 0;
            file_out << (decode_str = hexstr_to_ascii(str_file_in, xor_char)) << endl;

            FrequencyTally['e']=0;FrequencyTally['t']=0;FrequencyTally['a']=0;FrequencyTally['o']=0;
            FrequencyTally['i']=0;FrequencyTally['n']=0;FrequencyTally['s']=0;FrequencyTally['h']=0;
            FrequencyTally['r']=0;FrequencyTally['d']=0;FrequencyTally['l']=0;FrequencyTally['c']=0;
            FrequencyTally['u']=0;FrequencyTally['m']=0;FrequencyTally['w']=0;FrequencyTally['f']=0;
            FrequencyTally['g']=0;FrequencyTally['y']=0;FrequencyTally['b']=0;FrequencyTally['k']=0;
            FrequencyTally['p']=0;FrequencyTally['v']=0;FrequencyTally['j']=0;FrequencyTally['x']=0;
            FrequencyTally['q']=0;FrequencyTally['z']=0;FrequencyTally[' ']=0;

            for(char &c : decode_str){
                if ( (it = FrequencyTally.find(tolower(c))) != FrequencyTally.end()) {
                    ++FrequencyTally[c];
                }
                if(c < 31){
                   ++incorrect_car;
                }
                else{
                    ++correct_char;
                }
            }
            if(correct_char > incorrect_car){
                for(char &c : decode_str){
                    current_score = current_score + (FrequencyTally[c]*KnownFrequency[c]/decode_str.size());
                }
            }
            if(max_score < current_score){
                max_score = current_score;
                best_xor_char = xor_char;
                best_str = decode_str;
            }
        }
    }

    cout << "Best decoded string: " << best_str << " key: " << best_xor_char << endl;

    //fifth

    cout << ascii_to_hex("I go crazy when I hear a cymbal") << endl;
    cout << repeating_key_xor("I go crazy when I hear a cymbal", "ICE") << endl;

    return 0;

}

char bits_to_base64(bitset<6> base64_bset){
    char ret;
    if(base64_bset.to_ulong() < 26){
        ret = 'A' + base64_bset.to_ulong();
    }
    else if(base64_bset.to_ulong() < 52){
        ret = 'a' + base64_bset.to_ulong() - 26;
    }
    else if(base64_bset.to_ulong() < 62){
        ret = '0' + base64_bset.to_ulong() - 52;
    }
    else if(base64_bset.to_ulong() == 62){
        ret = '+';
    }
    else if(base64_bset.to_ulong() < 63){
        ret = '/';
    }

    return ret;
}

char int_to_base64(int dec){
    char ret;
    if(dec < 26){
        ret = 'A' + dec;
    }
    else if(dec < 52){
        ret = 'a' + dec - 26;
    }
    else if(dec < 62){
        ret = '0' + dec - 52;
    }
    else if(dec == 62){
        ret = '+';
    }
    else if(dec < 63){
        ret = '/';
    }

    return ret;
}

string hexstr_to_base64(string hexstr){
    int len = hexstr.length();
    std::string newString;
    for(int i=0; i< len; i+=3)
    {

        string byte = hexstr.substr(i,2);
        cout << "Debug base func: hex: " << byte << endl;
        uint8_t converted_hex = (int)strtol(byte.c_str(), NULL, 16);
        uint8_t saved_part = (converted_hex << 6);
        saved_part = saved_part >> 2;
        cout << "Debug base func: saved_part: " << to_string(saved_part) << endl;
        converted_hex = converted_hex >> 2;
        cout << "Debug base func: int: " << to_string(converted_hex) << endl;
        char chr =  int_to_base64(converted_hex);
        newString.push_back(chr);
        byte = hexstr.substr(i+2,1);
        cout << "Debug base func: hex: " << byte << endl;
        converted_hex = (int)strtol(byte.c_str(), NULL, 16);
        //converted_hex = (converted_hex << 2) + saved_part;
        converted_hex = converted_hex + saved_part;
        cout << "Debug base func: int: " << to_string(converted_hex) << endl;
        chr =  int_to_base64(converted_hex);
        newString.push_back(chr);

    }

    return newString;
}

string hexstr_to_ascii(string hexstr, char xorchar){
    int len = hexstr.length();
    std::string newString;
    for(int i=0; i< len; i+=2)
    {
        string byte = hexstr.substr(i,2); // надо преобразовать в строчные
        int converted_hex = (int)strtol(byte.c_str(), NULL, 16);
        char chr = (char) converted_hex ^ xorchar;
        newString.push_back(chr);
    }
    return newString;
}

int hex_to_decimal(char hex) {
  if ('0' <= hex && hex <= '9') {
      return hex - '0';
  }

  if (hex >= 'A' && hex <= 'Z') {
      return hex - 'A'  + 10;
  }

  return hex - 'a' + 10;
}

string ascii_to_hex(string str){
    std::ostringstream result;
    result << std::setw(2)  << std::setfill('0') << std::hex << std::uppercase;
    std::copy(str.begin(), str.end(), std::ostream_iterator<unsigned int>(result));
    //std::cout << ":" << result.str() << std::endl;

//    char to_hex[1];
//    for(char c : str){
//        std::cout << std::setw(2) << static_cast<int>(c);
//        //sprintf(new_string, "%0x", c);
//        //new_string.push_back(to_hex);
//    }
    return result.str();
}

string repeating_key_xor(string str, string key){
    string hex_str;
    size_t hex_str_pos = 0;
    string decoded_str;
    hex_str = ascii_to_hex(str);
    while(hex_str_pos < hex_str.length()){
        for(char c : key){
            decoded_str.push_back(c ^ hex_str.at(hex_str_pos));
            if(hex_str_pos < hex_str.length()){   //исправить это говно
                hex_str_pos++;                    //исправить это говно
            }                                     //исправить это говно
            else break;                           //исправить это говно
        }
    }
    reverse(decoded_str.begin(),decoded_str.end());
    return decoded_str;
}
