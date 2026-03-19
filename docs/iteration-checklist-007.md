# Volume Lighting 执行前检查单

## 1. 轮次信息

- 日期：2026-03-19
- 轮次编号：007
- 负责人：Codex

## 2. 本轮主目标

- 本轮唯一主目标：提升基线测试效率，并收缩点光阴影相关运行成本
- 对应需求文档章节：性能效率指标、计算资源指标、每轮测试后记录指标

## 3. 本轮明确不做

- 不做项 1：不实现 `EquivalentVolumeV1`
- 不做项 2：不做自动截图
- 不做项 3：不做 Ground Truth 画质指标

## 4. 成功标准

- 成功标准 1：程序支持固定帧数自动退出，便于稳定采样指标
- 成功标准 2：程序退出时自动打印性能摘要
- 成功标准 3：点光阴影资源仅为实际可采样阴影灯分配和生成
- 成功标准 4：完成三场景固定帧数测试并把指标写入日志

## 5. 预计改动范围

- 代码模块：`include/engine.h`, `include/renderManager.h`, `src/engine.cpp`, `src/main.cpp`, `src/renderManager.cpp`, `src/scene.cpp`
- 着色器模块：无
- 文档模块：本检查单与迭代日志

## 6. 验证计划

- 编译验证：`Release` 构建
- 启动验证：三场景固定 `120` 帧自动退出
- 场景验证：`Sponza`, `MetalRoughSpheres`, `DamagedHelmet`
- 模式验证：`ClusteredBaseline`
- 指标测试：记录 `Frame Time`、`FPS`、阶段耗时、`Cull ms/light`、资源占用估计
- 光源数量测试点（1/10/50/100）：本轮先保留 active light 能力，不额外改场景
- 分阶段耗时记录：`Dir Shadow`, `Depth Prepass`, `Light Culling`, `Shading`, `Post Process`
- 计算资源记录：`Cluster AABB`, `Light`, `Light Index`, `Light Grid`
- 存储资源记录：无新增图像产物
- 运行时图片：延期
- 光照效果图：延期
- Ground Truth 对照：不涉及
- PSNR / SSIM / RMSE / FLIP：不涉及

## 7. 提交计划

- 预期提交标题：Add fixed-frame benchmarks and trim shadow overhead
- 预期提交内容摘要：加入自动化定长基准测试出口，并收缩点光阴影分配和绑定范围

## 8. 备注

- 新发现的超范围想法：可在后续考虑自动 CSV 导出
- 是否需要延期登记：是
- 对应测试记录文件：`docs/iteration-log-007.md`
