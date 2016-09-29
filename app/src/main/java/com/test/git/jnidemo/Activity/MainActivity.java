package com.test.git.jnidemo.Activity;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import com.test.git.jnidemo.JniUtil.CatchThrow;
import com.test.git.jnidemo.JniUtil.JniDemo;
import com.test.git.jnidemo.R;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity-";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        jniDemo();
        catchThrow();

    }

    private void catchThrow() {
        CatchThrow catchThrow = new CatchThrow();
        try {
            catchThrow.doit();
        }catch (Exception e){
            Log.i(TAG, "In Java catchThrow: " + e);
        }
    }

    private void jniDemo() {
        JniDemo jd = new JniDemo();
        Log.i(TAG, "age修改前: " + jd.age);
        Log.i(TAG, "helloJni->" + jd.helloJni());
        Log.i(TAG, "age修改后: " + jd.age);

        Log.i(TAG, "------------------------------------------");

        Log.i(TAG, "age修改前: " + jd.age);
        Log.i(TAG, "courses修改前: " + jd.courses[0]);
        JniDemo.helloJniStatic();
        Log.i(TAG, "age修改后: " + jd.age);
        Log.i(TAG, "courses修改后: " + jd.courses[0]);

        Log.i(TAG, "------------------------------------------");

        Log.i(TAG, "name修改前: " + jd.name);
        jd.accessField();
        Log.i(TAG, "name修改后: " + jd.name);

        Log.i(TAG, "------------------------------------------");

        Log.i(TAG, "age修改前: " + jd.age);
        jd.accessStaticField();
        Log.i(TAG, "age修改后: " + jd.age);

        Log.i(TAG, "------------------------------------------");

        Log.i(TAG, "courses修改前: " + jd.courses[0]);
        jd.accessArrayField();
        Log.i(TAG, "courses修改后: " + jd.courses[0]);

        Log.i(TAG, "------------------------------------------");

        jd.accessMethod();

        Log.i(TAG, "------------------------------------------");

        jd.accessStaticMethod();

        Log.i(TAG, "------------------------------------------");

        jd.accessConstructMethod();

        Log.i(TAG, "------------------------------------------");

        jd.accessParentMethod();

        Log.i(TAG, "------------------------------------------");

        int[] arr = {1, 3, 2, 6, 8, 0};
        Log.i(TAG, "arr修改前: " + getArrayString(arr));
        jd.passArrayMethod(arr);
        Log.i(TAG, "arr修改后: " + getArrayString(arr));

        Log.i(TAG, "------------------------------------------");

        int[] arr_new = jd.createArrayMethod(10);
        Log.i(TAG, "arr_new: "+ getArrayString(arr_new) );


        Log.i(TAG, "------------------------------------------");

        Log.i(TAG, "name修改前: " + jd.name);
        jd.cacheFieldWhenUse();
        Log.i(TAG, "name修改后: " + jd.name);

        Log.i(TAG, "------------------------------------------");

        char[] chars = {'a', 'b', 'c'};
        Log.i(TAG, "result传入:{'a', 'b', 'c'}");
        String result = jd.cacheMethodWhenUse(chars);
        Log.i(TAG, "result输出:" + result);

        Log.i(TAG, "------------------------------------------");

        Log.i(TAG, "result传入:{'a', 'b', 'c'}");
        result = jd.cacheWhenInitInvoke(chars);
        Log.i(TAG, "result输出:" + result);

        Log.i(TAG, "------------------------------------------");

        Log.i(TAG, "初始化全局引用");
        jd.createGlobalRef();
        Log.i(TAG, "传入:{'a', 'b', 'c'}");
        Log.i(TAG, "使用全局引用,并释放全局引用");
        result = jd.useGlobalRef(chars);
        Log.i(TAG, "输出:" + result);
//        result = jd.useGlobalRef(chars);
        Log.i(TAG, "------------------------------------------");
    }

    /**
     * 拼接数组元素
     * @param arr
     * @return
     */
    private String getArrayString(int[] arr){
        String s = "";
        for (int i :
                arr) {
            s += "," + i;
        }
        return s;
    }
}
