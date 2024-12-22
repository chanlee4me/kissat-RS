#ifndef HTAB_H
#define HTAB_H

#include <stddef.h>  // 为 size_t 定义
#include <stdint.h>  // 为 uint32_t 定义
#include <stdlib.h>  // 为 malloc、calloc、realloc、free 定义
#include <string.h>  // 为 memset 定义
#include <assert.h>  // 为 assert 定义

#ifdef __cplusplus
extern "C" {
#endif

// 定义 htab 结构体
typedef struct htab {
    unsigned *data;    // 指向动态数组的指针
    size_t size;       // 当前元素数量
    size_t capacity;   // 当前分配的容量
} htab;

// 创建并初始化一个新的 htab，初始大小为 initial_size，所有元素设为 0
// 返回指向 htab 的指针，失败时返回 NULL
htab *htab_create(size_t initial_size);

/* 扩展 htab 的容量至至少 new_capacity
// 返回 0 表示成功，-1 表示失败
*/
int htab_expand(htab *table, size_t new_capacity);

// 释放 htab 资源
void htab_free(htab *table);

// // 宏控制边界检查
// #ifdef HTAB_ENABLE_BOUNDS_CHECK
//     #define HTAB_BOUNDS_CHECK(table, index) assert((index) < (table)->size)
// #else
//     #define HTAB_BOUNDS_CHECK(table, index) ((void)0)
// #endif


// 获取 htab 中指定索引的元素
// 如果索引超出当前大小，会自动扩展 htab 以包含该索引，并将新元素初始化为 0
// 返回 0 表示成功，-1 表示失败
// flag为 1 时，表示不扩展，只是获取
static inline unsigned htab_get(htab *table, size_t index, int flag) {
    if (index >= table->size) {
        if(flag == 1){
            return 0;
        }
        // 需要扩展 htab 至 index + 1
        if (htab_expand(table, index + 1) != 0) {
            // 扩展失败，返回 0 作为默认值
            return -1;
        }
        // 更新 size
        table->size = index + 1;
    }
    return table->data[index];
}
// 设置 htab 中指定索引的元素值加 1
static inline int htab_update(htab *table, size_t index) {
    if (index >= table->size) {
        // 需要扩展 htab 至 index + 1
        if (htab_expand(table, index + 1) != 0) {
            // 扩展失败
            return -1;
        }
        // 更新 size
        table->size = index + 1;
        table->data[index] = 1;
    }
    else table->data[index] += 1;
    return 0; // 成功
}

// 获取 htab 当前的大小
static inline size_t htab_size(const htab *table){
    return table->size;
}
// 获取 htab 当前的容量
static inline size_t htab_capacity(const htab *table){
    return table->capacity;
}

#endif // HTAB_H
