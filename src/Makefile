NETWORK_NAME = nn-dfb6dafd17fab88-380.nnue

_THIS     := $(realpath $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
_ROOT     := $(_THIS)
EVALFILE   = $(_ROOT)/$(NETWORK_NAME)
CXX       := g++
TARGET    := smallbrain
CXXFLAGS  := -Wall -Wcast-qual -fno-exceptions -std=c++17 -pedantic -Wextra -DNDEBUG
NATIVE     = -march=native
COMP       =

# engine name
NAME      := smallbrain

# Detect Windows
ifeq ($(OS), Windows_NT)
	uname_S := Windows
	SUFFIX  := .exe
	FLAGS    = -pthread -lstdc++ -static
	CXXFLAGS += -static -static-libgcc -static-libstdc++ -Wl,--whole-archive -lpthread -Wl,--no-whole-archive
else
ifeq ($(COMP), MINGW)
	uname_S := Windows
	SUFFIX  := .exe
	FLAGS    = -pthread -lstdc++ -static
	CXXFLAGS += -static -static-libgcc -static-libstdc++ -Wl,--whole-archive -lpthread -Wl,--no-whole-archive
else
	FLAGS   = -lpthread -lstdc++
	SUFFIX  :=
	uname_S := $(shell uname -s)
endif
endif

# Remove native for distributed builds
ifdef build
	NATIVE =
endif

# all bmi2 instructions
INSTRUCTIONS_BMI2 = -m64 -msse -msse3 -mpopcnt -mavx -mavx2 -msse4.1 -mssse3 -msse2 -mbmi -mbmi2

# SPECIFIC BUILDS
ifeq ($(build), native)
	NATIVE   = -march=native
	ARCH     = -x86-64-native
endif

ifeq ($(build), x86-64)
	NATIVE       = -mtune=znver1
	INSTRUCTIONS = -msse -msse2 -mpopcnt
	ARCH         = -x86-64
endif

ifeq ($(build), x86-64-avx2)
	NATIVE       = -mtune=znver3
	INSTRUCTIONS = -m64 -msse -msse3 -mpopcnt -mavx -mavx2 -mssse3 -msse2
	ARCH         = -x86-64-avx2
endif

ifeq ($(build), x86-64-bmi2)
	NATIVE       = -mtune=znver3
	INSTRUCTIONS = $(INSTRUCTIONS_BMI2)
	ARCH         = -x86-64-bmi2
endif

ifeq ($(build), x86-64-avx512)
	NATIVE       = -mtune=alderlake
	INSTRUCTIONS = $(INSTRUCTIONS_BMI2) -mavx512f -mavx512bw
	ARCH         = -x86-64-avx512
endif

ifeq ($(build), x86-64-vnni256)
	NATIVE       = -mtune=alderlake
	INSTRUCTIONS = $(INSTRUCTIONS_BMI2) -mavx512f -mavx512bw -mavx512vnni -mavx512dq -mavx512vl -mprefer-vector-width=256
	ARCH         = -x86-64-vnni256
endif

ifeq ($(build), x86-64-vnni512)
	NATIVE       = -mtune=alderlake
	INSTRUCTIONS = $(INSTRUCTIONS_BMI2) -mavx512vnni -mavx512dq -mavx512vl
	ARCH         = -x86-64-vnni512
endif

# Different native flag for macOS
ifeq ($(uname_S), Darwin)
	NATIVE = -mcpu=apple-a14	
	FLAGS = 
endif

# Native build with debug symbols
ifeq ($(build), symbols)
	CXXFLAGS += -g3 -fno-omit-frame-pointer
	NATIVE   = -march=native
	FLAGS    = -lpthread -lstdc++
endif

# OS independent build with full debug
ifeq ($(build), debug)
	CXXFLAGS = -g3 -fno-omit-frame-pointer -std=c++17
	NATIVE   = -msse -msse3 -mpopcnt
	FLAGS    = -lpthread -lstdc++
endif

# Try to include git commit sha for versioning
GIT_SHA = $(shell git rev-parse --short HEAD 2>/dev/null)
ifneq ($(GIT_SHA), )
	CXXFLAGS += -DGIT_SHA=\"$(GIT_SHA)\"
endif

# Try to include git commit date for versioning
GIT_DATE = $(shell git show -s --date=format:'%Y%m%d' --format=%cd HEAD 2>/dev/null)
ifneq ($(GIT_DATE), )
	CXXFLAGS += -DGIT_DATE=\"$(GIT_DATE)\"
endif

# Add network name and Evalfile
CXXFLAGS += -DNETWORK_NAME=\"$(NETWORK_NAME)\" -DEVALFILE=\"$(EVALFILE)\"

SOURCES := $(wildcard *.cpp) syzygy/Fathom/src/tbprobe.cpp tests/tests.cpp
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))
EXE     := $(NAME)$(ARCH)$(SUFFIX)

.PHONY: all clean FORCE

all: $(TARGET)
clean:
	rm -rf *.o syzygy/Fathom/src/*.o $(DEPENDS) *.d tests/tests.d tests/tests.o

# Linking the executable from the object files
$(TARGET): $(OBJECTS)
	$(CXX) -o $(EXE) $^ $(CXXFLAGS) $(NATIVE) $(INSTRUCTIONS) $(FLAGS) -flto

-include $(DEPENDS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(NATIVE) $(INSTRUCTIONS) -funroll-loops -O3  -flto -MMD -MP -c -o $@ $< $(FLAGS)

# Force recompilation of ucicommands to include latest version string
uci.o: FORCE
FORCE:

# Profile Guided Optimizations for gcc, largely depends on compiler version
pgo:
	$(CXX) $(CXXFLAGS) $(NATIVE) $(INSTRUCTIONS) -funroll-loops -O3 -fprofile-generate -lgcov -flto -MMD -MP -o $(EXE) $(SOURCES) $(FLAGS)
	./$(EXE) go depth 20
	$(CXX) $(CXXFLAGS) $(NATIVE) $(INSTRUCTIONS) -funroll-loops -O3 -fprofile-use -flto -MMD -MP -o $(EXE) $(SOURCES) $(FLAGS)
	@rm -f *.gcda 
	rm -rf *.o syzygy/Fathom/src/*.o $(DEPENDS) *.d tests/tests.d tests/tests.o
