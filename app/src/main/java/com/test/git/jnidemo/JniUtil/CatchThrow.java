package com.test.git.jnidemo.JniUtil;

/**
 * Created by lk on 16/9/29.
 */

public class CatchThrow {
    public native void doit() throws IllegalArgumentException;

    private void callback() throws NullPointerException{
        throw new NullPointerException("CatchThrow.callback");
    }
}
