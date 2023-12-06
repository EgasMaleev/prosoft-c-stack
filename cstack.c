#include <iostream>

int i = 0;
typedef struct node* stack_t;
typedef int hstack_t;
typedef struct stack_entry stack_entry_t;

struct stack_entry //структура, описывающая конкретный стек
{
    int reserved; //индикация, используется ли сейчас данный элемент таблицы стека(то есть конкретный стек); показывает число элементов в стеке
    stack_t stack; //верхушка стека - указатель на верхний узел
};

struct stack_entries_table //структура, представляющая собой таблицу стеков
{
    unsigned int size; //размер таблицы(количество стеков)
    stack_entry_t* entries; //указатель на конкретный стек
};

struct stack_entries_table g_table[20];

struct node //структура, описывающая конкретный узел данного стека
{
    struct node* prev; // указатель на предыдущий элемент
    unsigned int size; //размер данных
    char* data[0]; // поле данных
};

hstack_t stack_new(void)  //создание нового стека
{
    ++i;
    stack_entry* p = (stack_entry*)malloc(sizeof(stack_entry)); // указатель на конкретный стек
    p->reserved = 0; //стек активен
    p->stack = NULL;
    g_table[i - 1].size = i;
    g_table[i - 1].entries = p;
    return(i);
}
//стек создавался на удаленном месте??????????????
//data[0]
// malloc and realloc

int stack_valid_handler(const hstack_t stack)
{
    if (stack - 1 >= i)
    {
        return 1;
    }
    if (g_table[stack - 1].entries->reserved == -1)
    {
        return 1;
    }
    return(0);
}

void stack_free(const hstack_t stack) //удаление стека
{
    if (stack_valid_handler(stack) == 1)
    {
        exit;
    }
    stack_entry* p = g_table[stack - 1].entries; // указатель на конкретный стек
    p->reserved = -1; //стек неактивен
}

unsigned int stack_size(const hstack_t stack)
{
    if (stack_valid_handler(stack) == 1)
    {
        exit;
    }
    stack_entry* p = g_table[stack - 1].entries;
    return(p->reserved);
}

void stack_push(const hstack_t stack, const void* data, const unsigned int size)
{
    if (data == NULL)
    {
        exit;
    }
    if (size == 0)
    {
        exit;
    }
    if (stack_valid_handler(stack) == 1)
    {
        exit;
    }
    stack_entry* p = g_table[stack - 1].entries;//указатель на данный стек, в который мы пушаем элемент
    node* lst = (struct node*)malloc(sizeof(node) + size); // выделение памяти под узел
    const char* data_char = (const char*)malloc(sizeof(data)); // приведение входных данных типа const void* к типу const char*
    memcpy((void*)lst->data[0], data, size);
    if (stack_size(stack) == 0)
    {
        lst->prev = NULL;
    }
    else
    {
        lst->prev = p->stack;
    } //переставляем указатель на предыдущий элемент
    p->stack = lst;//переставляем указатель на вершину стека
    --(p->reserved);
}

unsigned int stack_pop(const hstack_t stack, void* data_out, const unsigned int size)
{
    if (stack_valid_handler(stack) == 1)
    {
        exit;
    }
    node* lst = g_table[stack - 1].entries->stack;
    unsigned int razmer = lst->size;
    stack_entry* p = g_table[stack - 1].entries;
    p->stack = lst->prev; //переставляем указатель на вершину стека
    data_out = (void*)lst->data[razmer - 1];
    node* free(lst);
    return(razmer);
}
int main()
{

}