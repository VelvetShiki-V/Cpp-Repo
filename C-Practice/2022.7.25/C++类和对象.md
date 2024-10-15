C++类和对象



<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719142816981.png" alt="image-20220719142816981" style="zoom:50%;" />

C语言关注过程，C++关注对象

面向对象的三大特性

封装，继承和多态

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719152257453.png" alt="image-20220719152257453" style="zoom:50%;" />

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719152031092.png" alt="image-20220719152031092" style="zoom:50%;" />

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719152304456.png" alt="image-20220719152304456" style="zoom:50%;" />

封装的意义就在于，把可以给用户访问的函数接口等放到public上，供用户对应功能使用，而不对外开放的成员变量等封装到private中不对外开放，更规范和更安全，不易于堆数据造成修改。



类class

C++兼容C的用法，将C语言的struct结构体升级成了==类==，其域中可以存放成员变量和成员函数，可以不写struct：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719144342685.png" alt="image-20220719144342685" style="zoom:50%;" />

都合法

而对于结构体的定义，C++中更喜欢用class关键字代替

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719144703984.png" alt="image-20220719144703984" style="zoom:50%;" />

1. 类名就是类型，class默认的访问权限是private（访问限定符），struct默认的访问权限是public，两者区别是一个能在类外面不能访问，一个能访问。
2. 在class中第一行加上public：，直到遇到下一个访问限定符前，都是对外可见的

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719145234168.png" alt="image-20220719145234168" style="zoom:50%;" />

3. 除了public之外，private和protected都不能直接被类外访问，而只能在类中被访问



类的定义方式（与C类似）

1. 声明和定义全部放在类class中，如果成员函数放在类中定义，则可能会被编译器当做内联函数处理（短小的函数默认加了inline）
2. 声明和定义分离，声明放在.h头文件，定义放在.cpp文件中。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719164904691.png" alt="image-20220719164904691" style="zoom:50%;" />

定义规则：

1. 小函数想成为内联，直接在类中定义即可
2. 大函数应该声明和定义分离
3. 类定义了一个新的作用域，类的所有成员都在类的作用域中，在类外定义类成员变量需要使用作用域解析符号：：指明该类型属于哪个类域。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719151225163.png" alt="image-20220719151225163" style="zoom:50%;" />

否则将在局部找，全局找，找不到就报错



类的实例化

类在头文件中的函数和变量具有不同属性，类中的函数带分号的成员都是函数或变量的声明，告诉编译器将会在主调函数中用到这些成员函数和变量，因为在头文件中这些函数或变量都没有实际开辟空间，所以都是声明。而在外函数中引用这些成员函数和变量时实际开辟内存空间了，就是类的实例化。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719170733371.png" alt="image-20220719170733371" style="zoom:50%;" />

比喻来说，头文件中的类就是一张设计图，类的实例化就是由类实际开辟建造出的房子。虽然头文件中的类没有具体的空间开辟，但是是可以提前算出总大小的（sizeof）：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719171953581.png" alt="image-20220719171953581" style="zoom:50%;" />

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719171928817.png" alt="image-20220719171928817" style="zoom:50%;" />

注：头文件中的全局变量使用extern来让定义转声明，否则将重定义；也可以在头文件给变量前加上static静态属性，仅当前文件可见，其他cpp文件如果要引用也要单独加extern。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719172830790.png" alt="image-20220719172830790" style="zoom: 67%;" />

链接属性不一样，全局变量在头文件中的符号表相同，且所有文件可见，所以每个文件去头文件拿数据时去符号表找，找到的都是同一个；但静态全局不会放进符号表里，所以每个文件去头文件拿的静态全局都不是同一个，各是各的。



类对象模型

如何计算类对象的大小

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719173436669.png" alt="image-20220719173436669" style="zoom:50%;" />

得到字节为：1

结论：不计算成员函数，计算成员变量

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719174144241.png" alt="image-20220719174144241" style="zoom:50%;" />

存储解释：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719174239666.png" alt="image-20220719174239666" style="zoom:50%;" />

