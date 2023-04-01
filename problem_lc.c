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
    page->data[0] = 'A';        //here can read page's data
    page->index = index;

    return page;
}

int change_last_el(struct page **hash_t, int last)
{
    last = hash_t[last]->before->index; //penultimate el becomes last
    hash_t[hash_t[last]->next->index] = NULL;
    hash_t[last]->next = NULL;
    return last;
}

int change_head_el(struct page **hash_t, int head, int el)
{
    hash_t[el] = create_list(el, hash_t[head], NULL);
    hash_t[head]->before = hash_t[el];
    head = el;

    return head;
}

int count_cache_hit(struct page **hash_t, int count_el, int size_cache)
{
    int i = 0;
    int el = 0;
    int last = 0;
    int head = 0;
    int cache_hit = 0;
    int count_cache_el = 0;

    //create first el in list
    scanf("%d", &el);
    head = el;
    last = el;
    hash_t[el] = create_list(el, NULL, NULL);
    ++count_cache_el;

    for (i = 1; i < count_el; ++i) {
        scanf("%d", &el);
        if (hash_t[el] == NULL) {       //cache miss
            if (count_cache_el >= size_cache)   //cache not full?
                last = change_last_el(hash_t, last);
            head = change_head_el(hash_t, head, el);
            ++count_cache_el;
        } else {
            ++cache_hit;
            if (hash_t[el]->before == NULL) {   //if first in list
                continue;
            } else if (hash_t[el]->next == NULL) {      //if last in list
                last = change_last_el(hash_t, last);
                head = change_head_el(hash_t, head, el);
            } else {
                hash_t[hash_t[el]->before->index]->next =    //elements between el are connecting here
                hash_t[hash_t[el]->next->index];
                hash_t[hash_t[el]->next->index]->before =    //elements between el are connecting here
                hash_t[hash_t[el]->before->index];
                head = change_head_el(hash_t, head, el);
            }
        }
    }

    return cache_hit;
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
    int size_cache = 0;

    struct page **hash_t;

    scanf("%d", &size_cache);
    scanf("%d", &count_el);

    hash_t = (struct page **) calloc(count_el + 1, sizeof(struct page *));
    create_hash_t(hash_t, count_el);

    printf("%d\n", count_cache_hit(hash_t, count_el, size_cache));

    return 0;
}
