#include <stdio.h>

#include "linked_list.h"


void Test() {
    typedef struct test_t {
        uint8_t a, b, c;
        uint32_t d;
    } test_t;
    
    test_t a = {1,2,3,4};
    test_t b = {5,6,7,8};
    test_t c = {9,10,11,12};
    test_t d = {13,14,15,16};
    
    node_t *nodes = node_new( NODE_TO_ADDR(a) );
    node_append( nodes, NODE_TO_ADDR(b) );
    node_append( nodes, NODE_TO_ADDR(c));
    node_append( nodes, NODE_TO_ADDR(d));
    
    
    node_t *cur = node_first(nodes);
    while (true) {
        test_t *t = NODE_FROM_ADDR( cur->item_addr, test_t* );
        printf("%02d %02d %02d %02d\n", t->a, t->b, t->c, t->d);
        if ( cur->next == NULL )
            break;
        cur = cur->next;
    }
    
    node_freeall( nodes );
}

int main() {
    Test();
    return 0;
}