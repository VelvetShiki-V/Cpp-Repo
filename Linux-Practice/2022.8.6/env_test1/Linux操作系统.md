Linux操作系统

操作系统给用户提供了一个稳定，安全，简单的执行环境



![image-20220801213943236](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220801213943236.png)

存储器可以缓解整个计算机体系的木桶效应，使CPU从磁盘拿取数据的低效转移到内存上

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220801214418266.png" alt="image-20220801214418266" style="zoom:50%;" />

IO流

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220801215458548.png" alt="image-20220801215458548" style="zoom:50%;" />



冯诺依曼机信息交互

![image-20220801220610024](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220801220610024.png)



操作系统的本质：先描述，再组织

描述：用struct结构体，描述一个进程

组织：用数据结构等高效的数据结构，将所有PCB结构体连接起来

操作系统是对软硬件进行管理的，管理是对被管理对象的数据进行管理，类比于学校中校长（操作系统）对辅导员（驱动软件）和学生（硬件）的管理，以及银行中行长（操作系统）对经理（驱动软件）和业务人员等公司设施（硬件）的管理。管理是做决策的，而软硬件是具体执行的。linux内核是用C语言写的，其中包含大量的struct，以及各种数据结构。

对操作系统的访问只能通过系统接口，因为操作系统不信任任何人

![image-20220802110700982](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802110700982.png)

操作系统内核是接口之下的一批操作系统内部的主体。操作系统包含的主体可以分为内核，各种对外的接口，以及库和外壳。在操作系统OS学科中，其主要指的是内核。



---

进程

linux下运行一条指令，就是在系统层面创建一个进程。Linux可以同时加载多个进程，可能同时大量存在进程在系统中（OS,内存）。linux管理进程的方式为先描述，再组织。

进程——进程对应的代码和数据，以及一个进程匹配的数据结构PCB结构体（描述），这两个统称为进程。

![image-20220802114211940](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802114211940.png)

一旦一个应用运行起来，PCB对该应用进程的的描述是新增的。然后再将左右PCB连接起来就是组织。当一个进程被建立起来时，应用程序的所有数据信息和其对应的PCB结构体统称为一个进程，当一个进程结束时，其包含的所有数据数据信息和其对应的PCB进程属性都释放才是进程的结束。



PCB——Process Control Block

进程控制模块，是一个结构体struct，在不同的OS中，PCB名字不同。在linux中称为struct task_struct，它是linux内核的一种数据结构，当进程加载时会被装载到内存RAM里并包含进程的所有属性信息，这是堆对进程的描述。通过链表将所有test struct的PCB结构体链接（双向链表）起来，就是对所有进程的组织。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802115543649.png" alt="image-20220802115543649" style="zoom:50%;" />



进程指令

ps——仅查看当前终端下对应的进程（常用）

ps axj——查看所有进程，其中a表示all，xj表示所有进程信息，如果要查看目标进程信息，通过管道和筛选来完成

ps axj | grep 'exe文件名'——查看目标进程的信息

ps axj | head -1 && ps axj | grep 'exe文件名'——带头部查看目标进程信息，其中PID表示进程ID编号，当逻辑与符号左侧执行成功时才执行右侧指令

top——可以查看linux系统中所有进程，类似于windows资源管理器，输入q退出

ls /proc——以文件查看所有进程的内存占用和进程信息

kill -9 [进程PID]——将正在执行中的进程关闭



查看当前可执行程序的进程PID

```c
//系统调用头文件
#include<sys/types.h>
#include<unistd.h>
//获取PID
pid_t id = getpid();
printf("PID:%d", id);
//使用进程监视指令观测是否为PID所属进程
ps axj | grep '可执行程序名'
//或包含头部信息进程指令的
ps axj | head -l && ps axj | grep '可执行程序名'
```

![image-20220802144204129](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802144204129.png)

cwd是进程运行时所在路径（工作路径）



获得父进程PPID（shell外壳进程BASH，通过shell来执行子进程）

