#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

/* ============================test function ============================*/

int main(int argc, char** argv)//主调函数
{
	//***************源程序文件的读取和哈希表的建立**********************
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
		printf("%2d:%10s|      ", ++m, keywords[j]);
		if ((j + 1) % 4 == 0)
			printf("\n");
	}
	//****************对C语言中的关键字建立哈希树*************************
	printf("\n对C语言中的关键字建立哈希表：\n");
	char str[10];
	hash_table_init();
	for (int i = 0; i < 32; i++)
	{


		hash_table_insert(keywords[i]);
	}
	printf("哈希表已建立完成！共有%d个结点\n", hash_table_size);
	printf("输出哈希表：\n");
	hash_table_print();
	printf("请输入要查询的字符串:\n");
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
	printf("查询完后的哈希表状态为：\n");
	hash_table_print();
	hash_table_release();
	return 0;
}