#include <stdio.h>

#include "linked_list.h"

typedef struct test_t {
    uint8_t a, b, c;
    uint32_t d;
} test_t;

void print_data( test_t *t ) {
    printf("%02d %02d %02d %02d\n", t->a, t->b, t->c, t->d);
}

void Test() {
    
    test_t a = {1,2,3,4};
    test_t b = {5,6,7,8};
    test_t c = {9,10,11,12};
    test_t d = {13,14,15,16};
    test_t e = {17,18,19,20};
    
    node_t *head = node_new( NODE_TO_ADDR(a) );
    node_append( node_last(head), NODE_TO_ADDR(b) );
    node_append( node_last(head), NODE_TO_ADDR(c));
    node_append( node_last(head), NODE_TO_ADDR(d));
    head = node_prepend( head, NODE_TO_ADDR(e));
    
    head = head->next;
    print_data( NODE_FROM_ADDR( node_pop( node_first(head) ), test_t * ) );
    printf("\n");
    
    node_t *cur = head;
    while ( 1 ) {
        test_t *t = NODE_FROM_ADDR( cur->item_addr, test_t* );
        print_data( t );
        if ( cur->next == NULL )
            break;
        cur = cur->next;
    }
    
    node_freeall( head );
}

int main() {
    Test();
    return 0;
}