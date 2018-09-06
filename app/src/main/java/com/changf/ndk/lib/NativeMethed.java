package com.changf.ndk.lib;

public class NativeMethed {
    private static final String TAG = NativeMethed.class.getSimpleName();

    static {
        System.loadLibrary("cfjni");
    }
    private String constructAttr;
    private String instanceAttr = "instance";//实例属性
    private static String staticAttr = "static";//静态属性

    private static NativeMethed mNativeMethed;

    private NativeMethed (){}

    //专供JNI来调用
    public NativeMethed (String msg){
        constructAttr = msg;
    }

    public static synchronized NativeMethed getInstance(){
        if(mNativeMethed==null){
            mNativeMethed = new NativeMethed();
        }
        return mNativeMethed;
    }

    public String getConstructAttr() {
        return constructAttr+"生成对象"+toString();
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
    public native NativeMethed callConstructMethod();
    public native String callSuperClassMethod();
    //C调用Java属性
    public native String callInstanceAttr();
    public native String callStaticAttr();
}
