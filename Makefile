
all: build
	touch meson.build
	(cd build && ninja)

build:
	mkdir -p build
	(cd build && meson ..)

clean:
	rm -rf bin build mnt

mount: all unmount
	mkdir -p mnt
	(cd build && ./fogfs -f -s ../mnt)

gdb: all unmount
	mkdir -p mnt
	(cd build && gdb --args ./fogfs -f -s ../mnt)

unmount:
	fusermount -u mnt || true

.PHONY: all clean mount unmount gdb

