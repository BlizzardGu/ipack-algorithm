from core import size_matching, packing_calculator

if __name__ == "__main__":
    # 订单信息
    total_qty = 1000
    size_ratio = {"S": 2, "M": 3, "L": 3, "XL": 2}
    box_capacity = 50

    # 1. 计算尺码配比
    print("=== 尺码分配结果 ===")
    size_qty = size_matching.calculate(total_qty, size_ratio)
    for size, qty in size_qty.items():
        print(f"{size}: {qty}")

    # 2. 计算装箱方案
    print("\n=== 装箱方案 ===")
    packing_result = packing_calculator.optimize(size_qty, box_capacity)
    for k, v in packing_result.items():
        print(f"{k}: {v}")
