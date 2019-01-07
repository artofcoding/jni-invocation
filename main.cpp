#include <iostream>
#include <jni.h>
#include "main.hpp"

int createJvm() {
    /* Java VM initialization arguments */
    auto *options = new JavaVMOption[3];
    /* user classes */
    options[0].optionString = const_cast<char *>("-Djava.class.path=../jars/Demo.jar");
    /* set native library path */
    //options[0].optionString = const_cast<char *>("-Djava.library.path=c:/my-native-libs");
    /* disable JIT */
    options[1].optionString = const_cast<char *>("-Djava.compiler=NONE");
    /* print JNI-related messages */
    options[2].optionString = const_cast<char *>("-verbose:jni");
    JavaVMInitArgs vm_args;
    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 3;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;
    printf("Creating JVM...\n");
    jint res = JNI_CreateJavaVM(&jvm, (void **) &env, &vm_args);
    delete[]options;
    if (res == JNI_ERR) {
        printf("Can't create Java VM\n");
        return 1;
    } else {
        printf("JVM created\n");
        return res;
    }
}

jclass loadClass(JNIEnv *env) {
    printf("Loading class Demo...\n");
    jclass demoClass = env->FindClass("Demo");
    if (demoClass == nullptr) {
        printf("Cannot find class\n");
    } else {
        printf("Class Demo loaded\n");
    }
    return demoClass;
}

jobjectArray makeStringArray() {
    jstring jstr = env->NewStringUTF("");
    jobjectArray args =
            env->NewObjectArray(1, env->FindClass("java/lang/String"), jstr);
    return args;
}

void invokeStaticNoParamNoReturn(JNIEnv *env, jclass clazz, const char *name) {
    // See javap -s Demo
    const char *signature = "()V";
    printf("Invoking method %s(%s)...\n", name, signature);
    jmethodID methodID = env->GetStaticMethodID(clazz, name, "()V");
    if (methodID != nullptr) {
        env->CallStaticVoidMethod(clazz, methodID, "");
        printf("Method %s(%s) invoked\n", name, signature);
    } else {
        printf("Method %s(%s) not found\n", name, signature);
    }
}

void invokeStaticNoParamReturnString(JNIEnv *env, jclass clazz, const char *name) {
    // See javap -s Demo
    const char *signature = "()Ljava/lang/String;";
    printf("Invoking method %s(%s)...\n", name, signature);
    jmethodID methodID = env->GetStaticMethodID(clazz, name, signature);
    env->CallStaticVoidMethod(clazz, methodID, nullptr);
    auto res = (jstring) (env->CallStaticObjectMethod(clazz, methodID, nullptr));
    const char *string = env->GetStringUTFChars(res, nullptr);
    std::cout << "debug: " << string << "\n";
    printf("Method %s(%s) invoked\n", name, signature);
}

void invokeGreet(JNIEnv *env, jclass demoClass) {
    printf("Invoking method Demo#greet(String)...\n");
    jmethodID methodID = env->GetStaticMethodID(demoClass, "greet", "(Ljava/lang/String;)V");
    env->CallStaticVoidMethod(demoClass, methodID, "Ralf");
    printf("Method Demo#greet(String) invoked\n");
}

void invokeGetString(JNIEnv *env, jclass demoClass) {
    invokeStaticNoParamReturnString(env, demoClass, "getString");
}

void invokeDoNothing(JNIEnv *env, jclass demoClass) {
    invokeStaticNoParamNoReturn(env, demoClass, "doNothing");
}

int main() {
    createJvm();
    jclass demoClass = loadClass(env);
    invokeDoNothing(env, demoClass);
    invokeGetString(env, demoClass);
    invokeGreet(env, demoClass);
    jvm->DestroyJavaVM();
    printf("JavaVM destroyed\n");
    return 0;
}
