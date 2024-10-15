[TOC]



# ⭐二叉树OJ

二叉树有很多变种形式，比如单值二叉树，两棵数值上完全相同的树，两棵轴对称的树，一棵树为另一棵更大树的子树等等。因为树本身采取的是一种分治递归向下遍历的思路，所以对不同结构的树进行挖掘和思考可以让我们对二叉树这个概念有更好的了解，本章将详细介绍几种变种二叉树并随附代码解析。



---

## ✨单值二叉树

顾名思义，单值树就是一种仅包含单一数值的二叉树，该树的所有结点中数值域的值都相等，如下图所示：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220723200852342.png" alt="image-20220723200852342" style="zoom:67%;" />

而判断一棵二叉树是否为单值二叉树具有两种解决方案：

🥝flag置反法

此种方法的核心是对二叉树的前序遍历，将所有结点数值与根结点值进行比较，采取此种方式的遍历函数可以不带返回值，通过全局变量flag进入函数内部，当遇到所传入的根结点值与所遍历到的结点值不相同时，将全局变量flag置反，即如果该二叉树值不单一，则全局变量经过该前序遍历后，flag将会从真变为假，而如果该树的值单一，则flag值置反将不会被执行，跳出函数后仍保持真的状态。

🎀前序遍历置反函数

```c
void PreorderComp(BTNode* root, int value)
{
    if(root == NULL || flag == false)			//如果全局变量flag为假，直接跳出不进行后续遍历
        return;
    if(root->data != value)						//如果遍历到的结点值与根值不同，则将flag值置反
        flag = false;
    	return;
    PreorderComp(root->left, value);			//前序遍历
    PreorderComp(root->right, value);
}
```

🎀单值树判断主调函数

```c
bool flag = true;						//定义全局变量flag
bool TreeJudge(BTNode* root)
{
    if(root == NULL)
        return true;
    PreorderComp(root. root->data);		//调用前序遍历函数
    return flag;						//将flag最终结果返回
}
```



🥝父子比较遍历法

大体上采取与前一种方法相同的思路，但在代码简洁程度上有所优化，省去了全局变量取而代之使用逻辑与的方式让根结点值与固定的单值传入进行对比，如果遍历后发现有结点值与给定传入的value值不相等，则返回假；如果所有值都相等，则不会返回假，进行与运算后全部返回真，则为单值二叉树。

🎀单值遍历

```c
bool UnivalTree(BTNode* root, BTEtype value)
{
	if (root == NULL)				//如果结点为空，则该路径上所有结点都单值，返回真
	{
		return true;
	}
	if (root->data != value)		//只要一个结点值与单值value不等，则返回假，其他路径所有值再为真也不是单值二叉树
	{
		return false;
	}
	return UnivalTree(root->left, value) && UnivalTree(root->right, value);		//每条路径上的二叉单值结果逻辑与
}
```

🎀单值树建立

```c
BTNode* UnivalTreeCreate()
{
	BTNode* root = BuyTreeNode(2);
	BTNode* n1 = BuyTreeNode(2);
	BTNode* n2 = BuyTreeNode(2);
	BTNode* n3 = BuyTreeNode(2);
	BTNode* n4 = BuyTreeNode(2);
	BTNode* n5 = BuyTreeNode(2);
	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n2->left = n4;
	n2->right = n5;
	return root;
}
```

🌈测试用例

```c
BTNode* root = UnivalTreeCreate();
if (UnivalTree(root, 2))
{
    puts("是单值二叉树");
}
else
{
    puts("不是单值二叉树");
}
```

🌈调试观察结果

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220723175401971.png" alt="image-20220723175401971" style="zoom: 50%;" />

如果将其中的某个值更改为其他值，则会识别为非单值树

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220723175533170.png" alt="image-20220723175533170" style="zoom:67%;" />





---

## ✨相同二叉树

判断两棵树是否在数值上完全相等，需要对两棵树进行遍历，遍历的方式只不过从一棵树替换成了两棵树的同时遍历，过程中还要同时对比两棵树对应的数值是否相等，如果两棵树的其中一棵树对应结点值与另一棵树不相等，则这两课树不相同，反之则相同。

