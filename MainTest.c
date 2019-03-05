#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"                //调用哈希结构头文件
#include "Trie.h"                //调用键树结构头文件
void chengxu();
int main()
{

	//**********************************读取文件中的C语言关键字*****************
	char keywords[32][10];                                   //声明一个存储关键字的二维数组
	FILE *fp;                                                //声明文件指针
	fp = fopen("keywords.txt", "r");                         //打开存储C语言关键字的文件并且规定为只读
	if (fp == NULL)                                          //如果文件指针指向为空
	{
		printf("open file error!\n");                        //打印提示字符串
		return -1;                                           //返回-1
	}
	for (int i = 0; i < 32; i++)                             //循环读取，控制不超过32个
	{
		if (fscanf(fp, "%s", keywords[i]) != 1)              //控制每个单词不超过20个
			break;
	}
	fclose(fp);                                              //关闭文件指针
	int m = 0;
	printf("C语言中的关键字有：\n");                         //打印C语言关键字
	for (int j = 0; j < 32; j++)
	{                                                        
		printf("%2d:%10s|      ", ++m, keywords[j]);         //按照指定格式输出序号和关键字
		if ((j + 1) % 4 == 0)
			printf("\n");
	}

	//***********************************对C语言中的关键字建立键树*************************
	printf("\n对C语言中的关键字建立键树：\n");               //打印提示字符
	//char str[10];                                            //声明字符数组存储字符串
	Trie_node root = NULL;                                   //声明一个键树的根节点
	root = CreateTrie();                                     //初始化一个键树
	if (root == NULL)                                        //如果根节点指向为空  即创建键树失败
		printf("创建Trie树失败\n");                          //打印提示字符
	for (int i = 0; i < 32; i++)                             //循环在键树中依次插入之前数组存储的关键字
	{
		insert_node(root, keywords[i]);                       
	}
	printf("Trie树已建立完成\n");                            //打印提示字符串
	/*
	printf("请输入要查询的字符串:\n");                        //检验查询
	scanf("%s", str);
	while (strcmp(str, "$") != 0)
	{
		if (search_str(root, str))
		{
			printf("该关键字存在！\n请输入下一个要查询的关键字：(输入$退出)\n");
			scanf("%s", str);
		}
		else
		{
			printf("该关键字不存在！\n请输入下一个要查询的关键字：(输入$退出)\n");
			scanf("%s", str);
		}
	}
	*/
	//***********************************对C语言中的关键字建立哈希树*************************
	printf("\n对C语言中的关键字建立哈希表：\n");             //打印提示字符串

	hash_table_init();                                       //初始化哈希表
	for (int i = 0; i < 32; i++)                             //循环在哈希表中依次插入关键字
	{


		hash_table_insert(keywords[i]);
	}
	printf("哈希表已建立完成！共有%d个结点\n", hash_table_size);//打印提示字符串
	printf("输出哈希表：\n"); 
	hash_table_print();                                       //输出哈希表
	/*
	printf("请输入要查询的字符串:\n");                        //检验查询
	scanf("%s", str);
	while (strcmp(str, "$") != 0)
	{
		if (hash_table_lookup(str))
		{
			printf("该关键字存在！\n请输入下一个要查询的关键字：(输入$退出)\n");
			scanf("%s", str);
		}
		else
		{
			printf("该关键字不存在！\n请输入下一个要查询的关键字：(输入$退出)\n");
			scanf("%s", str);
		}
	}
	*/

	//***********************************对C源程序1进行查询计算*************************
	
	//读取并计算第一个源程序                                  
	FILE * fp1;
	int ch1;
	if ((fp1 = fopen("chengxu1.txt", "r")) == NULL)
	{
		printf("打开测试文件失败");
		exit(1);
	}
	
	char words1[10];
	int i = 0;
	while ((ch1 = getc(fp1)) != EOF)
	{
		if ((ch1 >= 'a') && (ch1 <= 'z'))
		{
			words1[i] = ch1;
			i++;
		}
		else if ((words1[0] >= 'a') && (words1[0] <= 'z'))
		{
			if (search_str(root, words1))
				hash_table_lookup(words1);
			i = 0;
			for (int j = 0; j < 10; j++)
			{
				words1[j] = '\0';
			}
		}
		else
		{
			for (int j = 0; j < 10; j++)
			{
				words1[j] = '\0';
			}
			i = 0;
		}
	}
	if (fclose(fp1) != 0)
	{
		printf("关闭测试文件失败");
		exit(1);
	}
	
	printf("\n第一个程序查询完后的哈希表状态为：\n");                      //打印提示字符串
	hash_table_print();                                                    //打印哈希表

	printf("第一个程序的频率为：\n\n");
	hash_table_nvalue();
	hash_table_revalue();
	
	//printf("\n清除权值完后的哈希表状态为：\n");                         //打印提示字符串
	//hash_table_print();                                                 //打印哈希表
	
	hash_table_release();                                               //释放哈希表的存储空间     
	
	chengxu();
	return 0;
}



