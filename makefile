include header.inc
include source.inc
include libs.inc

TARGET=test_main.exe

OBJECTS=$(patsubst %.cpp,%.o,$(SOURCE))
all: $(OBJECTS) $(TARGET)

ifndef newstd
    newstd = 0
endif
ifeq ($(newstd),1)
    CXXFLAG += -std=c++0x
    CXXFLAG += -D_CPP0X_
endif

$(OBJECTS): %.o:%.cpp
	g++ -g -c $(INCLUDES) $(CXXFLAG) $< -o $@
$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(GTEST_OBJ)
clean:
	rm -f $(OBJECTS) $(TARGET)

