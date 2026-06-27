#include "hash.h"

unsigned long hash_int(int n){
    return n * 2654435761u;  // Knuth's multiplicative hash
}

// DJB2
unsigned long hash_str(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}