void chengxu()
{
	char keywords[32][10];                                   //声明一个存储关键字的二维数组
	FILE *fp;                                                //声明文件指针
	fp = fopen("keywords.txt", "r");                         //打开存储C语言关键字的文件并且规定为只读
	if (fp == NULL)                                          //如果文件指针指向为空
	{
		printf("open file error!\n");                        //打印提示字符串
		return -1;                                           //返回-1
	}
	for (int i = 0; i < 32; i++)                             //循环读取，控制不超过32个
	{
		if (fscanf(fp, "%s", keywords[i]) != 1)              //控制每个单词不超过20个
			break;
	}
	fclose(fp);                                              //关闭文件指针

	//***********************************对C语言中的关键字建立键树*************************
	//printf("\n对C语言中的关键字建立键树：\n");               //打印提示字符
	//char str[10];                                            //声明字符数组存储字符串
	Trie_node root = NULL;                                   //声明一个键树的根节点
	root = CreateTrie();                                     //初始化一个键树
	if (root == NULL)                                        //如果根节点指向为空  即创建键树失败
		printf("创建Trie树失败\n");                          //打印提示字符
	for (int i = 0; i < 32; i++)                             //循环在键树中依次插入之前数组存储的关键字
	{
		insert_node(root, keywords[i]);
	}
	//printf("Trie树已建立完成\n");                            //打印提示字符串
	/*
	printf("请输入要查询的字符串:\n");                        //检验查询
	scanf("%s", str);
	while (strcmp(str, "$") != 0)
	{
		if (search_str(root, str))
		{
			printf("该关键字存在！\n请输入下一个要查询的关键字：(输入$退出)\n");
			scanf("%s", str);
		}
		else
		{
			printf("该关键字不存在！\n请输入下一个要查询的关键字：(输入$退出)\n");
			scanf("%s", str);
		}
	}
	*/
	//***********************************对C语言中的关键字建立哈希树*************************
	//printf("\n对C语言中的关键字建立哈希表：\n");             //打印提示字符串

	hash_table_init();                                       //初始化哈希表
	for (int i = 0; i < 32; i++)                             //循环在哈希表中依次插入关键字
	{


		hash_table_insert(keywords[i]);
	}
	//printf("哈希表已建立完成！共有%d个结点\n", hash_table_size);//打印提示字符串
	//printf("输出哈希表：\n");
	//hash_table_print();                                       //输出哈希表
	/*
	printf("请输入要查询的字符串:\n");                        //检验查询
	scanf("%s", str);
	while (strcmp(str, "$") != 0)
	{
		if (hash_table_lookup(str))
		{
			printf("该关键字存在！\n请输入下一个要查询的关键字：(输入$退出)\n");
			scanf("%s", str);
		}
		else
		{
			printf("该关键字不存在！\n请输入下一个要查询的关键字：(输入$退出)\n");
			scanf("%s", str);
		}
	}
	*/

	//***********************************对C源程序1进行查询计算*************************

	//读取并计算第二个源程序                                  
	FILE * fp1;
	int ch1;
	if ((fp1 = fopen("chengxu2.txt", "r")) == NULL)
	{
		printf("打开测试文件失败");
		exit(1);
	}

	char words1[10];
	int i = 0;
	while ((ch1 = getc(fp1)) != EOF)
	{
		if ((ch1 >= 'a') && (ch1 <= 'z'))
		{
			words1[i] = ch1;
			i++;
		}
		else if ((words1[0] >= 'a') && (words1[0] <= 'z'))
		{
			if (search_str(root, words1))
				hash_table_lookup(words1);
			i = 0;
			for (int j = 0; j < 10; j++)
			{
				words1[j] = '\0';
			}
		}
		else
		{
			for (int j = 0; j < 10; j++)
			{
				words1[j] = '\0';
			}
			i = 0;
		}
	}
	if (fclose(fp1) != 0)
	{
		printf("关闭测试文件失败");
		exit(1);
	}

	printf("\n第二个程序查询完后的哈希表状态为：\n");                      //打印提示字符串
	hash_table_print();                                                    //打印哈希表

	printf("第二个程序的频率为：\n");
	hash_table_nvalue();
	//hash_table_revalue();

	//printf("\n清除权值完后的哈希表状态为：\n");                         //打印提示字符串
	//hash_table_print();                                                 //打印哈希表

	hash_table_release();                                               //释放哈希表的存储空间    
}