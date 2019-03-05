/*=================哈希表的准备阶段——开放定址法——二次探测再散列=========================================*/

#define HASH_TABLE_MAX_SIZE 43//哈希表的数组总个数
typedef struct HashNode_Struct HashNode;//声明哈希表的结点结构

struct HashNode_Struct//写出哈希表的结点模板
{
	char* sKey;//哈希结点中的关键字
	int nValue;//哈希结点中的权值
	int conflict;//记录冲突的次数
};

HashNode* hashTable[HASH_TABLE_MAX_SIZE]; //定义哈希表——哈希数组
int hash_table_size;  //声明哈希表中实际数组的大小

//初始化哈希表
void hash_table_init()
{
	hash_table_size = 0;//使哈希数组长度为0
	memset(hashTable, 0, sizeof(HashNode*) * HASH_TABLE_MAX_SIZE);//为哈希数组分配内存空间
}


//构造哈希函数
int hash_table_hash_str(char* skey)
{
	char *p = skey;//设置指针指向要传递的字符串
	int h;
	int i;//声明一个新的int值
	for (i = 0; i < 10; i++)//算一下字符的长度并依次向后移动指针
		if (p[i] == '\0')//如果指针指向了空的地方
			break;//跳出循环
	h = ((p[0] - 97) * 100 + (p[i - 1] - 97)) % 41;//计算哈希值

	return h;//返回计算出的数组序号
}

//将结点插入哈希表
void hash_table_insert(char* skey)
{
	if (hash_table_size >= HASH_TABLE_MAX_SIZE)//判断哈希表的实际元素数目是否已经超过了哈希表的规定数组长度
	{
		printf("out of hash table memory!\n");//如果超出了，就给出提示
		return;//并中断返回
	}

	int pos = hash_table_hash_str(skey);//通过哈希函数计算出数组的序号

	HashNode* pHead = hashTable[pos];//声明一个指针指向待插向的结点
	int i = 1, j = 0, k = pos;
	while (pHead)//如果这个结点已经被占用了
	{
		if (strcmp(pHead->sKey, skey) == 0)//如果这个结点的值与带插入的结点值相等
		{
			printf("%s already exists!\n", skey);//输出提示字符串
			return;//中断并返回
		}
		//继续进行二测探测
		else if (j % 2 == 0) {
			//pHead = hashTable[pos + i * i];
			k = pos + i * i;
			if (k > HASH_TABLE_MAX_SIZE)
				k = k - HASH_TABLE_MAX_SIZE;
			pHead = hashTable[k];
			j++;
		}
		else
		{
			pHead = hashTable[pos - i * i];
			j++;
			k = pos - i * i;
			i++;
		}
	}

	HashNode* pNewNode = (HashNode*)malloc(sizeof(HashNode));//声明一个新的结点并为其分配向量空间
	memset(pNewNode, 0, sizeof(HashNode));//分配指针空间哦
	pNewNode->sKey = (char*)malloc(sizeof(char) * (strlen(skey) + 1));//为结点的关键字分配动态存储空间
	strcpy(pNewNode->sKey, skey);//复制待插入字符串到刚刚分配的结点的关键字
	pNewNode->nValue = 0;//将待出入的value值付给刚刚建立的结点的value
	pNewNode->conflict = j;//这个不确定要运行一下才能看出来
	//pNewNode->pNext = hashTable[pos];//将新分配的结点next指向哈希表数组中的对应结点地址-----实现了将最后一个结点指向数组本身
	hashTable[k] = pNewNode;//将哈希表数组中的对应结点指向新的结点
	hash_table_size++;//哈希表的实际长度加一
}
/*
//在哈希表数组中删除一个关键字
void hash_table_remove(const char* skey)
{
	unsigned int pos = hash_table_hash_str(skey);//通过哈希函数计算出数组的序号
	if (hashTable[pos])//如果对应哈希值结点上的值存在
	{
		HashNode* pHead = hashTable[pos];//声明新的指针指向该结点
		HashNode* pLast = NULL;//定义上一个上一个结点指针
		HashNode* pRemove = NULL;//定义删除结点指针
		while (pHead)//如果指向的结点一直存在值
		{
			if (strcmp(skey, pHead->sKey) == 0)//如果要删除的值与该结点上面的值相等
			{
				pRemove = pHead;//让新声明的删除指针指向该结点
				break;//跳出循环
			}
			pLast = pHead;//新声明的上一个结点的指针指向该节点
			pHead = pHead->pNext;//该节点向后移动一位
		}
		if (pRemove)//如果删除结点存在值
		{
			if (pLast)//如果上一个结点存在值
				pLast->pNext = pRemove->pNext;//上一个结点的next指针指向被删除结点的下一个结点
			else
				hashTable[pos] = NULL;//上一个结点不存在指针，则直接让哈希表中对应的结点数组指向空

			free(pRemove->sKey);//释放要删除结点的空间
			free(pRemove);
		}
	}
}
*/
//在哈希表中查找一个关键字
HashNode* hash_table_lookup(char* skey)
{
	int pos = hash_table_hash_str(skey);//通过哈希函数计算出数组的序号;
	if (hashTable[pos])//如果对应结点存在值
	{
		HashNode* pHead = hashTable[pos];//声明一个新的结点指针指向该结点
		int i = 1, j = 0, k = pos;
		while (pHead)//如果新的结点指针指向的结点的值存在
		{
			if (strcmp(skey, pHead->sKey) == 0)
			{//如果要查找的关键字与指向结点道德关键字相等
				pHead->nValue++;
				return pHead;//返回该节点
			}
			//继续进行二测探测
			else if (j % 2 == 0) {
				//pHead = hashTable[pos + i * i];
				j++;
				k = pos + i * i;
				if (k > HASH_TABLE_MAX_SIZE)
					k = k - HASH_TABLE_MAX_SIZE;
				pHead = hashTable[k];
			}
			else
			{
				pHead = hashTable[pos - i * i];
				j++;
				k = pos - i * i;
				i++;
			}
		}
	}
	return NULL;//如果对应结点值不存在，则返回空值
}

