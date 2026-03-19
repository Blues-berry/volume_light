# Volume Lighting 执行前检查单

## 1. 轮次信息

- 日期：2026-03-19
- 轮次编号：006
- 负责人：Codex

## 2. 本轮主目标

- 本轮唯一主目标：增加运行时指标采集与测试效率控制面板
- 对应需求文档章节：指标测试协议、性能效率指标、计算资源指标

## 3. 本轮明确不做

- 不做项 1：不生成自动截图
- 不做项 2：不实现 Ground Truth 对照
- 不做项 3：不进入 `EquivalentVolumeV1`

## 4. 成功标准

- 成功标准 1：UI 可显示主要 GPU 分阶段耗时
- 成功标准 2：UI 可显示主要 light/cluster 缓冲理论占用
- 成功标准 3：UI 支持 active point light 调节，便于后续做扩展测试

## 5. 预计改动范围

- 代码模块：`include/renderManager.h`, `src/renderManager.cpp`
- 着色器模块：`clusterCullLightShader.comp`, `PBRClusteredShader.frag`
- 文档模块：本检查单与迭代日志

## 6. 验证计划

- 编译验证：`Release` 构建
- 启动验证：短时启动验证
- 场景验证：`Sponza`, `MetalRoughSpheres`, `DamagedHelmet`
- 模式验证：`ClusteredBaseline`
- 指标测试：确认 UI 可展示分阶段耗时和资源大小
- 光源数量测试点（1/10/50/100）：先支持 active light 控制，受当前场景真实灯数限制
- 分阶段耗时记录：方向光阴影、Depth Prepass、Light Culling、Shading、Post Process
- 计算资源记录：Cluster AABB / Light / Light Index / Light Grid SSBO
- 存储资源记录：无新增图像产物
- 运行时图片：延期
- 光照效果图：延期
- Ground Truth 对照：不涉及
- PSNR / SSIM / RMSE / FLIP：不涉及

## 7. 提交计划

- 预期提交标题：Add runtime profiling and test controls
- 预期提交内容摘要：增加 GPU 分阶段计时、资源指标展示和 active light 调节

## 8. 备注

- 新发现的超范围想法：无
- 是否需要延期登记：是
- 对应测试记录文件：`docs/iteration-log-006.md`