```c
getppid();
```

![image-20220802144914561](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802144914561.png)

如果将该父进程关闭，即将外壳进程关闭，则用户不能公国shell来控制操作系统。而等到用户下一次登录，系统由默认开启另一个PPID不同或相同的进程提供==shell开启子进程服务==对接用户使用



创建一个子进程fork

```c
//头文件
#include<unistd.h>
//函数
pid_t fork();
```

该函数具有两个返回值：

当子进程创建成功

1. 给父进程返回子进程的PID
2. 并给子进程返回0

当子进程创建失败，返回-1

验证fork的父子进程关系（fork之后，父子进程是代码共享的）

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802152111093.png" alt="image-20220802152111093" style="zoom: 67%;" />

fork用法

1. 让父子进程执行不同代码——两个进程同时运行，同时if判断，同时执行while循环。可以通过if的PID判断，使父子进程实现分流，在同一个源文件的exe中执行不同的功能。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802162725644.png" alt="image-20220802162725644" style="zoom:50%;" />

检测代码：while :; do ps axj | head -1 && ps ajx | grep myproc | grep -v grep; sleep 1; echo "##################"; done

![image-20220802162826545](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802162826545.png)

![image-20220802204235560](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802204235560.png)

意义：

1. fork之后，产生两个不同的执行流。（id在父进程中是子进程的PID，在子进程中是0）
2. 一个变量在同一份C语言代码中会有不同的值。



为什么给子返回0，给父返回子的PID？

给父进程返回子进程的PID，是因为要让父进程知道有哪些子进程是在自己的管辖范围内，因为要通过编号管理这些进程，所以需要确切知道它们的PID。而子进程仅需要得知自己有没有在fork之后从父进程中分离并成功创建出来，返回0即成功创建，否则返回-1。



为什么fork有两个返回值？

![image-20220802170207513](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802170207513.png)

因为fork执行的时候，子进程以父进程模块信息为模板，创建了一个进程的同时也生成了一个PCB结构体，此时就有两个进程在代码中同时执行，且该两个进程是父子关系，即多进程。又因为是同一份代码的两个进程，所以后续代码如果不使用以if判断id进行父子区分，则开放的代码将分别会被父进程和子进程执行依次，且执行顺序是不确定的，有可能父进程跑一段时间就被放到队尾，转而执行子进程，或相反，是由OS的调度器决定的。因为是两个进程对应的两个代码，所以return也会被执行两次，就会有两个返回值。

进程调度队列解释：

![image-20220802170632123](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802170632123.png)

CPU执行系统进程，其实本质上是对每个进程的PCB结构体模块对应的进程发起控制，从其中取出该进程的相关信息并发出命令来执行，且这个执行是有顺序的，即PCB被组织的过程是通过数据结构的链表等，结合运行队列来完成



---

进程状态

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802220054774.png" alt="image-20220802220054774" style="zoom:50%;" />

创建：将PCB结构体新建，但是一般新建出来马上入运行队列，所以直接进入了运行状态

运行（R）：task struct结构体在CPU的等待执行运行队列中排队，称为运行态

阻塞（S）：等待非CPU资源就绪（比如scanf等待键盘输入的进程就是阻塞状态，或程序卡死）。系统中存在多种队列，CPU准备执行的进程模块PCB为执行队列，等待磁盘资源和CPU资源就绪的队列为阻塞队列

进程睡眠（D）：磁盘睡眠，或进程深度睡眠，该进程不可被kill唤醒；一般该状态涉及到的进程与磁盘数据写入或读取有关，操作系统无法再内存压力过大时结束该进程，甚至用户主动使用kill -9也无法结束该进程（可使用dd命令模拟D状态）。

调试暂停状态（t）：调试运行到断点处的进程状态，此时进程暂停。

进程暂停状态（T）：使用kill -19 [PID]使进程暂停，此时状态为T；再通过kill -18 [PID]使进程继续。