🎀相同树判断

```c
bool SameTree(BTNode* root1, BTNode* root2)		//两棵树根结点地址传入
{
	if (root1 == NULL && root2 == NULL)			//如果两棵树在某一路径上同时达到空结点处，则该路径上所有结点值都相等
	{
		return true;						
	}
	if (root1 == NULL || root2 == NULL)			//如果两树遍历过程中，其中一棵树提前到达了空结点处，则不相同
	{
		return false;
	}
	if (root1->data != root2->data)				//如果对应结点值不相同，则判断为不相同树，返回假
	{
		return false;
	}
	return SameTree(root1->left, root2->left) && SameTree(root1->right, root2->right);
}
```

1. 如果两棵树是完全相同的，则就默认了它们无论再逻辑结构的结点对应还是结点中的数值对应上都应该是相同的，假设树A的左子树共有3个结点，每个结点的值依次为1,2,3，则相同树B的左子树构造应该与树A完全一致，且无论是逻辑链接上还是数值的相对位置都是相同的。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220723205102311.png" alt="image-20220723205102311" style="zoom:67%;" />

2. 这也就意味着，两棵树同时进行向下前序遍历，不仅要同时保证结点的相对结构，父子间或兄弟结点间的关系都一一对应，还要保证每个结点中的数值也是一比一复刻的，从上述的代码中可以看出这两个条件都恰好完全满足，如果结点不统一对应，就一定会有其中的一棵树先遍历到空结点处，或数值不相同而返回假，使得最后返回逻辑与运算时结果为假，则该两棵树不相同。

🌈测试用例

```c
BTNode* root = BinaryTreeCreate();		//将一棵树重复传参两次，则一定为相同树
if (SameTree(root, root))
{
    puts("是相同二叉树");
}
else
{
    puts("不是相同二叉树");
}
```

🌈观察结果

```c
是相同二叉树
```

为了方便对比相同树函数的不同对比，引入第二组数据

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220723211143853.png" alt="image-20220723211143853" style="zoom: 50%;" />

🌈测试用例2

```c
BTNode* root = BinaryTreeCreate();
BTNode* root1 = NotSameTreeCreate();		//造一棵树，与原树在结构上完全相同，但数值上有略微差别
if (SameTree(root, root1))
{
    puts("是相同二叉树");
}
else
{
    puts("不是相同二叉树");
}
```

🌈root1结构定义

```c
BTNode* NotSameTreeCreate()
{
	BTNode* root = BuyTreeNode(0);
	BTNode* n1 = BuyTreeNode(1);
	BTNode* n2 = BuyTreeNode(2);
	BTNode* n3 = BuyTreeNode(2);			//不相同值定义在此
	BTNode* n4 = BuyTreeNode(4);
	BTNode* n5 = BuyTreeNode(5);
	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n2->left = n4;
	n2->right = n5;
	return root;
}
```

🌈调试观察

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220723210542499.png" alt="image-20220723210542499" style="zoom:67%;" />

可以发现，在遍历到两个对应结点的值不相同后，递归函数的逻辑与运算直接为假，从而导致整个函数返回值结果为假，不进行右递归的继续遍历对比了。在此过程中还可以发现，每个结点的地址一定不相等，因为两棵树是在不同的内存空间由链表申请开辟的，所以即使两棵树在逻辑结构和数值上是完全相同的，但在物理地址上一定不相同。



---

## ✨对称二叉树

一棵二叉树的对称结构是以轴对称展开的，如果两棵树轴对称，则将它们重叠到一起，两棵树会分文不差的高度缝合，这也就意味着一棵树与另一棵对称树在结点的逻辑结构上是镜像的，同样镜像处理的还有结点中所带的值，如下图所示：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220723211704722.png" alt="image-20220723211704722" style="zoom:50%;" />

