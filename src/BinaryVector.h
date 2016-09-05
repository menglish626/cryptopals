#ifndef __BINARYVECTOR_H__INCLUDED__
#define __BINARYVECTOR_H__INCLUDED__

#include <vector>
#include "BinaryVectorError.h"
class string;

enum Base { HEX, B64, BIN };



template class T;
class BinaryVector<T>
    {
    
    public:

        BinaryVector();
        ~BinaryVector();

        BinaryVector(string str, Base base);

        BinaryVector(const BinaryVector& bin)
            {
            this->binary_string = bin.binary_string;
            return *this;
            }

        BinaryVector& operator = (cost BinaryVector& rhs)
            {
            this->binary_string = rhs.binary_string;
            return *this;
            };

        BinaryVector& operator ^= (const BinaryVector& rhs)
            {
            if(this->binary_string.size() != rhs.binary_string.size())
                {
                throw BinaryVectorSizeError();
                }
            std::vector<T>::iterator it_r = lhs.binary_string.begin();
            for(std::vector<T>::iterator it_l = this->binary_string.begin(); it_l != this->binary_string.end(); it++)
                {
                *it_l ^= *(it_r++);
                }

            return *this;

            }

        BinaryVector& operator ^ (const BinaryVector& lhs, const BinaryVector& rhs)
            if(lhs.binary_string.size() != rhs.binary_string.size())
                {
                throw BinaryVectorSizeError();
                }
           
            BinaryVector tmp();

            std::vector<T>::iterator it_r = lhs.binary_string.begin();
            for(std::vector<T>::iterator it_l = lhs.binary_string.begin(); it_l != lhs.binary_string.end(); it++)
                {
                 tmp.binary_string.push_back(*it_l ^ *(it_r++));
                }

            return tmp;

            }

        BinaryVector& operator ^= (const T rhs);
            {
            std::vector<T>::iterator it_r = lhs.binary_string.begin();
            for(std::vector<T>::iterator it_l = this->binary_string.begin(); it_l != this->binary_string.end(); it++)
                {
                *it_l ^= rhs;
                }

            return *this;

            }

        BinaryVector& operator ^ (const BinaryVector& lhs, const T rhs);
            {
            BinaryVector tmp();

            std::vector<T>::iterator it_r = lhs.binary_string.begin();
            for(std::vector<T>::iterator it_l = lhs.binary_string.begin(); it_l != lhs.binary_string.end(); it++)
                {
                 tmp.binary_string.push_back(*it_l ^ rhs);
                }

            return tmp;
            ;

        bool operator == (const BinaryVector& lhs, const BinaryVector& rhs){return lhs.binary_string == rhs.binary_string;}
        bool operator != (const BinaryVector& lhs, const BinaryVector& rhs){return !(lhs == rhs)};

        virtual std::string to_string(Base base) const;
        
    private:

        std::vector<T> binary_string;


    }

typedef unsigned char Byte;
typedef bool Bit;
class BitVector;

class ByteVector : BinaryVector<Byte>
    {
    
    public:
    
        ByteVector(string str, Base base)
            {
            
            switch(base){
                case b64 : break;
                case hex : break;
                case 

                }
            
            };
        ByteVector(const BitVector& bit);

        friend const BitVector(const ByteVector& byte);
        friend const BitVector to_bits(const ByteVector& byte);
        friend const ByteVector to_bytes(const BitVector& bit);
        
        const std::string to_string(Base base) const;

    };

class BitVector : BinaryVector<Bit>
    {
    
    public:
        
        BitVector(string str, Base base);
        BitVector(const ByteVector& byte);
        
        friend const ByteVector(const BitVector& bit);
        friend const ByteVector to_bytes(const BitVector& byte);
        friend const BitVector to_bits(const ByteVector& bit);
        
        const std::string to_string(Base base) const;


    };


#endif
