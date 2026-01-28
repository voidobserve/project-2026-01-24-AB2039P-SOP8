# ============================================================================
# ble_peripheral 项目 Makefile
# 从 Code::Blocks 配置转换生成
# 目标平台: RISC-V 32位 (AB2039P)
# ============================================================================
# shell: cd "F:\单片机项目\L鲁米玖\车控照明-AB2039P\app\project\ble_peripheral"
# shell: make help
# shell: make all

# 项目名称
PROJECT_NAME = ble_peripheral

# 工具链路径 (使用短路径避免空格和括号问题)
TOOLCHAIN_PATH = /c/PROGRA~2/RV32-T~1/RV32-V1/bin
TOOLCHAIN_PATH_WIN = C:\PROGRA~2\RV32-T~1\RV32-V1\bin
CROSS_COMPILE = $(TOOLCHAIN_PATH)/riscv32-elf-
CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
XMAKER  = $(CROSS_COMPILE)xmaker

# 导出 PATH 环境变量供批处理文件使用
export PATH := $(TOOLCHAIN_PATH):$(PATH)

# 目录定义
TOP_DIR     = ../..
DRIVER_DIR  = $(TOP_DIR)/driver
HEADER_DIR  = $(TOP_DIR)/header
LIBS_DIR    = $(TOP_DIR)/libs
MODULES_DIR = $(TOP_DIR)/modules

# 根据CLIENT宏定义选择不同的输出目录
ifdef CLIENT
OUT_DIR     = client_output
else
OUT_DIR     = server_output
endif

BIN_DIR     = $(OUT_DIR)/bin
OBJ_DIR     = $(OUT_DIR)/obj

# 输出文件
TARGET      = $(BIN_DIR)/app.rv32
TARGET_BIN  = $(BIN_DIR)/app.bin
TARGET_DCF  = $(BIN_DIR)/app.dcf
MAP_FILE    = $(BIN_DIR)/map.txt
LINKER_SCR  = $(OBJ_DIR)/ram.o

# 编译器选项
CFLAGS = -Os -Wall
CFLAGS += -march=rv32imacxbs1
CFLAGS += -ffunction-sections
CFLAGS += -msave-restore
CFLAGS += -mjump-tables-in-text

# 头文件包含路径
INCLUDES = -I.
INCLUDES += -I$(HEADER_DIR)
INCLUDES += -I$(LIBS_DIR)
INCLUDES += -I$(LIBS_DIR)/ble
INCLUDES += -I$(LIBS_DIR)/cpu
INCLUDES += -I$(LIBS_DIR)/usb
INCLUDES += -I$(DRIVER_DIR)
INCLUDES += -I$(MODULES_DIR)/notch_iir
INCLUDES += -Iapp
INCLUDES += -Ible
INCLUDES += -Ibsp
INCLUDES += -Iprod_test
INCLUDES += -Iprod_test/iodm
INCLUDES += -Iprod_test/tbox

# 链接器选项
LDFLAGS = -T$(LINKER_SCR)
LDFLAGS += --gc-sections
LDFLAGS += -Map=$(MAP_FILE)

# 静态库
LIBS = $(LIBS_DIR)/cpu/libplatform.a
LIBS += $(LIBS_DIR)/cpu/libm.a
LIBS += $(LIBS_DIR)/cpu/libc.a
LIBS += $(LIBS_DIR)/cpu/libgcc.a
ifdef CLIENT
CFLAGS += -DCLIENT
LIBS += $(LIBS_DIR)/ble/libbtstack_central.a
else
LIBS += $(LIBS_DIR)/ble/libbtstack.a
endif

# ============================================================================
# 源文件
# ============================================================================

# 驱动源文件
DRIVER_SRCS = \
	$(DRIVER_DIR)/driver_clk.c \
	$(DRIVER_DIR)/driver_gpio.c \
	$(DRIVER_DIR)/driver_hsuart.c \
	$(DRIVER_DIR)/driver_keyscan.c \
	$(DRIVER_DIR)/driver_ledc.c \
	$(DRIVER_DIR)/driver_lowpwr.c \
	$(DRIVER_DIR)/driver_pwm.c \
	$(DRIVER_DIR)/driver_rtc.c \
	$(DRIVER_DIR)/driver_saradc.c \
	$(DRIVER_DIR)/driver_spi.c \
	$(DRIVER_DIR)/driver_tmr.c \
	$(DRIVER_DIR)/driver_uart.c \
	$(DRIVER_DIR)/driver_wdt.c

