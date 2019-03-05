#define MAX_CHILD 26                          //此函数只虑26个英文字母的情况

typedef struct Tree                           //构建Trie树的模板
{
	int count;                                //用来标记该节点是个可以形成一个单词，如果count！=0，则从根节点到该节点的路径可以形成一个单词
	struct Tree *child[MAX_CHILD];            //声明它的子树结点
}Node, *Trie_node;

Node* CreateTrie()                             //创建Trie树的叶子结点模板
{
	Node *node = (Node*)malloc(sizeof(Node));  //为Trie树的叶子结点分配空间
	memset(node, 0, sizeof(Node));             //分配空间
	return node;                               //返回叶子结点指针
}

//Trie树的结点插入
void insert_node(Trie_node root, char *str)      
{
	if (root == NULL || *str == '\0')          //如果根节点为NULL或者字符串为空
		return;                                //中断插入并返回
	Node *t = root;                            //声明一个指向根结点的指针
	char *p = str;                             //声明一个指向字符串的指针
	while (*p != '\0')                         //如果被指向的字符不为结尾空字符
	{
		if (t->child[*p - 'a'] == NULL)        //如果根结点的孩子中这个字母为首的结点为空
		{
			Node *tmp = CreateTrie();          //创建一个结点
			t->child[*p - 'a'] = tmp;          //将孩子结点指向这个所建立的叶子结点
		}
		t = t->child[*p - 'a'];                //指针指向子节点
		p++;                                   //字符串指针后移
	}
	t->count++;                                //标记该结点为1，即存在指向字符串的指针
}

int search_str(Trie_node root, char *str)             //查找串是否在该trie树中
{
	if (NULL == root || *str == '\0')                  //如果Trie树为空或者待查找的字符串为空
	{
		printf("trie is empty or str is null\n");      //打印提示
		return 0;                                        //中断并返回
	}

	char *p = str;                                      //否则声明指针指向字符串即首个字符
	Node *t = root;
	while (*p != '\0')                                  //声明指针指向Trie树根节点
	{
		if (t->child[*p - 'a'] != NULL)                 //如果这个字符在树子结点中不空
		{
			t = t->child[*p - 'a'];                      //指针指向子节点
			p++;                                         //向后移动字符串指着
		}
		else                                              //子节点为空
			break;                                        //跳出循环
	}
	if (*p == '\0')                                       //字符串指向到了字符串结尾
	{
		if (t->count == 0)                                 //但是该结点的叶子节点数目为0
		{
			return 0;
		}
		else                                               //该结点的子结点不为0，即存在下面的叶子结点
		{
			return 1;
		}
	}
	else                                                   //还没有到字符串结尾树中的结点就结束了
	{
		return 0;
	}
}

void del(Trie_node root)                    //释放整个Trie树占的堆空间
{
	int i;                                  //声明一个int类型的变量i
	for (i = 0; i < MAX_CHILD; i++)         //如果i<26(字母表总字母个数)
	{
		if (root->child[i] != NULL)         //如果该结点不为空
			del(root->child[i]);            //递归删除下面的孩子结点，直至整个子树为空
	}
	free(root);                             //释放整个Trie树根结点的空间
}
