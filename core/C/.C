// packing_calc.h (头文件)
#ifndef PACKING_CALC_H
#define PACKING_CALC_H

#ifdef __cplusplus
extern "C" {
#endif

// 定义数据结构（对应Python的矩阵、数组）
typedef struct {
    int matrix[40][20];  // 输出矩阵
    int m_column[40];    // M列（箱数）
    int n_column[40];    // N列（小计）
} CalcResult;

// 核心计算函数（尾箱配比模式）
__declspec(dllexport) void CalculateRatioMode(
    int a2,          // 标准装箱件数
    int b2,          // 最大装件数
    int size_list[20],// 20个尺码数量
    CalcResult* result// 输出结果
);

// 辅助函数：正常模式/尾箱单独模式计算（按需实现）
__declspec(dllexport) void CalculateNormalMode(
    int a2, int b2, int size_list[20], CalcResult* result
);

#ifdef __cplusplus
}
#endif

#endif // PACKING_CALC_H
