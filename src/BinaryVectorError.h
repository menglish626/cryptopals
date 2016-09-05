#include    <exception>

struct BinaryVectorError: public std::exception
    {

    const char* what() const throw ()
        {
        return "BinaryVectorError";
        }

    };

struct BinaryVectorSizeError : public BinaryVectorError
    {

    const char* what() const throw ()
        {
        return "Byte Vector Size Mismatch";
        }

    };

struct Base64FormatError : public BinaryVectorError
    {

    const char* what() const throw ()
        {
        return "Malformated base64 String";
        }

    };
