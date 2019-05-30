#include "Test.h"
#include <iostream>

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char *filename, int lineNum) {
	if (!expr) {
		std::cout << "error in file: " << filename << ", func: " << func << ", line:" << lineNum << "\n";
		failedNum++;
	}
	totalNum++;
}

void Test::showFinalResult() {
	std::cout << totalNum - failedNum << " out of " << totalNum << " correct" << "\n";
}

void Test::runAllTests() {

}