将成员函数存放在公共代码区，在编译链接的时候就确定好类中各函数的地址，无论后续被哪个类实例化对象所访问都能将函数指针提供给它并及时访问：

![image-20220719174957415](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719174957415.png)

而成员变量由类实例化对象直接在主调函数中定义就可以使用，头文件中的类中的所有都是声明。声明不会将数据进符号表，定义才会进。

例2：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719175654982.png" alt="image-20220719175654982" style="zoom:50%;" />

字节为：8——内存对齐

例3：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719202520727.png" alt="image-20220719202520727" style="zoom:50%;" />

没有成员大小的类对象，给1字节站位，标识类对象存在，但不存储实际数据



C++命名规范：

类中private的成员变量一般在变量名前或后加下划线"_"，以区分成员函数的参数，看下例：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719203109230.png" alt="image-20220719203109230" style="zoom:50%;" />

驼峰法——单词与单词之间首字母大写间隔

分割法——单词全部小写，单词间以下划线分割

函数名，类名等所有单词首字母大写

变量首字母小写，成员变量首字母前加_



this指针

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719204650958.png" alt="image-20220719204650958" style="zoom:50%;" />

如果两个类对象分别调用了类中的相同成员函数，则在函数公共区的函数参数如何识别不同的类传来的不同参数？

![image-20220719210357688](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719210357688.png)

this指针默认隐藏在类成员函数的首成员中，每次函数传参调用时，都会将调用对象的类取地址并传参给this指针，让其知道是谁在调用它并正确接收参数。

this指针存在哪里？

存在栈上，因为它是函数中的一个形参，计算类大小时不将this指针计入大小。vs下传递this指针是通过ecx寄存器传递，这样this访问取类对象地址可以提高参数传输效率（传递优化）。

看下例，编译链接时将p的地址值传递给this指针，即空指针，但空指针不解引用，而是直接call了类函数，所以正常运行

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719205532823.png" alt="image-20220719205532823" style="zoom:50%;" />

例2：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719205947482.png" alt="image-20220719205947482" style="zoom:50%;" />





---

默认（缺省）成员函数（6个）



构造函数——用于初始化函数

构造函数可以由用户显式定义，也可以由C++编译器本身自动生成一个无参的默认构造函数，若前者构造完成，后者不再构造。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719213611669.png" alt="image-20220719213611669" style="zoom:50%;" />

构造函数特殊在，不能以普通函数的定义和返回规则去理解和定义该构造函数

![image-20220719214252990](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719214252990.png)

可以结合==全缺省参数==使用默认初始化的构造函数，这样不传参或传部分参或全部参数都可以调用：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719214945211.png" alt="image-20220719214945211" style="zoom:50%;" />



例2：栈的构造函数

遵循构造函数建造规则：函数名与类名相同，无返回值，缺省参数

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719215334896.png" alt="image-20220719215334896" style="zoom:50%;" />

效果：

![image-20220719215452157](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719215452157.png)



如果用户不显式建立构造函数，则默认生成的无参构造函数可以初始化吗？

![image-20220719220018567](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719220018567.png)

C++类型分类，分为

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719220357365.png" alt="image-20220719220357365" style="zoom: 67%;" />

由系统隐式生成的构造函数堆内置类型的数据不初始化，但自定义类型会自动调用其默认构造函数：

![image-20220719221701768](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719221701768.png)

例2：

对于Time类：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724143128952.png" alt="image-20220724143128952" style="zoom:50%;" />

调用系统的无参默认构造函数观察是否被系统默认构造初始化：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724142810263.png" alt="image-20220724142810263" style="zoom:50%;" />



可看到，仅有用户自定义类型成员会被提前声明的缺省值初始化为0，而其他内置类型则不初始化。如果将Time换做Time*的指针类型，因为指针也是内置类型，不管什么类型的指针都是内置类型，所以不会被初始化 

C++11打了个补丁，可以给类成员变量设置默认缺省值，以调用默认构造函数时可以默认初始化自定义类型和内置类型数据：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719221332941.png" alt="image-20220719221332941" style="zoom:50%;" />

效果：

![image-20220719221444844](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719221444844.png)

