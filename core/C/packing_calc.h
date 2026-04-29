// packing_calc.c (实现文件)
#include "packing_calc.h"
#include <string.h>

// 复制Python的calculate_p_values逻辑（简化版，完整需对齐）
void calculate_p_values(int size_qty, int a2, int b2, int e2, int* p1, int* p2, int* p3, int* p4, int* p5) {
    *p1 = 0; *p2 = 0; *p3 = 0; *p4 = 0; *p5 = 0;
    if (size_qty == 0) return;

    // 计算P5
    if (size_qty <= e2) {
        *p5 = size_qty;
    } else {
        int mod_val = size_qty % a2;
        if (mod_val == 0) {
            *p5 = 0;
        } else {
            if (mod_val + a2 <= b2) {
                *p5 = mod_val + a2;
            } else {
                *p5 = mod_val;
            }
        }
    }

    // 计算P3
    *p3 = (*p5 > 0) ? 1 : 0;

    // 计算P1
    if (size_qty % a2 == 0) {
        *p1 = size_qty / a2;
    } else {
        if (*p5 >= a2) {
            *p1 = size_qty / a2;
        } else {
            *p1 = size_qty / a2 + 1;
        }
    }

    // 计算P2、P4
    *p2 = *p1 - *p3;
    *p4 = (*p2 > 0) ? a2 : 0;
}

// 尾箱配比模式核心逻辑（对齐Python的arrange_output_matrix_ratio）
void CalculateRatioMode(int a2, int b2, int size_list[20], CalcResult* result) {
    // 初始化结果为0
    memset(result->matrix, 0, sizeof(result->matrix));
    memset(result->m_column, 0, sizeof(result->m_column));
    memset(result->n_column, 0, sizeof(result->n_column));

    int row = 0;
    int e2 = b2 - a2 + 1;

    // 1. 处理标准箱
    int tail_list[20][2] = {0}; // 存储尾箱 (col, qty)
    int tail_count = 0;
    int standard_boxes[20][3] = {0}; // (col, qty, boxes)
    int standard_count = 0;

    for (int col = 0; col < 20; col++) {
        int qty = size_list[col];
        if (qty <= 0) continue;

        int full_boxes = qty / a2;
        int tail = qty % a2;

        // 尾箱≤(b2-a2)则合并到最后一个标准箱
        if (full_boxes > 0 && tail > 0 && tail <= (b2 - a2)) {
            full_boxes -= 1;
            tail += a2;
        }

        // 存储标准箱
        if (full_boxes > 0) {
            standard_boxes[standard_count][0] = col;
            standard_boxes[standard_count][1] = a2;
            standard_boxes[standard_count][2] = full_boxes;
            standard_count++;
        }

        // 存储尾箱
        if (tail > 0) {
            tail_list[tail_count][0] = col;
            tail_list[tail_count][1] = tail;
            tail_count++;
        }
    }

    // 写入标准箱到矩阵
    for (int i = 0; i < standard_count && row < 40; i++) {
        int col = standard_boxes[i][0];
        int q = standard_boxes[i][1];
        int boxes = standard_boxes[i][2];
        result->matrix[row][col] = q;
        result->m_column[row] = boxes; // 箱数
        row++;
    }

    // 2. 处理尾箱混装
    int remaining_tails[20][2] = {0};
    int remain_count = tail_count;
    memcpy(remaining_tails, tail_list, sizeof(tail_list));

    while (remain_count > 0 && row < 40) {
        int current_total = 0;
        int combo[20][2] = {0}; // 本次混装的尺码 (col, qty)
        int combo_count = 0;
        int new_remain[20][2] = {0};
        int new_remain_count = 0;

        // 挑选可混装的尺码
        for (int i = 0; i < remain_count; i++) {
            int col = remaining_tails[i][0];
            int q = remaining_tails[i][1];
            if (current_total + q <= b2) {
                combo[combo_count][0] = col;
                combo[combo_count][1] = q;
                combo_count++;
                current_total += q;
            } else {
                new_remain[new_remain_count][0] = col;
                new_remain[new_remain_count][1] = q;
                new_remain_count++;
            }
        }

        // 写入混装箱到矩阵
        if (combo_count > 0) {
            for (int i = 0; i < combo_count; i++) {
                int col = combo[i][0];
                int q = combo[i][1];
                result->matrix[row][col] = q;
            }
            result->m_column[row] = 1; // 混装箱数为1
            row++;
        }

        // 更新剩余尾箱
        remain_count = new_remain_count;
        memcpy(remaining_tails, new_remain, sizeof(remaining_tails));
    }

    // 计算小计（N列）
    for (int r = 0; r < 40; r++) {
        if (result->m_column[r] > 0) {
            int total = 0;
            for (int c = 0; c < 20; c++) {
                total += result->matrix[r][c] * result->m_column[r];
            }
            result->n_column[r] = total;
        }
    }
}
