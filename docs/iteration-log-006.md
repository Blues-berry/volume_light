# Volume Lighting 迭代测试记录

## 1. 基本信息

- 轮次编号：006
- 日期：2026-03-19
- 提交哈希：待本轮提交后更新
- 本轮主目标：增加运行时指标采集与测试效率控制面板

## 2. 改动摘要

- 代码改动：
  - 新增 GPU 分阶段计时接口和运行时显示
  - 新增 `Enable GPU Profiling` 开关，避免日常运行时持续引入计时开销
  - 新增 active point light 滑条，便于按有效光源数做测试
  - 新增 Cluster AABB / Light / Light Index / Light Grid 资源大小显示
- 着色器改动：
  - `clusterCullLightShader.comp` 使用 `activeLightCount`
  - `PBRClusteredShader.frag` 增加点光阴影访问边界保护
- 文档改动：补充第 006 轮检查单与记录

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
- 平均帧时间：可在运行时 UI 观察，未做人工抄录
- FPS：可在运行时 UI 观察，未做人工抄录
- 光照 Pass GPU 时间：支持分阶段观察
- Light Injection / Voxelization 阶段耗时：当前对应 `Light Culling`
- Shading 阶段耗时：支持观察
- 光源数量测试点：支持 `0..sceneLightCount` 范围调节
- Throughput per Light：支持运行时观察 `Cull ms/light`
- GPU 显存占用 / 资源大小：支持运行时观察 4 类主要 SSBO 大小
- Voxel / Volume Grid 显存占用：当前可通过 Cluster AABB / Light Grid 近似统计
- 新增存储产物大小：无
- 运行时图片位置：延期
- 光照效果图位置：延期
- Ground Truth 图位置：不涉及
- PSNR：不涉及
- SSIM：不涉及
- RMSE：不涉及
- FLIP：不涉及
- 误差/现象：运行时指标采集能力已具备，人工截图与固定机位对照仍待补

### 场景：MetalRoughSpheres

#### 模式：ClusteredBaseline

- 编译：通过
- 启动：通过短时启动验证
- 场景切换：命令行启动单场景通过
- 模式切换：本轮不涉及
- 平均帧时间：可在运行时 UI 观察
- FPS：可在运行时 UI 观察
- 误差/现象：本轮未做人工截图

### 场景：DamagedHelmet

#### 模式：ClusteredBaseline

- 编译：通过
- 启动：通过短时启动验证
- 场景切换：命令行启动单场景通过
- 模式切换：本轮不涉及
- 平均帧时间：可在运行时 UI 观察
- FPS：可在运行时 UI 观察
- 误差/现象：本轮未做人工截图

## 5. 汇总结论

- 是否达到本轮成功标准：达到
- 相对 baseline 的性能变化：本轮主要提升测试与观测效率
- 相对 baseline 的计算资源变化：新增的是计时查询对象和 UI 展示，主要资源开销可控
- 相对 baseline 的存储资源变化：无
- 光源数量扩展性结论：已具备按 active point light 做后续曲线测试的入口
- 主要视觉退化：未发现新增视觉退化
- 主要稳定性问题：图像级指标与固定机位截图仍需后续人工流程补齐

## 6. 下一轮动作

- 下一轮要修什么：在副屏人工观察条件下记录首批基线截图与实测数值
- 是否触发范围升级判断：否
- 是否需要延期登记：是