1. 秉承两棵相同树的遍历思路，因为对称树相对于原树的结构是相对镜像的，所以对于对称树的遍历也需要进行镜像处理，当原树遍历左子树时，对称树遍历右子树；反之当原树开始遍历右子树时，对称树应遍历左子树以保持对称结点的对称统一。
2. 剩下的操作就基本与相同树的递归向下遍历规律一致了，如果对称树的镜像遍历同时到达了空结点，则证明在到达该空结点前没有发生任何的结点不对称或数值不对称的情况，换言之，如果在遍历至末空结点的过程中发生了结点不一一镜像对称的情况，则必有其中一棵树会提前到达空结点，或者第二种情况为，两棵树在逻辑结构上相对镜像统一，但是数值上却有差异，发生这两种情况之一都会提前使递归返回的逻辑与判断为假，则使两棵树不对称的结果返回。

🎀对称树函数

```c
bool SymmetricTree(BTNode* root1, BTNode* root2)	//判断两棵树是否相互对称
{
	if (root1 == NULL && root2 == NULL)				//如果两棵树在某一路径上值相等且同时到达空结点处，则该路径一定对称
	{
		return true;
	}
	if (root1 == NULL || root2 == NULL)				//如果其中一棵树提前到达空结点，则一定不对称，返回假
	{
		return false;
	}
	if (root1->data != root2->data)					//如果两棵树的对应路径某结点值不为镜像，则不对称，返回假
	{
		return false;
	}
	return SymmetricTree(root1->left, root2->right) && SymmetricTree(root1->right, root2->left);
}													//逻辑与判断对称路径上的真假情况
```

🌈测试用例

```c
BTNode* root = BinaryTreeCreate();		//以上图左边的root树作为传参用例
if (SymmetricTree(root, root))			//将同一棵树作为两次传参，判断是否对称
{
    puts("是对称二叉树");
}
else
{
    puts("不是对称二叉树");
}
```

🌈观察结果

```c
不是对称二叉树
```

由此可以说明，一棵普通的二叉树不可能是它自身的对称结构，除非该树仅有根结点，或为满二叉树且为单值树的情况才满足对称要求。

🌈测试用例2

```c
BTNode* root = BinaryTreeCreate();
BTNode* root1 = SymmetricTreeCreate();
if (SymmetricTree(root, root1))
{
    puts("是对称二叉树");
}
else
{
    puts("不是对称二叉树");
}
```

🌈对称树的创建

```c
BTNode* SymmetricTreeCreate()
{
	BTNode* root = BuyTreeNode(0);		//对称树在结点结构上和数值上是镜像轴对称的
	BTNode* n1 = BuyTreeNode(2);
	BTNode* n2 = BuyTreeNode(1);
	BTNode* n3 = BuyTreeNode(5);
	BTNode* n4 = BuyTreeNode(4);
	BTNode* n5 = BuyTreeNode(3);
	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->right = n5;
	return root;
}
```

🌈调试观察

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220723220427190.png" alt="image-20220723220427190" style="zoom:50%;" />

观察结构可发现，两棵树中的结点数值两两对称，还有一部分因为显示问题没办法完全展示，但是它们在逻辑上已经在本问题的开头很好地显示出来了。



---

## ✨子树问题

在前面的章节中我们了解到了链表的合并话题，知道两个链表在中间某一个结点开始向后与另一个链表相交并合并为同一个链表，这种合二为一的思想如今放到二叉树上也同样有所体现，即二叉树本身就是一个以根结点为分界向下分叉的数据结构，如果能将一棵二叉树以某种手段拆成两棵子树，并判断该子树是否为原主树的分叉树，就演变为了子树与主树的归属问题。

1. 判断一棵树是否为另一棵树的子树，需要对该树以根结点为起点向下的所有分支结点路径和数值都必须与原树的某条路径相互同一，即一棵子树与原树的某条分支路径完全相同，如下图：

![子树](C:\Users\Shiki\Desktop\资料\博客\子树.png)

