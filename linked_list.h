// -*- C++ -*-
//
// LICENSE:
//  The MIT License (MIT)
//  Copyright (c) 2023 Lucas Newcomb, lucasnewcomb721@gmail.com
//
//  Use of this source code is governed by an MIT-style license that can be
//  found in the LICENSE file or at https://opensource.org/licenses/MIT.
//
// REFERENCES:
//  https://en.wikipedia.org/wiki/Linked_list
//
// HOWTO:
//  #include "linked_list.h"
//
//  LinkedList *list = linked_list_create();
//
// TODO:
//  - Add testing

// =============================================================================
// LINKED_LIST PUBLIC API
// =============================================================================

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

Node *node_create(int data);
void node_destroy(Node *node);

typedef struct LinkedList {
    Node *head;
} LinkedList;

LinkedList *linked_list_create(void);
void linked_list_destroy(LinkedList *list);
void linked_list_clear(LinkedList *list);
void linked_list_print(LinkedList *list);
Node *linked_list_back(LinkedList *list);
Node *linked_list_front(LinkedList *list);
void linked_list_push_back(LinkedList *list, int data);
void linked_list_push_front(LinkedList *list, int data);
int linked_list_pop_back(LinkedList *list);
int linked_list_pop_front(LinkedList *list);
/* void linked_list_remove_value(LinkedList *list, int data); */
void linked_list_remove(LinkedList *list, size_t index);
int linked_list_length(LinkedList *list);
bool linked_list_contains(LinkedList *list, int data);
bool linked_list_is_empty(LinkedList *list);
void linked_list_reverse(LinkedList *list); // UNIMPLEMENTED

#endif // LINKED_LIST_H

// =============================================================================
// LINKED_LIST IMPLEMENTATION
// =============================================================================

#ifndef LINKED_LIST_IMPL
#define LINKED_LIST_IMPL

Node *node_create(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

void node_destroy(Node *node) {
    // Previous node's next is current node's next
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }

    // Next node's previous is current node'e previous
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    // This should (hopefully) eliminate all references to node

    free(node);
}

LinkedList *linked_list_create() {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;

    return list;
}

void linked_list_destroy(LinkedList *list) {
    Node *tmp;

    // Iterate until a head's next points to NULL
    while (list->head != NULL) {
        tmp = list->head; // Store current head
        list->head = list->head->next; // Move on to next node
        free(tmp); // Free memory held by the previous head
    }

    free(list);
}

void linked_list_clear(LinkedList *list) {
    // literally linked_list_destroy without the free(list)
    Node *tmp;

    // Iterate until a head's next points to NULL
    while (list->head != NULL) {
        tmp = list->head;              // Store current head
        list->head = list->head->next; // Move on to next node
        free(tmp);                     // Free memory held by the previous head
    }
}

void linked_list_print(LinkedList *list) {
    if (list->head == NULL) {
        return;
    }
    Node *current = list->head;

    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

Node *linked_list_back(LinkedList *list) {
    Node *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }

    return current;
}

Node *linked_list_front(LinkedList *list) {
    return list->head;
}

void linked_list_push_back(LinkedList *list, int data) {
  // TODO: Improve time complexity to O(1)
  Node *current = NULL;
  if (list->head == NULL) {
    list->head = node_create(data);
    } else {
        current = list->head;

        // Find end of list
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node_create(data);
        current->next->prev = current;
    }
}

void linked_list_push_front(LinkedList *list, int data) {
    Node *current = NULL;
    if (list->head == NULL) {
        list->head = node_create(data);
    } else {
        current = list->head;

        current->prev = node_create(data);
        current->prev->next = current;

        list->head = current->prev;
    }

}

int linked_list_pop_back(LinkedList *list) {
    // TODO: Improve time complexity to O(1)
    Node *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }


    // Reached when current->next is NULL
    int ret = current->data;
    node_destroy(current);

    return ret;
}

int linked_list_pop_front(LinkedList *list) {
    Node *current = list->head;
    list->head = current->next;

    int ret = current->data;
    node_destroy(current);

    return ret;
}

/* void linked_list_remove_value(LinkedList *list, int data) { */
/*     Node *current = list->head; */

/*     while (current != NULL) { */
/*         // Find node with data */
/*         if (current->data == data) { */
/*             if (current == list->head) { */
/*                 list->head = current->next; */
/*             } */
/*             node_destroy(current); */
/*             return; */
/*         } */
/*         current = current->next; */
/*     } */
/* } */

void linked_list_remove(LinkedList *list, size_t index) {
    size_t current_index = 0;
    Node *current = list->head;

    // Change head if head is being removed
    if (index == 0) {
        list->head = current->next;
        node_destroy(current);
        return;
    }

    while (current != NULL) {

        // Check if at index to remove
        if (current_index == index) {
            node_destroy(current);
            return;
        }

        // Move on
        current_index++;
        current = current->next;
    }
}

int linked_list_length(LinkedList *list) {
    int count = 0;
    Node *current = list->head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

bool linked_list_contains(LinkedList *list, int data) {
    Node *current = list->head;

    while (current != NULL) {
        if (current->data == data) {
            return true;
        }
    }

    return false;
}

bool linked_list_is_empty(LinkedList *list) {
    if (list->head == NULL) {
        return true;
    }

    return false;
}

void linked_list_reverse(LinkedList *list) {

}

#endif // LINKED_LIST_IMPL
