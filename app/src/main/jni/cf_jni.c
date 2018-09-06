#include <jni.h>
#include <string.h>
#include <stdlib.h>
#include "cf_log.h"
#include "cf_util.c"

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
    jint *arr;//java数组jintArray在C中对应的类型
    jintArray result;//jni方法返回的新数组
    int* newArr;//新数组

    //数组默认长度
    int length = (*env)->GetArrayLength(env, arr_);
    if(length==0){
        return arr_;
    }
    arr = (*env)->GetIntArrayElements(env, arr_, NULL);

    //新数组的长度
    int newLength = length-1;
    //创建一个新数组
    newArr = malloc_int(newLength);
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
    result = (*env)->NewIntArray(env,newLength);
    (*env)->SetIntArrayRegion(env,result,0,newLength,newArr);

    //此处统一释放
    free(newArr);
    //不对arr指针进行修改，就可以进行释放
    (*env)->ReleaseIntArrayElements(env, arr_, arr, 0);

    return result;
}

//给数组添加值
JNIEXPORT jintArray JNICALL
Java_com_changf_ndk_lib_NativeMethed_addArrayValue(JNIEnv *env, jobject instance, jintArray arr_) {
    jint *arr = (*env)->GetIntArrayElements(env, arr_, NULL);
    //数组默认长度
    int length = (*env)->GetArrayLength(env, arr_);
    int newLength = length+1;
    //创建一个新数组
    int* newArr = malloc_int(newLength);
    for(int i=0;i<newLength;i++){
        if(i<length){
            newArr[i] = arr[i];
        }else{
            newArr[i] = 0;
        }
    }
    jintArray result = (*env)->NewIntArray(env,newLength);
    (*env)->SetIntArrayRegion(env,result,0,newLength,newArr);

    //此处统一释放
    free(newArr);
    //不对arr指针进行修改，随时可以进行释放
    (*env)->ReleaseIntArrayElements(env, arr_, arr, 0);

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

    (*env)->DeleteLocalRef(env, cls);
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

    (*env)->DeleteLocalRef(env, cls);
    return result;
}

//调用实例属性
JNIEXPORT jstring JNICALL
Java_com_changf_ndk_lib_NativeMethed_callInstanceAttr(JNIEnv *env, jobject instance) {
//    //根据包名+类名得到jclass
//    char *classname = "com/changf/ndk/lib/NativeMethed";
//    jclass cls = (*env)->FindClass(env, classname);
//    //通过jclass得到jobject
//    jobject clsObj = (*env)->AllocObject(env,cls);

    //使用传递过来的对象instance,只需得到instance的jclass
    jclass cls = (*env)->GetObjectClass(env,instance);
    //根据属性名，属性签名，得到属性jfieldID
    jfieldID fid = (*env)->GetFieldID(env, cls, "instanceAttr", "Ljava/lang/String;");
    if (fid == NULL) {
        return NULL;
    }
    //根据类的实例，和属性id，得到属性的值
    jstring fieldValue = (*env)->GetObjectField(env,instance,fid);
    //jstring转换成char指针
    char *charValue="null";
    if (fieldValue!=NULL) {
        charValue = (*env)->GetStringUTFChars(env, fieldValue, JNI_FALSE);
    }
    char *prefixValue = "NativeMethed实例属性instanceAttr的值为";
    char *finalValue = malloc_char(strlen(prefixValue)+strlen(charValue));
    //连接两个字符指针
    strcat(finalValue,prefixValue);
    strcat(finalValue,charValue);
    //c字符串 ->jstring
    jstring result = (*env)->NewStringUTF(env, finalValue);

    //此处统一释放
    free(finalValue);
    (*env)->DeleteLocalRef(env, cls);
    (*env)->DeleteLocalRef(env, fieldValue);
    return result;
}

JNIEXPORT jstring JNICALL
Java_com_changf_ndk_lib_NativeMethed_callStaticAttr(JNIEnv *env, jobject instance) {
    //根据包名+类名得到jclass
//    char *classname = "com/changf/ndk/lib/NativeMethed";
//    jclass cls = (*env)->FindClass(env, classname);
    //根据实例对象获取jclass
    jclass cls = (*env)->GetObjectClass(env,instance);
    //根据属性名，属性签名，得到属性jfieldID
    jfieldID fid = (*env)->GetStaticFieldID(env, cls, "staticAttr", "Ljava/lang/String;");
    if (fid == NULL) {
        return NULL;
    }
    //根据类的实例，和属性id，得到属性的值
    jstring fieldValue = (*env)->GetStaticObjectField(env,cls,fid);
    //jstring转换成char指针
    char *charValue="null";
    if (fieldValue!=NULL) {
        charValue = (*env)->GetStringUTFChars(env, fieldValue, JNI_FALSE);
    }
    char *prefixValue = "NativeMethed静态属性staticAttr的值为";
    char *finalValue = malloc_char(strlen(prefixValue)+strlen(charValue));
    //连接两个字符指针
    strcat(finalValue,prefixValue);
    strcat(finalValue,charValue);

    //c字符串 ->jstring
    jstring result = (*env)->NewStringUTF(env, finalValue);

    //此处统一释放
    free(finalValue);
    (*env)->DeleteLocalRef(env, cls);
    (*env)->DeleteLocalRef(env, fieldValue);

    return result;
}

JNIEXPORT jobject JNICALL
Java_com_changf_ndk_lib_NativeMethed_callConstructMethod(JNIEnv *env, jobject instance) {
    jclass cls = (*env)->GetObjectClass(env,instance);
    jmethodID methodId = (*env)->GetMethodID(env,cls,"<init>","(Ljava/lang/String;)V");
    //实例化Student并传递参数
    jstring msgJstr = (*env)->NewStringUTF(env,"JIN调用了NativeMethed的构造方法");

    return (*env)->NewObject(env,cls,methodId,msgJstr);
}

JNIEXPORT jstring JNICALL
Java_com_changf_ndk_lib_NativeMethed_callSuperClassMethod(JNIEnv *env, jobject instance) {


//    return (*env)->NewStringUTF(env, returnValue);
}
