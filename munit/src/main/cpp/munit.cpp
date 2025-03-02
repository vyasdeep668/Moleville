/*
 * Copyright Kardium Inc. 2024.
 */

#include <stdio.h>
#include <string.h>
#include "munit.h"

typedef struct {

    // Suite configuration
    const char* suiteName;
    Callback testSetup;
    Callback testCleanup;

    // Current test
    const char* testName;
    int numAssertionsInTest;
    int numFailedAssertionsInTest;

    // Cumulative
    int numTests;
    int numAssertions;
    int numFailedTests;
    int numFailedAssertions;

} SuiteState;

static SuiteState suite;


void mu_init(const char* suiteName, Callback testSetup, Callback testCleanup) {
    printf("\nStarting test suite: %s\n", suiteName);
    memset(&suite, 0, sizeof(suite));
    suite.suiteName = suiteName;
    suite.testSetup = testSetup;
    suite.testCleanup = testCleanup;
}


void mu_startTest(const char* testName) {
    suite.testName = testName;
    if (suite.testSetup != 0) {
        suite.testSetup();
    }
}


bool mu_assert(const char* comment, bool success) {
    suite.numAssertionsInTest++;
    if (!success) {
        printf("Assertion failed in %s: %s\n", suite.testName, comment == 0 ? "unspecified" : comment);
        suite.numFailedAssertionsInTest++;
    }
    return success;
}


#define STRBUF_SIZE (256)

bool mu_assert(const char* message, const char* codeloc, bool success) {
    if (strlen(message) + strlen(codeloc) > STRBUF_SIZE - 2) {
        mu_assert(codeloc, success);
    } else {
        char buffer[STRBUF_SIZE];
        strcpy(buffer, message);
        strcat(buffer, " ");
        strcat(buffer, codeloc);
        mu_assert(buffer, success);
    }
    return success;
}


void mu_finishTest() {
    const bool incomplete = suite.numAssertionsInTest == 0;
    const bool failed = suite.numFailedAssertionsInTest != 0;

    suite.numTests++;
    suite.numAssertions += suite.numAssertionsInTest;
    suite.numFailedAssertions += suite.numFailedAssertionsInTest;
    suite.numAssertionsInTest = 0;
    suite.numFailedAssertionsInTest = 0;

    printf("Test: %s...%s\n", suite.testName, incomplete ? "INCOMPLETE" : (failed ? "FAILED" : "passed"));
    if (incomplete || failed) {
        suite.numFailedTests++;
    }
    if (suite.testCleanup != 0) {
        suite.testCleanup();
    }
}

int mu_summary() {
    printf("Summary for %s:\n", suite.suiteName);
    printf("\tTests run:          %d\n", suite.numTests);
    printf("\tTests failed:       %d\n", suite.numFailedTests);
    printf("\tAssertions checked: %d\n", suite.numAssertions);
    printf("\tAssertions failed:  %d\n", suite.numFailedAssertions);
    return suite.numFailedTests;
}