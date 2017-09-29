#include"Stack.cpp"
#pragma warning(disable:4996)

void menu()
{
	printf("\t\t--------------------------------------------\n");
	printf("\t\t|                  计算器                  |\n");
	printf("\t\t|              ----------------            |\n");
	printf("\t\t|              |              |            |\n");
	printf("\t\t|              ----------------            |\n");
	printf("\t\t|              1    2    3   +             |\n");
	printf("\t\t|              4    5    6   -             |\n");
	printf("\t\t|              7    8    9   *             |\n");
	printf("\t\t|              0   （    ）  /             |\n");
	printf("\t\t--------------------------------------------\n");
	printf("Please Enter 算式：");
	//printf("\t\t 请输入你要进行的操作：\n");
	//printf("\t\t a表达式求值 b清空 c退出\n");
}
void clear()
{
	system("cls");
	menu();
}
void Quit()
{
	system("cls");
	exit(1);
}

void Test()
{
	menu();
	//char prefixion[] = "";
	//scanf("%s", prefixion);
	char prefixion[] = "12 * (3 + 4) - 6 + 8 / 2 ";//保存前缀表达式
	//char prefixion[] = "12 * (3 + 4)";
	char suffix[25] = {};//保存后缀表达式
	int res = SuffixionToValue(suffix, prefixion);
	cout << res << endl;
}


int main()
{
	Test();
	system("pause");
	return 0;
}