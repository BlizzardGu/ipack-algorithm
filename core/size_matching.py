def calculate(total_qty: int, size_ratio: dict) -> dict:
    """
    根据总数量和尺码比例，自动计算每个尺码的数量
    :param total_qty: 订单总数量
    :param size_ratio: 尺码比例，例如 {"S":2, "M":3, "L":3, "XL":2}
    :return: 各尺码分配数量
    """
    total_ratio = sum(size_ratio.values())
    size_qty = {}

    # 基础分配
    for size, ratio in size_ratio.items():
        size_qty[size] = int(total_qty * ratio / total_ratio)

    # 处理余数（让总数刚好等于 total_qty）
    remainder = total_qty - sum(size_qty.values())
    sizes = list(size_ratio.keys())

    for i in range(remainder):
        size_qty[sizes[i % len(sizes)]] += 1

    return size_qty
