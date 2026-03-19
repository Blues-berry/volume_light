# Volume Lighting 迭代测试记录

## 1. 基本信息

- 轮次编号：008
- 日期：2026-03-19
- 提交哈希：待本轮提交后更新
- 本轮主目标：修正头盔和球体发黑的高概率代码路径，并把 benchmark 日志正式落盘

## 2. 改动摘要

- 代码改动：
  - `glTF` baseColor 贴图查询改为优先取 `aiTextureType_DIFFUSE` 的索引 `1`，兼容 Assimp 的 `pbrMetallicRoughness` 语义
  - normal / AO / metallicRoughness 贴图查询改为按明确类型和索引读取，而不是只按旧材质习惯读取
  - 法线贴图只有在 mesh 真的有 tangents/bitangents 时才启用
  - 默认 normal 贴图改为平面法线，默认 AO 贴图改为白色
  - 方向光阴影增加投影边界保护和小 bias
  - 点光阴影 PCF 修正为真正使用 `diskRadius` 偏移采样坐标，并加入小 bias
- 产物改动：
  - benchmark 输出保存到 [iter-008](C:\Users\Bluesky\Desktop\codex_test\HybridRenderingEngine\docs\artifacts\benchmarks\iter-008)
  - 新增批量 benchmark 脚本 [run_fixed_frame_benchmarks.ps1](C:\Users\Bluesky\Desktop\codex_test\HybridRenderingEngine\scripts\run_fixed_frame_benchmarks.ps1)
- 文档改动：补充第 008 轮检查单与测试记录

## 3. 测试环境

- 分支：main
- 构建配置：Release
- 设备：NVIDIA GeForce RTX 4060 Laptop GPU
- 驱动版本：591.86
- 分辨率：默认窗口分辨率
- Ground Truth 来源：本轮不涉及

## 4. 测试结果

### 场景：Sponza

#### 模式：ClusteredBaseline

- 编译：通过
- 启动：通过
- 场景切换：命令行单场景启动通过
- 模式切换：本轮不涉及
- 平均帧时间：约 `2.50 ms`
- FPS：`400.00`
- 光照 Pass GPU 时间：本轮拆分记录为 `Light Culling + Shading`
- Light Injection / Voxelization 阶段耗时：`0.005 ms`
- Shading 阶段耗时：`0.336 ms`
- 光源数量测试点：`4`
- Throughput per Light：`0.0013 ms/light`
- GPU 显存占用 / 资源大小：
  - `Cluster AABB SSBO`: `0.105 MB`
  - `Light SSBO`: `0.000 MB`
  - `Light Index SSBO`: `0.659 MB`
  - `Light Grid SSBO`: `0.026 MB`
- Voxel / Volume Grid 显存占用：约 `0.131 MB`
- 新增存储产物大小：benchmark 文本日志 1 份
- 运行时图片位置：延期
- 光照效果图位置：延期
- Ground Truth 图位置：不涉及
- PSNR：不涉及
- SSIM：不涉及
- RMSE：不涉及
- FLIP：不涉及
- 误差/现象：
  - 当前主耗时阶段仍为 `Shading`
  - 本轮改动主要面向 glTF 材质和阴影正确性，对 Sponza 性能无明显优化目标
- benchmark 输出位置：[sponza-120.txt](C:\Users\Bluesky\Desktop\codex_test\HybridRenderingEngine\docs\artifacts\benchmarks\iter-008\sponza-120.txt)

### 场景：MetalRoughSpheres

#### 模式：ClusteredBaseline

- 编译：通过
- 启动：通过
- 场景切换：命令行单场景启动通过
- 模式切换：本轮不涉及
- 平均帧时间：约 `1.64 ms`
- FPS：`609.14`
- 光照 Pass GPU 时间：本轮拆分记录为 `Light Culling + Shading`
- Light Injection / Voxelization 阶段耗时：`0.005 ms`
- Shading 阶段耗时：`0.058 ms`
- 光源数量测试点：`3`
- Throughput per Light：`0.0017 ms/light`
- GPU 显存占用 / 资源大小：
  - `Cluster AABB SSBO`: `0.105 MB`
  - `Light SSBO`: `0.000 MB`
  - `Light Index SSBO`: `0.659 MB`
  - `Light Grid SSBO`: `0.026 MB`
