Linux软件工具



Linux软件包管理器



IDE——集成开发环境（集代码编辑，运行，调试，编译，链接于一体）

而Linux下

编写代码——vim

编译代码——gcc/g++

调试代码——gdb

运行/自动化构建程序——make



Linux编辑器vim

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220721131322442.png" alt="image-20220721131322442" style="zoom:50%;" />

vim只能写代码，不能编译代码

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220721134329844.png" alt="image-20220721134329844" style="zoom: 50%;" />

进入vim后，默认为vim的命令模式，此时无法编写代码，而只能输入指令进行编辑器操作

vim下输入模式：

i——进入输入模式

ESC——退出输入模式，返回到命令模式



vim下底行模式：

shift [分号] + q——退出vim编辑器

q——退出

q！——强制退出

w——保存diamante

qw——保存并退出

ESC——退出底行模式，返回命令模式

注：不能直接从输入模式进入到底行模式，而先需要ESC到命令模式，再到底行模式保存退出



vim常见命令

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220721155746208.png" alt="image-20220721155746208" style="zoom:67%;" />



vim配置

![image-20220721160019999](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220721160019999.png)



sudoers权限

对于以往普通用户想临时提升root权限查看文件列表或将文件转交给其他用户，使用sudo指令但不在信任列表，所以有了vim工具，可以通过执行vim /etc/sudoers进入信任文档添加信任用户：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220721160305074.png" alt="image-20220721160305074" style="zoom: 67%;" />



---

Linux编译器gcc/g++

gcc -v——查看gcc版本

很多linux默认没够g++，使用yum install -y gcc-c++指令安装g++编译器，再使用g++ -v查看即安装完成

gcc是专门用于编译链接C语言的，g++用来编译链接C++的，后者可以包容前者，前者不包含后者

![image-20220721214035687](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220721214035687.png)

-o——指定一个新名字

-E——对源文件进行翻译，主要是进行==预处理==，当预处理完成就停止，形成.i为后缀的预处理过的源文件

-S——对已经预处理过的源文件进行==编译==，当编译完成就停止，形成.s为后缀的编译文件

-c——对编译好的文件进行==汇编==处理，形成.o为后缀的可重定向目标二进制文件（即.obj文件，可使用od [目标文件名]查看二进制文件），注意，该文件尚不可被执行，即使提升了可执行权限也无法执行二进制文件

![image-20220731144208827](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731144208827.png)

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731143959560.png" alt="image-20220731143959560" style="zoom: 67%;" />

==gcc [源文件名.c/目标文件名.o] -o [可执行程序文件名]==——将源文件编译为可执行程序文件（==gcc一步到位编译+链接==，可以直接形成可执行程序）

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731144932677.png" alt="image-20220731144932677" style="zoom:67%;" />

注意：可直接使用gcc [源文件名]而不带-o选项，此时意为对该源文件编译＋链接但没有给定可执行程序文件名，由系统默认生成一个名为==a.out==的该源文件的可执行程序文件名

![image-20220731150731296](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731150731296.png)

也可以分布执行（分别进行预处理-E，汇编-S，编译-c），链接没有特殊指令，直接gcc [] -o []完成编译+链接即可

gcc -E [源文件名]——将源文件进行预处理，如果直接输入该指令则会将处理的结果反馈到显示器上

gcc -E[源文件名] -o [源文件名.i]——把预处理完毕的源文件写到一个临时文件.i中，改文件包含展开的头文件，去掉的注释行和去掉的条件编译语句。

![image-20220731133835722](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731133835722.png)

预处理阶段完成的事情：

1. 去注释
2. 将宏的值直接替换
3. 头文件替换.h并编译
4. 条件编译

gcc -S [预处理过的源文件名.i] -o [编译的文件名.s]——将预处理文件进行编译

![image-20220731143337149](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731143337149.png)

gcc -c [编译过的源文件名.s] -o [汇编的文件名.o]——将编译文件重定向目标为二进制文件（即.obj文件）

./[可执行程序名]——

总结：

一个源文件经过gcc编译器的处理经过预处理，编译，汇编和链接的阶段，前三个步骤可由gcc编译选项==ESc==来完成（-E代表源文件预处理，-S代表编译，-c代表汇编），链接直接由gcc自动完成，而这三个阶段分别完成阶段任务所生成的文件及后缀依次为==iso==（.i代表预处理的源文件，.s代表编译过的源文件，.o为经过汇编处理的可重定向二进制目标文件），最后经过编译器编译+链接，形成系统可执行程序.exe，通过./[可执行程序名]即可运行程序。



---

动静态库

每个使用C编译链接而形成的可执行程序.exe都使用了C语言的动态库，查询方法为：

ldd [可执行程序文件名]——查看使用了哪些C语言动态库

file [可执行程序文件名]——查看在多少位环境下使用了什么库

链接的过程一般分为两种方式：动态链接和静态链接

1. 动态链接——需要动态库，将库中的可执行程序需要调用到的方法的地址，拿到可执行程序中，建立关联。
2. 静态链接——需要静态库，将库中方法的实现，具体拷贝到可执行程序中。

库就是C语言官方提供给用户使用的函数定义和源代码所在之处，而头文件就是这些库函数的声明之处

![image-20220731151443674](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731151443674.png)

Linux下和Windows在动静态库的文件夹后缀不同

Linux：.so（动态库），.a（静态库）

Windows：.dll（动态库），.lib（静态库）

总结：

1. 库函数在链接阶段才与C语言提供的动静态库相互关联匹配，在链接之前的所有阶段如.i, .s, .o这类的源文件或编译文件仅完成了代码本身的编译，而没有对库函数（方法）进行库链接和方法的定义。

