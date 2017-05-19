BIN  := bin/fogfs
SRCS := $(wildcard src/*.cc)
OBJS := $(subst src,build,$(SRCS:cc=o))
HDRS := $(wildcard include/*.hh)

CXX  := g++
CXXFLAGS := -g -std=gnu++11 -Wall -Werror -I./include \
	`pkg-config --cflags fuse libsodium`
LDFLAGS  :=
LDLIBS   := -lbsd -lxdg-basedir \
	`pkg-config --libs fuse libsodium`

$(BIN): $(OBJS) bin
	$(CXX) $(LDFLAGS) -o $(BIN) $(OBJS) \
        $(LDLIBS)

$(OBJS): build/%.o: src/%.cc build $(HDRS)
	$(CXX) -c $(CXXFLAGS) \
        -o $@ $<

bin:
	mkdir -p bin

build:
	mkdir -p build

clean:
	rm -rf bin build

.PHONY: clean

