# YVM
ȥ������Javaд��һ�����Ʒ��jvm(�μ�commit history)�������������ݽṹ��ƴ����´���ִ������һ�Σ�����޸Ľṹ�������Ƶ��������������η�����
��ѧ��ʱ��ܳ�ԣ�����Ƶ�������C++дǰ���Ѿ���ƹ���ŵ����ݽṹ�����˼���˼�������˼��ֱ����ٶȡ�
����Ȥ������fork/star/pr�ɣ�

#

# ����
0. YVM���ڲ�֧��JavaSE6����֮ǰ�汾�����������`.class`
1. ��֧��`synchronized`
2. ����ʹ���κ�JDK�ķ���,��ʹ��`ydk.lang.*`(���ʹ��һ��jdk�����������͵�ʵ�ִ󲿷�jdk��,������һ���˵�����дJDK������죬����ҵĳ���(��һ�����õ�����JVM)���)

# ������ƣ�˽��ʵ��
0. ��JVM��`byte`,`char`,`boolean`,`short`������з�����չ��`int`,��JVMʵ�ʴ��ڵ�����ֻ��`int`,`long`,`float,`double`,`object ref`,`array`
1. YVM����ֻ��һ��Ȩ����ʾ,��"package/foo/Bar",�κ�������ʾ��"java.lang.Object"���ܾ�����
2. ����JVMSPEC,�����ִ�������ֱ�Ӳ���JDKһЩ��,��`java/lang/Class`,`java/lang/invoke/MethodType`,`java/lang/invoke/MethodHandle`,`java/lang/String`.Ϊ��ʵ��һ��"Runnable"��JVM������ʹ���Խ�YDK����������ǡ�


# License
Code licensed under the MIT License.