而如果栈的类内部将用户显示定义的构造函数屏蔽：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719222803339.png" alt="image-20220719222803339" style="zoom:50%;" />

则当调用队列的时候：

![image-20220719222954064](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719222954064.png)

![image-20220719223124717](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719223124717.png)



总结：默认构造函数由三类

1. 编译器隐式自动生成的默认无参构造函数
2. 用户显式生成的全缺省的默认构造函数
3. 用户显式生成的无参的默认构造函数

注意：默认构造只能存在一个，且用户生成的默认构造和系统生成的无参默认构造是互斥的。如果用户自己创建了默认构造函数，但是参数的配置没有按照上面的要求来，即没配置缺省或无参的形式，而只是设置了参数，则会出现编译报错：

例1：Time类

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724143442477.png" alt="image-20220724143442477" style="zoom: 50%;" />

在用户显性定义的默认构造函数中加入了参数定义，而不是无参或全缺省的情况下，函数编译显示没有合适的默认构造函数可用，因为用户自己定义了一个默认构造，所以系统不会自己又构造一个，但用户自定义的这个又是非法的，所以编译报错。

例2：栈类

![image-20220719223631253](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220719223631253.png)

注意2：调用的二义性

如果用户手动配置了默认构造函数，且无参默认和全缺省默认构造进行了函数重载，则当用户仅调用函数而不传参时会出现歧义（下图中的d1情况），系统将不知道调用无参默认构造还是全缺省默认构造，将会编译报错；而如果调用d2函数，虽然传了参数一定调用的是全缺省的默认构造函数，但编译器仍会报警告，说存在多个默认构造函数导致的歧义性。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724141722223.png" alt="image-20220724141722223" style="zoom:50%;" />

所以最好不写为无参默认构造函数，而是最好写为全缺省参数的默认构造函数



总结——默认构造函数特点：

1. 不穿参数就可以调用
2. 无返回值
3. 一般的类都不会让编译器默认生成无参构造函数，最好是自己写一个全缺省的默认构造函数，这样能让内置类型都初始化。
4. 只有特殊情况才会用到系统自动生成的默认构造函数



实例运用：

![image-20220725220903333](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725220903333.png)



---

析构函数

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724145022188.png" alt="image-20220724145022188" style="zoom:50%;" />

注意：析构函数不是负责数据对象的销毁，而是随着函数栈帧的销毁而消失；而析构函数在对象销毁时会调用该函数，进行打扫工作。

每个函数在函数销毁，对象销毁后如果没有用户显示定义的无参无返回值无重载的析构函数，都会由系统默认生成并调用对应函数的析构函数，但在用户看来是看不见摸不着的，如果用户自己定义了，在里面加上一句printf打印就可以验证确实调用了析构函数。

对于一般的函数而言（比如上例的日期类），因为数据量少，且都是栈区开辟的临时形参变量，所以虽然调用了析构函数，但是没有清理的价值，如果IDE优化的厉害甚至会将析构函数直接优化掉。

实际意义：

对于用户显性开辟的内存空间，如栈的顺序表空间开辟，链表的结点空间开辟等，如果用户在调用函数结束后忘记释放开辟的内存空间，则析构函数会在函数结束后自动调用，并帮助用户及时清理函数调用结束后没有及时清理的内存空间

![image-20220724150715456](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724150715456.png)

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724151310474.png" alt="image-20220724151310474" style="zoom: 67%;" />

同构造函数一样，析构函数也是类中特殊的成员函数，写好后会被系统自动调用（默认构造函数会自动初始化自定义类型数据，而析构函数会自动在函数被销毁时清理用户动态开辟的空间（堆上））。

而如果用户不显式定义析构函数，则会有系统生成默认析构函数，其主要作用是：

1. 与构造函数类似，内置类型不清理（比如指针（不指向开辟空间的指针）），只清理自定义类型成员，才会去调用这类成员的析构函数。

![image-20220724152912357](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724152912357.png)

所以涉及到空间开辟的函数需要手动去写析构函数，用以被自身自动调用释放空间或放在其他类中作为成员函数时被其他函数的默认析构函数自动回掉手动写的析构函数以及时释放空间。



