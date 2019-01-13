#include <stdio.h>

class TestClass{
public:
	int
		a1 = 0x1,
		a2 = 0x2,
		a3 = 0x3;
	const char string1[4] = "123";

	void printSelf() {
		printf("called printSelf %d\n", a1);
	}
};

void testFunctionNoParams() {
	printf("called testFunctionNoParams\n");
}

void testFunctionParamString(const char *string) {
	printf("called testFunctionParamString: \"%s\" \n",string);
}

void testFunctionParamClass(TestClass *s) {
	printf("called testFunctionParamClass\n");
	s->printSelf();
}

void testFunctionForHooking() {
	printf("called testFunctionForHooking\n");
}

static auto testClass = TestClass();

int main(int argc, char **argv){
	while (true) {
		auto c = fgetc(stdin);
		if (c == '\n') continue; 
		printf("---------- char: %c -----------\n", c);
		if (c == 'q') break;

		if (c == 'h') {
			testFunctionForHooking();
		} else {
			testFunctionNoParams();
			testFunctionParamString("Test string");
			testFunctionParamClass(&testClass);
		}
	}
	return 0;
}