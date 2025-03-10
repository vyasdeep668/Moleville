/**
 * Precompiled [project.cpp-application-conventions.gradle.kts][Project_cpp_application_conventions_gradle] script plugin.
 *
 * @see Project_cpp_application_conventions_gradle
 */
public
class Project_cppApplicationConventionsPlugin : org.gradle.api.Plugin<org.gradle.api.Project> {
    override fun apply(target: org.gradle.api.Project) {
        try {
            Class
                .forName("Project_cpp_application_conventions_gradle")
                .getDeclaredConstructor(org.gradle.api.Project::class.java, org.gradle.api.Project::class.java)
                .newInstance(target, target)
        } catch (e: java.lang.reflect.InvocationTargetException) {
            throw e.targetException
        }
    }
}
