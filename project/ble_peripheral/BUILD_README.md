# 构建说明

## Makefile 改动说明

本项目的 Makefile 已修改为支持主机/从机双构建系统。

### 构建命令

- `make client` - 仅构建主机（CLIENT）固件
  - 输出目录：`client_output/`
  - 生成文件：`client_output/bin/app.dcf`

- `make server` - 仅构建从机（SERVER）固件
  - 输出目录：`server_output/`
  - 生成文件：`server_output/bin/app.dcf`

- `make all` - 同时构建主机和从机固件

- `make clean` - 清理所有构建输出

### 关键改动

1. **分离的输出目录**
   - 主机固件使用 `client_output/` 目录
   - 从机固件使用 `server_output/` 目录
   - 原 `Output/` 目录保留作为参考

2. **独立的构建脚本**
   - 每个输出目录有独立的 `prebuild.bat` 和 `postbuild.bat`
   - 脚本中的路径已相应修改

3. **库文件选择**
   - 主机（CLIENT）使用 `libbtstack_central.a`
   - 从机（SERVER）使用 `libbtstack.a`
