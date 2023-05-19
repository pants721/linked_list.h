#include "../linked_list.h"

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"

static MunitResult
node_create_test(const MunitParameter params[], void *user_data) {
    Node *node = node_create(5);

    assert_int(node->data, ==, 5);
    assert_not_null(node);
    return MUNIT_OK;
}

static MunitResult
node_destroy_test(const MunitParameter params[], void *user_data) {
    Node *node1 = node_create(4);
    Node *node2 = node_create(5);

    node1->next = node2;

    node_destroy(node2);
    assert_null(node2);
    assert_null(node2->prev);
    assert_null(node2->next);
    assert_null(node1->next);
    assert(!node2);
    return MUNIT_OK;
}

static MunitResult
create_test(const MunitParameter params[], void *user_data) {
    LinkedList *list = linked_list_create();
    assert_not_null(list);
    return MUNIT_OK;
}

static MunitResult
destroy_test(const MunitParameter params[], void *user_data) {
    LinkedList *list = linked_list_create();
    linked_list_push_back(list, 3);
    linked_list_push_back(list, 20);
    linked_list_push_back(list, 22);

    linked_list_destroy(list);
    assert_null(list->head);
    return MUNIT_OK;
}

static MunitResult
clear_test(const MunitParameter params[], void *user_data) {
    LinkedList *list = linked_list_create();
    linked_list_push_back(list, 3);
    linked_list_push_back(list, 20);
    linked_list_push_back(list, 22);

    linked_list_clear(list);

    assert(linked_list_is_empty(list));
    return MUNIT_OK;
}

static MunitResult
back_test(const MunitParameter params[], void *user_data) {
    LinkedList *list = linked_list_create();
    linked_list_push_back(list, 3);
    linked_list_push_back(list, 20);
    linked_list_push_back(list, 22);

    assert_int(linked_list_back(list)->data, ==, 22);
    return MUNIT_OK;
}

static MunitResult
front_test(const MunitParameter params[], void *user_data) {
    LinkedList *list = linked_list_create();
    linked_list_push_back(list, 3);
    linked_list_push_back(list, 20);
    linked_list_push_back(list, 22);

    assert_int(linked_list_front(list)->data, ==, 3);
    return MUNIT_OK;
}

static MunitResult
push_back_test(const MunitParameter params[], void *user_data) {
    LinkedList *list = linked_list_create();
    list->head = node_create(42);
    linked_list_push_back(list, 91);
    assert_int(linked_list_back(list)->data, ==, 91);
    return MUNIT_OK;
}

static MunitResult
push_front_test(const MunitParameter params[], void *user_data) {
    LinkedList *list = linked_list_create();
    list->head = node_create(42);
    linked_list_push_front(list, 91);
    assert_int(list->head->data, ==, 91);
    assert_int(linked_list_front(list)->data, ==, 91);
    return MUNIT_OK;
}

static MunitResult
pop_back_test(const MunitParameter params[], void *user_data) {
    LinkedList *list = linked_list_create();
    linked_list_push_back(list, 3);
    linked_list_push_back(list, 20);
    linked_list_push_back(list, 22);

    int back = linked_list_pop_back(list);
    assert_int(linked_list_back(list)->data, ==, 20);
    assert_int(linked_list_back(list)->data, !=, 22);
    assert_int(back, ==, 22);
    return MUNIT_OK;
}

static MunitResult
pop_front_test(const MunitParameter params[], void *user_data) {
    LinkedList *list = linked_list_create();
    linked_list_push_back(list, 3);
    linked_list_push_back(list, 20);
    linked_list_push_back(list, 22);

    int front = linked_list_pop_front(list);
    assert_int(linked_list_front(list)->data, ==, 20);
    assert_int(linked_list_front(list)->data, !=, 3);
    assert_int(front, ==, 3);
    return MUNIT_OK;
}

static MunitResult
remove_test(const MunitParameter params[], void *user_data) {
    LinkedList *list = linked_list_create();
    linked_list_push_back(list, 3);
    linked_list_push_back(list, 20);
    linked_list_push_back(list, 22);

    linked_list_remove(list, 0);
    assert_int(list->head->data, ==, 20);
    assert(!linked_list_contains(list, 3));
    return MUNIT_OK;
}

static MunitResult
length_test(const MunitParameter params[], void *user_data) {
  LinkedList *list = linked_list_create();
  linked_list_push_back(list, 3);
  linked_list_push_back(list, 20);
  linked_list_push_back(list, 22);

  assert_int(linked_list_length(list), ==, 3);
  return MUNIT_OK;
}

static MunitResult
contains_test(const MunitParameter params[], void *user_data) {
  LinkedList *list = linked_list_create();
  linked_list_push_back(list, 3);
  linked_list_push_back(list, 20);
  linked_list_push_back(list, 22);

  linked_list_contains(list, 3);
  linked_list_contains(list, 20);
  linked_list_contains(list, 22);
  return MUNIT_OK;
}

static MunitResult
is_empty_test(const MunitParameter params[], void *user_data) {
  LinkedList *list = linked_list_create();
  linked_list_push_back(list, 3);
  linked_list_push_back(list, 20);
  linked_list_push_back(list, 22);

  linked_list_clear(list);
  assert(linked_list_is_empty(list));
  return MUNIT_OK;
}

MunitTest tests[] = {
    {
        "/node-create-test",
        node_create_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/node-destroy-test",
        node_destroy_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/create-test",
        create_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/destroy-test",
        destroy_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/clear-test",
        clear_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/back-test",
        back_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/front-test",
        front_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/push-back-test",
        push_back_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/push-front-test",
        push_front_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/pop-back-test",
        pop_back_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/pop-front-test",
        pop_front_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/remove-test",
        remove_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/length-test",
        length_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/contains-test",
        contains_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {
        "/is-empty-test",
        is_empty_test,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL,
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL} // End of array

};

static const MunitSuite suite = {
    "/tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char **argv) {
  munit_suite_main(&suite, NULL, argc, argv);
  return 0;
}
