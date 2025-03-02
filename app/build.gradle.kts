
/*
 * Copyright Kardium Inc. 2024.
 */

plugins {
    id("project.cpp-application-conventions")
}

dependencies {
    implementation(project(":interface"))
    implementation(project(":work"))
}