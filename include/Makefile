# ��Ŀ��Ŀ¼
SOURCE_ROOT  := $(shell pwd)
# build + ��Ŀ¼������Ŀ��buildĿ¼ ���ڷŶ������ļ� => ˳�㷽��git ignore
BUILD_DIR    :=  build_$(notdir $(SOURCE_ROOT))
# ��Ŀbuild�ľ���·��
BUILD_DIR_ABS := $(SOURCE_ROOT)/$(BUILD_DIR)
# ��ִ���ļ��ø�Ŀ¼�ļ�����
TARGET := $(BUILD_DIR_ABS)/$(notdir $(SOURCE_ROOT))

CC ?= gcc
CXX ?= g++
CFLAGS := -fPIC -pthread -std=c11 -g -Wall -Wextra -pedantic -O3 -ftree-vectorize -ffast-math -mavx -mfma -mavx2
# man gcc
# -g ѡ�����g++����������Ϣ���Ե��Գ���
# -O[n]�Ż�Դ���� �ڵ��Թ�����ע��ر�
# -l ����ָ������Ҫ���ӵĿ⣬���ӵľ��ǿ��� ��/lib��/usr/lib��/usr/local/lib��Ŀ�ֱ����-l��������
# ������ļ�û�з�����������Ŀ¼�У���Ҫʹ��-L����ָ�����ļ�����Ŀ¼ -L����ӵľ��ǿ��ļ����ڵ�Ŀ¼��
# e.g g++ -L/home/xiaotongl/testlibfolder -lmytest test.cc
# -I ָ��ͷ�ļ�������Ŀ¼ ͷ�ļ����������·�� ����ͷ�ļ��ڵ�ǰĿ¼��������-I.��ָ��
# -Wall ��ӡ������Ϣ
# -w �ر����о�����Ϣ
# -std=c++11���ñ����׼
# -o ָ������ļ���

# https://blog.csdn.net/wuu19/article/details/118252637
# -Wno-unused-variable������ʾδʹ�õı����澯
# -Wno-unused-parameter������ʾδʹ�õĲ����澯
# -Wno-unused-function������ʾδʹ�õĺ����澯
# -Wno-unused-but-set-variable������ʾ�Ѹ�ֵ��δʹ�õı����澯
# -Wno-unused-private-field������ʾδʹ�õ���˽�г�Ա�澯
# -Wno-unused-label������ʾδʹ�õ���ת��Ǹ澯
# error: undefined symbol: std::__cxx11 https://blog.csdn.net/Three_dog/article/details/104701644

# [TODO] ����Makefile�ŵ�Ŀ¼��Ȳ�ͬ, ��������Ŀ¼��һ�µ�����
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
# �����÷��ǣ�$(wildcard PATTERN...) ����Makefile�У�
# ����չ��Ϊ�Ѿ����ڵġ�ʹ�ÿո�ֿ��ġ�ƥ���ģʽ�������ļ��б�������������κη��ϴ�ģʽ���ļ������������ģʽ�ַ������ؿա�
# һ�����ǿ���ʹ�á�$(wildcard *.c)������ȡ����Ŀ¼�µ����е�.c�ļ��б���
SOURCES := $(TARGET_FILE).cc
# patsubst ģʽ�滻 ==> (Դģʽ�� Ŀ��ģʽ�� �ļ��б�) �ǵõ�һ�������½�.obj�ļ���
OBJECTS := $(ODIR)/$(TARGET_FILE).o
# OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# ����������е�job���ƶ��ӽ��� ���������ʵ���Ƿ�ֹjob�������ļ����Ƴ�ͻ����ָ�ִ�У����Զ��ӽ�������
# ������������� .bashrc�����Զ�����alias�� ����ÿ��makeǰ����Ҫcleanall ����ʹ����ʵ����ǰ����Ҫcleanall��
# �Լ�����Ϊ�������ٶȾͲ�����cleanall�� nonono 
# ����Ҫÿ�ζ�Ҫcleanall������±��룬��Ȼ�����е�ʱ����Ч
# alias make="make cleanall; make -j8"
.PHONY: all clean

# main�����������ɵĿ�ִ���ļ���
all: $(TARGET)

# LDFLAGS += -L$(SOURCE_ROOT)/../../lib -lprotobuf -lgrpc++ -lgrpc -laddress_sorting -lupb -lgpr -lssl -ldl -pthread -lcrypto -ldl -pthread -lre2 -lcares -lz -labsl_raw_hash_set -labsl_hashtablez_sampler -labsl_hash -labsl_city -labsl_low_level_hash -labsl_random_distributions -labsl_random_seed_sequences -labsl_random_internal_pool_urbg -labsl_random_internal_randen -labsl_random_internal_randen_hwaes -labsl_random_internal_randen_hwaes_impl -labsl_random_internal_randen_slow -labsl_random_internal_platform -labsl_random_internal_seed_material -labsl_random_seed_gen_exception -labsl_statusor -labsl_status -labsl_cord -labsl_cordz_info -labsl_cord_internal -labsl_cordz_functions -labsl_exponential_biased -labsl_cordz_handle -labsl_crc_cord_state -labsl_crc32c -labsl_crc_internal -labsl_crc_cpu_detect -labsl_bad_optional_access -labsl_strerror -labsl_str_format_internal -labsl_synchronization -labsl_graphcycles_internal -labsl_stacktrace -labsl_symbolize -labsl_debugging_internal -labsl_demangle_internal -labsl_malloc_internal -labsl_time -labsl_civil_time -labsl_strings -labsl_strings_internal -lrt -labsl_base -labsl_spinlock_wait -labsl_int128 -labsl_throw_delegate -labsl_time_zone -labsl_bad_variant_access -labsl_raw_logging_internal -labsl_log_severity 
# LDFLAGS += -pthread -ldl

# ��һ��������Ҫ����ľ�̬���ӿ�
# $^ �������һ��Ҫ�ŵ���ǰ�� ��g++��
# $(CXX) $^ $(LDFLAGS) -o $@ 
$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ 

# $@��������ļ�
# ��ʾ"$D"��Ŀ¼���֣�����б����Ϊ��β��
# ����Ŀ���еĵ�һ��Ŀ�����֡��������Ŀ������ģʽ����"%"������ģ���ô"$<"���Ƿ���ģʽ��һϵ�е��ļ�����ע�⣬����һ��һ��ȡ�����ġ�
# -c ����������.oĿ���ļ�
# ǰ��%��ƥ���
# https://blog.csdn.net/qq_39498080/article/details/79237260
$(OBJECTS): $(SOURCES)
	@mkdir -p $(@D)
	$(CXX) $< $(CXXFLAGS_DEBUG) -c -o $@

clean:
	rm -rf $(ODIR)
	rm -rf $(BUILD_DIR_ABS)
	@echo "Begin to compile code!"