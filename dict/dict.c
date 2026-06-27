#include <stdlib.h>
#include "dict.h"
#include "lib/hash.h"

#define DICT_DEFAULT_SIZE 128 // keep this a power of 2

typedef enum
{
    EMPTY = 0,
    OCCUPIED,
    DELETED
} EntryState;

typedef struct DictEntry
{
    void *key;
    void *value;
    EntryState state;
    unsigned long hash;
} DictEntry;

struct Dict
{
    int capacity;
    int size;
    DictEntry *data;
    unsigned long (*hash_fn)(void *);
    int (*eq_fn)(void *, void *);
};

Dict *dict_init(unsigned long (*hash_fn)(void *), int (*eq_fn)(void *, void *))
{
    Dict *d = malloc(sizeof(Dict));
    d->size = 0;
    d->capacity = DICT_DEFAULT_SIZE;
    d->data = calloc(d->capacity, sizeof(DictEntry));
    d->hash_fn = hash_fn;
    d->eq_fn = eq_fn;

    return d;
}

void dict_free(Dict *d)
{
    free(d->data);
    free(d);
}

static int next_idx(int i, int cap)
{
    return (i + 1) & (cap - 1); // % cap
}

static int find_slot(Dict *d, void *key, unsigned long hash, int *found_existing)
{
    *found_existing = 0;
    int idx = hash & (d->capacity - 1);
    int first_deleted = -1;

    while (d->data[idx].state != EMPTY)
    {
        if (d->data[idx].state == OCCUPIED &&
            d->data[idx].hash == hash &&
            d->eq_fn(d->data[idx].key, key))
        {
            *found_existing = 1;
            return idx;
        }

        if (d->data[idx].state == DELETED && first_deleted == -1)
            first_deleted = idx;

        idx = next_idx(idx, d->capacity);
    }

    if (first_deleted != -1)
        return first_deleted;

    return idx;
}

static void dict_resize(Dict *d)
{
    int old_cap = d->capacity;
    DictEntry *old = d->data;

    d->capacity *= 2;
    d->size = 0;

    d->data = calloc(d->capacity, sizeof(DictEntry));

    for (int i = 0; i < old_cap; i++)
    {
        if (old[i].state == OCCUPIED)
        {
            int found = 0;
            int idx = find_slot(d, old[i].key, old[i].hash, &found);

            d->data[idx] = old[i];
            d->data[idx].state = OCCUPIED;

            d->size++;
        }
    }

    free(old);
}

void dict_set(Dict *d, void *key, void *value)
{
    if (d->size >= (2 * d->capacity) / 3)
        dict_resize(d);

    unsigned long hash = d->hash_fn(key);

    int found = 0;
    int idx = find_slot(d, key, hash, &found);

    if (found)
    {
        d->data[idx].value = value;
        return;
    }

    d->data[idx] = (DictEntry){
        .key = key,
        .value = value,
        .hash = hash,
        .state = OCCUPIED};

    d->size++;
}

int dict_get(Dict *d, void *key, void **out_value)
{
    unsigned long hash = d->hash_fn(key);
    int found = 0;
    int index = find_slot(d, key, hash, &found);
    if (found)
    {
        *out_value = d->data[index].value;
        return 0;
    }
    else
        return 1;
}