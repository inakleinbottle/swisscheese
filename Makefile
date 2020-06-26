

CPP_FILES=$(wildcard src/*.cpp)
TEST_FILES=$(wildcard tests/*.cpp)

TEST_OPTIONS=-s



.PHONY: test

test:
	g++ -o tests/test.out -lm -Iinclude ${CPP_FILES} ${TEST_FILES}
	tests/test.out $(TEST_OPTIONS)
	rm -f tests/test.out