![image-20220802215355874](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802215355874.png)

终止状态（X）：当进程停止准备被OS回收，但OS还没回收到该进程的状态就是终止状态。但是由于OS速度非常快，所以用户几乎很难捕捉到该状态，但其实是存在的，其瞬时性非常强。

僵尸状态（Z）：一个进程因为某种原因已经退出（代码和资源被释放），但（描述进程的PCB结构体）还不允许被OS释放，处于一个被检测的状态。一般由父进程或OS来检测该进程的状态。该状态的维持是为了让父进程或OS进行检测并回收。

![image-20220803095554065](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220803095554065.png)

T与S的区别是，前者没有等待非CPU资源，而是用户手动暂停进程；后者一定是等待非CPU资源而被动暂停（阻塞状态）。僵尸状态的危害是内存泄漏。

挂起：当内存不足时，OS通过适当的置换进程的代码和数据到磁盘的SWAP分区上，此时进程的状态为挂起态。等待内存占用小或准备执行时再换回到内存，进入执行队列的运行态。

挂起阻塞：长期等待非CPU资源不执行的进程阻塞态下被OS将struct从内存中置换到磁盘上，两者状态不冲突

![image-20220802200122345](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802200122345.png)

例：代码死循环打印printf和死循环不执行其他操作

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802201623593.png" alt="image-20220802201623593" style="zoom:50%;" />

当死循环执行printf时，该进程状态显示S的阻塞态，因为CPU运算速度极快，而在冯诺依曼体系下对输出流的外设硬件设备的输出速度是远小于CPU的执行速度的，所以死循环打印的大部分是处于等待外设刷新输出的硬件队列，而CPU处理该指令则是很快的，所以几乎没有struct task在执行队列中，就造成了大多数结构体处于阻塞状态下。而后者因为没有对接外设的硬件设备，所以执行速度与CPU运算一致，处于运行态R。

在运行状态后带"+"号，称为前排进程，在此状态下运行的进程占据了bash的shell命令窗口，即用户只能对在该进程下而无法执行其他进程操作，但是可以通过终止指令ctrl c停止该进程（interruptible sleep，可中断睡眠）。如果在指令后加上一个空格及取地址符，就可以让该进程后台运行或后台阻塞，即把"+"号去除，用户可以操作其他进程且不影响该进程的运行，如果想终止该进程就使用kill -9 [PID]即可。

打印printf：

![image-20220802204740596](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802204740596.png)

后台运行：

![image-20220802204902151](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802204902151.png)

kill进程（后台进程）

![image-20220802205443782](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802205443782.png)

如果fork了程序，则此时父和子进程都在执行，且两者独立，将父进程关闭不会影响子进程的继续运行，需要kill两者才会全部关闭进程

![image-20220802205553101](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802205553101.png)

不执行任何指令，死循环（进程在CPU执行队列的运行态）

![image-20220802210520229](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802210520229.png)

后台执行

![image-20220802210650602](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802210650602.png)

kill后台运行的进程

![image-20220802210803031](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802210803031.png)



kill信号

通过kill -1查看所有信号

T中断进程测试

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220802221236040.png" alt="image-20220802221236040"  />



#### 🍧孤儿进程

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220805105923934.png" alt="image-20220805105923934" style="zoom:50%;" />

1号进程就是操作系统，如果一个程序被fork，产生了父子程序，在运行过程中父进程先终止，而子进程没有被终止，则子进程需要被OS领养，此时其PPID变为1号进程，即init的系统进程，由S+装填变为后台S状态，所以ctrl c没用，必须手动kill该子进程。

调试中的代码进程（父子进程）

![image-20220803132704068](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220803132704068.png)

调试结束后，如果代码中存在死循环，将自动结束父进程（使用了fork），而子进程的死循环将会被OS托管，不会被被动kill掉

![image-20220803134441846](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220803134441846.png)

此时需要主动kill -9 [子进程PID]来将其干掉

