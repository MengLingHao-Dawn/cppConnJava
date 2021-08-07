# cppConnJava
## This is a project that C++ connects Java by using jnit. The system is Windows10.

#### First, you need a jdk and a simple java project.
#### Next, you can write C++ Code. But after you build C++ project, you must set environment configuration, because this project will use jni.h and jvm.lib. So you need add path of jdk/include, jdk/include/win32 and jdk/jre/bin/client.

## Code instructions:
#### 1. The format of Java is file whose suffix is .class by compiling. If you used JARs you can make project package in JAR. I recommend the second way.
#### 2. When you find class, if your java project has name of package, you must use package/class in your C++ code.
#### 3. The Method of java for obtaining a signature: Enter in the path of java project: javap -s -private xxx.class.


### 我是中国人，以上用英文知识图个练习英语，虽然没啥大用，勿喷。
