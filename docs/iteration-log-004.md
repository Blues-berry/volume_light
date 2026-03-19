# Volume Lighting 迭代测试记录

## 1. 基本信息

- 轮次编号：004
- 日期：2026-03-19
- 提交哈希：待本轮提交后更新
- 本轮主目标：修正 clustered light culling 的无效复杂度与计数正确性问题

## 2. 改动摘要

- 代码改动：
  - `lightSSBO` 改为按场景实际点光源数量分配，不再固定按 `1000` 盏灯分配
  - 新增 `activePointLights`，支持以有效光源数驱动 culling
  - `globalIndexCount` 改为 CPU 侧每帧显式清零，移除 compute shader 中的跨 workgroup 竞态写入
- 着色器改动：
  - `clusterCullLightShader.comp` 新增 `activeLightCount`
  - 修正批次尾部光源越界访问，超范围线程显式禁用
- 文档改动：补充第 004 轮检查单与记录

## 3. 测试环境

- 分支：main
- 构建配置：Release
- 设备：本机
- 驱动版本：待补
- 分辨率：默认窗口分辨率
- Ground Truth 来源：本轮不涉及

## 4. 测试结果

### 场景：Sponza

#### 模式：ClusteredBaseline

- 编译：通过
- 启动：通过短时启动验证
- 场景切换：本轮不涉及
- 模式切换：本轮不涉及
- 平均帧时间：待后续人工观测补充
- FPS：待后续人工观测补充
- 光照 Pass GPU 时间：本轮不涉及
- Light Injection / Voxelization 阶段耗时：不涉及
- Shading 阶段耗时：本轮不涉及
- 光源数量测试点：支持 active light 控制，待后续实测
- Throughput per Light：待后续实测
- GPU 显存占用 / 资源大小：`lightSSBO` 从“按 1000 灯预分配”收缩为“按场景实际灯数分配”
- Voxel / Volume Grid 显存占用：无变化
- 新增存储产物大小：无
- 运行时图片位置：延期
- 光照效果图位置：延期
- Ground Truth 图位置：不涉及
- PSNR：不涉及
- SSIM：不涉及
- RMSE：不涉及
- FLIP：不涉及
- 误差/现象：本轮主要修正光源裁剪路径的性能浪费和计数正确性

## 5. 汇总结论

- 是否达到本轮成功标准：达到
- 相对 baseline 的性能变化：理论上降低了 light culling 的无效扫描成本
- 相对 baseline 的计算资源变化：lightSSBO 显存占用降低
- 相对 baseline 的存储资源变化：无
- 光源数量扩展性结论：已具备后续按 active light 做扩展测试的基础
- 主要视觉退化：本轮不涉及
- 主要稳定性问题：当前仍缺少自动截图与定量画质采集

## 6. 下一轮动作

- 下一轮要修什么：缓存方向光阴影刷新，减少静态场景下的重复阴影开销
- 是否触发范围升级判断：否
- 是否需要延期登记：是