注意点3——析构与构造函数的顺序不同

![image-20220725093327702](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725093327702.png)

两个类调用时，默认构造函数与调用顺序相同，而析构函数则是先执行的后调用，后执行的先调用，这与它们的函数栈帧有关，如上图。且在此过程中，析构函数不是负责栈帧空间的销毁和返还，而是负责待销毁栈帧空间中用户显示开辟的堆空间内存，完成及时的释放再让寄存器变量控制移动内存单元销毁栈帧返还内存。

例2：全局类和静态局部类

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725094654617.png" alt="image-20220725094654617" style="zoom:67%;" />

全局在main调用前就存入静态区，后续默认构造开辟保持相对顺序，而main函数调用结束时，析构函数先对栈区的空间随诊栈帧的销毁同时进行堆数据的清理，所以处于栈上的1和2满足后进先清理的相对顺序，而处于静态区的三个静态和全局变量也遵守栈的压入和清理规则，也是后构造的先清理，所以304的压入静态区顺序，以403的顺序析构清理。

例3：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725095910276.png" alt="image-20220725095910276" style="zoom:50%;" />

静态区构造只会在第一次函数调用创建，后续对于相同静态类不会再创建，全局同理，构造和析构顺序如上。





总结：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724154455203.png" alt="image-20220724154455203" style="zoom:67%;" />

析构就是构造的反，构造用于初始化，析构用于清理内存；构造进入函数自动调用初始化，析构出了函数作用域，自动调用析构函数。



---

拷贝构造函数

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724155017442.png" alt="image-20220724155017442" style="zoom:50%;" />

拷贝构造是默认构造函数的重载，它们以参数进行区分：

![image-20220724164456683](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724164456683.png)

注意：必须传类对象的引用，如果传值传对象会无穷递归导致报错，解释：

![image-20220724162541398](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724162541398.png)

解决方法1——引用

引用实参，因为形参是实参的别名

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724162752806.png" alt="image-20220724162752806" style="zoom: 67%;" />

注意：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725101450996.png" alt="image-20220725101450996" style="zoom:50%;" />

aa1在进入主函数已经默认构造了。此时调用两个函数分别将该类对象传参：如果选择传值传参的方式，则参数会进入函数中，因为传值的形参是实参的临时拷贝，所以对于该拷贝的形参同样需要默认构造，拷贝构造以及出了函数栈帧时需要清理数据，对于函数而言如果该类本身就很大，则经过拷贝和构造的开销就很大。而如果选择传引用传参，则参数只是实参的别名，则因为之前已经构造过一次，且无需拷贝构造，所以只需要在出函数进行一次析构函数即可。

解决方法2——地址

![image-20220724163057084](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724163057084.png)

传引用比传指针更好，因为拷贝构造函数规定其中的唯一一个参数必须是类名，而不是类指针，如果传类的地址给拷贝构造函数，虽然也能达到同样的效果，但是不符合官方对拷贝构造函数的要求规范：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724163250536.png" alt="image-20220724163250536" style="zoom:50%;" />

特别是对于拷贝构造传参的另一种用法，如下图所示：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724163614442.png" alt="image-20220724163614442" style="zoom:67%;" />

上图汇总前两行的写法是等价的，都是传d1引用的拷贝构造，而三四行传地址的拷贝构造虽然也都能达到效果，但没有传引用那么好理解了。



传引用返回比传值返回更好

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725102740669.png" alt="image-20220725102740669" style="zoom:50%;" />

不需要像func3那样返回时再将形参拷贝一份给临时的返回值，且返回给实参后马上将临时拷贝构造的aa析构掉。而func4的传引用返回是直接返回静态类引用给实参，无需拷贝构造给临时返回值且无需额外析构

总结：无论是传引用传参还是传引用返回都比传值更高效，特别是对于自定义的类，无需额外默认构造，且无需拷贝构造和额外析构，就可以实现等价的功能。而唯一需要注意的点是如果函数中需要返回的自定义类对象不是静态的，会随着函数的销毁而析构掉，则这时返回的形参别名是有问题的，如果空间清理可能会置成随机值：

