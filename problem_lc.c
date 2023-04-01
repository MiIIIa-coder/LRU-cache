#include <stdio.h>
#include <stdlib.h>

struct page {
    struct page *next;
    struct page *before;
    int index;
    char data[64];
};

struct page *create_list(int index, struct page *next, struct page *before)
{
    struct page *page = (struct page *) malloc(sizeof(struct page));
    page->next = next;
    page->before = before;
    page->data[0] = 'A';     //here can read page's data
    page->index = index;

    return page;
}

void change_last_el(struct page **hash_t, int last, int el)
{
    last = hash_t[last]->before->index;    //penultimate el becomes last
    free(hash_t[last]->next->data);
    hash_t[hash_t[last]->next->index] = NULL;
}

void change_head_el(struct page **hash_t, int head, int el)
{
    hash_t[el] = create_list(el, hash_t[head], NULL);
    hash_t[head]->before = hash_t[el];
    head = el;
}

int count_cash_hit(struct page **hash_t, int count_el, int size_cash)
{
    int i = 0;
    int el = 0;
    int last = 0;
    int head = 0;
    int index_find_el = 0;
    int cash_hit = 0;

    //create first el in list
    scanf("%d ", &el);
    head = el;
    last = el;
    hash_t[el] = create_list(el, NULL, NULL);

    //fill cash
    for (i = 1; i < size_cash; ++i) {
        scanf("%d ", &el);
        change_head_el(hash_t, head, el);
    }

    for (i = size_cash; i < count_el; ++i) {
        scanf("%d ", &el);
        if (hash_t[el] == NULL) {
            change_last_el(hash_t, last, el);
            //hash_t[last]->next = NULL;
            change_head_el(hash_t, head, el);
        } else {
            ++cash_hit;
            if (hash_t[el]->before == NULL) {       //if first in list
                continue;
            } else if (hash_t[el]->next == NULL) {  //if last in list
                hash_t[hash_t[el]->before->index]->next = NULL;
                change_head_el(hash_t, head, el);
            } else {
                hash_t[hash_t[el]->before->index]->next = hash_t[hash_t[el]->next->index];
                change_head_el(hash_t, head, el);
            }
        }
    }

    return cash_hit;
}

void create_hash_t(struct page **hash_t, int count_el)
{
    int i = 0;

    for (i = 0; i < count_el; ++i) {
        hash_t[i] = NULL;
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
    create_hash_t(hash_t, count_el);

    printf("%d\n", count_cash_hit(hash_t, count_el, size_cash));

    return 0;
}
