#include <jni.h>
#include <string.h>
#include <stdlib.h>
#include "cf_log.h"


int* mk_malloc(int length){
    return (int*)(malloc(length*sizeof(int)));
}

//加
JNIEXPORT jlong JNICALL
Java_com_changf_ndk_lib_NativeMethed_add(JNIEnv *env, jobject instance, jlong value) {
    return value+1;
}

//减
JNIEXPORT jlong JNICALL
Java_com_changf_ndk_lib_NativeMethed_minus(JNIEnv *env, jobject instance, jlong value) {
    return value-1;
}

//乘
JNIEXPORT jlong JNICALL
Java_com_changf_ndk_lib_NativeMethed_multiply(JNIEnv *env, jobject instance, jlong value) {
    return value*value;
}

//除
JNIEXPORT jlong JNICALL
Java_com_changf_ndk_lib_NativeMethed_divide(JNIEnv *env, jobject instance, jlong value) {
    return value/2;
}

//修改数组的值
JNIEXPORT void JNICALL
Java_com_changf_ndk_lib_NativeMethed_remindArray(JNIEnv *env, jobject instance, jintArray arr_) {
    jint *arr = (*env)->GetIntArrayElements(env, arr_, NULL);
    int length = (*env)->GetArrayLength(env, arr_);
    for(int i=0;i<length;i++){
        arr[i] = i+1;
    }
    (*env)->ReleaseIntArrayElements(env, arr_, arr, 0);
}

//删除数组的数据
JNIEXPORT jintArray JNICALL
Java_com_changf_ndk_lib_NativeMethed_deleteArrayValue(JNIEnv *env, jobject instance,jintArray arr_) {
    //数组默认长度
    int length = (*env)->GetArrayLength(env, arr_);
    if(length==0){
        return arr_;
    }
    jint *arr = (*env)->GetIntArrayElements(env, arr_, NULL);
    //不对arr指针进行修改，则现在就可以释放内存
    (*env)->ReleaseIntArrayElements(env, arr_, arr, 0);
    //新数组的长度
    int newLength = length-1;
    //创建一个新数组
    int* newArr = mk_malloc(newLength);
    //获取一个随机索引
    int deletePosi = (rand() % (length));
    for(int i=0;i<newLength;i++){
        if(deletePosi==i){
            for(int j=deletePosi;j<newLength;j++){
                newArr[j] = arr[j+1];
            }
            break;
        }else{
            newArr[i] = arr[i];
        }
    }
    jintArray result = (*env)->NewIntArray(env,newLength);
    (*env)->SetIntArrayRegion(env,result,0,newLength,newArr);

    free(newArr);
    return result;
}

//给数组添加值
JNIEXPORT jintArray JNICALL
Java_com_changf_ndk_lib_NativeMethed_addArrayValue(JNIEnv *env, jobject instance, jintArray arr_) {
    jint *arr = (*env)->GetIntArrayElements(env, arr_, NULL);
    //不对arr指针进行修改，则现在就可以释放内存
    (*env)->ReleaseIntArrayElements(env, arr_, arr, 0);
    //数组默认长度
    int length = (*env)->GetArrayLength(env, arr_);
    int newLength = length+1;
    //创建一个新数组
    int* newArr = mk_malloc(newLength);
    for(int i=0;i<newLength;i++){
        if(i<length){
            newArr[i] = arr[i];
        }else{
            newArr[i] = 0;
        }
    }
    jintArray result = (*env)->NewIntArray(env,newLength);
    (*env)->SetIntArrayRegion(env,result,0,newLength,newArr);

    free(newArr);
    return result;
}

//调用java的实例方法
JNIEXPORT jstring JNICALL
Java_com_changf_ndk_lib_NativeMethed_callInstanceMethod(JNIEnv *env, jobject instance) {
      //根据包名+类名得到jclass，再通过jclass得到jobject
//      char* classname = "com/changf/ndk/lib/NativeMethed";
//      jclass cls = (*env)->FindClass(env, classname);
//      jobject clsObj = (*env)->AllocObject(env,cls);
//      jmethodID methodId = (*env)->GetMethodID(env,cls,"instanceMethod","()Ljava/lang/String;");
//      jstring result = (*env)->CallObjectMethod(env, clsObj, methodId);

     //使用传递过来的对象instance,只需得到instance的jclass
     jclass cls = (*env)->GetObjectClass(env,instance);
     jmethodID methodId = (*env)->GetMethodID(env,cls,"instanceMethod","()Ljava/lang/String;");
     jstring result = (*env)->CallObjectMethod(env, instance, methodId);

    return result;
}

//调用java的静态方法
JNIEXPORT jstring JNICALL
Java_com_changf_ndk_lib_NativeMethed_callStaticMethod(JNIEnv *env, jobject instance) {
    //根据包名+类名得到jclass，再通过jclass得到jobject
//    char* classname = "com/changf/ndk/lib/NativeMethed";
//    jclass cls = (*env)->FindClass(env, classname);
//    jmethodID methodId = (*env)->GetStaticMethodID(env,cls,"staticMethod","()Ljava/lang/String;");
//    jstring result = (*env)->CallStaticObjectMethod(env,cls,methodId);

    //使用传递过来的对象instance,只需得到instance的jclass
    jclass cls = (*env)->GetObjectClass(env,instance);
    jmethodID methodId = (*env)->GetStaticMethodID(env,cls,"staticMethod","()Ljava/lang/String;");
    jstring result = (*env)->CallStaticObjectMethod(env, cls, methodId);
    return result;
}