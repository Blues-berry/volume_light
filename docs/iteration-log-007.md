# Volume Lighting 迭代测试记录

## 1. 基本信息

- 轮次编号：007
- 日期：2026-03-19
- 提交哈希：待本轮提交后更新
- 本轮主目标：提升基线测试效率，并收缩点光阴影相关运行成本

## 2. 改动摘要

- 代码改动：
  - 增加固定帧数自动退出能力，支持 `hybridRenderer.exe <SceneName> <FrameCount>`
  - 程序退出时自动打印统一性能摘要，便于每轮记录指标
  - 点光阴影 FBO、预处理生成和运行时绑定统一限制为“最多 4 盏可采样阴影灯”
  - compute dispatch 的 `z` 维改为基于 `gridSizeZ / 4` 计算，移除硬编码 `6`
- 着色器改动：无
- 文档改动：补充第 007 轮检查单与测试记录

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
- 平均帧时间：约 `1.88 ms`
- FPS：`533.33`
- 光照 Pass GPU 时间：本轮拆分记录为 `Light Culling + Shading`
- Light Injection / Voxelization 阶段耗时：`0.004 ms`（当前对应 `Light Culling`）
- Shading 阶段耗时：`0.324 ms`
- 光源数量测试点：`4`
- Throughput per Light：`0.0010 ms/light`
- GPU 显存占用 / 资源大小：
  - `Cluster AABB SSBO`: `0.105 MB`
  - `Light SSBO`: `0.000 MB`（四盏灯，理论值很小）
  - `Light Index SSBO`: `0.659 MB`
  - `Light Grid SSBO`: `0.026 MB`
- Voxel / Volume Grid 显存占用：`Cluster AABB + Light Grid` 合计约 `0.131 MB`
- 新增存储产物大小：无
- 运行时图片位置：延期
- 光照效果图位置：延期
- Ground Truth 图位置：不涉及
- PSNR：不涉及
- SSIM：不涉及
- RMSE：不涉及
- FLIP：不涉及
- 误差/现象：
  - `Dir Shadow` 为 `0.000 ms`，说明方向光阴影缓存生效
  - 当前主耗时阶段是 `Shading (0.324 ms)`，其次是 `Depth Prepass (0.202 ms)`
  - `Light Culling` 成本已经很低，不是当前瓶颈

### 场景：MetalRoughSpheres

#### 模式：ClusteredBaseline

- 编译：通过
- 启动：通过
- 场景切换：命令行单场景启动通过
- 模式切换：本轮不涉及
- 平均帧时间：约 `2.31 ms`
- FPS：`433.21`
- 光照 Pass GPU 时间：本轮拆分记录为 `Light Culling + Shading`
- Light Injection / Voxelization 阶段耗时：`0.004 ms`
- Shading 阶段耗时：`0.056 ms`
- 光源数量测试点：`3`
- Throughput per Light：`0.0014 ms/light`
- GPU 显存占用 / 资源大小：
  - `Cluster AABB SSBO`: `0.105 MB`
  - `Light SSBO`: `0.000 MB`
  - `Light Index SSBO`: `0.659 MB`
  - `Light Grid SSBO`: `0.026 MB`
- Voxel / Volume Grid 显存占用：约 `0.131 MB`
- 新增存储产物大小：无
- 运行时图片位置：延期
- 光照效果图位置：延期
- Ground Truth 图位置：不涉及
- PSNR：不涉及
- SSIM：不涉及
- RMSE：不涉及
- FLIP：不涉及
- 误差/现象：
  - 当前主耗时阶段是 `Depth Prepass (0.133 ms)`，明显高于 `Shading (0.056 ms)`
  - 对于这种简单场景，clustered 光照计算已经不是主要开销

### 场景：DamagedHelmet

#### 模式：ClusteredBaseline

- 编译：通过
- 启动：通过
- 场景切换：命令行单场景启动通过
- 模式切换：本轮不涉及
- 平均帧时间：约 `1.34 ms`
- FPS：`745.34`
- 光照 Pass GPU 时间：本轮拆分记录为 `Light Culling + Shading`
- Light Injection / Voxelization 阶段耗时：`0.004 ms`
- Shading 阶段耗时：`0.108 ms`
- 光源数量测试点：`2`
- Throughput per Light：`0.0020 ms/light`
- GPU 显存占用 / 资源大小：
  - `Cluster AABB SSBO`: `0.105 MB`
  - `Light SSBO`: `0.000 MB`
  - `Light Index SSBO`: `0.659 MB`
  - `Light Grid SSBO`: `0.026 MB`
- Voxel / Volume Grid 显存占用：约 `0.131 MB`
- 新增存储产物大小：无
- 运行时图片位置：延期
- 光照效果图位置：延期
- Ground Truth 图位置：不涉及
- PSNR：不涉及
- SSIM：不涉及
- RMSE：不涉及
- FLIP：不涉及
- 误差/现象：
  - 当前主耗时阶段是 `Shading (0.108 ms)`，其次是 `Post Process (0.046 ms)`
  - `Light Culling` 保持在 `0.004 ms`，说明当前灯数下扩展性开销可忽略

## 5. 汇总结论

- 是否达到本轮成功标准：达到
- 相对 baseline 的性能变化：
  - 本轮没有切换算法路径，主要收益是“测试效率提升 + 阴影资源收缩”
  - 方向光阴影缓存仍有效，静态场景帧内方向光阴影开销为 `0.000 ms`
- 相对 baseline 的计算资源变化：
  - 点光阴影相关资源和预处理工作现在只覆盖最多 4 盏真正会采样阴影的灯
  - 这项优化主要影响启动/预处理和资源分配，对当前三场景的帧内收益有限
- 相对 baseline 的存储资源变化：无
- 光源数量扩展性结论：
  - 当前三场景下 `Light Culling` 恒定约 `0.004 ms`
  - 在 `2~4` 盏灯范围内，culling 成本基本稳定，符合 clustered 路径预期
- 主要视觉退化：本轮未做图像级对照，无法下视觉结论
- 主要稳定性问题：
  - 仍缺固定机位截图和颜色恢复人工确认
  - 仍缺 `1/10/50/100` 光源规模实验场景

## 6. 性能分析

- 这轮真正解决的是“怎么稳定测”，而不是只盯某一个阶段做局部微优化。固定帧数自动退出后，每轮都能用同一命令拿到可复现指标，这比手工观察 UI 更可靠。
- 对当前三场景来说，`Light Culling` 已经不是主要瓶颈。`Sponza` 和 `DamagedHelmet` 更偏向 `Shading` 主导，`MetalRoughSpheres` 反而是 `Depth Prepass` 更占比。
- 方向光阴影缓存生效后，静态场景里 `Dir Shadow` 已经退到 `0.000 ms`。这说明继续在方向光阴影路径上抠帧收益不会太大，下一阶段更该盯 `Shading` 或材质/后处理成本。
- 点光阴影上限收缩主要减少的是无效资源和无效预处理，对启动路径和后续扩展到更多灯时更有意义；在当前 `2~4` 盏灯的小场景里，帧内提升不会特别显著，这和实测现象一致。

## 7. 下一轮动作

- 下一轮要修什么：
  - 做固定机位截图和“物体是否仍偏黑”的人工验证
  - 补一组可控多光源压力测试，真正测 `1/10/50/100` 曲线
  - 如果 baseline 颜色正常，再进入 `EquivalentVolumeV1`
- 是否触发范围升级判断：否
- 是否需要延期登记：是
