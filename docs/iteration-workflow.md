# Volume Lighting 执行总流程

## 1. 目的

本文件整合当前需求、执行守则、测试协议和迭代记录流程，减少多文档切换成本。

## 2. 当前唯一默认目标

- 当前默认目标是 `EquivalentVolumeV1`
- 当前只做单 Volume 单等效光源
- 当前不做动态增量更新、方向基函数、多代表光源和间接光传播

## 3. 单轮执行顺序

1. 阅读主需求文档
   - `graphics-engine-voxel-lighting/docs/requirements.md`

2. 填写执行前检查单
   - 基于 `docs/pre-execution-checklist.md`

3. 实现单轮唯一主目标
   - 本轮不可跨出 `v1` 范围

4. 运行指标测试
   - 按 `docs/metrics-protocol.md`

5. 记录结果
   - 基于 `docs/iteration-log-template.md`

6. 提交代码与文档
   - 代码、测试记录和文档同步提交

## 4. 每轮必须产出

- 可编译代码
- 可运行程序
- 至少一份迭代日志
- 对应测试结果
- 对应 Git 提交

## 5. 当前轮次安排

### Iteration 001

- 目标：补齐三实验场景的启动路径
- 产物：场景配置文件、启动方式、基础测试记录

### Iteration 002+

- 目标：在后续轮次中逐步引入等效光照数据结构、双路径渲染和实验记录
