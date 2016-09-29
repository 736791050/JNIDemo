//
// Created by lk on 16/9/18.
//
#include "com_test_git_jnidemo_JniUtil_JniDemo.h"

void jclsToJobj(JNIEnv *env, const _jclass *cls);

JNIEXPORT jstring JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_helloJni
        (JNIEnv *env, jobject jobj){
    jclass cls = env->GetObjectClass(jobj);
    //2.获取age的jfieldID 注意用GetStaticFieldID方法
    jfieldID jfid = env->GetStaticFieldID(cls, "age", "I");
    //3.通过jfid获取age的属性值,注意用GetStaticIntField
    jint jage = env->GetStaticIntField(cls, jfid);
    jage += 10;
    //4.修改age的属性值,注意用GetStaticIntField
    env->SetStaticIntField(cls,jfid, jage);
    return env->NewStringUTF("hello jni");
}

JNIEXPORT void jclsToJobj(JNIEnv *env, jclass cls) {
    jmethodID cid = env->GetMethodID(cls, "<init>", "()V");
    jobject  jobj = env->NewObject(cls, cid);
    jfieldID fid = env->GetFieldID(cls, "courses", "[Ljava/lang/String;");
    jobjectArray jarray = (jobjectArray) env->GetObjectField(jobj, fid);
    env->SetObjectArrayElement(jarray, 0, env->NewStringUTF("美术"));
}

jstring JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_helloJniStatic
        (JNIEnv *env, jclass cls){
    //jclass 转换成 jobject
    jclsToJobj(env, cls);


    //2.获取age的jfieldID 注意用GetStaticFieldID方法
    jfieldID jfid = env->GetStaticFieldID(cls, "age", "I");
    //3.通过jfid获取age的属性值,注意用GetStaticIntField
    jint jage = env->GetStaticIntField(cls, jfid);
    jage += 10;
    //4.修改age的属性值,注意用GetStaticIntField
    env->SetStaticIntField(cls,jfid, jage);
    return env->NewStringUTF("hello jni static");
};


JNIEXPORT void JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_accessField
        (JNIEnv *env, jobject obj){
    //1.获取jclass obj是JniDemo对象, JNIDemo.class
    jclass cls = (*env).GetObjectClass(obj);

    //2.获取jfieldID
    //name:属性名称,sig:属性签名
    //jfieldID GetFieldID(jclass clazz, const char* name, const char* sig)
    jfieldID fid = (*env).GetFieldID(cls, "name", "Ljava/lang/String;");

    //3.修改name的值

    //a.获取name属性的值 Get<Type>Field
    jstring jstr = (jstring) (*env).GetObjectField(obj, fid);

    //b.jstring转成c字符串
    //isCopy:true复制, false不复制,或者NULL
    //const char* GetStringUTFChars(jstring string, jboolean* isCopy)
    const char* c_str = (*env).GetStringUTFChars(jstr, NULL);

    //c.拼接得到新的字符串
    char new_char[40] = "changed ";
    //复制c_str 到 new_char
    strcat(new_char, c_str);

    //d.c字符串转换成String
    jstring new_jstr = (*env).NewStringUTF(new_char);

    //e.修改name值
    //Set<Type>Field
    (*env).SetObjectField(obj, fid, new_jstr);

    //释放资源
    (*env).ReleaseStringUTFChars(jstr, c_str);
};

JNIEXPORT void JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_accessArrayField
        (JNIEnv *env, jobject jobj){
    jclass cls = env->GetObjectClass(jobj);
    jfieldID fid = env->GetFieldID(cls, "courses", "[Ljava/lang/String;");
    jobjectArray jarray = (jobjectArray) env->GetObjectField(jobj, fid);
    env->SetObjectArrayElement(jarray, 0, env->NewStringUTF("英语"));
};


JNIEXPORT void JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_accessStaticField
        (JNIEnv *env, jobject obj){
    //1.获取jclass
    jclass cls = env->GetObjectClass(obj);
    //2.获取age的jfieldID 注意用GetStaticFieldID方法
    jfieldID jfid = env->GetStaticFieldID(cls, "age", "I");
    //3.通过jfid获取age的属性值,注意用GetStaticIntField
    jint jage = env->GetStaticIntField(cls, jfid);
    jage ++;
    //4.修改age的属性值,注意用GetStaticIntField
    env->SetStaticIntField(cls,jfid, jage);
};


JNIEXPORT void JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_accessMethod
        (JNIEnv *env, jobject jobj){
    //1.获取jclass
    jclass cls = env->GetObjectClass(jobj);
    //2.获取方法的ID
    //clazz为上面获取到的cls, name为java中的方法名, sig为方法的签名
    //jmethodID GetMethodID(jclass clazz, const char* name, const char* sig)
    jmethodID mid = env->GetMethodID(cls, "printMessage", "(I)V");
    //3.调用printfMessage方法并传递参数
    env->CallVoidMethod(jobj, mid, 10);
};