![image-20220725103802409](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725103802409.png)



注意点2：const修饰拷贝源

如果程序员在定义拷贝构造函数时不小心将拷贝源与拷贝对象写反了，导致待拷贝的随机值通过别名的类对象拷贝回去，就造成了实参也同样被无意义的随机值修改了

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724200830875.png" alt="image-20220724200830875" style="zoom:50%;" />

函数在定义和赋值上是没有问题的，因为不存在编译错误，所以导致了如下情况：

![image-20220724201031156](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724201031156.png)

可见，本来想将自身类中的值拷贝给被人，反倒被被人数据给覆盖了，解决此问题可以通过给拷贝构造的参数加上const修饰，以禁止对引用的类对象通过别名修改实参值：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724201204214.png" alt="image-20220724201204214" style="zoom:50%;" />

如果用户自己不生成定义拷贝构造函数，由系统默认生成，其用途在于：

![image-20220724202028281](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724202028281.png)

即内置类型，自定义类型都会被系统自动生成的拷贝构造函数处理：

![image-20220724202325807](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724202325807.png)

但在某些场景中，默认构造的拷贝函数因为对内置类型是直接按字节拷贝的，所以对于下列的栈拷贝上，对栈的数组指针进行直接拷贝给另一个栈指针，即两个指针指向了同一块数组内存空间，其他内置类型如int size和capacity都完成了拷贝，但在栈销毁时由于用户定义了析构函数，两个指针指向了同一块空间，所以进行了两次free，此时就会报错：

![image-20220724202600662](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724202600662.png)

解释：

![image-20220724203247580](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724203247580.png)

所以拷贝构造自定义类型需要以深拷贝的方式实现，而对内置类型则直接按字节拷贝即可

应用场景：

用于类的拷贝





---

运算符重载

![image-20220724204213813](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724204213813.png)

编译器知道如何让内置类型之间进行运算，但不知道对自己定义的类之间进行运算，比如日期间，让编译器知道自己定义的类型如何进行运算，就是运算符重载。

运算符重载也是特殊的函数，

private成员不能在类外部被直接访问

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724205132152.png" alt="image-20220724205132152" style="zoom:50%;" />

可以屏蔽private，就可以得到公开的参数，而调用的具体操作如下

![image-20220724205631692](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724205631692.png)

上述两种流输出是等价的，第一种为第二种的运算符重载转换，即用户输入第二种类的自定义运算，则系统在编译阶段自动转换为第一种，其本质是==调用了运算符函数==。写第二种的意义就在于，将类就可以像内置类型一样进行运算了，代码可读性和可维护性更好。

注意1：常量引用

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724210403203.png" alt="image-20220724210403203" style="zoom: 67%;" />

因为运算符重载本质上是一个函数，所以为了防止类过大导致传参拷贝栈溢出，所以使用引用的方式进行传参，而一些运算函数不需要对数值本身进行修改，比如类之间的加减乘除等对类本身数据不能修改，仅仅需要计算结果并返回值，所以带一个const修饰以免代码疏忽和误操作对实参进行了修改。

注意2：private无法访问

运算符重载函数时类之间的运算，但实质上是类的private成员间内置类型数据的比较，所以为了规避private成员无法访问问题且不让private公开，可以直接将运算符函数放入class类中，这样private的作用域就能给运算符函数共享了：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724211647493.png" alt="image-20220724211647493" style="zoom:50%;" />

而对于运算符函数的调用就变成了this指针指向的类中的函数公共区的问题了：

![image-20220724211744011](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724211744011.png)

同时还需注意，域限定符：：只是为了让一个函数的public成员找到它是在哪个类的，而不能让它访问类中的private私有域，因为private成员变量仅仅只对类的作用域中有效。



<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724213756038.png" alt="image-20220724213756038" style="zoom:50%;" />

该函数会被频繁调用，所以放在类中作为内联函数使用，其中数组每次都会被开辟和使用到，所以加上一个static作为静态区数组就不需要每次到堆区开辟了。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724213410108.png" alt="image-20220724213410108" style="zoom:50%;" />

