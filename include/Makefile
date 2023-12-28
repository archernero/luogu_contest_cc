# 项目根目录
SOURCE_ROOT  := $(shell pwd)
# build + 根目录名是项目的build目录 用于放二进制文件 => 顺便方便git ignore
BUILD_DIR    :=  build_$(notdir $(SOURCE_ROOT))
# 项目build的绝对路径
BUILD_DIR_ABS := $(SOURCE_ROOT)/$(BUILD_DIR)
# 可执行文件用根目录文件命名
TARGET := $(BUILD_DIR_ABS)/$(notdir $(SOURCE_ROOT))

CC ?= gcc
CXX ?= g++
CFLAGS := -fPIC -pthread -std=c11 -g -Wall -Wextra -pedantic -O3 -ftree-vectorize -ffast-math -mavx -mfma -mavx2
# man gcc
# -g 选项告诉g++产生调试信息，以调试程序
# -O[n]优化源代码 在调试过程中注意关闭
# -l 用来指定程序要链接的库，紧接的就是库名 在/lib和/usr/lib和/usr/local/lib里的库直接用-l就能链接
# 如果库文件没有放在上面三个目录中，需要使用-L参数指定库文件所在目录 -L后面接的就是库文件所在的目录名
# e.g g++ -L/home/xiaotongl/testlibfolder -lmytest test.cc
# -I 指定头文件的搜索目录 头文件可以用相对路径 比如头文件在当前目录，可以用-I.来指定
# -Wall 打印警告信息
# -w 关闭所有警告信息
# -std=c++11设置编译标准
# -o 指定输出文件名

# https://blog.csdn.net/wuu19/article/details/118252637
# -Wno-unused-variable：不显示未使用的变量告警
# -Wno-unused-parameter：不显示未使用的参数告警
# -Wno-unused-function：不显示未使用的函数告警
# -Wno-unused-but-set-variable：不显示已赋值但未使用的变量告警
# -Wno-unused-private-field：不显示未使用的类私有成员告警
# -Wno-unused-label：不显示未使用的跳转标记告警
# error: undefined symbol: std::__cxx11 https://blog.csdn.net/Three_dog/article/details/104701644

# [TODO] 随着Makefile放的目录深度不同, 这里会出现目录不一致的问题
CXXFLAGS_DEBUG := -fPIC -pthread -std=c++11 -g -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wno-unused-private-field -Wno-unused-label -pedantic -ftree-vectorize -ffast-math -mavx -mfma -mavx2 -I.
CXXFLAGS_DEBUG += \
-I$(SOURCE_ROOT)/../include \
-I$(SOURCE_ROOT)

CXXFLAGS := -fPIC -pthread -std=c++11 -g -Wall -Wextra -pedantic -O3 -ftree-vectorize -ffast-math -mavx -mfma -mavx2 -I.
CXXFLAGS += \
-I$(SOURCE_ROOT)/../include \
-I$(SOURCE_ROOT)

ODIR=.obj

# SOURCES := $(wildcard $(SRC)/*.c)
# 它的用法是：$(wildcard PATTERN...) 。在Makefile中，
# 它被展开为已经存在的、使用空格分开的、匹配此模式的所有文件列表。如果不存在任何符合此模式的文件，函数会忽略模式字符并返回空。
# 一般我们可以使用“$(wildcard *.c)”来获取工作目录下的所有的.c文件列表。
SOURCES := $(TARGET_FILE).cc
# patsubst 模式替换 ==> (源模式， 目标模式， 文件列表) 记得第一次运行新建.obj文件夹
OBJECTS := $(ODIR)/$(TARGET_FILE).o
# OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# 把下面的所有的job名称都加进来 这个东西其实就是防止job名称与文件名称冲突导致指令不执行，所以都加进来即可
# 罪魁祸首在这里 .bashrc里面自动给你alias了 导致每次make前都需要cleanall 线上使用其实编译前是需要cleanall的
# 自己测试为了提升速度就不进行cleanall了 nonono 
# 就是要每次都要cleanall清除重新编译，不然代码有的时候不生效
# alias make="make cleanall; make -j8"
.PHONY: all clean

# main就是最终生成的可执行文件名
all: $(TARGET)

# LDFLAGS += -L$(SOURCE_ROOT)/../../lib -lprotobuf -lgrpc++ -lgrpc -laddress_sorting -lupb -lgpr -lssl -ldl -pthread -lcrypto -ldl -pthread -lre2 -lcares -lz -labsl_raw_hash_set -labsl_hashtablez_sampler -labsl_hash -labsl_city -labsl_low_level_hash -labsl_random_distributions -labsl_random_seed_sequences -labsl_random_internal_pool_urbg -labsl_random_internal_randen -labsl_random_internal_randen_hwaes -labsl_random_internal_randen_hwaes_impl -labsl_random_internal_randen_slow -labsl_random_internal_platform -labsl_random_internal_seed_material -labsl_random_seed_gen_exception -labsl_statusor -labsl_status -labsl_cord -labsl_cordz_info -labsl_cord_internal -labsl_cordz_functions -labsl_exponential_biased -labsl_cordz_handle -labsl_crc_cord_state -labsl_crc32c -labsl_crc_internal -labsl_crc_cpu_detect -labsl_bad_optional_access -labsl_strerror -labsl_str_format_internal -labsl_synchronization -labsl_graphcycles_internal -labsl_stacktrace -labsl_symbolize -labsl_debugging_internal -labsl_demangle_internal -labsl_malloc_internal -labsl_time -labsl_civil_time -labsl_strings -labsl_strings_internal -lrt -labsl_base -labsl_spinlock_wait -labsl_int128 -labsl_throw_delegate -labsl_time_zone -labsl_bad_variant_access -labsl_raw_logging_internal -labsl_log_severity 
# LDFLAGS += -pthread -ldl

# 这一步加上需要引入的静态链接库
# $^ 这个参数一定要放到最前面 即g++后
# $(CXX) $^ $(LDFLAGS) -o $@ 
$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ 

# $@代表输出文件
# 表示"$D"的目录部分（不以斜杠作为结尾）
# 依赖目标中的第一个目标名字。如果依赖目标是以模式（即"%"）定义的，那么"$<"将是符合模式的一系列的文件集。注意，其是一个一个取出来的。
# -c 编译器产生.o目标文件
# 前后%号匹配的
# https://blog.csdn.net/qq_39498080/article/details/79237260
$(OBJECTS): $(SOURCES)
	@mkdir -p $(@D)
	$(CXX) $< $(CXXFLAGS_DEBUG) -c -o $@

clean:
	rm -rf $(ODIR)
	rm -rf $(BUILD_DIR_ABS)
	@echo "Begin to compile code!"
