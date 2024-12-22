//added by cl
#include "htab.h"

// 初始容量的最小值
#define HTAB_MIN_CAPACITY 4

// 创建并初始化一个新的 htab，初始大小为 initial_size，所有元素设为 0
htab *htab_create(size_t initial_size) {
    htab *table = (htab *)malloc(sizeof(htab));
    if (!table) {
        return NULL; // 内存分配失败
    }
    // 确保初始容量至少为 HTAB_MIN_CAPACITY
    size_t capacity = initial_size > 0 ? initial_size : HTAB_MIN_CAPACITY;
    // 分配内存并初始化为 0
    table->data = (unsigned *)calloc(capacity, sizeof(unsigned));
    if (!table->data) {
        free(table);
        return NULL; // 内存分配失败
    }
    table->size = initial_size;
    table->capacity = capacity;
    // 如果 initial_size < capacity，已由 calloc 初始化为 0
    // 无需额外操作
    return table;
}

// 内部函数：扩展 htab 的容量至至少 new_capacity
int htab_expand(htab *table, size_t new_capacity) {
    if (new_capacity <= table->capacity) {
        return 0; // 无需扩展
    }
    // 选择新的容量，通常为当前容量的倍数，以减少扩展次数
    size_t adjusted_capacity = table->capacity;
    while (adjusted_capacity < new_capacity) {
        adjusted_capacity *= 2;
        if (adjusted_capacity < HTAB_MIN_CAPACITY) {
            adjusted_capacity = HTAB_MIN_CAPACITY;
            break;
        }
    }
    unsigned *new_data = (unsigned *)realloc(table->data, adjusted_capacity * sizeof(unsigned));
    if (!new_data) {
        return -1; // 内存重新分配失败
    }
    // 初始化新分配的内存为 0
    if (adjusted_capacity > table->capacity) {
        memset(new_data + table->capacity, 0, (adjusted_capacity - table->capacity) * sizeof(unsigned));
    }
    table->data = new_data;
    table->capacity = adjusted_capacity;

    return 0; // 成功
}



// 释放 htab 资源
void htab_free(htab *table) {
    if (!table) {
        return;
    }
    free(table->data);// 释放数据数组
    free(table);// 释放 htab 结构体
}
