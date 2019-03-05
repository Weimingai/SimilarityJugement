#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include"Trie.h"
//#include"Hash.h"
//#include"Status.h"

void main()
{
	//****************读取文件中的C语言关键字*****************
	char keywords[32][10];
	FILE *fp;//创建文件指针
	fp = fopen("keywords.txt", "r");//打开一个文件并且规定为只读
	if (fp == NULL)
	{
		printf("open file error!\n");
		return -1;
	}
	for (int i = 0; i < 32; i++) //循环读取，控制不超过32个
	{
		if (fscanf(fp, "%s", keywords[i]) != 1) //控制每个单词不超过20个
			break;
	}
	fclose(fp);
	int m = 0;
	printf("C语言中的关键字有：\n");
	for (int j = 0; j < 32; j++) { //输出各单词
		printf("%2d:%10s|      ", ++m,keywords[j]);
		if ((j + 1) % 4 == 0)
		printf("\n");
	}
	//****************对C语言中的关键字建立键树*************************
	printf("\n对C语言中的关键字建立键树：\n");
	char str[20];
	Trie_node root = NULL;
	root = CreateTrie();
	if (root == NULL)
		printf("创建Trie树失败\n");
	for (int i = 0; i < 32; i++)
	{
		insert_node(root,keywords[i]);
	}
	printf("Trie树已建立完成\n");
	printf("请输入要查询的字符串:\n");
	while (scanf("%s", str) != NULL)
	{
		search_str(root, str);
	}
	//***************源程序文件的读取和哈希表的建立**********************
	
	return 0;
}