JNIEXPORT void JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_accessStaticMethod
        (JNIEnv *env, jobject jobj){
    //1.获取jclass方法
    jclass  cls = env->GetObjectClass(jobj);
    //2.获取静态方法的ID
    //clazz为上面获取到的cls, name为java中的静态方法的方法名, sig为方法的签名
    //jmethodID GetStaticMethodID(jclass clazz, const char* name, const char* sig)
    jmethodID mid = env->GetStaticMethodID(cls, "printLog", "(Ljava/lang/String;)V");
    jstring jstr = env->NewStringUTF("JNI invoke Java Static Method");
    //3.调用printLog方法并传递参数
    //env->CallStaticVoidMethod(cls, mid, "JNI invoke Java Static Method");会报错,这种方法不允许
    //所以String参数需要通过NewStringUTF生成jstring使用
    env->CallStaticVoidMethod(cls, mid, jstr);
};


JNIEXPORT void JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_accessConstructMethod
        (JNIEnv *env, jobject jobj){
    //1.获取package com.test.git.jnidemo.JniUtil目录下Person的jclass
    jclass  cls = env->FindClass("com/test/git/jnidemo/JniUtil/Person");
    //2.获取Person的构造函数ID
    jmethodID mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;I)V");
//    jobject jniDemo = env->NewObject(cls, mid);
    //3.初始化构造函数(此处传递了参数)
    jobject jniDemo = env->NewObject(cls, mid, env->NewStringUTF("小明"), 10);
    //4.获取Person的printPerson方法ID
    jmethodID pritid = env->GetMethodID(cls, "printPerson", "()V");
    //5.调用Person的printPerson方法
    env->CallVoidMethod(jniDemo, pritid);
};

JNIEXPORT void JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_accessParentMethod
        (JNIEnv *env, jobject jobj){
    //1.获取Student的jclass
    jclass jcls = env->FindClass("com/test/git/jnidemo/JniUtil/Student");
    //2.获取Student的构造方法ID
    jmethodID mid = env->GetMethodID(jcls, "<init>", "(Ljava/lang/String;I)V");
    //3.实例化Student并传递参数
    jobject jcobj = env->NewObject(jcls, mid, env->NewStringUTF("小学生"), 5);
    //4.获取父类的jclass
    jclass jpcls = env->FindClass("com/test/git/jnidemo/JniUtil/Person");
    //5.获取子类的eat方法ID
    jmethodID peatID = env->GetMethodID(jcls, "eat", "()V");
    //直接调用子类方法
//    env->CallVoidMethod(jcobj, peatID);
    //6.调用父类方法
    env->CallNonvirtualVoidMethod(jcobj, jpcls, peatID);
};
int com(const void *a, const void *b){
    return *(int *)a - *(int *)b;//升序
}
JNIEXPORT void JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_passArrayMethod
        (JNIEnv *env, jobject jobj, jintArray jarr){
    //1.获取数组指针
    jint *arr = env->GetIntArrayElements(jarr, NULL);
    *arr = 100;
    //2.获取数组长度
    int len = env->GetArrayLength(jarr);
    //3.排序
    qsort(arr, len, sizeof(jint), com);

    //4.释放资源
    env->ReleaseIntArrayElements(jarr, arr, JNI_COMMIT);
//    env->ReleaseIntArrayElements(jarr, arr, JNI_ABORT);
    //  对于最后一个参数(如果指针指向的数组为副本时，否则该参数不起作用)
    //      0       copy back the content and free the elems buffer
    //      JNI_COMMIT      copy back the content but do not free the elems buffer
    //      JNI_ABORT       free the buffer without copying back the possible changes
};

JNIEXPORT jintArray JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_createArrayMethod
        (JNIEnv *env, jobject jobj, jint len){
    //1.新建长度len数组
    jintArray jarr = env->NewIntArray(len);
    //2.获取数组指针
    jint *arr = env->GetIntArrayElements(jarr, NULL);
    //3.赋值
    int i = 0;
    for(; i < len; i++){
        arr[i] = i;
    }
    //4.释放资源
    env->ReleaseIntArrayElements(jarr, arr, 0);
    //5.返回数组
    return jarr;
};