代码：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724214315979.png" alt="image-20220724214315979" style="zoom:50%;" />

结果：

不对原日期本身改变的情况下，通过拷贝构造函数将返回值拷贝到一个新的类对象上，实现了类与内置类型的运算

![image-20220724214407315](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724214407315.png)

如果要求让日期自身改变，改变做出如下变化（不定义返回的类）

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724214521660.png" alt="image-20220724214521660" style="zoom: 50%;" />



注意点3：传引用返回和传值返回

![image-20220724214809404](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724214809404.png)

前者可以传引用返回，因为对的是类本身修改，而第二种只能用传值返回，因为是在函数中定义的形参类，出了函数作用于就销毁，得到的引用将是随机值。

还需注意，第二种中的Date ret(*this)是拷贝构造，而不是赋值运算符，因为赋值运算符只针对两个已存在的类，而ret是新创建的类，由传参 * this拷贝给，它的写法等价于：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725135429898.png" alt="image-20220725135429898" style="zoom:50%;" />

类作为一个整体在头文件中的前后顺序不重要，因为它会上下搜索，不必担心前后顺序问题

结果验证

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725140346143.png" alt="image-20220725140346143" style="zoom: 67%;" />



---

赋值运算符重载

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725104152943.png" alt="image-20220725104152943" style="zoom: 67%;" />

赋值运算可以对类之间如同内置类型赋值那般的操作：

![image-20220725111311704](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725111311704.png)

本质是编译器在翻译时写成了上图注释的形式，通过this指针将两个参数传入类中，然后获取private变量信息来逐个赋值日期，再通过加入赋值完成后的本值类对象，即this指向的被赋值类即可支持连续赋值：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725112208644.png" alt="image-20220725112208644" style="zoom:50%;" />

因为this指针指向的是类外面的对象，所以出了该赋值运算符函数，*this指向的类空间仍然存在于外部，所以可以用传引用返回，因为这块空间不会被销毁。（如果传值返回将会拷贝构造并析构）

优化：相同类自己赋值

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725113024078.png" alt="image-20220725113024078" style="zoom:50%;" />

加一个if判断如果自己赋值自己，则不执行赋值操作。



默认赋值运算符重载

![image-20220725113400027](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725113400027.png)

内置类型直接拷贝，自定义类型调用赋值运算符重载，观察：

![image-20220725113910336](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725113910336.png)

year, month, day都是int类型，在Date类中没有写运算符赋值重载，所以直接调用d2 = d1 = d3时会对每个类中的数据直接进行数据赋值，而此时在类Date的private中加入了自定义类型Time：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725114252910.png" alt="image-20220725114252910" style="zoom:67%;" />

而对于自定义类型，默认的赋值运算符重载会去调用自定义类中的运算符重载函数，如果有就按照其中的规则赋值，没有就不做处理（本例中Time类型中也都是内置类型，所以不写赋值重载也可以)。

而对下面这种情况，就必须自己手动写赋值运算符重载了：

![image-20220725114505736](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725114505736.png)

可以看到，指针的浅拷贝会造成两个栈指针指向同一块空间，且析构时同一块空间会被释放两次，造成编译器报错。



而对于其中的成员类已经定义了默认成员函数的类而言，就不需要多余定义了：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725114757589.png" alt="image-20220725114757589" style="zoom:50%;" />



默认成员函数总结：

![image-20220725115449457](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725115449457.png)





---

实例——日期类

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725121702074.png" alt="image-20220725121702074" style="zoom:50%;" />

先实现两个（放在类中当做内联函数，因为需要被其他复用重载函数频繁调用），其他的直接重载（不放在头文件的类中，而放去函数cpp中，当做普通函数看待），复用重载的本质上是递归。

效果：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725121942100.png" alt="image-20220725121942100" style="zoom:50%;" />

一般定义运算符重载，是根据需求和对数据的比较和运算有意义才定义运算符复用重载，比如日期里对比大小没有太大意义，而一般使用日期加上几天或减去几天，可以计算出几天后的日期后多久之前的日期才是有意义去运算和复用重载的。

