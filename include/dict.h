#ifndef DICT_H
#define DICT_H

typedef struct Dict Dict;

Dict *dict_init(unsigned long (*hash_fn)(void *), int (*eq_fn)(void *, void *));
void dict_free(Dict *d);

void dict_set(Dict *d, void *key, void *value);
int dict_get(Dict *d, void *key, void **out_value);

#endif