
typedef struct List{
    int capacity;
    int size;
    int elem_size;
    void *data;
} List;

List *init_list(int elem_size);
void free_list(List *arr);

void list_get(List *arr, int i, void *out);
void list_set(List *arr, int i, void *p);
void list_append(List *arr, void *p);
void list_pop(List *arr, void *out);
void list_sort(List *arr, int (*cmp)(const void *, const void *));
