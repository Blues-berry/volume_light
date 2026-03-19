# Volume Lighting Task Set

## 1. 任务总览

本项目当前围绕“基于 Volume 的等效直接光照表示”推进，任务拆分如下：

1. 搭建项目基础目录与需求文档
2. 调研对标论文与可复用开源项目
3. 选择并本地部署可改造的渲染引擎基底
4. 修复 GitHub 上传问题，建立稳定推送链路
5. 选择适合创新算法验证的 2 到 3 个场景
6. 基于对标论文设计初步实验方案
7. 验证本地部署代码可实际运行
8. 在此基础上再进入算法改造与对比实验

执行约束以以下文档为准：

- `docs/execution-rules.md`
- `docs/pre-execution-checklist.md`

## 2. 当前完成状态

### 已完成

1. 对标论文调研完成
   - Clustered Deferred and Forward Shading
   - Forward+
   - Efficient Real-Time Shading with Many Lights
   - Light Propagation Volumes in CryEngine 3
   - Interactive Indirect Illumination Using Voxel Cone Tracing

2. 开源基底选型完成
   - 选定 `HybridRenderingEngine` 作为主改造基底

3. 本地部署完成
   - SSH 克隆成功
   - CMake 配置成功
   - Release 编译成功

4. GitHub 上传问题已修复
   - 解决了远端 unpack 失败和本地分支名不一致问题
   - 当前本地分支已统一为 `main`
   - `origin` 已切换为 SSH

5. 运行时兼容问题已修复
   - `src/scene.cpp` 中旧版 JSON 隐式转换已改为显式 `.get<...>()`
   - `assets/shaders/PBRClusteredShader.frag` 中 `mod(uint, float)` 已改为 `zTile % 8u`

6. 实际运行验证完成
   - 程序可以成功加载 `Sponza`
   - 修复 shader 兼容问题后，程序可稳定运行

### 待完成

1. 在仓库内补齐第二和第三个实验场景描述文件
2. 记录基线渲染参数与性能数据
3. 实现 Volume 等效光源数据结构与实验路径
4. 开始第一轮算法对比实验

### 当前默认范围

- 当前默认目标固定为 `EquivalentVolumeV1`
- 当前只做单 Volume 单等效光源
- 当前不做动态增量更新和方向基函数

## 3. 场景选择

### 场景 A: Sponza Atrium

用途：

- 作为主性能场景
- 验证多点光源、遮挡结构和长空间布局下的分块效果
- 适合对比 Clustered Light List 与 Volume 等效光照表示

原因：

- 场景体量足够大
- 遮挡关系复杂
- 已在当前工程中直接可运行

### 场景 B: Metal Rough Spheres

用途：

- 作为受控材质场景
- 验证等效光源表示对不同粗糙度、金属性的影响
- 重点观察镜面方向误差和高光稳定性

原因：

- 变量少，适合做材料维度对比
- 便于做定量截图和误差分析

### 场景 C: Damaged Helmet Close-up

用途：

- 作为高频法线和局部高光场景
- 检验等效光照在近距离细节处的保真度
- 验证法线贴图与镜面反射区域是否对压缩表示更敏感

原因：

- 近景更容易暴露方向误差
- 适合作为画质风险验证样例

## 4. 初步实验设计

### 4.1 基线方法

1. 原始 Clustered Lighting
   - 保留当前引擎的 Cluster AABB + Light Grid + Global Light Index List 路径

2. 对照方法
   - Forward+ 作为文献对比背景
   - Lightmap 作为“静态低成本但不可局部更新”的背景工程对照
   - `v1` 不要求本地工程复现这两条路径

### 4.2 目标方法

在 Clustered Rendering 的三维分块基础上，为每个 Volume 构建等效直接光照表示。

第一轮建议从最简单版本开始：

1. 单 Volume 内多点光源压缩为一个等效光源
2. 保留能量、颜色和代表位置
3. 先重点验证漫反射，再评估镜面误差

### 4.3 变量设计

主要自变量：

- Volume 网格分辨率
- 单个 Volume 内的光源密度
- 等效光源数量

主要因变量：

- 平均帧时间
- 光照 Pass GPU 时间
- 与基线图像的平均误差
- 高光区域误差

### 4.4 场景与指标对应关系

1. Sponza
   - 重点记录性能收益与分块规模影响

2. Metal Rough Spheres
   - 重点记录粗糙度变化对误差的影响

3. Damaged Helmet
   - 重点记录法线贴图和近景高光误差

## 5. 本地运行验证记录

### 5.1 初始运行结果

初次启动时，程序在渲染初始化阶段失败：

- 原因：`PBRClusteredShader.frag` 中存在 `mod(uint, float)` 类型歧义
- 现象：Renderer 初始化失败，程序退出

### 5.2 修复后结果

修复内容：

- 将 `colors[uint(mod(zTile, 8.0))]` 改为 `colors[zTile % 8u]`

结果：

- 程序成功通过初始化
- 在 `Sponza` 场景下可稳定运行

## 6. 下一阶段执行顺序

1. 补齐 `MetalRoughSpheres` 与 `DamagedHelmet` 的场景描述文件
2. 记录当前 Clustered 基线在三个场景下的启动参数与运行截图
3. 建立基线性能记录表
4. 再开始写 Volume 等效光照的数据结构与 shader 路径

每一轮开始前，先填写 `docs/pre-execution-checklist.md`，再执行对应迭代。

## 7. 参考论文链接

- Clustered Deferred and Forward Shading
  https://www.cse.chalmers.se/~uffe/clustered_shading_preprint.pdf

- Forward+: Bringing Deferred Lighting to the Next Level
  https://diglib.eg.org/items/1db2c4c6-dcab-42ea-8c0a-6805d781759e

- Efficient Real-Time Shading with Many Lights
  https://www.zora.uzh.ch/id/eprint/107598/1/a11-olsson.pdf

- Light Propagation Volumes in CryEngine 3
  http://www.crytek.com/download/Light_Propagation_Volumes.pdf

- Interactive Indirect Illumination Using Voxel Cone Tracing
  https://research.nvidia.com/labs/rtr/publication/crassin2011givoxels/
