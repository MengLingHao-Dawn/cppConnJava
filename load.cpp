#include <iostream>
#include <Windows.h>
#include "load.h"
using namespace std;

Load::Load() {

}
Load::~Load() {

}

void Load::connJava() {
	typedef jint(WINAPI* PFunCreateJavaVM)(JavaVM**, void**, void*);

	// ���뵱ǰ·����jvmѰ��class���û��Զ���·��
	options[0].optionString = const_cast<char *>("-Djava.class.path=C:\\Users\\Dawn\\Desktop");
	memset(&vm_args, 0, sizeof(vm_args));

	// Java�汾
	vm_args.version = JNI_VERSION_1_8;
	// �����options�ж���
	vm_args.nOptions = 1;
	// ��JavaVMOptions����JavaVMInitArgs
	vm_args.options = options;
	// ����jvm.dll�ļ�������ʱjdkĿ¼�µ�
	HINSTANCE hInstance = ::LoadLibraryA("D:\\Program Files (x86)\\Java\\jdk1.8.0_301\\jre\\bin\\client\\jvm.dll");
	if (hInstance == NULL) {
		cout << "hInstance is null!" << endl;
		return;
	}
	else {
		// ����JNI_CreateJavaVM�����ı���
		PFunCreateJavaVM createJVM = (PFunCreateJavaVM)::GetProcAddress(hInstance, "JNI_CreateJavaVM");
		if (createJVM == NULL) {
			cout << "createJVM is null!" << endl;
			return;
		}
		else {
			jvm = new JavaVM();
			env = new JNIEnv();
			// ���������
			long status = (*createJVM)(&jvm, (void**)&env, &vm_args);
			// JNI_ERR����jvm.h�ж���ģ�ֵΪ-1
			// ��statusΪ0ʱ�������ɹ�
			if (status != JNI_ERR) {
				// ���class����
				cls = env->FindClass("Sample");
				if (cls != 0) {
					// ��ȡ��̬����ID, ͨ����������ǩ��, ���þ�̬����
					mid = env->GetStaticMethodID(cls, "sayHello", "(Ljava/lang/String;I)Ljava/lang/String;");
					if (mid != 0) {
						const char* name = "World";
						const int year = 2021;
						// ������ת��ΪJava�ĸ�ʽ
						jint argYear = year;
						jstring argName = env->NewStringUTF(name);
						// ����Java������ͬʱ��ȡ����ֵ
						jstring result = (jstring)env->CallStaticObjectMethod(cls, mid, argName, argYear);
						// ������ֵת��Ϊconst char*����
						const char* str = env->GetStringUTFChars(result, 0);
						cout << "Result of sayHello: " << str << endl;
						env->ReleaseStringUTFChars(result, 0);
					}

					// ���ù��캯��, ���캯�������ֽ���<init>
					mid = env->GetMethodID(cls, "<init>", "()V");
					// ����Java��Ķ���
					obj = env->NewObject(cls, mid);
					if (obj == 0) {
						cout << "Create object failed!" << endl;
					}

					// ͨ����������ǩ������ȡ����id
					fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
					if (fid != 0) {
						const char* name = "ice-creame";
						jstring argName = env->NewStringUTF(name);
						env->SetObjectField(obj, fid, argName);
					}

					// ������ͨ��Ա����
					mid = env->GetMethodID(cls, "sayHello", "()Ljava/lang/String;");
					if (mid != 0) {
						jstring result = (jstring)env->CallObjectMethod(obj, mid);
						const char* str = env->GetStringUTFChars(result, 0);
						cout << "Result of sayHello: " << str << endl;
						env->ReleaseStringUTFChars(result, 0);
					}
				}
				// ���������
				jvm->DestroyJavaVM();
			}
			else {
				cout << "JVM created failed!" << endl;
			}
		}
	}



}