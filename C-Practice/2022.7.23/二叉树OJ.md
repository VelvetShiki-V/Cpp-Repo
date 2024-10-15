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



🎀子树判断

```c
bool SubTree(BTNode* root, BTNode* subroot)
{
	if (root == NULL && subroot == NULL)
	{
		return true;
	}
	if (root == NULL)
	{
		return false;
	}
	else if (subroot == NULL)
	{
		return true;
	}
	if (root->data == subroot->data)
	{
		if (SameTree(root, subroot))
		{
			return true;
		}
	}
	return SubTree(root->left, subroot) || SubTree(root->right, subroot);
}
```





## ✨完全二叉树



🎀判断完全二叉

```c
bool CompleteTree(BTNode* root)
{
	if (root == NULL)
	{
		return false;
	}
	QNode* QueueHead = BuyQueueNode(root);
	while (QueueTop(&QueueHead) != NULL)
	{
		QueuePush(&QueueHead, QueueHead->data->left);
		QueuePush(&QueueHead, QueueHead->data->right);
		QueuePop(&QueueHead);
	}
	while (!QueueEmpty(&QueueHead))
	{
		if (QueueTop(&QueueHead) != NULL)
		{
			QueueDestroy(&QueueHead);
			return false;
		}
		QueuePop(&QueueHead);
	}
	QueueDestroy(&QueueHead);
	return true;
}
```





## ✨前序建树



🎀前序建树及插入

```c
BTNode* PreorderCreate(char arr[])
{
	if (*arr == '#')
	{
		return NULL;
	}
	char* cur = arr;
	BTNode* root = NULL;
	PreorderInsert(&root, &cur);
	return root;
}
```

🎀前序插入

```c
void PreorderInsert(BTNode** root, char** letter)
{
	if (**letter == '#')
	{
		(*letter)++;
		return;
	}
	if (**letter == NULL)
	{
		return;
	}
	*root = BuyTreeNode(**letter);
	(*letter)++;
	PreorderInsert(&(*root)->left, letter);
	PreorderInsert(&(*root)->right, letter);
}
```