而将死循环从父子进程中去掉，则随着调试结束，两个进程就自然终止

![fork子进程](C:\Users\Shiki\Desktop\资料\Linux\fork子进程.png)

如果没有fork程序，即仅有当前代码主进程，此时再加入死循环，调试结束后也会自动关闭进程

<img src="C:\Users\Shiki\Desktop\资料\Linux\无fork死循环.png" alt="无fork死循环" style="zoom:50%;" />

![无fork死循环1](C:\Users\Shiki\Desktop\资料\Linux\无fork死循环1.png)

总结

gdb也是一个进程，通过gdb的run命令执行程序并在其中fork的话，如果是死循环，父进程会随着gdb调试结束而随之结束，因为父进程被强制运行到程序终止return 0的地方，所以被kill了。但是子进程不会结束，因为gdb无权结束用户run起来的进程，所以即使gdb调试结束了，子进程因为死循环，并不会被kill，而是需要用户手动kill。如果父子都不是死循环，用户在gdb中打了断点使两者进入僵尸状态但并未结束时，此时退出调试，两个进程同时执行return 0终止进程，所以都会被kill并被OS回收。



---

### 🌠进程优先级

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220805111937940.png" alt="image-20220805111937940" style="zoom:50%;" />

为什么要有优先级？

CPU是有限的，进程太多需要竞争CPU资源，优先级可以用数据来表明和排序。

Linux的优先级做法：

优先级 = 老的优先级 + nice值

![image-20220805113200469](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220805113200469.png)

![image-20220805113255029](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220805113255029.png)



调整优先级指令

进入top系统进程管理器后，输入r打开调度器。

Renice PID [进程PID] to value [新的nice值]——nice值范围从-20~19，输入更大数或更小数都会强制限制在该范围内。注意，系统默认只让普通用户将某个进程的优先级PRI调低（即调大nice值），而不让将nice值设为负数使进程的优先级变高。如果要执行此操作，需要使用sudo打开top进程列表，再调高优先级

新的优先级一定是以默认的老优先级的PRI值开始调的，而不是以当前的优先级值被nice值修正。如一个进程默认优先级值为80，调整nice值到10，则新优先级 = 80 + 10 = 90；设置优先级值为-20，则新优先级 = 80 - 20 = 60；设置nice值为-5，则新优先级值 = 80 - 5 = 75。

优先级设置nice值范围意义：

使每个程序在一定的优先级范围内均衡排序，防止恶意程序无限将优先级调高，占用系统资源导致系统变慢变卡。

![image-20220805114858140](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220805114858140.png)

---

### 🌠环境变量

![image-20220805114931572](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220805114931572.png)

企业的服务器一般有==多个CPU构成==，这些CPU同时工作，同时处理不同的进程，称为==并行==。

一般的家用电脑CPU只有一个，而一个CPU也需要多进程处理，每个进程的PCB排成队列，依次执行，只不过每个PCB对应的进程都有==时间片==来约束每个进程占用CPU资源的时间，比如10ms左右，不会等到一个进程的所有任务处理完了再到下一个进程，因为那样会造成系统工作效率极低，且容易被恶意进程长时间占用CPU使操作系统卡死。这样短时间段内看起来同时执行多个进程的过程就叫==并发==。

服务器并行中的多个CPU的每个CPU也采用并发模式。

抢占：如果一个进程正在其时间片当中占用着CPU资源，此时一个更高优先级的PCB进程想使用CPU资源，而低优先级==出让==给高优先级进程的过程，就是高优先级进程对CPU资源的==抢占==。

![image-20220806120118582](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806120118582.png)

切换：多个进程之间在时间片内占用CPU资源，有时因为时间片到期或进程出让资源给高优先级进程，则进程会将此时在CPU中还没处理完全的代码信息数据打包带走（放回PCB结构体中），腾出资源给另一个进程，存入CPU的寄存器中进行数据处理，而上一个进程则因为临走前打包带走了数据，所以不会因为其他进程的打断而在下次进入CPU处理时继续上一次进度处理，而不会丢失进度。

