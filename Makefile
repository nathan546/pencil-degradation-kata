
OUTPUT_DIR                 := build
SRC_DIR                    := src tests
SRC                        :=  $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))

SOURCES_TEST               := $(filter-out src/main.cpp, $(SRC))
OBJECTS_TO_COMPILE_TEST    := $(SOURCES_TEST:.cpp=.o)
OBJECTS_COMPILED_TEST      := $(addprefix $(OUTPUT_DIR)/, $(OBJECTS_TO_COMPILE_TEST))
EXECUTABLE_TEST            := pencilDegradation-test

SOURCES_PRODUCTION               := $(filter-out tests/testPencilFactory.cpp, $(SRC))
OBJECTS_TO_COMPILE_PRODUCTION    := $(SOURCES_PRODUCTION:.cpp=.o)
OBJECTS_COMPILED_PRODUCTION      := $(addprefix $(OUTPUT_DIR)/, $(OBJECTS_TO_COMPILE_PRODUCTION))
EXECUTABLE_PRODUCTION            := pencilDegradation-production

INCLUDE                    := $(foreach sdir,$(SRC_DIR),-I$(sdir)/include)
CC                         := g++
CFLAGS                     := $(INCLUDE) -c -O3 -std=c++11
LFLAGS                     := 
PFLAGS                     := 

all: $(EXECUTABLE_PRODUCTION) $(EXECUTABLE_TEST)

$(EXECUTABLE_PRODUCTION): $(OBJECTS_TO_COMPILE_PRODUCTION)
	$(CC) $(LFLAGS) $(OBJECTS_COMPILED_PRODUCTION) $(PFLAGS) -o $(OUTPUT_DIR)/$@

$(EXECUTABLE_TEST): $(OBJECTS_TO_COMPILE_TEST)
	$(CC) $(LFLAGS) $(OBJECTS_COMPILED_TEST) $(PFLAGS) -o $(OUTPUT_DIR)/$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $(OUTPUT_DIR)/$@

clean:
	rm -f $(OBJECTS_COMPILED_PRODUCTION) $(OBJECTS_COMPILED_TEST)
	rm -f $(OUTPUT_DIR)/$(EXECUTABLE_PRODUCTION) $(OUTPUT_DIR)/$(EXECUTABLE_TEST)