# 应用源文件
APP_SRCS = \
	app/func.c \
	app/func_bt.c \
	app/func_idle.c \
	app/func_iodm.c \
	app/func_le_bqb_rf.c \
	app/func_le_fcc.c \
	app/func_lowpwr.c \
	app/func_tbox.c

# 蓝牙源文件
BLE_SRCS = \
	ble/ble_adv.c \
	ble/ble_alarm.c \
	ble/ble_client.c \
	ble/ble_fota_service.c \
	ble/ble_init.c \
	ble/ble_proc.c \
	ble/ble_profile.c \
	ble/ble_service.c \
	ble/ble_user_service.c

# 板级支持包源文件
BSP_SRCS = \
	bsp/bsp_huart.c \
	bsp/bsp_huart_iodm.c \
	bsp/bsp_io_key.c \
	bsp/bsp_key.c \
	bsp/bsp_param.c \
	bsp/bsp_saradc.c \
	bsp/bsp_saradc_key.c \
	bsp/bsp_saradc_tsen.c \
	bsp/bsp_saradc_vbat.c \
	bsp/bsp_sys.c \
	bsp/bsp_uart_debug.c \
	bsp/bsp_uart_transfer.c \

# 产测源文件
PROD_TEST_SRCS = \
	prod_test/prod_test.c \
	prod_test/iodm/prod_test_iodm.c \
	prod_test/tbox/prod_test_tbox.c \
	prod_test/tbox/tbox_key.c

# 主程序源文件
MAIN_SRCS = \
	main.c \
	strong_ble.c \
	strong_symbol.c

# 所有源文件
SRCS = $(DRIVER_SRCS) $(APP_SRCS) $(BLE_SRCS) $(BSP_SRCS) $(PROD_TEST_SRCS) $(MAIN_SRCS)

# ============================================================================
# 目标文件
# ============================================================================

# 驱动目标文件
DRIVER_OBJS = $(patsubst $(DRIVER_DIR)/%.c,$(OBJ_DIR)/driver/%.o,$(DRIVER_SRCS))

# 应用目标文件
APP_OBJS = $(patsubst app/%.c,$(OBJ_DIR)/app/%.o,$(APP_SRCS))

# 蓝牙目标文件
BLE_OBJS = $(patsubst ble/%.c,$(OBJ_DIR)/ble/%.o,$(BLE_SRCS))

# 板级支持包目标文件
BSP_OBJS = $(patsubst bsp/%.c,$(OBJ_DIR)/bsp/%.o,$(BSP_SRCS))

# 产测目标文件
PROD_TEST_OBJS = $(patsubst prod_test/%.c,$(OBJ_DIR)/prod_test/%.o,$(PROD_TEST_SRCS))

# 主程序目标文件
MAIN_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(MAIN_SRCS))

# 所有目标文件
OBJS = $(DRIVER_OBJS) $(APP_OBJS) $(BLE_OBJS) $(BSP_OBJS) $(PROD_TEST_OBJS) $(MAIN_OBJS)

# ============================================================================
# 构建规则
# ============================================================================

.PHONY: all clean prebuild postbuild directories build client server clean-all _build_client _build_server

# 默认目标 - 构建主机和从机
all: client server
	@echo "============================================"
	@echo "All builds complete!"
	@echo "  Client: client_output/bin/app.rv32"
	@echo "  Server: server_output/bin/app.rv32"
	@echo "============================================"

# 添加便捷的主机/从机编译目标
client:
	@echo "============================================"
	@echo "Building CLIENT (主机) firmware..."
	@echo "============================================"
	$(MAKE) CLIENT=1 _build_client

server:
	@echo "============================================"
	@echo "Building SERVER (从机) firmware..."
	@echo "============================================"
	$(MAKE) _build_server

# 内部构建目标 - 完整构建 (包含预处理和后处理步骤)
_build_client _build_server: prebuild build postbuild
	@echo "============================================"
	@echo "Build complete: $(TARGET)"
	@echo "============================================"

# 仅编译 (跳过预处理和后处理步骤) - 适用于快速重编译
build: directories $(TARGET)

# 预处理步骤 - 运行 Windows 批处理文件
prebuild: directories
	@echo "Running pre-build steps..."
	$(BIN_DIR)/prebuild.bat $(PROJECT_NAME)

# 后处理步骤 - 运行 Windows 批处理文件
postbuild: $(TARGET) $(BIN_DIR)/appxm.o
	@echo "Running post-build steps..."
	$(BIN_DIR)/postbuild.bat $(PROJECT_NAME)

