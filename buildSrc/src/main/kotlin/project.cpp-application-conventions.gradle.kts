
/*
 * Copyright Kardium Inc. 2024.
 */

plugins {
    id("project.common-conventions")
    id("cpp-application")
}

application {
    if (providers.gradleProperty("win32").isPresent) {
        targetMachines.add(machines.windows.x86)
    }
}

if (providers.gradleProperty("c++11").isPresent) {
    tasks.withType(CppCompile::class.java).configureEach {
        compilerArgs.add("-std=c++11")
    }
}