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

	// 传入当前路径，jvm寻找class的用户自定义路径
	options[0].optionString = const_cast<char *>("-Djava.class.path=C:\\Users\\Dawn\\Desktop");
	memset(&vm_args, 0, sizeof(vm_args));

	// Java版本
	vm_args.version = JNI_VERSION_1_8;
	// 传入的options有多少
	vm_args.nOptions = 1;
	// 把JavaVMOptions传给JavaVMInitArgs
	vm_args.options = options;
	// 加载jvm.dll文件，必须时jdk目录下的
	HINSTANCE hInstance = ::LoadLibraryA("D:\\Program Files (x86)\\Java\\jdk1.8.0_301\\jre\\bin\\client\\jvm.dll");
	if (hInstance == NULL) {
		cout << "hInstance is null!" << endl;
		return;
	}
	else {
		// 创建JNI_CreateJavaVM函数的变量
		PFunCreateJavaVM createJVM = (PFunCreateJavaVM)::GetProcAddress(hInstance, "JNI_CreateJavaVM");
		if (createJVM == NULL) {
			cout << "createJVM is null!" << endl;
			return;
		}
		else {
			jvm = new JavaVM();
			env = new JNIEnv();
			// 启动虚拟机
			long status = (*createJVM)(&jvm, (void**)&env, &vm_args);
			// JNI_ERR是再jvm.h中定义的，值为-1
			// 若status为0时即启动成功
			if (status != JNI_ERR) {
				// 获得class对象
				cls = env->FindClass("Sample");
				if (cls != 0) {
					// 获取静态方法ID, 通过方法名和签名, 调用静态方法
					mid = env->GetStaticMethodID(cls, "sayHello", "(Ljava/lang/String;I)Ljava/lang/String;");
					if (mid != 0) {
						const char* name = "World";
						const int year = 2021;
						// 将参数转换为Java的格式
						jint argYear = year;
						jstring argName = env->NewStringUTF(name);
						// 调用Java方法，同时获取返回值
						jstring result = (jstring)env->CallStaticObjectMethod(cls, mid, argName, argYear);
						// 将返回值转换为const char*类型
						const char* str = env->GetStringUTFChars(result, 0);
						cout << "Result of sayHello: " << str << endl;
						env->ReleaseStringUTFChars(result, 0);
					}

					// 调用构造函数, 构造函数的名字叫做<init>
					mid = env->GetMethodID(cls, "<init>", "()V");
					// 创建Java类的对象
					obj = env->NewObject(cls, mid);
					if (obj == 0) {
						cout << "Create object failed!" << endl;
					}

					// 通过属性名和签名来获取属性id
					fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
					if (fid != 0) {
						const char* name = "ice-creame";
						jstring argName = env->NewStringUTF(name);
						env->SetObjectField(obj, fid, argName);
					}

					// 调用普通成员方法
					mid = env->GetMethodID(cls, "sayHello", "()Ljava/lang/String;");
					if (mid != 0) {
						jstring result = (jstring)env->CallObjectMethod(obj, mid);
						const char* str = env->GetStringUTFChars(result, 0);
						cout << "Result of sayHello: " << str << endl;
						env->ReleaseStringUTFChars(result, 0);
					}
				}
				// 销毁虚拟机
				jvm->DestroyJavaVM();
			}
			else {
				cout << "JVM created failed!" << endl;
			}
		}
	}



}