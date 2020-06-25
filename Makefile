


TEST_FILES=$(wildcard tests/*.cpp)

TEST_OPTIONS=-s



.PHONY: test

test:
	g++ -o tests/test.out -Iinclude ${TEST_FILES}
	tests/test.out $(TEST_OPTIONS)
	rm -f tests/test.out
