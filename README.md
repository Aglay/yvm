# YVM
这是用C++写的一个虚拟机，现在支持java功能，不过还有很多bug等待修复。
感兴趣的朋友pull request/fork/star吧！

# 支持功能
:-0 高级特性逐步支持中，可以开Issue提议或者直接PR
+ Java基本算术运算，流程控制语句，面向对象。
+ [RTTI](./javallib_src/ydk/test/InstanceofTest.java)
+ [字符串拼接(+,+=符号重载)](./javalib_src/ydk/test/StringConcatenation.java)
+ [异常处理](./javalib_src/ydk/test/ThrowExceptionTest.java)

# 使用方法
1. 配置src/main.cpp
```cpp
#include "YVM.h"

int main() {
    const char * ydk[] = {
    	//该项目java lib文件所在的绝对路径
        R"(C:\Users\Cthulhu\Desktop\yvm\javalib)"
    };

    YVM vm;
    vm.warmUp(ydk, sizeof(ydk) / sizeof(ydk[0]));
    vm.callMain("ydk/test/InheritanceTest");
    system("pause");
    return 0;
}
```
2. 支持G++7.0,MSVC 2017,直接编译运行即可

# 关于JDK
部分JDK类是JVM运行攸关的,但由于JDK比较复杂不便于初期开发,所以这里用重写过的JDK代替,源码参见[javalib_src](./javalib_src)目录,编译后`*.class`文件位于[javalib](./javalib)
目前重写过的JDK类有:
+ `java.lang.String`
+ `java.lang.StringBuilder`
+ `java.lang.Throwable`

# 运行效果
0. helloworld
![](./public/hw.png)
![](./public/helloworld.png)
1. 冒泡排序
![](./public/bubbletest.png)
![](./public/bbb.png)

# License
Code licensed under the MIT License.


## {↓ For developers}
---
### {文件结构}
+ `javalib` 编译后的*.class文件，用于代替部分JDK，相当于yvm的rt.jar
+ `javalib_src` 运行时库和功能库的源码
+ `public` 文档，图片
+ `src/JavaClass.h` `.class`文件在YVM中的类表示
+ `src/Frame.h` 函数调用栈
+ `src/MethodArea.h` 方法区，管理JavaClass
+ `src/JavaHeap.h` 堆管理类，管理所有实例和数组数据但不拥有
+ `src/JavaType.h` 虚拟机机对象表示
+ `src/RuntimeEnv.h` 运行时数据。拥有堆，调用栈，和方法区数据
+ `src/CodeExecution.h` 执行引擎，现在是解释执行

### {公有设计，私有实现}
1. YVM中类只有一种权威表示,即"package/foo/Bar",任何其他表示如"java.lang.Object"都拒绝加载
2. 根据JVM SPEC,虚拟机执行引擎会直接操纵JDK一些类,如`java/lang/Class`,,`java/lang/String`.为了实现一个"Runnable"的JVM，这里使用重写的同名类(位于javalib)代替。
3.  YVM不支持(未来也不打算)JavaSE6及其之前版本编译器编译的`.class`
4. **不能使用任何JDK的方法**,不过部分运行攸关的JDK类已经重写过。输出可用`ydk.lang.IO`代替。
5. YVM中`float`相等取6位小数精度，`double`相等取12位小数精度
