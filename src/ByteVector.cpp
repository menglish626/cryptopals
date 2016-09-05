typedef unsigned char Byte;
typedef bool Bit;
typedef BitVector;

enum Base { hex, b64, bin };


ByteVector(BitVector bit);
ByteVector(string str, Base base);

ByteVector(const ByteVector& byte);

ByteVector& operator^(const ByteVector& rhs);

bool operator==(const ByteVector& lhs, const ByteVector* rhs);

const std::string ByteVector::to_hex(void);
const std::string ByteVector::to_b64(void);
const std::string ByteVector::to_string(void);
const BitVector ByteVector::to_bits(void);

    };
#include     <stdlib.h>
#include     <string.h>
#include     <iostream>
#include     <vector>

typedef char Byte ;
typedef bool Bit ;

using namespace std;

char BASE64[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

vector<Byte> bit_to_byte(vector<Bit> bit)
    {
    
    vector<Bit>::iterator it = bit.begin();
    
    vector<Byte> byte;

    while(it != bit.end())
        {
        Byte tmp = 0;
        int i = 0;
        while( i < 8)
            {
            i++;
            tmp = tmp << 1;
            if(it == bit.end()){break;}
            if(*it){tmp += 1;}
            it++;
            }

        while(i < 8)
            {
            tmp = tmp << 1;
            i++;
            }
 
        byte.push_back(tmp);
        }

    return byte;
    }

vector<Bit> byte_to_bit(vector<Byte> byte)
    {

    vector<Byte>::iterator it = byte.begin();
    vector<Bit> bit;
        
    while(it != byte.end())
        {
        for(char i=0; i<8; i++)
            {
            bit.push_back(((*it) & (0b10000000 >> i)) ? 1 : 0);
            }
        it++;
        }

    return bit;
    }


vector<Byte> hex_to_bin(string hex)
    {

    vector<Byte> bin;
    string::iterator it = hex.begin();
    
    Byte tmp;    

    while(it != hex.end())
        {   
        tmp = 0;
        for(int i=0; i<2; i++)
            {
            tmp = tmp << 4;
            if(it == hex.end()){break;}
            
	        if(*it >= 'a'){
	            tmp += (*it - 'a' + 10);
	        }else if(*it >= 'A'){
	            tmp += (*it - 'A' + 10);
	        }else{
	            tmp += (*it - '0');
	            }
            it++;
            }
        bin.push_back(tmp);
        }

    return bin;
    }

string bin_to_hex(vector<Byte> bin)
    {

    string hex;

    for(vector<Byte>::iterator it=bin.begin(); it!=bin.end(); ++it)
        {
        char tmp = ((*it & 0xf0) >> 4);
        if( tmp >= 10){
            hex.push_back(tmp + 'a' - 10);
        }else{
            hex.push_back(tmp + '0');
            }
        
        tmp = (*it & 0xf);
        if(tmp >= 10){
            hex.push_back(tmp + 'a' - 10);
        }else{
            hex.push_back(tmp + '0');
            }
        }

    return hex;
    }

struct Base64FormatError : public exception
    {
    
    const char* what() const throw ()
        {
        return "Malformated base64 String";
        } 

    };

vector<Byte> b64_to_bin(string b64)
    {
    
    vector<Bit> bit;
    char tmp; 
    for(string::iterator it=b64.begin(); it!=b64.end(); ++it)
        {
        if(*it >= 'a'){
            tmp = (*it - 'a' + 26);
            for(int i=0; i<6; i++)
                {
                bit.push_back(tmp & (0b100000 >> i));
                }

        }else if(*it >= 'A'){
            tmp = (*it - 'A');
            for(int i=0; i<6; i++)
                {
                bit.push_back(tmp & (0b100000 >> i));
                }

        }else if(*it >= '0'){
            tmp = (*it - '0' + 52);
            for(int i=0; i<6; i++)
                {
                bit.push_back(tmp & (0b100000 >> i));
                }

        }else if(*it == '+'){
            tmp = (62);
            for(int i=0; i<6; i++)
                {
                bit.push_back(tmp & (0b100000 >> i));
                }

        }else if(*it == '/'){
            tmp = (63);
            for(int i=0; i<6; i++)
                {
                bit.push_back(tmp & (0b100000 >> i));
                }

        }else{
            throw Base64FormatError();
            }
        }

    return bit_to_byte(bit);
    }   

string bin_to_b64(vector<Byte> bin)
    {
    
    string b64;

    vector<Bit> bit = byte_to_bit(bin);
    vector<Bit>::iterator it = bit.begin();

    while(it != bit.end())
        {
        int tmp = 0;
        int i = 0;
        while(i < 6)
            {
            i++;
            tmp = tmp << 1;
            if(it == bit.end()){break;} 
            if(*it){tmp += 1;}
            it++;
            }
        
        while(i != 6)
            {
            tmp = tmp << 1;
            i++;
            }
        b64.push_back(BASE64[tmp]);        

        }

    return b64;
    }

string hex_to_b64(string hex_str)
    {
    return bin_to_b64(hex_to_bin(hex_str));          
    }

string b64_to_hex(string b64_str)
    {
    return bin_to_hex(b64_to_bin(b64_str));
    }

// Now that all the conversion stuff is out of the way
// more computation stuff can be implemented

struct ByteVectorSizeError : public exception
    {
    
    const char* what() const throw ()
        {
        return "Byte Vector Size Mismatch";
        } 

    };

vector<Byte> byte_xor(vector<Byte> a, vector<Byte> b)
    {
    if(a.size() != b.size())
        {
        throw ByteVectorSizeError();
        }

    vector<Byte> ans;
    vector<Byte>::iterator it_a = a.begin();
    vector<Byte>::iterator it_b = b.begin();

    while(it_a != a.end())
        {
        ans.push_back(*it_a ^ *it_b);
        it_a++;
        it_b++;
        }

    return ans;
    }

int main()
    {
    cout << "Conversion Tests" << endl;
    string hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    string b64 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    cout << (bin_to_hex(hex_to_bin(hex)) == hex) << endl;
    cout << (bin_to_hex(bit_to_byte(byte_to_bit(hex_to_bin(hex)))) == hex) << endl;
    cout << (hex_to_b64(hex) == b64) << endl;
    cout << (bin_to_hex(b64_to_bin(b64)) == hex) << endl;
    cout << (bin_to_b64(bit_to_byte(byte_to_bit(b64_to_bin(b64)))) == b64) << endl;
    cout << (b64_to_hex(b64) == hex) << endl;

    cout << "xor tests" << endl;
    string hex1 = "1c0111001f010100061a024b53535009181c";
    string hex2 = "686974207468652062756c6c277320657965";

    string ans = "746865206b696420646f6e277420706c6179";

    cout << ans << endl;
    cout << bin_to_hex(byte_xor(hex_to_bin(hex1), hex_to_bin(hex2))) << endl; 

    return 0;
    }


