#include <stdio.h>
#include <string.h>
#include "cstack.h"

typedef int hstack_t;

struct node // структура, описывающая конкретный узел данного стека
{
    struct node *prev; // указатель на предыдущий элемент
    unsigned int size; // размер данных
    void *data_void;   // поле данных
};
typedef struct node* node_t;

struct stack_entry // структура, описывающая конкретный стек
{
    int reserved; // показывает число элементов в стеке (если -1, то стек не создан)
    struct node_t stack; // верхушка стека - указатель на верхний узел
};
typedef struct stack_entry stack_entry_t;

struct stack_entries_table // структура, представляющая собой таблицу стеков
{
    unsigned int size;      // количество стеков
    struct stack_entry_t* entries; // указатель на конкретный стек
};

struct stack_entries_table g_table = {0u, NULL};


int stack_valid_handler(const hstack_t stack)  // проверка на корректность введенного хендлера стека
{
    if (stack > g_table.size - 1 || g_table.entries + stack == NULL)
        return 1;

    return 0;
}


hstack_t stack_new(void) // создание нового стека
{
    g_table.entries = (stack_entry_t*) realloc(g_table.entries, sizeof(stack_entry_t) * (g_table.size + 1)); // расширяем память под новый стек
    if (g_table.entries == NULL)
        return -1;

    struct stack_entry_t* table_stack = g_table.entries + g_table.size;  // указатель на конкретный стек
    table_stack->reserved = 0;
    table_stack->stack = NULL;
    g_table.size++;

    return g_table.size - 1;
}


void stack_free(const hstack_t stack)  // удаление стека
{
    if (stack_valid_handler(stack) == 1)
        return;

    struct stack_entry* p = g_table.entries + stack;  // указатель на конкретный стек
	
    struct node_t cur_node = p->stack;
    while (cur_node != NULL)
    {
        struct node_t prev = cur_node->prev;
        free(cur_node->data_void);
        free(cur_node);
        cur_node = prev;
    }

    p->reserved = -1;
}


unsigned int stack_size(const hstack_t stack)
{
    if (stack_valid_handler(stack) == 1)
        return 0;

    struct stack_entry_t* p = g_table.entries + stack;
    return p->reserved;
}


void stack_push(const hstack_t stack, const void* data, const unsigned int size)
{
    if (data == NULL || size == 0 || stack_valid_handler(stack) == 1)
        return;

    struct node_t new_node = (node_t) malloc(sizeof(node));  // выделение памяти под узел
    if (new_node == NULL)
        return;

    new_node->data_void = (void*) malloc(size);  // выделение памяти под данные
    if (new_node->data_void == NULL)
    {
        free(new_node);
        return;
    }
    memcpy(new_node->data_void, data, size);
    new_node->size = size;

    struct stack_entry* p = g_table.entries + stack;
    new_node->prev = p->stack;  // переставляем указатель на предыдущий элемент
    p->stack = new_node;  // переставляем указатель на вершину стека
    ++(p->reserved);
}


unsigned int stack_pop(const hstack_t stack, void* data_out, const unsigned int size)
{
    if (stack_valid_handler(stack) == 1)
        return 0;

    struct stack_entry* p = g_table.entries + stack;

    struct node_t pop_node = p->stack;
    if (pop_node == NULL)
        return 0;
        
    p->stack = pop_node->prev;  // переставляем указатель на вершину стека

    unsigned int data_size;
    if (pop_node->size > size)
        data_size = size;  // копируем size байт, так как размер буфера меньше
    else
        data_size = pop_node->size;  // копируем необходимое количество байт
    memcpy(data_out, pop_node->data_void, data_size);

    free(pop_node->data_void);
    free(pop_node);
    --(p->reserved);

    return data_size;
}