- Voxel / Volume Grid 显存占用：约 `0.131 MB`
- 新增存储产物大小：benchmark 文本日志 1 份
- 运行时图片位置：延期
- 光照效果图位置：延期
- Ground Truth 图位置：不涉及
- PSNR：不涉及
- SSIM：不涉及
- RMSE：不涉及
- FLIP：不涉及
- 误差/现象：
  - `MetalRoughSpheres` 的 FPS 相比上一轮记录有提升
  - 发黑问题的高概率代码路径已修正，但本轮仍缺人工截图确认最终颜色表现
- benchmark 输出位置：[metalroughspheres-120.txt](C:\Users\Bluesky\Desktop\codex_test\HybridRenderingEngine\docs\artifacts\benchmarks\iter-008\metalroughspheres-120.txt)

### 场景：DamagedHelmet

#### 模式：ClusteredBaseline

- 编译：通过
- 启动：通过
- 场景切换：命令行单场景启动通过
- 模式切换：本轮不涉及
- 平均帧时间：约 `1.50 ms`
- FPS：`666.67`
- 光照 Pass GPU 时间：本轮拆分记录为 `Light Culling + Shading`
- Light Injection / Voxelization 阶段耗时：`0.004 ms`
- Shading 阶段耗时：`0.099 ms`
- 光源数量测试点：`2`
- Throughput per Light：`0.0020 ms/light`
- GPU 显存占用 / 资源大小：
  - `Cluster AABB SSBO`: `0.105 MB`
  - `Light SSBO`: `0.000 MB`
  - `Light Index SSBO`: `0.659 MB`
  - `Light Grid SSBO`: `0.026 MB`
- Voxel / Volume Grid 显存占用：约 `0.131 MB`
- 新增存储产物大小：benchmark 文本日志 1 份
- 运行时图片位置：延期
- 光照效果图位置：延期
- Ground Truth 图位置：不涉及
- PSNR：不涉及
- SSIM：不涉及
- RMSE：不涉及
- FLIP：不涉及
- 误差/现象：
  - `DamagedHelmet` 的 FPS 相比上一轮记录有下降后回升，当前仍处在同一量级
  - 头盔发黑的高概率根因之一是“无切线 mesh 仍启用 normal map”，本轮已修正
- benchmark 输出位置：[damagedhelmet-120.txt](C:\Users\Bluesky\Desktop\codex_test\HybridRenderingEngine\docs\artifacts\benchmarks\iter-008\damagedhelmet-120.txt)

## 5. 汇总结论

- 是否达到本轮成功标准：达到
- 相对 baseline 的性能变化：
  - 本轮重点不是压榨性能，而是修正 glTF 贴图与阴影错误路径
  - 性能维持在同一量级，说明修复没有引入明显退化
- 相对 baseline 的计算资源变化：无显著变化
- 相对 baseline 的存储资源变化：
  - 新增 benchmark 文本日志与批量运行脚本
  - 产物可复用，便于后续继续做长时间迭代
- 光源数量扩展性结论：本轮不涉及新的光源规模测试
- 主要视觉退化：
  - 目前仍无法仅凭日志确认“黑色是否已完全消失”
  - 但代码层面已修掉最可疑的 glTF 材质和阴影路径
- 主要稳定性问题：
  - 仍缺固定机位截图
  - 仍缺人工副屏观察确认

## 6. 性能分析

- 这轮的核心不是单纯追 FPS，而是先把“可能让画面整体偏黑”的错误路径去掉，否则后续任何算法指标都不可信。
- `MetalRoughSpheres` 和 `DamagedHelmet` 这两个场景都属于 glTF PBR 模型，材质槽位和切线空间比 `Sponza` 更敏感，所以优先修复 `baseColor` 读取、normal map 启用条件和 shadow bias 是合理的。
- 从 benchmark 指标看，修复后没有出现大幅性能退化；这说明这次改动主要修的是正确性，不是以高额性能成本换显示结果。
- 现在 benchmark 文件已经固定落盘，后续每一轮都可以直接比较同目录下的文本产物，不需要再人工抄终端。

## 7. 下一轮动作

- 下一轮要修什么：
  - 在副屏人工观察条件下确认 `MetalRoughSpheres` 和 `DamagedHelmet` 是否仍发黑
  - 如果仍黑，继续追查 IBL / skybox / BRDF LUT 路径
  - 如果颜色恢复正常，再继续做多光源压力测试或进入 `EquivalentVolumeV1`
- 是否触发范围升级判断：否
- 是否需要延期登记：是
