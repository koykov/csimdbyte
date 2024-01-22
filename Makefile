ALL=\
	build_sse2 \
	build_sse4 \
	build_avx2 \

build_all: $(ALL)

build_sse2:
	gcc -O3 -Wextra -pedantic -msse4.2 -mavx2 -S index_sse2.c

build_sse4:
	gcc -O3 -Wextra -pedantic -msse4.2 -mavx2 -S index_sse4.c

build_avx2:
	gcc -O3 -Wextra -pedantic -msse4.2 -mavx2 -S index_avx2.c