![image-20220806120715532](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806120715532.png)



环境变量

观察现象：

系统命令可以直接运行（比如list, ls, ll, which, pwd等），而自己写的可执行程序必须带上相对会绝对路径

![image-20220806121904991](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806121904991.png)

因为系统命令默认在哪个目录下都可以被找到，而自己的exe则只有在自己的文件夹下才可被找到	

$PATH为系统指令所处于的环境变量路径，使用echo $PATH指令可以查看该路径位置

![image-20220806122557422](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806122557422.png)

![image-20220806122338834](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806122338834.png)

一个系统指令由环境变量在这些搜索路径下逐个查找，每个路径以冒号" : "分隔，如果第一个路径里没有，就去第二个路径找，如果找到了就可以直接调用，整个搜索的过程是环境变量自动帮我们完成搜索并调用的，所以用户可以不需要输入该指令对应路径即可直接使用。

这样就解释了我们自己的指令必须去对应exe路径下使用./使用，或使用绝对路径才能使用。因为该exe文件不在环境变量维护的众多搜索路径下，当调用该exe时系统不会调用环境变量自动为我们搜索该exe。



怎么解决？

因为环境变量维护着众多系统指令所在的搜索路径，如果用户将自己的exe文件直接放入系统指令exe中，这样做会污染系统已经配置好的代码池，不推荐这样做。

可以通过配置环境变量，将自己定义的exe所在文件路径放入环境变量的路径维护中，就可以直接调用了。

echo——显示某个环境变量值

export——设置一个新的环境变量，仅在本shell中显示，即一次性的环境变量（可被子进程继承）

env——显示所有环境变量

unset——清除环境变量

set——显示用户自定义的shell变量和环境变量

![image-20220806123445193](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806123445193.png)

![image-20220806123429310](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806123429310.png)

![image-20220806124455234](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806124455234.png)

HOME代表根目录路径，是一个环境变量，$HOME表示该变量可以直接映射当前用户的根目录路径。

SHELL代表外壳程序所在路径，是一个环境变量，$SHELL表示该变量可以映射当前SHELL外壳程序的目录位置。

PATH为环境变量路径，是一个环境变量，$PATH可以展示所有被char* env[]环境变量指针数组指向的所有指令环境变量路径（==简而言之，就是一个系统指令需要被调用时系统默认对该指令的搜索路径==）。



env——查看linux下所有的环境变量

![image-20220806125009696](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806125009696.png)



不同用户的环境变量配置不同

![image-20220806125503195](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806125503195.png)



例：main函数的3个参数

1. 一个程序启动时，操作系统（一般是父进程继承来的）会给该进程的main函数传入几个参数，分别为：

![image-20220806144050091](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806144050091.png)

其中char * env[]指针数组参数是系统传入该进程需要使用到的环境变量信息：

![image-20220806130036924](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806130036924.png)

该参数为环境变量的字符指针数组，其中存储了不同的环境变量（如HOME, PATH等），每个变量都是字符指针，指向了其维护的不同路径的内存地址，这些路径实际上就是字符串，每个路径以\0结尾。

2. 除了main的参数，还可以通过引入全局变量的环境变量来观察（需要使用extern，头文件为unistd.h）

![image-20220806131250943](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806131250943.png)

3. 除了上述两种方法获取环境变量外，还可以通过getenv函数来获取对应环境变量的路径

![image-20220806131621490](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806131621490.png)

其描述

![image-20220806143357858](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806143357858.png)

需要包含头文件stdlib.h，直接获取。



测试1

定义环境变量shikienv

![image-20220806201119021](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806201119021.png)

主函数调用getenv获取用户自定义的全局环境变量

![环境变量1](C:\Users\Shiki\Desktop\资料\Linux\博客图片\环境变量1.png)

