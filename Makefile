
all: build
	touch meson.build
	(cd build && ninja)

build:
	mkdir -p build
	(cd build && meson ..)

clean:
	rm -rf bin build mnt

mount: all
	mkdir -p mnt
	(cd build && ./fogfs -f -s ../mnt)

.PHONY: all clean mount