2. 如果一个可执行程序使用了动态链接的动态库文件，它的执行依赖于该库，如果库不存在，则程序无法正常执行。如果它使用了静态库，因为静态链接过程是将静态库中方法的声明和定义都拷贝到程序文件里，所有库存不存在都对程序执行本身没有影响。

3. 因此，使用动态链接的动态库的可执行程序文件比较节省资源，因为它不需要重复拷贝库中的文件就可以通过链接建立关联访问到该方法函数，缺点在于对于动态库的依赖。而使用静态链接的静态库可执行程序不依赖库，但是每个文件都是静态链接的话，会重复拷贝大量冗余的相同方法函数，比较占用资源。

4. gcc, g++默认生成的可执行程序是动态链接的，如果想使用静态链接，则使用gcc [源文件名] -o [可执行程序文件名] -static，编译和链接成功可以发现，静态链接的exe文件比动态链接的占用大非常多。

   <img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731161518332.png" alt="image-20220731161518332" style="zoom:80%;" />

   其中在编译链接后加上==-static==选项表示使用静态链接的方式形成可执行程序，通过ldd和file可以查看具体的库信息

   ![image-20220731161656311](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731161656311.png)

   如果系统自身没有静态库，会导致链接失败。即如果要使用动态链接，必须使用.so动态库文件；要使用静态链接，需要使用.a静态库文件。

   使用如下指令安装静态库文件

   ![image-20220731162036279](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731162036279.png)



---

make/makefile

![image-20220731162654199](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731162654199.png)

make是一条命令，makefile是一个文件



makefile文件：

在makefile文件包含可执行程序编译出必须用到的依赖关系和依赖方法：

1. 依赖关系：根据哪个源文件而来
2. 依赖方法：使用什么样的编译器和指令来构建出可执行程序

使用vim打开，编写程序编译自动化构建，通常一个可执行程序的生成包含构建和清理两个依赖关系和对应的依赖方法：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731165156938.png" alt="image-20220731165156938" style="zoom: 67%;" />

其中的指令第一条为可执行程序根据源文件编译链接的依赖关系，其下面一条的依赖方法必须用tab开头，并附上的语句称为依赖方法，即一个可执行程序的生成必须知道与源文件的对应关系（WHERE）和执行方法（HOW）。

换句话说，如果要编译出可执行程序，直接执行make指令，就可以直接生成该源文件对应的exe，效果等同于自己输入gcc [] -o

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731165605713.png" alt="image-20220731165605713" style="zoom:67%;" />

如果源文件代码发生了修改，想要重新构造该源文件的可执行程序exe，必须先清理掉之前生成的exe，并再次构建该源文件的可执行程序文件，可以使用指令组合make clean来达到双重效果。

所以同理，清理原可执行程序文件使用到的clean指令所用到的依赖关系从.PHONY修饰的clean关系名中而来，而具体的清理方法由依赖关系下的rm -f []具体实施。

但是，makefile自动化构建中，只会对自顶向下遇到的第一个目标文件所对应的依赖关系和依赖方法执行，而处于第二个clean所处的目标文件则会被无视。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731170758215.png" alt="image-20220731170758215" style="zoom:67%;" />

如果想让makefile文件中的所有目标文件和关系依赖和方法都被执行，就必须在使用make执行仅第一条语句的基础上，在后续加上其他目标关系名，如clean，或者mytest等自己定义的名字。

但是如果将源文件编译链接命令放在makefile最顶上，如果对相同文件进行重复编译，则会报出以下信息

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731172035026.png" alt="image-20220731172035026" style="zoom:67%;" />

.PHONY——其修饰的依赖关系称为伪目标，将指令设置为总是被执行

![image-20220731172143183](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731172143183.png)

效果

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731171819009.png" alt="image-20220731171819009" style="zoom:67%;" />

一般习惯给clean数值.PHONY修饰，使其总是被执行，而编译指令一般不需要修饰，因为不用每次都编译链接，写为如下的makefile文件即可：

![image-20220731202703431](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731202703431.png)

但是，makefile如何知道源文件已经被编译过是最新的而不让用户编译链接了？

是因为它是根据文件最近的修改时间来确定的，也就是文件的ACM：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731203533132.png" alt="image-20220731203533132" style="zoom:67%;" />

其中modify是对文件内容做出修改时改变的时间，而change是对文件属性（如权限或路径）进行修改时改变的时间

但更具体一点说，makefile是根据源文件.c的modify时间与对应编译而成的可执行程序文件的modify时间进行对比，如果后者比前者更新，则说明用户堆源文件没有修改，则说明exe版本已经是最新；而如果前者比后者，即源文件的修改时间比exe的修改时间更新，则说明用户在编译该文件后，又对源文件进行了某些修改，致使源文件时间更新，以此为判断标准，断定用户更新过源文件，所以允许用户再次编译链接形成新的可执行程序文件。



例：对一个工程文件进行makefile编译整合

![image-20220731212956303](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731212956303.png)

或着也可以一步到位

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731214724771.png" alt="image-20220731214724771" style="zoom: 67%;" />





---

缓冲区

C语言中存在缓冲区，表层的认识来看，语句是从上往下顺序执行的，且当上条语句执行完毕结束后再执行下条语句。但观察下面两个代码

![image-20220731222054959](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731222054959.png)

左右两个函数执行的结果是什么？

左图结果：

![缓冲区](C:\Users\Shiki\Desktop\资料\Linux\博客图片\缓冲区.gif)

右图结果：

![缓冲区1](C:\Users\Shiki\Desktop\资料\Linux\博客图片\缓冲区1.gif)

可以看到，带了换行符的程序的执行逻辑是符合常理的，但不带换行符的程序却是"先执行"第二条语句，后执行第一条语句？

解释

![image-20220731221837689](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220731221837689.png)

