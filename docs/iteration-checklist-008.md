# Volume Lighting 执行前检查单

## 1. 轮次信息

- 日期：2026-03-19
- 轮次编号：008
- 负责人：Codex

## 2. 本轮主目标

- 本轮唯一主目标：修正头盔和球体发黑的高概率代码路径，并把 benchmark 日志正式落盘
- 对应需求文档章节：稳定性问题修复、每轮指标记录、性能分析

## 3. 本轮明确不做

- 不做项 1：不实现 `EquivalentVolumeV1`
- 不做项 2：不做自动截图
- 不做项 3：不做 Ground Truth 量化指标

## 4. 成功标准

- 成功标准 1：修正 glTF PBR 贴图读取和阴影采样中的明显错误
- 成功标准 2：三场景固定帧 benchmark 输出保存到仓库目录
- 成功标准 3：根据输出文件更新测试日志和性能分析

## 5. 预计改动范围

- 代码模块：`src/model.cpp`, `include/mesh.h`, `src/mesh.cpp`, `assets/shaders/PBRClusteredShader.frag`
- 着色器模块：`assets/shaders/PBRClusteredShader.frag`
- 文档模块：本检查单、迭代日志、`docs/artifacts/benchmarks/iter-008/`

## 6. 验证计划

- 编译验证：`Release` 构建
- 启动验证：三场景固定 `120` 帧自动退出
- 场景验证：`Sponza`, `MetalRoughSpheres`, `DamagedHelmet`
- 模式验证：`ClusteredBaseline`
- 指标测试：读取仓库内 benchmark 输出文件
- 光源数量测试点（1/10/50/100）：本轮不涉及
- 分阶段耗时记录：读取自动输出的阶段耗时
- 计算资源记录：读取自动输出的资源估计
- 存储资源记录：记录 benchmark 日志文件
- 运行时图片：延期
- 光照效果图：延期
- Ground Truth 对照：不涉及
- PSNR / SSIM / RMSE / FLIP：不涉及

## 7. 提交计划

- 预期提交标题：Fix dark glTF shading path and save benchmark artifacts
- 预期提交内容摘要：修正 glTF 贴图/阴影 bug，并将 benchmark 输出保存到仓库目录

## 8. 备注

- 新发现的超范围想法：可后续增加截图和 CSV 汇总
- 是否需要延期登记：是
- 对应测试记录文件：`docs/iteration-log-008.md`