2. 上图左边的树为主树，右边分别为主树各个分支路径的零散片段，根据上条称述，仅有以子树根结点向下的所有路径分支结点结构和数值域主树某路径向下完全相同时，才能被称为主树的子树。所以树1和树3不是主树的子树，因为以根结点为起点向下应该包含所有路径与分支与主树都相同才为子树，而树2是主树的子树，因为从结点值为3开始向下的所有左子树和右子树斗鱼主树相同。
3. 一棵树总是它自身的子树，因为两棵树一模一样。

🎀子树判断

```c
bool SubTree(BT* root, BT* subroot)
{
	if (root == NULL)				//如果主树为空，则该树无子树
	{
		return false;
	}
	if (SameTree(root, subroot))	//主树每遍历一个结点，调用一次相同树函数，如果以该结点向下都与子树相同，返回真
	{
		return true;
	}
	return SubTree(root->left, subroot) || SubTree(root->right, subroot);
```

4. 从代码中可以看出，主树每次递归遍历到一个结点都与子树的根结点值进行比较，如果发现两者相同，则判断两棵树是否在后续的遍历中完全相同，从前例相同树的规律可以得知，当两棵树只有在结构与数据上完全相同一致时，两棵树就是相同树，只不过在本例问题中变为了子树与主树的某一分叉路径和数值完全相同，则可判定该子树为主树的子树了。

🌈测试用例

```c
BTNode* root = BinaryTreeCreate1();
BTNode* root1 = SubTreeCreate();
if (SubTree(root, root1))
{
    puts("是子树");
}
else
{
    puts("不是子树");
}
```

其中，因为以上图的左主树与右边三个子树为例

🌈主树创建

```c
BTNode* BinaryTreeCreate1()
{
	BTNode* root = BuyTreeNode(1);
	BTNode* n1 = BuyTreeNode(2);
	BTNode* n2 = BuyTreeNode(3);
	BTNode* n3 = BuyTreeNode(4);
	BTNode* n4 = BuyTreeNode(5);
	BTNode* n5 = BuyTreeNode(6);
	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n2->left = n4;
	n2->right = n5;
	return root;
}
```

🌈子树创建

```c
BTNode* SubTreeCreate()
{
	BTNode* root = BuyTreeNode(1);
	BTNode* n1 = BuyTreeNode(2);
	BTNode* n2 = BuyTreeNode(3);
	root->left = n1;
	root->right = n2;
    return root;
}
```

🌈观察结果

```c
不是子树
```

再以树3为例，可以得到同样不是子树的结果

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724104625396.png" alt="image-20220724104625396" style="zoom: 67%;" />

而以树2为例，则因为定义的结点逻辑结构与数值和主树的右子树完全相同，则可以得到如下结果：

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724104806968.png" alt="image-20220724104806968" style="zoom:67%;" />



---

## ✨完全二叉树

对于完全二叉这个概念已经很不陌生了，稍微回顾一下，相比于二叉树随性生结点的特性，完全二叉树则有着独特的结点排布规则：一棵树有k层，前k-1层都是满的，但最后一层不满，但最后一层从左到右的结点是连续的树称为完全二叉树；因为二叉树区分左右子结点，如果最后一层仅有右结点而没有左结点，则不能称为完全二叉树，如下图：

![image-20220702175201954](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220702175201954.png)

1. 前两棵树不是完全二叉树，因为完全二叉树除了前K-1层都必须全都为度为2的结点外，最后一层K的结点必须对于每个双亲结点从左到右依次占满才为完全二叉树，可以不将该层2^K-1^个结点都占满，但数据必须连续存储，如果占满即为满二叉树。

2. 所以一棵二叉树想成为完全二叉，不仅除开最后一层的前K-1层的结点都必须全部占满，最后一层也必须从左到右依次排布，这样才满足完全二叉树的要求，如果要判断一棵树是否完全二叉，可以使用层序遍历的方式。

3. 回顾层序遍历二叉树的模式，使用到了队列的性质，即先对每层的结点从左向右依次遍历，全部遍历结束后再向下一层执行相同遍历的模式，使用队列的原因是，将每层的结点从左往右依次入队，并在队头每出一个父结点，就在该层的所有结点队列后入队下一层的左右子结点，从而达到所有结点在队列中保持相对顺序而不会被打乱。

