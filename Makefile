CXX := clang++
CXXFLAGS := -Wall -Wextra -std=gnu++17 -I/usr/local/include
LDFLAGS :=

EXES := printer printer-s test/rand
OBJS := main.o minmaxheap.o main-s.o minmaxheap-s.o
deps := $(OBJS:%.o=.%.o.d)
compdb-dep := $(OBJS:%.o=.%.o.json) # compilation database
compdb := compile_commands.json


ifndef DEBUG
	DEBUG := 1
endif
ifeq ($(DEBUG), 1)
	CXXFLAGS += -g
else
	CXXFLAGS += -DNDEBUG -O2
endif


.PHONY: all clean run upload scan-build
all: $(EXES) $(compdb)


$(compdb): $(compdb-dep)
	sed -e '1s/^/[/' -e '$$s/,$$/]/' $^ > $@

printer: main.o minmaxheap.o
	$(CXX) $(LDFLAGS) -o $@ $^

printer-s: main-s.o minmaxheap-s.o
	# stable version
	$(CXX) $(LDFLAGS) -o $@ $^

main-s.o: main.cpp
	$(CXX) $(CXXFLAGS) -D_STABLE -c -o $@ -MMD -MF .$@.d -MJ .$@.json $<

minmaxheap-s.o: minmaxheap-s.cpp
	$(CXX) $(CXXFLAGS) -D_STABLE -c -o $@ -MMD -MF .$@.d -MJ .$@.json $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ -MMD -MF .$@.d -MJ .$@.json $<

test/rand: test/rand.c
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test/rand $^


loop: printer printer-s test/rand
	while true; do \
		printf .; \
		test/rand > test/in; \
		./printer < test/in > test/out || break; \
		./printer-s < test/in > test/outs || break; \
		diff test/out test/outs || break; \
	done

run: printer
	./printer < 1.in | diff - 1.out

scan-build:
	PATH=/usr/local/opt/llvm/bin:$(PATH) scan-build make

upload:
	scp -P 9453 -r *.hpp *.h *.cpp Makefile \
		soyccan@bravo.nctu.me:/home/soyccan/Documents/dsa-hw5/

clean:
	rm -rf $(EXES) $(OBJS) $(deps) $(compdb) $(compdb-dep)

-include $(deps)
