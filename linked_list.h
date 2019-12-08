#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdint.h>
#include <stdlib.h>

#define NODE_ITEM_ADDR_T uint32_t
#define NODE_TO_ADDR(addr) ( (NODE_ITEM_ADDR_T)&addr )
#define NODE_FROM_ADDR(addr, type) ( ( type ) addr )

typedef struct node_t {
    struct node_t *prev;
    struct node_t *next;
    NODE_ITEM_ADDR_T *item_addr;
} node_t;

node_t *node_first( node_t *n ) {
    node_t *cur = n;
    while (cur->prev != NULL)
        cur = cur->prev;
    return cur;
}

node_t *node_last( node_t *n ) {
    node_t *cur = n;
    while (cur->next != NULL)
        cur = cur->next;
    return cur;
}

node_t *node_new( NODE_ITEM_ADDR_T d ) {
    node_t *new_node = (node_t *) malloc( sizeof(node_t) );
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->item_addr = (NODE_ITEM_ADDR_T *)d;
    return new_node;
}

node_t *node_append( node_t *n, NODE_ITEM_ADDR_T d ) {
    
    // [n], <new>, n->next, b, c
    node_t *new_node = node_new( d );
    node_t *next = n->next;
    
    if (n->next != NULL)
        next->prev = new_node;
    new_node->next = next;
    new_node->prev = n;
    n->next = new_node;
    return new_node;
}


node_t *node_prepend( node_t *n, NODE_ITEM_ADDR_T d ) {
    node_t *new_node = node_new( d );
    node_t *prev = n->prev;
    if ( n->prev != NULL )
        prev->next = new_node;
    new_node->prev = prev;
    new_node->next = n;
    n->prev = new_node;
    return new_node;
}

NODE_ITEM_ADDR_T *node_pop( node_t *n ) {
    if ( n->prev != NULL )
        n->prev->next = n->next;
    
    if (n->next != NULL )
        n->next->prev = n->prev;
    
    NODE_ITEM_ADDR_T *ret = n->item_addr;
    free( n );
    
    return ret;
}

void node_freeall( node_t *n) {
    node_t *cur = node_first( n );
    while (cur->next != NULL) {
        node_t *next = cur->next;
        free( cur );
        cur = next;
    }
    free( cur );
}

#endif //__LINKED_LIST_H__