JNIEXPORT void JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_cacheFieldWhenUse
        (JNIEnv *env, jobject jobj){
    //0.静态变量,用于缓存fid
    static jfieldID fid = NULL;
    //1.获取jclass
    jclass cls = (*env).GetObjectClass(jobj);

    //2.获取name的fid
    if(fid == NULL){
        fid = (*env).GetFieldID(cls, "name", "Ljava/lang/String;");
        //获取失败
        if(fid == NULL){
            return; //error
        }
    }
    //3.获取name字段值
    jstring jstr = (jstring) (*env).GetObjectField(jobj, fid);

    //4.将字符串转换成字符指针
    const char *str = (*env).GetStringUTFChars(jstr, NULL);
    //4.1如果为NULL,则发生了内存溢出
    if(str == NULL){
        return; //out of memory
    }
    //5.将str字符添加到str_new后面
    char *c = "缓存字段测试 ";
    char new_char[strlen(str) + strlen(c)];
    //复制c_str 到 new_char
    strcpy(new_char, c);
    strcat(new_char, str);

    //6.及时释放str
    (*env).ReleaseStringUTFChars(jstr, str);

    //7.重新生成jstr
    jstr = (*env).NewStringUTF(new_char);
    //7.1如果为NULL,则发生了内存溢出
    if(jstr == NULL){
        return; //out of memory
    }

    //8.修改name字段值
    (*env).SetObjectField(jobj, fid, jstr);
};

JNIEXPORT jstring JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_cacheMethodWhenUse
        (JNIEnv *env, jobject jobj, jcharArray elemArr){
    //1.要缓存的方法ID:cid
    static jmethodID cid = NULL;
    //2.获取String的jclass
    jclass stringClass = (*env).FindClass("java/lang/String");
    if(stringClass == NULL){
        return NULL; //exception
    }
    //3.判断cid是否已经初始化
    if(cid == NULL){
        cid = (*env).GetMethodID(stringClass, "<init>", "([C)V");
        if(cid == NULL){
            return NULL; //exception
        }
    }
    //4.把传入的字符数组转换成字符串
    jstring result = (jstring) (*env).NewObject(stringClass, cid, elemArr);
    //5.本地引用引用
    /* free local references */
    (*env).DeleteLocalRef(elemArr);
    (*env).DeleteLocalRef(stringClass);
    //6.返回字符串
    return result;
};



//缓存的String的String(char value[])方法id
jmethodID strInitID;
JNIEXPORT void JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_cacheWhenInit
        (JNIEnv *env, jclass jcls){
    //1.获取String的jclass
    jclass strClass = (*env).FindClass("java/lang/String");
    if(strClass == NULL){
        return; //exception
    }
    //2.判断cid是否已经初始化
    if(strInitID == NULL){
        strInitID = (*env).GetMethodID(strClass, "<init>", "([C)V");
        if(strInitID == NULL){
            return; //exception
        }
    }
};

//使用上面的strInitID
JNIEXPORT jstring JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_cacheWhenInitInvoke
        (JNIEnv *env, jobject jobj, jcharArray chars){
    jclass stringClass = (*env).FindClass("java/lang/String");
    //把传入的字符数组转换成字符串
    return (jstring) (*env).NewObject(stringClass, strInitID, chars);
};


//全局引用静态变量
static jclass strGloClass = NULL;
JNIEXPORT void JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_createGlobalRef
        (JNIEnv *env, jobject jobj){
    if(strGloClass == NULL){
        //创建本地引用
        jclass localRefCls = (*env).FindClass("java/lang/String");
        if(localRefCls == NULL){
            return; //exeption
        }
        //创建全局引用
        strGloClass = (jclass) (*env).NewGlobalRef(localRefCls);

        //当本地引用不用的时候,释放掉
        (*env).DeleteLocalRef(localRefCls);

        //判断全局引用是否创建成功
        if(strGloClass == NULL){
            return; //out of memory exception
        }
    }
};

JNIEXPORT jstring JNICALL Java_com_test_git_jnidemo_JniUtil_JniDemo_useGlobalRef
        (JNIEnv *env, jobject jobj,  jcharArray chars){
    //使用全局引用
    jstring result = (jstring) (*env).NewObject(strGloClass, strInitID, chars);
    //释放全局引用(这个根据自己需要释放,释放以后不能再使用全局引用)
    (*env).DeleteGlobalRef(strGloClass);
    return result;
};

jstring MyNewString(JNIEnv *env){
    static jstring cachedString = NULL;
    if(cachedString == NULL){
        jclass stringClass = (*env).FindClass("java/lang/String");
        //创建cachedStringLocal
        jstring cachedStringLocal = (jstring) (*env).NewObject(stringClass, strInitID);
        //缓存全局引用
        cachedString = (jstring) (*env).NewGlobalRef(cachedStringLocal);

        (*env).DeleteLocalRef(cachedString);
    }
    //创建并且保存本地引用字符串
    return (jstring) (*env).NewLocalRef(cachedString);
}


