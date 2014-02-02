#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "std11/mutex.hpp"
#include "std11/thread.hpp"

#define RANDOM(min, max) (rand() % (max - min) + min)

#define MIN_LEVEL  1
#define MAX_LEVEL  9
#define LIMIT (8*128*1024)

char bracket_indent[MAX_LEVEL][MAX_LEVEL];

unsigned shared_resource = 0;
std11::recursive_mutex rm;
std11::hash<std11::thread::id> hash;

bool recurser(int n, int origin) {
	bool ret = true;
	int level = origin - n + 1;

	std11::lock_guard<std11::recursive_mutex> l(rm);
	printf("Th[%08x] %s acquired Level %d lock\n"
		, hash(std11::this_thread::get_id()), bracket_indent[level - 1], level);

	if (--n) { recurser(n, origin); }
        else {
		shared_resource += origin;
		printf("Th[%08x] incremented %d. (shared_resource = %d)\n"
			, hash(std11::this_thread::get_id()), origin, shared_resource);
		if (shared_resource >= LIMIT) { ret = false; }
	}
	printf("Th[%08x] %s released Level %d lock\n"
		, hash(std11::this_thread::get_id()), bracket_indent[level - 1], level);

	return ret;
}

void worker()
{
	bool cont = true;
	do {
		int n = RANDOM(MIN_LEVEL, MAX_LEVEL);
		printf("Th[%08x] calling recurse(%d) ...\n",
			hash(std11::this_thread::get_id()), n);
		cont = recurser(n, n);
		std11::this_thread::yield();
	} while (cont);
}

#define THREAD_COUNT 4
int main()
{
	srand((unsigned int)time(NULL));

	for (unsigned i = 0; i < MAX_LEVEL; ++i) {
		for (unsigned c = 0; c <= i; ++c) { bracket_indent[i][c] = '>'; }
		bracket_indent[i][i + 1] = '\0';
	}

	std11::thread th[THREAD_COUNT];
	for (unsigned i = 0; i < THREAD_COUNT; ++i) {
		std11::thread t(&worker);
		th[i] = std11::move(t);
	}

	for (unsigned i = 0; i < THREAD_COUNT; ++i) { th[i].join(); }

	return 0;
}