# 创建输出目录
directories:
	mkdir -p $(OBJ_DIR)/driver
	mkdir -p $(OBJ_DIR)/app
	mkdir -p $(OBJ_DIR)/ble
	mkdir -p $(OBJ_DIR)/bsp
	mkdir -p $(OBJ_DIR)/prod_test/iodm
	mkdir -p $(OBJ_DIR)/prod_test/tbox
	mkdir -p $(BIN_DIR)
	@# 复制批处理脚本和依赖文件到新的输出目录
	@if [ -f Output/bin/prebuild.bat ] && [ ! -f $(BIN_DIR)/prebuild.bat ]; then \
		echo "Copying build scripts and dependencies to $(BIN_DIR)..."; \
		cp Output/bin/prebuild.bat $(BIN_DIR)/prebuild.bat; \
		cp Output/bin/postbuild.bat $(BIN_DIR)/postbuild.bat; \
		cp Output/bin/*.xm $(BIN_DIR)/ 2>/dev/null || true; \
		cp -r Output/bin/res $(BIN_DIR)/ 2>/dev/null || true; \
		echo "Build scripts copied successfully"; \
	fi

# 链接
$(TARGET): $(LINKER_SCR) $(OBJS)
	@echo "Linking $(TARGET)..."
	$(LD) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
	@echo "Output file is $@"

# 从 ram.ld 生成链接脚本
$(LINKER_SCR): ram.ld | directories
	@echo "Processing linker script..."
	$(CC) $(CFLAGS) $(INCLUDES) -E -P -x c -c $< -o $@

# 处理 app.xm
$(BIN_DIR)/appxm.o: $(BIN_DIR)/app.xm
	@echo "Processing app.xm..."
	$(CC) $(CFLAGS) $(INCLUDES) -E -P -x c -c $< -o $@

# ============================================================================
# 编译规则
# ============================================================================

# 驱动编译规则
$(OBJ_DIR)/driver/%.o: $(DRIVER_DIR)/%.c | directories
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 应用编译规则
$(OBJ_DIR)/app/%.o: app/%.c | directories
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 蓝牙编译规则
$(OBJ_DIR)/ble/%.o: ble/%.c | directories
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 板级支持包编译规则
$(OBJ_DIR)/bsp/%.o: bsp/%.c | directories
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 产测编译规则
$(OBJ_DIR)/prod_test/%.o: prod_test/%.c | directories
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 主程序编译规则
$(OBJ_DIR)/%.o: %.c | directories
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ============================================================================
# 清理
# ============================================================================

# 清理所有输出目录 (主机+从机)
clean:
	@echo "Cleaning all output directories..."
	rm -rf client_output/obj
	rm -rf server_output/obj
	rm -f client_output/bin/app.rv32
	rm -f client_output/bin/app.bin
	rm -f client_output/bin/app.dcf
	rm -f client_output/bin/map.txt
	rm -f client_output/bin/appxm.o
	rm -f server_output/bin/app.rv32
	rm -f server_output/bin/app.bin
	rm -f server_output/bin/app.dcf
	rm -f server_output/bin/map.txt
	rm -f server_output/bin/appxm.o
	@echo "Clean complete."

# 清理所有输出目录 (完全删除)
clean-all:
	@echo "Cleaning all output directories (complete removal)..."
	rm -rf client_output
	rm -rf server_output
	@echo "All clean complete."
	@echo "Note: Output/ directory is preserved (contains build scripts)"

# ============================================================================
# 重新构建
# ============================================================================

rebuild: clean all

# ============================================================================
# 帮助信息
# ============================================================================

help:
	@echo "用法: make [目标]"
	@echo ""
	@echo "可用目标:"
	@echo "  all        - 构建主机和从机固件 (默认)"
	@echo "  client     - 仅构建主机固件 (输出到 client_output/)"
	@echo "  server     - 仅构建从机固件 (输出到 server_output/)"
	@echo "  clean      - 清理主机和从机的编译产物"
	@echo "  clean-all  - 完全删除所有输出目录"
	@echo "  rebuild    - 清理后重新构建所有"
	@echo "  help       - 显示此帮助信息"
	@echo ""
	@echo "示例:"
	@echo "  make              # 构建主机和从机"
	@echo "  make all          # 构建主机和从机"
	@echo "  make client       # 仅构建主机"
	@echo "  make server       # 仅构建从机"
	@echo "  make clean        # 清理所有编译产物"
	@echo ""
	@echo "项目名称: $(PROJECT_NAME)"
