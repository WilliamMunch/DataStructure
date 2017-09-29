#include"Stack.cpp"
//flag 1 means it is the priority in stack ,0 means out stack
int GetPriority(char ch,int flag)
{
	if (ch == '-' || ch == '+'){
		if (flag){
			return 3;
		}
		return 2;
	}
	if (ch == '*' || ch == '/'){
		if (flag){
			return 5;
		}
		return 4;
	}
	if ('(' == ch){
		if (flag){
			return 1;
		}
		return 6;
	}
	if (')' == ch){
		if (flag){
			return 6;
		}
		return 1;
	}
	return -1;
}

bool IsOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/'\
		|| ch == '%' || ch == '(' || ch == ')')
	{
		return true;
	}
	return false;
}


void prefixionToSuffixion(char* dst, char* src)
{
	assert(dst);
	assert(src);
	char* cur = src;
	char* tmp = dst;
	Stack<char> s;
	while (*cur != '\0')
	{
		while (*cur <= '9' && *cur >= '0'){
			*tmp++ = *cur++;
			continue;
		}
		if (IsOperator(*cur))
		{
			if (s.Empty()){
				s.Push(*cur);
				cur++;
			}
			else if(*cur == ')'){
				while (*cur == ')' && s.Top() != '('){
					*tmp++ = s.Top();
					s.Pop();
				}
				s.Pop();
				cur++;
			}
			else if (GetPriority(*cur, 0) > GetPriority(s.Top(), 1)){
				s.Push(*cur++);
			}
			else{
				while (!s.Empty() && GetPriority(*cur, 0) < GetPriority(s.Top(), 1)){
					*tmp++ = s.Top();
					s.Pop();
				}
				s.Push(*cur++);
			}
		
		}
		else{
			*tmp++ = *cur++;
		}
	}
	while (!s.Empty()){
		*tmp++ = s.Top();
		s.Pop();
	}

}



int SuffixionToValue(char* suff, char* pre)
{
	assert(suff);
	assert(pre);
	prefixionToSuffixion(suff, pre);
	Stack<int> s;
	int res = 0;
	int tmp = 0;
	char* cur = suff;
	while (*cur != '\0')
	{
		if ('+' == *cur || '-' == *cur || '*' == *cur || '/' == *cur \
			|| '%' == *cur)
		{   //������������� ��ջ�е�ջ����Ԫ�ذ���ջ�Ⱥ���Ϊ������������ʹ��*cur����������
			//����������������ջ
			int right = s.Top();
			s.Pop();
			int left = s.Top();
			s.Pop();
			switch (*cur)
			{
			case '+':
				s.Push(left + right);
				break;
			case '-':
				s.Push(left - right);
				break;
			case '*':
				s.Push(left * right);
				break;
			case '%':
				s.Push(left & right);
				break;
			case '/':
				if (right){ s.Push(left / right); }
					
				break;
			}
			cur++;
		}
		else if (*cur >= '0' && *cur <= '9')
		{//��cur�ߵ��������ַ� �������ļ��������ַ�ת��ΪӦ��ʾ��������ջ
			res = 0;  //ÿһ�α��뽫����res���� ����ȷ������һ����������
			while (*cur >= '0' && *cur <= '9')
			{
				tmp = *cur - '0';
				res = res * 10 + tmp;
				cur++;
			}
			s.Push(res);
		}
		else{
			cur++;//����cur�Ȳ��������ַ�Ҳ���ǲ������ַ� �Ͳ������� ֱ��cur++
		}
	}
	if (!s.Empty()){
		res = s.Top();//��ʱջ��֮Ӧ��һ�������ַ� ��������Ĵ�
		return res;
	}
}





