/*
 * Copyright Kardium Inc. 2024.
 */

plugins {
    id("project.cpp-library-conventions")
    id("cpp-unit-test")
}

dependencies {
    implementation(project(":interface"))
    testImplementation(project(":munit"))
}