![层序遍历](C:\Users\Shiki\Desktop\资料\博客\链表OJ题\图片素材\层序遍历.gif)

🎀判断完全二叉

```c
bool CompleteTree(BTNode* root)
{
	if (root == NULL)										//如果为空树，则非完全二叉
	{
		return false;
	}
	QNode* QueueHead = BuyQueueNode(root);					//先将根结点入队
	while (QueueTop(&QueueHead) != NULL)					//当取到的队头不为空结点时，继续层序入队
	{
		QueuePush(&QueueHead, QueueHead->data->left);		//入队当前结点的左子结点
		QueuePush(&QueueHead, QueueHead->data->right);		//入队当前结点的右子结点
		QueuePop(&QueueHead);								//将当前结点出队
	}
	while (!QueueEmpty(&QueueHead))				//只要取到一个空结点，马上结束遍历入队并进入下一个循环
	{
		if (QueueTop(&QueueHead) != NULL)		//如果探测到空结点后仍有数值结点，则该二叉一定不完全二叉
		{
			QueueDestroy(&QueueHead);			//将剩余队列中存在的二叉结点销毁，并返回假
			return false;
		}
		QueuePop(&QueueHead);
	}
	QueueDestroy(&QueueHead);	
	return true;								//如果全部出队都没有探测到空结点后存在数值结点，则为完全二叉
}
```

4. 与常规对二叉树的层序遍历不同，在普通层序遍历中，入队与出队循环的结束条件是当队列为空的情况，因为当队列为空时，表示所有结点都已经入队并遍历完成了，所以出队后进行队列的销毁以及函数的退出，而此处为了判断一棵树是否具有完全二叉的性质，循环的结束条件改为当只要遍历到一个空结点就马上退出循环，因为这个空结点可能出现在满足完全二叉的最后一层的某个结点之后，也有可能出现在前K-1层的某个位置，如果是后者，则一定不是完全二叉树，需要立即停止循环并对其审判。

![image-20220724112603948](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724112603948.png)

5. 拿着遍历到空结点值以及后续没有被出完队的所有数据，再次进行一轮循环，该循环是为了监视该空结点值之后是否存在有效数据，以层序遍历的思路，如果后续仍存在有效数据，则一定不满足完全二叉的性质，因为完全二叉树的所有结点都是没有空结点作为间隙插入的有效结点之间的，而普通二叉树却允许这样的存在，所以只要侦测到空结点后仍有带值结点，直接对后续队列二叉结点销毁并返回假，表示该二叉树不为完全二叉。

🌈测试用例

```c
BTNode* root = CompTreeCreate();		//以上图右作为用例测试
if (CompleteTree(root))
{
    puts("是完全二叉树");
}
else
{
    puts("不是完全二叉树");
}
```

🌈完全二叉树创建

```c
BTNode* CompTreeCreate()
{
	BTNode* root = BuyTreeNode(0);
	BTNode* n1 = BuyTreeNode(1);
	BTNode* n2 = BuyTreeNode(2);
	BTNode* n3 = BuyTreeNode(3);
	BTNode* n4 = BuyTreeNode(4);
	BTNode* n5 = BuyTreeNode(5);
	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->left = n5;
	return root;
}
```

🌈观察结果

```c
是完全二叉树
```

如果以上图左作为用例测试，将结点值为1的右子结点去除，为值为2的右子树加上一个结点，则有

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724113057607.png" alt="image-20220724113057607" style="zoom: 67%;" />





---

## ✨前序建树

在前面的所有用例和二叉树的构建中，几乎都是人为开辟二叉树结点并手动将它们通过左右父子关系链接起来的，如果数据量很大，则这样的方式显而易见地会造成操作的繁琐和复杂。按照遍历的思路，一个二叉树通过某种遍历方式得到一串遍历的数值结果，如果将这种结果反向实现，即给定一串已知的前序遍历字符串，要求按照同样的前序方式来反向建树，则就可以让其自动完成建树的操作而无需用户手撕了。

