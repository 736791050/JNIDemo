//
// Created by lk on 16/9/29.
//
#include "com_test_git_jnidemo_JniUtil_CatchThrow.h"

JNIEXPORT void JNICALL Java_com_test_git_jnidemo_JniUtil_CatchThrow_doit
        (JNIEnv *env, jobject jobj){
    jthrowable exc;
    //获取jclass
    jclass cls = (*env).GetObjectClass(jobj);
    //获取callback 方法id
    jmethodID mid = (*env).GetMethodID(cls, "callback", "()V");

    if(mid == NULL){
        return;
    }
    //调用callback方法
    (*env).CallVoidMethod(jobj, mid);
    //异常检查
    exc = (*env).ExceptionOccurred();
    jboolean error = (*env).ExceptionCheck();
    if(error){
        //异常处理
        jclass newExcCls;
        //输出异常
        (*env).ExceptionDescribe();
        //清除异常
        (*env).ExceptionClear();
        newExcCls = (*env).FindClass("java/lang/IllegalArgumentException");
        if(newExcCls == NULL){
            //没有发现异常
            return;
        }
        (*env).ThrowNew(newExcCls, "thrown from C code");
    }
};


void JUN_ThrowByName(JNIEnv *env, const char *name, const char *msg){
    //生成jclass
    jclass cls = (*env).FindClass(name);
    //如果cls为NULL,一个异常已经发生
    if(cls != NULL){
        (*env).ThrowNew(cls, msg);
    }
    //释放本地引用
    (*env).DeleteLocalRef(cls);
};

jvalue JUN_CallMethodByName(JNIEnv *env,
                            jboolean *hasException,
                            jobject jobj,
                            const char* name,
                            const char* descriptor,
                            ...){
    va_list args;
    jclass clazz;
    jmethodID mid;
    jvalue result;
    if((*env).EnsureLocalCapacity(2) == JNI_OK){
        clazz = (*env).GetObjectClass(jobj);
        mid = (*env).GetMethodID(clazz, name, descriptor);
        if(mid){
            const char *p = descriptor;
            while (*p != ')') p++;
            p++;
            va_start(args, descriptor);
            switch (*p){
                case 'V':
                    (*env).CallVoidMethodV(jobj, mid, args);
                    break;
                case '[':
                case 'L':
                    result.l = (*env).CallObjectMethodV(jobj, mid, args);
                    break;
                case 'Z':
                    result.z = (*env).CallBooleanMethodV(jobj, mid, args);
                    break;
                default:
                    (*env).FatalError("illegal descriptor");
                    break;
            }
            va_end(args);
        }
        (*env).DeleteLocalRef(clazz);
    }
    if(hasException){
//        *hasException = (*env).ExceptionCheck();
        jthrowable exc = (*env).ExceptionOccurred();
        *hasException = exc != NULL;
        (*env).DeleteLocalRef(exc);
    }
    return result;
};
