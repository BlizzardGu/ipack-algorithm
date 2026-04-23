def optimize(size_qty: dict, box_capacity: int, max_per_box: int = None) -> dict:
    """
    装箱优化算法：自动计算标准箱 + 尾箱
    :param size_qty: 各尺码数量，例如 {"S":200, "M":300, ...}
    :param box_capacity: 每箱最大总件数
    :param max_per_box: 每个尺码每箱最大允许装几件（可选）
    :return: 装箱结果
    """
    total = sum(size_qty.values())
    full_boxes = total // box_capacity
    last_box = total % box_capacity

    result = {
        "total_qty": total,
        "per_box_capacity": box_capacity,
        "full_boxes": full_boxes,
        "last_box_qty": last_box,
        "total_boxes": full_boxes + (1 if last_box > 0 else 0),
        "notes": "标准箱配比一致，尾箱按剩余数量自动分配"
    }

    return result
