#pragma once

#include <jni.h>
#include <string>

// ��������PATH��Windows�º�Linux�µķָ������
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
	// ����Java�ĺ���
	void connJava();
private:
	// �൱�����������ﴫ�����
	JavaVMOption options[1];
	// Java����C/C++��ÿ�����������е�һ��������ӵ��һ��JNI�Ļ���
	JNIEnv* env;
	// �����ʵ��
	JavaVM* jvm;
	// ����������ĳ�ʼ�����������������������JavaVMOption
	JavaVMInitArgs vm_args;
	// ��������������״̬
	//long status;
	// Java��class����
	jclass cls;
	// Java�з�����id
	jmethodID mid;
	// Java�����Ե�id
	jfieldID fid;
	// ���Java��Ķ���
	jobject obj;
};