<img src="C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724115302628.png" alt="image-20220724115302628" style="zoom:67%;" />

1. 要想让函数自动根据前序递归遍历的规则自动完成二叉树的构建，首先就需要让字符串完整遍历下去，当字符串能整个从头到尾遍历完全，每个字符指针所指向的值才能进入到二叉树结点值当中完成赋值，或遍历到井号#代表的空结点时，能够返回上一层的父节点，就向其他分路继续递归直至字符串遍历完全。

🎀前序建树

```c
BTNode* PreorderCreate(char arr[])
{
	if (*arr == '#')				//如果首字符遇到井号#代表的空结点值，则代表根结点为空，该为空树，直接返回
	{
		return NULL;
	}
	char* cur = arr;				//定义一个指针指向字符数组首元素地址，通过不断后移逐个访问每个字符
	BTNode* root = NULL;			//定义一个二叉树根结点指针，该指针指向的二叉树等待建树并返回给实参
	PreorderInsert(&root, &cur);	//前序插入建树函数
	return root;
}
```

🎀前序插入

```c
void PreorderInsert(BTNode** root, char** letter)
{
	if (**letter == '#')			//如果遇到井号#代表的空结点值，则不进行前序插入操作
	{
		(*letter)++;				//直接将指针后移，访问字符串的后一个字符并返回到父节点处
		return;
	}
	if (**letter == NULL)			//如果指针指向字符为空，则表示数组中字符已经遍历完毕，直接返回根结点，插入完毕
	{
		return;
	}
	*root = BuyTreeNode(**letter);	//如果指针解引用不是空或井号字符，则代表该字符有效，应该插入父结点下的子结点中
	(*letter)++;					//插入结束后字符串指针应向后移动继续遍历访问下一个字符等待插入
	PreorderInsert(&(*root)->left, letter);		//前序递归至左子树
	PreorderInsert(&(*root)->right, letter);	//前序递归至右子树
}
```

2. 在函数中可以发现，前序建树的主函数中定义了两个指针分别指向待遍历的字符串数组和指向开辟树的根结点地址处，将这两个指针传参进入前序遍历的结点值插入函数中，必须以传地址的方式，因为如果传入的是地址本身，在结点赋值插入的过程中，所有的结点值都会在递归返回函数结束的时候被销毁，同时字符串指针随着递归的深入而不断后移，也会在函数的递归返回销毁中回到最初的位置，既达不到数据的有效结点插入，也不能使字符串有效后移，所以为了使实参得到切实的修改，要么对实参取地址传入插入函数中，要么定义返回值使每次形参的修改都可以返回给实参。
3. 在字符指针解引用取字符的过程中还可以发现，如果该字符为井号#即拿到了空结点值，则该轮递归不插入任何新结点和赋值，直接将指针后移访问后一个字符，并返回到上一层的父节点中；如果该字符为空，即数组已经遍历结束，直接递归返回至根结点即可。

![image-20220724120441630](C:\Users\Shiki\AppData\Roaming\Typora\typora-user-images\image-20220724120441630.png)

🌈测试用例

```c
char arr1[] = "ABC##DE#G##F###";
char arr2[] = "AB##CD##E";
BTNode* root1 = PreorderCreate(arr1);
PreOrder(root1);			//数组1的前序遍历
puts("\n");
InOrder(root1);				//数组1的中序遍历
puts("\n");
BTNode* root2 = PreorderCreate(arr2);
PostOrder(root2);			//数组2的后续遍历
puts("\n");
LevelOrder(root2);			//数组2的层序遍历
```

🌈观察结果

```c
//数组1前序遍历结果——与所给字符串一致
A B C NULL NULL D E NULL G NULL NULL F NULL NULL NULL
//数组1中序遍历结果
NULL C NULL B NULL E NULL G NULL D NULL F NULL A NULL
//数组2后序遍历结果
NULL NULL B NULL NULL D NULL NULL E C A
//数组2层序遍历结果
A B C D E
```

