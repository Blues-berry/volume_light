# Volume Lighting 执行前检查单

## 1. 轮次信息

- 日期：2026-03-19
- 轮次编号：004
- 负责人：Codex

## 2. 本轮主目标

- 本轮唯一主目标：修正 clustered light culling 的无效复杂度与计数正确性问题
- 对应需求文档章节：`v1` 基线运行效率与指标测试能力

## 3. 本轮明确不做

- 不做项 1：不实现 `EquivalentVolumeV1`
- 不做项 2：不做动态增量更新
- 不做项 3：不做方向基函数或 SH

## 4. 成功标准

- 成功标准 1：light SSBO 不再按 1000 盏灯固定扫描
- 成功标准 2：light culling 全局计数器改为 CPU 侧显式清零
- 成功标准 3：工程可重新编译并短时启动

## 5. 预计改动范围

- 代码模块：`src/renderManager.cpp`, `include/renderManager.h`
- 着色器模块：`assets/shaders/ComputeShaders/clusterCullLightShader.comp`
- 文档模块：本检查单与迭代日志

## 6. 验证计划

- 编译验证：`Release` 构建
- 启动验证：短时启动验证
- 场景验证：`Sponza`
- 模式验证：`ClusteredBaseline`
- 指标测试：记录可用指标能力
- 光源数量测试点（1/10/50/100）：先支持 active light 控制
- 分阶段耗时记录：本轮不做完整采集
- 计算资源记录：记录 light buffer 理论大小变化
- 存储资源记录：无新增图像产物
- 运行时图片：延期
- 光照效果图：延期
- Ground Truth 对照：不涉及
- PSNR / SSIM / RMSE / FLIP：不涉及

## 7. 提交计划

- 预期提交标题：Improve clustered light culling efficiency
- 预期提交内容摘要：修正光源缓冲大小、active light 计数和 culling 计数器清零路径

## 8. 备注

- 新发现的超范围想法：无
- 是否需要延期登记：是，截图与定量画质指标延期
- 对应测试记录文件：`docs/iteration-log-004.md`
