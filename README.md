# ipack-algorithm

外贸服装智能装箱与尺码配比核心算法 / Apparel intelligent packing and size matching algorithm for foreign trade.

---

## 📌 项目简介
这是一套专为**服装外贸跟单场景**设计的开源核心算法，专注解决两个高频痛点：
1.  **尺码配比计算**：根据订单总数量、尺码比例，快速拆分各尺码分配数量，支持多种配比规则。
2.  **智能装箱优化**：自动计算标准箱、尾箱的装箱方案，最大化利用箱规，减少人工反复试算的时间成本。

> ⚠️ 说明：本仓库仅开放**核心算法逻辑**，不包含完整的可执行软件界面与业务定制功能。
> 如果你是外贸同行，可直接参考、二次开发；如需定制适配你的业务场景，可联系作者沟通。

---

## ✨ 核心功能亮点
-   支持多尺码、多比例的订单配比计算，适配童装/男装/女装等常见服装品类
-   支持标准箱、混装箱、尾箱三种装箱模式，贴近真实工厂操作逻辑
-   计算结果可直接复制到 Excel 使用，无需手动二次处理
-   纯算法逻辑，可独立嵌入 Python 脚本、工具或系统中，灵活度高

---

## 🛠️ 使用示例
```python
# 示例：基础配比与装箱计算逻辑（简化版）
from core import size_matching, packing_calculator

# 1. 输入订单总数量与尺码比例
total_qty = 1000
size_ratio = {"S": 2, "M": 3, "L": 3, "XL": 2}

# 2. 自动拆分各尺码数量
size_qty = size_matching.calculate(total_qty, size_ratio)
print(size_qty)  # 输出各尺码分配数量

# 3. 输入箱规，计算装箱方案
box_size = {"length": 60, "width": 40, "height": 30}
packing_result = packing_calculator.optimize(size_qty, box_size)
print(packing_result)  # 输出标准箱数、尾箱数与每箱配比
