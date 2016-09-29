package com.test.git.jnidemo.JniUtil;

import android.util.Log;

/**
 * Created by lk on 16/9/18.
 */
public class JniDemo {

    //----------------------------Native方法----------------------------------------
    public native String helloJni();
    public native static String helloJniStatic();

    //修改字段值
    public native void accessField();
    public native void accessArrayField();
    //修改字段值(静态方法)
    public native void accessStaticField();

    //执行方法
    public native void accessMethod();
    //执行静态方法
    public native void accessStaticMethod();

    //访问构造方法
    public native void accessConstructMethod();

    //访问父类方法
    public native void accessParentMethod();

    //传递数组,操作后,返回
    public native void passArrayMethod(int[] arr);

    //创建指定长度数组
    public native int[] createArrayMethod(int len);

    //缓存字段(使用时)
    public native void cacheFieldWhenUse();

    //缓存方法ID(使用时)
    public native String cacheMethodWhenUse(char[] chars);

    //缓存(初始化时)
    public static native void cacheWhenInit();
    //使用上面方法的缓存
    public native String cacheWhenInitInvoke(char[] chars);

    //创建全局引用
    public native void createGlobalRef();
    //使用全局应用并释放
    public native String useGlobalRef(char[] chars);

    //----------------------------java----------------------------------------

    private static final String TAG = "JniDemo";
    //路径:/JNIDemo/app/build/intermediates/classes/debug/com/test/git/jnidemo/JniUtil/JniDemo.class

    public String name = "Lucy";

    public static int age = 10;

    public String[] courses = {"语文", "数学"};


    public JniDemo(){}

    public JniDemo(String name, int age){
        this.name = name;
        this.age = age;
    }


    public void printMessage(int message){
        Log.i(TAG, "printMessage: " + message);
    }

    public static void printLog(String log){
        Log.i(TAG, "printLog: " + log);
    }

    static {
        System.loadLibrary("NdkJniD");
        cacheWhenInit();
    }
}
