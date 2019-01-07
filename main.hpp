#include <jni.h>

#ifndef MYJNI_MAIN_H

JavaVM *jvm;       /* denotes a Java VM */
JNIEnv *env;       /* pointer to native method interface */
int createJvm();

jclass loadClass(JNIEnv *env);

void invokeStaticNoParamNoReturn(JNIEnv *env, jclass clazz, const char *name);

void invokeStaticNoParamReturnString(JNIEnv *env, jclass clazz, const char *name);

void invokeGreet(JNIEnv *env, jclass demoClass);

void invokeGetString(JNIEnv *env, jclass demoClass);

void invokeDoNothing(JNIEnv *env, jclass demoClass);

#define MYJNI_MAIN_H

#endif //MYJNI_MAIN_H
