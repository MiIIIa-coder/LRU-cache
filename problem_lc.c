#include <stdio.h>
#include <stdlib.h>

struct page {
    int index;
    char data[64];
};

struct page *create_list(int index)
{
    struct page *p = (struct page *) malloc(sizeof(struct page));
    p->data[0] = 'A';           //here can read page's data
    p->index = index;

    return p;
}


void change_pages(struct page **hash_t, int size_cash, int index_find_el)
{
    int i = 0;

    struct page *find_el;

    find_el = hash_t[index_find_el];

    for (i = index_find_el; i < size_cash - 1; ++i) {
        hash_t[i] = hash_t[i + 1];
    }

    hash_t[i] = find_el;

}

void add_new_page(struct page **hash_t, int size_cash, int el)
{
    int i = 0;

    for (i = 0; i < size_cash - 1; ++i)
        hash_t[i] = hash_t[i + 1];
    hash_t[i] = create_list(el);
}

int find_in_hash_t(struct page **hash_t, int size_cash, int el)
{
    int i = 0;

    for (i = size_cash - 1; i >= 0; --i) {
        if (hash_t[i]->index == el) {
            return i;
        }
    }

    return -1;

}

int count_cash_hit(struct page **hash_t, int count_el, int size_cash)
{
    int i = 0;
    int el = 0;
    int index_find_el = 0;
    int cash_hit = 0;

    for (i = 0; i < count_el; ++i) {
        scanf("%d ", &el);
        index_find_el = find_in_hash_t(hash_t, size_cash, el);  // -1 <=> not find, j (>= 0) - number of list
        if (index_find_el == -1) {
            add_new_page(hash_t, size_cash, el);
        } else {
            ++cash_hit;
            change_pages(hash_t, size_cash, index_find_el);
        }
    }

    return cash_hit;
}

void create_hash_t(struct page **hash_t, int size_cash)
{
    int i = 0;

    for (i = 0; i < size_cash; ++i) {
        hash_t[i] = create_list(0);
    }
}


int main()
{
    int count_el = 0;
    int size_cash = 0;

    struct page **hash_t;

    scanf("%d ", &size_cash);
    scanf("%d ", &count_el);

    hash_t = (struct page **) calloc(size_cash, sizeof(struct page *));
    create_hash_t(hash_t, size_cash);

    printf("%d\n", count_cash_hit(hash_t, count_el, size_cash));

    return 0;
}
