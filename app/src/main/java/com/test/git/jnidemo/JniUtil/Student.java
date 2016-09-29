package com.test.git.jnidemo.JniUtil;

import android.util.Log;

/**
 * Created by lk on 16/9/26.
 */

public class Student extends Person{
    private static final String TAG = "Student";

    public Student(String name, int age){
        this.name = name;
        this.age = age;
    }

    @Override
    public void eat() {
        super.eat();
        Log.i(TAG, "eat: Student");
    }
}
