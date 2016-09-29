package com.test.git.jnidemo.JniUtil;

import android.util.Log;

/**
 * Created by lk on 16/9/26.
 */

public class Person {
    private static final String TAG = "Person";
    protected String name;
    protected int age;

    public Person(){

    }


    public Person(String name, int age){
        this.name = name;
        this.age = age;
    }


    @Override
    public String toString() {
        return "name:" + name + "  age:" + age;
    }

    public void printPerson(){
        Log.i(TAG, "printPerson: " + toString());
    }

    public void eat(){
        Log.i(TAG, "eat: Person");
    }
}
