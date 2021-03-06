//
//  HCColor+JNI.c
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#include "HCColor+JNI.h"
#include "../Core/HCObject+JNI.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
jclass HCColorJNIClazz = NULL;

void HCColorJNIOnLoad(JNIEnv* env) {
    HCColorJNIClazz = (*env)->NewGlobalRef(env, (*env)->FindClass(env, HCColorJNIClass));
    HCObjectJNIAssociateTypeToClass(env, HCDataType, HCColorJNIClazz);
}

void HCColorJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCColor self) {
    HCDataRef value = HCDataCreateWithBytes(sizeof(self), (HCByte*)&self);
    jfieldID fieldID = (*env)->GetFieldID(env, HCColorJNIClazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)value);
}

void HCColorJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jfieldID fieldID = (*env)->GetFieldID(env, HCColorJNIClazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(value);
}

HCColor HCColorJNIFromJObject(JNIEnv* env, jobject thiz) {
    jfieldID fieldID = (*env)->GetFieldID(env, HCColorJNIClazz, HCObjectJNIReferenceFieldID, HCObjectJNIReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    HCColor self = *((HCColor*)HCDataBytes(value));
    return self;
}

jobject HCColorJNINewJObject(JNIEnv* env, HCColor self) {
    jmethodID constructor = (*env)->GetMethodID(env, HCColorJNIClazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, HCColorJNIClazz, constructor);
    HCColorJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Constructors
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_initNative(JNIEnv *env, jobject thiz, jdouble alpha, jdouble red, jdouble green, jdouble blue) {
    HCColor self = HCColorMake(alpha, red, green, blue);
    HCColorJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_finalizeNative(JNIEnv *env, jobject thiz) {
    HCColorJNIReleaseReferenceInJObject(env, thiz);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_isEqualNative(JNIEnv *env, jobject thiz, jobject other_instance) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCColor other = HCColorJNIFromJObject(env, other_instance);
    HCBoolean isEqual = HCColorIsEqual(self, other);
    return (jboolean)isEqual;
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_hashNative(JNIEnv *env, jobject thiz) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCInteger hashValue = HCColorHashValue(self);
    return (jlong)hashValue;
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_toStringNative(JNIEnv *env, jobject thiz) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCColorPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Color toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_getAlphaNative(JNIEnv *env, jobject thiz) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCReal alpha = self.a;
    return (jdouble)alpha;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_getRedNative(JNIEnv *env, jobject thiz) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCReal red = self.r;
    return (jdouble)red;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_getGreenNative(JNIEnv *env, jobject thiz) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCReal green = self.g;
    return (jdouble)green;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_getBlueNative(JNIEnv *env, jobject thiz) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCReal blue = self.b;
    return (jdouble)blue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Queries
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_isClampedNative(JNIEnv *env, jobject thiz) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCBoolean isClamped = HCColorIsClamped(self);
    return (jboolean)isClamped;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_isInvalidNative(JNIEnv *env, jobject thiz) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCBoolean isInvalid = HCColorIsInvalid(self);
    return (jboolean)isInvalid;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_isSimilarNative(JNIEnv *env, jobject thiz, jobject other_instance, jdouble axis_dissimilarity) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCColor other = HCColorJNIFromJObject(env, other_instance);
    HCBoolean isSimilar = HCColorIsSimilar(self, other, axis_dissimilarity);
    return (jboolean)isSimilar;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_aggregatedNative(JNIEnv *env, jobject thiz, jobject other_instance) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCColor other = HCColorJNIFromJObject(env, other_instance);
    HCColor aggregated = HCColorAdd(self, other);
    return HCColorJNINewJObject(env, aggregated);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_scaledByColorNative(JNIEnv *env, jobject thiz, jobject other_instance) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCColor other = HCColorJNIFromJObject(env, other_instance);
    HCColor scaled = HCColorMultiply(self, other);
    return HCColorJNINewJObject(env, scaled);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_scaledByDoubleNative(JNIEnv *env, jobject thiz, jdouble scalar) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCColor scaled = HCColorScale(self, scalar);
    return HCColorJNINewJObject(env, scaled);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_clampedNative(JNIEnv *env, jobject thiz) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCColor clamped = HCColorClamp(self);
    return HCColorJNINewJObject(env, clamped);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Color_interpolatedNative(JNIEnv *env, jobject thiz, jobject other_instance, jdouble t) {
    HCColor self = HCColorJNIFromJObject(env, thiz);
    HCColor other = HCColorJNIFromJObject(env, other_instance);
    HCColor interpolated = HCColorInterpolate(self, other, t);
    return HCColorJNINewJObject(env, interpolated);
}