其中定义环境变量使用和不使用export的区别在于，使用export为定义全局环境变量，而不使用则是局部环境变量，局部环境变量不能被子进程继承，所以如上图，getenv获取不到对应变量名的字符串，返回空指针，不进入if判断而直接退出函数

使用set指令可以查看当前用户的该次登录中定义的全部本地环境变量，我们可以实际看到局部和全局环境变量都实际存在，只不过全局具有父子进程继承特性，而局部没有

![image-20220806201422380](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806201422380.png)

如果将主函数中改为全局环境变量被getenv获取，则可被子进程识别到

![环境变量2](C:\Users\Shiki\Desktop\资料\Linux\博客图片\环境变量2.png)

则可以打印出由getenv识别到的环境变量并返回该字符串首地址给字符指针，并通过printf函数打印出来。



测试2

给自定义可执行程序路径配置环境变量

![image-20220806150407548](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806150407548.png)

![image-20220806150450576](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806150450576.png)

通过筛选该环境变量查看该环境变量的配置内容

![image-20220806152115885](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806152115885.png)

相当于给环境变量搜索的指令目录新增了一条路径，本质上是env指针数组扩容了一个char*指针，该指针指向我的exe所在路径，当直接运行该exe对应名字指令时，linux会通过环境变量数组列表搜索该指令，然后再运行。

![image-20220806130036924](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806130036924.png)

使用==ps ajx | head -1 && ps axj | grep [exe文件]==，可以观察到可执行程序为什么可以使用环境变量的原因，因为该exe的父进程是bash外壳程序，且因为环境变量是全局，所以外壳程序bash父进程下的所有子进程也都可以使用环境变量，因为PID与PPID是对应的。

![image-20220806153233366](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806153233366.png)



另：windows下环境变量

![image-20220806151127464](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806151127464.png)



总结

1. 子进程的环境变量由父进程来，追溯到底是从BASH来（BASH的环境变量从操作系统继承，其会随着每次SHELL的重启而重新加载；而自定义环境变量每次都会被重置）
2. 默认所有的环境变量，都会被子进程继承——即环境变量具有全局属性（被多叉树的各个子结点都接收）



问题：前两个参数是什么？

![image-20220806144152530](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806144152530.png)

答：命令行参数

我们平时用的ls -l, ls -i, ls -lia等等后面的选项都是基于ls延伸出来的，而这些选项就是前两个参数所控制。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806144856758.png" alt="image-20220806144856758" style="zoom: 67%;" />

如上图，如果执行该exe的后方带上-a或-b（指令行中），则该exe会根据用户所给选项执行不同的函数子功能，从而使一个函数具有不同的效果展示。

argc为exe附带的选项个数（所以类型为int），argc至少为1，当一个exe什么选项都不带，则argc为1；如果一个参数，则argc为2，带两个参数，argc为3，以此类推。

![image-20220806160001955](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806160001955.png)

argc为1，什么选项都不带，则argc只能读取到下标为0的main函数本身。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806155843179.png" alt="image-20220806155843179" style="zoom:67%;" />

如果附加了选项，因为每个选项是字符串，所以由字符指针指向首字符地址，每多加一个选项，argc++，则argv能访问的指针数组范围也增大，如果一次调用多个选项，就执行多种函数子功能；

![image-20220806155941018](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806155941018.png)



argv为用户定义的输入的选项内容，由指针数组来控制，因为选项内容本身就是字符串，所以需要用字符指针来维护。默认什么选项都不带，则argv[0]就是可执行程序本身，而argv[1]就是该exe附带的选项。



---

### 🌠程序地址空间

![image-20220806162033563](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806162033563.png)

观察

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806163542585.png" alt="image-20220806163542585" style="zoom:67%;" />

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220806163632561.png" alt="image-20220806163632561" style="zoom: 67%;" />

注意：地址空间规则在linux下严格遵守，但在windows的IDE下可能由于编译器自身原因会不遵循上述规则。

==注意，这些地址空间不在内存上！==

