#include <jni.h>
#include <stdlib.h>
#include <string.h>


int* malloc_int(int length){
    int* ip = (int*)(malloc(length*sizeof(int)));
    memset(ip,0,sizeof(ip));
    return ip;
}

char* malloc_char(int length){
    char* cp= (char*)(malloc(length*sizeof(char)));
    memset(cp,0,sizeof(cp));
    return cp;
}

//java字符串转C字符串
char* jstringTostr(JNIEnv* env, jstring jstr) {
    char* pStr = NULL;
    jclass     jstrObj   = (*env)->FindClass(env, "java/lang/String");
    jstring    encode    = (*env)->NewStringUTF(env, "utf-8");
    jmethodID  methodId  = (*env)->GetMethodID(env, jstrObj, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray byteArray = (jbyteArray)(*env)->CallObjectMethod(env, jstr, methodId, encode);
    jsize      strLen    = (*env)->GetArrayLength(env, byteArray);
    jbyte      *jBuf     = (*env)->GetByteArrayElements(env, byteArray, JNI_FALSE);
    if(jBuf > 0){
        pStr = (char*)malloc(strLen + 1);
        if (!pStr){
            return NULL;
        }
        memcpy(pStr, jBuf, strLen);
        pStr[strLen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env, byteArray, jBuf, 0);
    return pStr;
}

//C字符串转java字符串
jstring strToJstring(JNIEnv* env, const char* pStr) {
    int        strLen    = strlen(pStr);
    jclass     jstrObj   = (*env)->FindClass(env, "java/lang/String");
    jmethodID  methodId  = (*env)->GetMethodID(env, jstrObj, "<init>", "([BLjava/lang/String;)V");
    jbyteArray byteArray = (*env)->NewByteArray(env, strLen);
    jstring    encode    = (*env)->NewStringUTF(env, "utf-8");
    (*env)->SetByteArrayRegion(env, byteArray, 0, strLen, (jbyte*)pStr);
    return (jstring)(*env)->NewObject(env, jstrObj, methodId, byteArray, encode);
}