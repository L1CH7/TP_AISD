/**
 * 1.4 Инвертируйте значение бита в числе N по его номеру K.
 * Формат входных данных. Число N, номер бита K.
 * Формат выходных данных. Число с инвертированным битом в десятичном виде.
*/

#include <iostream>
#include <cstdint>

uint32_t GetBitK( uint32_t n, uint32_t k )
{
    return n >> k & 1;
}

void Run( std::istream & in, std::ostream & out )
{
    uint32_t n, k;
    in >> n >> k;
    out << GetBitK( n, k ) << std::endl;
}

int main()
{
    Run( std::cin, std::cout );
    return 0;
}