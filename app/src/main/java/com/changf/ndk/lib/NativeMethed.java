package com.changf.ndk.lib;

public class NativeMethed {

    static {
        System.loadLibrary("cfjni");
    }

    private static NativeMethed mNativeMethed;

    public static synchronized NativeMethed getInstance(){
        if(mNativeMethed==null){
            mNativeMethed = new NativeMethed();
        }
        return mNativeMethed;
    }

    public String instanceMethod(){
        return "C调用了Java实例方法 instanceMethod";
    }

    public static String staticMethod(){
        return "C调用了Java静态方法 staticMethod";
    }

   //加减乘除
    public  native long add(long value);
    public  native long minus(long value);
    public  native long multiply(long value);
    public  native long divide(long value);
    //数组操作
    public native void remindArray(int[] arr);
    public native int[] deleteArrayValue(int[] arr);
    public native int[] addArrayValue(int[] arr);
    //C调Java方法
    public native String callInstanceMethod();
    public native String callStaticMethod();

}
