#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list_node {
    char name[256];
    int value;
    struct list_node* ptr_next;
};

void insert(struct list_node** start_ptr, const char* str, int value)
{
    struct list_node* new_ptr = NULL, * prev_ptr = NULL, * cur_ptr = *start_ptr;

    new_ptr = (struct list_node*)malloc(sizeof(struct list_node));

    if (new_ptr != NULL)
    {
        memset(new_ptr, 0x00, sizeof(struct list_node));
        strcpy(new_ptr->name, str);
        new_ptr->value = value;
        new_ptr->ptr_next = NULL;

        while (cur_ptr != NULL && value < cur_ptr->value)
        {
            prev_ptr = cur_ptr;
            cur_ptr = cur_ptr->ptr_next;
        }

        if (prev_ptr == NULL)
        {
            new_ptr->ptr_next = *start_ptr;
            *start_ptr = new_ptr;
        }
        else
        {
            prev_ptr->ptr_next = new_ptr;
            new_ptr->ptr_next = cur_ptr;
        }
    }
}

void print_records(struct list_node* start_ptr_list)
{
    int i = 2;
    while (start_ptr_list != NULL && i < 22)
    {
        gotoxy(1, 1 + i);
        printf("%d) %d ", i / 2, start_ptr_list->value);
        puts(start_ptr_list->name);
        start_ptr_list = start_ptr_list->ptr_next;
        i += 2;
    }
}