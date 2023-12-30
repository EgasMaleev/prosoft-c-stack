#ifndef CSTACK_H
#define CSTACK_H
#pragma warning(disable: 4820)
#pragma warning(disable: 4018)
#pragma warning(disable: 4312)

struct node // ���������, ����������� ���������� ���� ������� �����
{
    void* data_void;   // ���� ������
    struct node* prev; // ��������� �� ���������� �������
    unsigned int size; // ������ ������
};
//typedef struct node* node_t;

struct stack_entry // ���������, ����������� ���������� ����
{
    int reserved; // ���������� ����� ��������� � ����� (���� -1, �� ���� �� ������)
    struct node* stack; // �������� ����� - ��������� �� ������� ����
};

struct stack_entries_table // ���������, �������������� ����� ������� ������
{
    unsigned int size;      // ���������� ������
    struct stack_entry* entries; // ��������� �� ���������� ����
};

struct stack_entries_table g_table = { 0u, NULL };

typedef int hstack_t;
//struct node;
//struct node_t;
//typedef struct node* node_t;
//struct stack_entry;
//typedef struct stack_entry stack_entry_t;
//struct stack_entries_table;

hstack_t stack_new(void);
void stack_free(const hstack_t stack);
int stack_valid_handler(const hstack_t stack);
unsigned int stack_size(const hstack_t stack);
void stack_push(const hstack_t stack, const void* data_in, const unsigned int size);
unsigned int stack_pop(const hstack_t stack, void* data_out, const unsigned int size);

#endif /* CSTACK_H */