//打印哈希表中的存在的结点
void hash_table_print()
{
	printf(" 序号     关键字 频数 冲突\n");//
	int i;//声明一个int类型的值
	for (i = 0; i < HASH_TABLE_MAX_SIZE; i++)//从头遍历哈希表的结点数组
	{
		HashNode* pHead = hashTable[i];//声明新的结点指针指向该结点
		if (pHead)
		{
			printf("%4d=>", i);//打印结点序号		
			printf("%9s:%4d %4d", pHead->sKey, pHead->nValue, pHead->conflict);//打印结点的关键字和权值
			//pHead = pHead->pNext;//指向下一个结点		
			printf("\n");//打印换行符
		}
	}
}

//释放整个哈希表的内存空间
void hash_table_release()
{
	int i;//声明一个int值i
	for (i = 0; i < HASH_TABLE_MAX_SIZE; ++i)//从头遍历哈希表的结点数组
	{
		if (hashTable[i])//如果结点不为NULL
		{
			HashNode* pTemp = hashTable[i];//设置新的哈希结点指针指向该结点
			if (pTemp)//如果新设置的哈希结点指针不为NULL
			{
				free(pTemp->sKey);//释放这个结点的空间吧
				free(pTemp);
			}


		}
	}
}
//使哈希表中的所有权值为0
void hash_table_revalue()
{
	int i;//声明一个int类型的值
	for (i = 0; i < HASH_TABLE_MAX_SIZE; i++)//从头遍历哈希表的结点数组
	{
		HashNode* pHead = hashTable[i];//声明新的结点指针指向该结点
		if (pHead)
		{			
			pHead->nValue = 0;//使结点的权值为0
		}
	}
}

hash_table_nvalue()
{
	int i, j=0;//声明一个int类型的值
	for (i = 0; i < HASH_TABLE_MAX_SIZE; i++)//从头遍历哈希表的结点数组
	{
		HashNode* pHead = hashTable[i];//声明新的结点指针指向该结点
		if (pHead)
		{		
			printf("%4d", pHead->nValue);//打印结点的关键字和权值
			//pHead = pHead->pNext;//指向下一个结点		
			j++;
			if (j % 8 == 0)
				printf("\n");//打印换行符
		}
	}
}


/* ===============================哈希表的构建以及实现的操作函数结束了=========================*/