所以定义+=天数和+天数运算符函数（+=天数已由上图给出，此处定义+天数是由+=天数函数重载俄日来）：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725140756417.png" alt="image-20220725140756417" style="zoom:50%;" />

如果想由日期+来实现日期+=运算符重载，也能做得到，但是效率会低很多：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725141348449.png" alt="image-20220725141348449" style="zoom:50%;" />

发现对比+=实现+的两次拷贝构造，用这种方法还多出来一次赋值重载，效率变慢一点。



前置后置自增函数重载在类中的声明：

![image-20220725142015925](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725142015925.png)

下图左是主函数中调用的，实际上编译器看到的自增（右边翻译成的是取该类的this指针和传参不同类型区分两个自增重载函数）：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725142841269.png" alt="image-20220725142841269" style="zoom:67%;" />



函数实现：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725142231798.png" alt="image-20220725142231798" style="zoom:50%;" />

结果：

![image-20220725142530546](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725142530546.png)



计算日期减天数：

由-=实现-的重载

![image-20220725145245341](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725145245341.png)

结果：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725145511792.png" alt="image-20220725145511792" style="zoom: 50%;" />





前置后置自减

前置--使用-=函数重载实现，传引用返回；后置--

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725145744683.png" alt="image-20220725145744683" style="zoom:50%;" />





计算日期差：两个日期类相减，得到天数差

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725143128878.png" alt="image-20220725143128878" style="zoom: 67%;" />

为了定义日期差函数，有几种方法：

1. 分别减年，月，日再换算成天的方法，最后相加得到总天数
2. 深度重载复用之前写过的拷贝构造，赋值运算符重载等其他函数，通过让较小的日期自增重载到更大日期，每自增一天，计数n+1，当达到目标日期时，就得到了总天数。

![image-20220725152842755](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725152842755.png)



优化2：构造函数

如果初始化的日期不合法，就会导致后序运算出现不想要的结果：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725154033781.png" alt="image-20220725154033781" style="zoom:50%;" />

日期警告函数（放在内联里，因为每构造一个日期都要检查依次）：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725154639079.png" alt="image-20220725154639079" style="zoom:50%;" />

调用时可采用温和的if+cout方式提醒，也可以直接采用函数返回的布尔值调用assert暴力断言。



优化3：加一个负数天，在+=函数里进行改造

将日期对自己的修改变为-=，同时将传参的天数置反，即减去那么多天

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725160038406.png" alt="image-20220725160038406" style="zoom:50%;" />

对-=的负数天减去也做同样处理即可

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725160404109.png" alt="image-20220725160404109" style="zoom:50%;" />



优化4：流插入运算符支持自定义类型Date的打印输出

因为cout是ostream类中的库函数，我们不能对该类中的cout进行其他自定义类型的函数和运算符重载修改，所以可以在自己的Date类中重载一个cout函数以供使用：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725164236920.png" alt="image-20220725164236920" style="zoom:67%;" />

可以发现，通过正常的流插入运算无法实现日期的输出打印，而通过解构该重载函数，因为该函数是在Date类中声明的，而Date对象d1必定会作为第一个参数由this指针传参进入，而cout作为第二个参数，所以调用时必须由cout流入d1中，此种写法意义不明，可读性差：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725163514760.png" alt="image-20220725163514760" style="zoom:50%;" />

解决方法：

在Date类的外面定义和声明单独的函数流插入重载，将Date类对象的传参放在流插入对象之后，即可将流插入作为第一个参数，从而在该打印函数调用时就可以按照正常顺序书写：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725164503862.png" alt="image-20220725164503862" style="zoom:67%;" />

但是该方法无法访问d中的private成员，解决方法为==友元函数==：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725164853608.png" alt="image-20220725164853608" style="zoom:67%;" />



就可以让cout输出自定义类型了，但还存在一个问题，如果多次调用流插入符（像内置类型那样），则无法支持：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725165156584.png" alt="image-20220725165156584" style="zoom:50%;" />

解决方法：返回值为cout

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725165641155.png" alt="image-20220725165641155" style="zoom:50%;" />

解释：

![image-20220725165504373](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725165504373.png)

