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
    //char* data[0]; // поле данных
    void* data_void;
};

hstack_t stack_new(void)  //создание нового стека
{
    ++i;
    stack_entry* p = (stack_entry*)realloc(g_table[i - 1].entries, sizeof(stack_entry)); // указатель на конкретный стек
    p->reserved = 0; //стек активен
    //p->stack = (node*)malloc(sizeof(node*));
    p->stack = NULL;
    g_table[i - 1].size = i;
    g_table[i - 1].entries = p;
    return(i);
}
//стек создавался на удаленном месте??????????????

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

    node* lst = (struct node*)malloc(sizeof(node) + size + sizeof(lst->prev)); // выделение памяти под узел
    //lst->prev = (node*)malloc(sizeof(node*)); // выделяем память под указатель на предыдущий элемент

    //stack_entry* p = (stack_entry*)realloc(g_table[stack - 1].entries, sizeof(lst) + sizeof(stack_entry));
    stack_entry* p = g_table[stack - 1].entries;

    lst->prev = p->stack; //переставляем указатель на предыдущий элемент
    p->stack = lst; //переставляем указатель на вершину стека
    ++(p->reserved);

    //std::cout << g_table[stack - 1].entries << "\n";

    //lst->data[0] = (char*)data;
    memcpy(lst->data_void, data, size);
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
    //data_out = (void*)lst->data[razmer - 1];
    data_out = lst->data_void;
    node* free(lst);
    return(razmer);
    --(p->reserved);
}
int main()
{
}