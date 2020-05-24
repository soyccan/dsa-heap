CXX := clang++
CXXFLAGS := -Wall -Wextra -std=gnu++17 -I/usr/local/include
LDFLAGS :=

EXES := printer
OBJS := main.o minmaxheap.o
deps := $(OBJS:%.o=.%.o.d)
compdb-dep := $(OBJS:%.o=.%.o.json) # compilation database
compdb := compile_commands.json


ifndef DEBUG
	DEBUG := 1
endif
ifeq ($(DEBUG), 1)
	CXXFLAGS += -g -D_TEST
else
	CXXFLAGS += -DNDEBUG -O2
endif


.PHONY: all clean run upload scan-build
all: $(EXES) $(compdb)


$(compdb): $(compdb-dep)
	sed -e '1s/^/[/' -e '$$s/,$$/]/' $^ > $@

printer: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ -MMD -MF .$@.d -MJ .$@.json $<

run: printer
	./printer < 1.in

scan-build:
	PATH=/usr/local/opt/llvm/bin:$(PATH) scan-build make

upload:
	scp -P 9453 -r *.hpp *.h *.cpp Makefile \
		soyccan@bravo.nctu.me:/home/soyccan/Documents/dsa-hw5/

clean:
	rm -rf $(EXES) $(OBJS) $(deps) $(compdb) $(compdb-dep)

-include $(deps)