友元，函数声明都需要改。该函数不在类中，但又需要频繁调用，所以手动设置为inline内联函数，并且声明与定义不应该分离，都放入头文件中：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725165932718.png" alt="image-20220725165932718" style="zoom:50%;" />



优化5：通过日期计算周几

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725205830060.png" alt="image-20220725205830060" style="zoom: 67%;" />

先算出目标日期与公元1年1月1日相差多少天，已知1年1月1日为周六，所以算出相差多少天后需要再加上0，这个0代表的是周一，因为如果差距天数直接模7的话范围时0~6，所以实际上0代表周一，1代表周二...5代表周六，6代表周天，所以相差天数加上本来的0代表的周一，最后模7再加1，就能把周期范围控制在1-7之间。（起始时间元年周期数不确定）

打印出来有周7，很不好看，可以创建静态数组来映射打印

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725210529091.png" alt="image-20220725210529091" style="zoom:50%;" />

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725172100449.png" alt="image-20220725172100449" style="zoom:50%;" />

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725171743445.png" alt="image-20220725171743445" style="zoom:50%;" />

有了流插入，同样可以构建流提取重载函数，用于支持Date类型的输入>>

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725170917103.png" alt="image-20220725170917103" style="zoom:50%;" />

为了防止输入的日期不合法，加上断言检查日期合法性就可以。加上友元后，就可以正常访问Date类中的私有成员了，而且可以注意到Date引用不需要加const修饰了，因为需要对日期本身进行流提取修改插入

流提取输入后再流插入打印结果：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725170812292.png" alt="image-20220725170812292" style="zoom:50%;" />

注意，流提取每个数据间都以空格间隔，或已回车间隔都是可以的，如同scanf一致。

并且观察到，cout和cin都能连续流插入或流提取不同类型的数据，如Date流的d1或内置类型的day，这是因为流插入或提取是自左向右运算的，每调用完一次函数，返回istream或ostream的引用，这样就可以继续下一次流的函数重载继续调用了，各数据间对流的函数调用都是独立不相干的：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725171556418.png" alt="image-20220725171556418" style="zoom:50%;" />





总结：

关于流提取和流插入可以自动识别类型，是因为IO流库函数中已经给用户定义好了重载函数，所以表面上看起来是自动类型识别的，而函数重载又是通过函数名修饰规则来区分的：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725161042586.png" alt="image-20220725161042586" style="zoom: 50%;" />

解释：

![image-20220725161604292](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725161604292.png)

2. ![image-20220725211402032](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725211402032.png)

3. const修饰的this指针

现象：

![image-20220725213409295](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725213409295.png)

加上const

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725213246145.png" alt="image-20220725213246145" style="zoom:50%;" />

结果：

![image-20220725213431333](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725213431333.png)

总结：

只有指针之间存在权限的放大和缩小，比如int i = 10不是权限的放大，因为i的修改不会影响常量10，而int& i = 10是对常量10权限的放大，对i造成的修改会影响10，而10不能从常量放大成为变量，所以是非法的。

所以类中的成员函数，在不修改传参值的情况下最好都加const给this指针和参数，因为如果是普通的传参只是权限的缩小，且不会对传参本身造成结果的改变，而如果传参const类就调不动函数了，因为涉及到权限的放大。而如果是涉及到传参值自身的修改则不能加const，否则常量类权限放大需要修改参数值将会报错：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725214201184.png" alt="image-20220725214201184" style="zoom: 67%;" />

给this指针加const禁止修改this解引用值的方式就是在函数参数后，分号前加const即可。

解释：

![image-20220725214436136](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725214436136.png)



取地址及const取地址操作符重载

对于类中的两个函数，有和没有const修饰的两个同名函数是可以同时存在的，因为它们构成了函数重载，编译器会给调用同名函数的实参寻找最匹配传参的那一个函数：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725215357346.png" alt="image-20220725215357346" style="zoom: 67%;" />

如果用户不显式定义有和没有被const修饰的取地址运算符重载函数，系统也会默认生成该默认取地址运算符重载：

![image-20220725220006913](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220725220006913.png)