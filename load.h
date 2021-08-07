#pragma once

#include <jni.h>
#include <string>

// 环境变量PATH在Windows下和Linux下的分割符定义
#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif // _WIN32

class Load
{
public:
	Load();
	~Load();

public:
	// 连接Java的函数
	void connJava();
private:
	// 相当于在命令行里传入参数
	JavaVMOption options[1];
	// Java调用C/C++中每个方法都会有的一个参数，拥有一个JNI的环境
	JNIEnv* env;
	// 虚拟机实例
	JavaVM* jvm;
	// 虚拟机创建的初始化参数，这个参数里面会包含JavaVMOption
	JavaVMInitArgs vm_args;
	// 存放启动虚拟机的状态
	//long status;
	// Java中class对象
	jclass cls;
	// Java中方法的id
	jmethodID mid;
	// Java中属性的id
	jfieldID fid;
	// 存放Java类的对象
	jobject obj;
};

