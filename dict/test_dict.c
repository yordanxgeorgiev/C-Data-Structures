#include <stdio.h>
#include <string.h>
#include "dict.h"

unsigned long hash_str(void *key) {
    unsigned char *s = (unsigned char *)key;
    unsigned long hash = 5381;
    int c;

    while ((c = *s++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int eq_str(void *a, void *b) {
    return strcmp((char *)a, (char *)b) == 0;
}

int main(void) {
    Dict *d = dict_init(hash_str, eq_str);

    dict_set(d, "apple", "red");
    dict_set(d, "banana", "yellow");
    dict_set(d, "grape", "purple");

    void *value;

    if (dict_get(d, "apple", &value) == 0)
        printf("apple -> %s\n", (char *)value);
    else
        printf("apple not found\n");

    if (dict_get(d, "banana", &value) == 0)
        printf("banana -> %s\n", (char *)value);
    else
        printf("banana not found\n");

    if (dict_get(d, "grape", &value) == 0)
        printf("grape -> %s\n", (char *)value);
    else
        printf("grape not found\n");

    dict_free(d);
    return 0;
}