/*
 * Copyright Kardium Inc. 2024.
 */

#ifndef __MUNIT_H__
#define __MUNIT_H__

typedef void (*Callback)(void);

/**
 * Initializes the micro-unit test suite and prints the suite name.
 *
 * @param suiteName     The name of the test suite.
 * @param testSetup     A callback to execute at the start of each test (may be null).
 * @param testCleanup   A callback to execute at the end of each test (may be null).
 */
void mu_init(const char* suiteName, Callback testSetup, Callback testCleanup);

/**
 * Starts a test, calling the setup callback if one was provided.
 *
 * @param testName  A label for the test.
 */
void mu_startTest(const char* testName);

/**
 * Reports an assertion for the current test.  This is often wrapped by a method which evaluates a condition and/or
 * prints error information when the assertion fails.
 *
 * @param message   A message to describe or locate the fault if the assertion fails.
 * @param success   The result of evaluating the assertion.  If false, the test fails.
 * @returns the result, for the convenience of a wrapper function.
 */
bool mu_assert(const char* message, bool success);

/**
 * Reports an assertion for the current test.  This is often wrapped by a method which evaluates a condition and/or
 * prints error information when the assertion fails.
 *
 * @param message   A message to describe the fault if the assertion fails.
 * @param codeloc   A string containing the code location of the fault (usually obtained using the CODELOC macro).
 * @param success   The result of evaluating the assertion.  If false, the test fails.
 * @returns the result, for the convenience of a wrapper function.
 */
bool mu_assert(const char* message, const char* codeloc, bool success);

/**
 * This macro can be used to provide the code location in a mu_assert() message.
 *
 * <pre>
 * mu_assert("n must be non-zero: " CODELOC, n != 0);
 * </pre>
 */
#define CODELOC __FILE__ ":" MACROFY(__LINE__)
#define MACROFY(X) STRINGIFY(X)
#define STRINGIFY(X) #X

/**
 * Finishes the currently active test, calling the cleanup callback if one was called.  If any assertions have failed
 * during the test then the test fails.
 */
void mu_finishTest();

/**
 * Prints a summary of the test suite results.  This includes the number of tests run, assertions evaluated, and the
 * number of failures.
 *
 * @returns the number of failed tests.  This should be returned by main() to pass or fail the build.
 */
int mu_summary();

#endif