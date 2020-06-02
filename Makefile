CXX := /usr/bin/clang++
CXXFLAGS := -Wall -Wextra -std=gnu++17 -I/usr/local/include
LDFLAGS :=

EXES := printer printer-s test/rand
OBJS := main.o minmaxheap.o main-s.o minmaxheap-s.o
deps := $(OBJS:%.o=.%.o.d)
compdb-dep := $(OBJS:%.o=.%.o.json) # compilation database
compdb := compile_commands.json


.PHONY: all debug release loop clean run upload scan-build valgrind

# set debug to release before handing in
all: release

debug: CXXFLAGS += -g
debug: printer printer-s test/rand $(compdb)

release: CXXFLAGS += -DNDEBUG -O2
release: printer


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
	gcc -o $@ $^


loop: printer printer-s test/rand
	while true; do \
		printf .; \
		test/rand > test/in; \
		./printer < test/in > test/tmp || break; \
		./printer-s < test/in > test/out || break; \
		diff test/out test/tmp || break; \
	done

run: printer
	/usr/bin/time -v ./printer < test/samp.in | diff - test/samp.out

valgrind: printer
	valgrind --leak-check=full --show-leak-kinds=all --quiet \
		./printer < test/5.in > /dev/null

scan-build:
	@PATH=/usr/local/opt/llvm/bin:$(PATH) scan-build make

upload:
	scp -P 9453 -r *.hpp *.h *.cpp Makefile \
		soyccan@bravo.nctu.me:/home/soyccan/Documents/dsa-hw5/

clean:
	rm -rf $(EXES) $(OBJS) $(deps) $(compdb) $(compdb-dep)

-include $(deps)
