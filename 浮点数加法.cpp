#pragma warning(disable:4996);
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
using namespace std;
const int maxn = 2000;
struct bign {	//�洢������
	int d[maxn];
	int len;
	bign() {
		memset(d, 0, sizeof(d));
		len = 0;
	}
};
/*int compare(bign a, bign b) {
	if (a.len > b.len) return 1;//a��
	else if (a.len < b.len)return -1;//aС
	else {
		for (int i = a.len - 1;i >= 0;i--) {
			//�Ӹ�λ����λ�Ƚϣ�
			if (a.d[i] > b.d[i])return 1;
			else if (a.d[i] < b.d[i]) return -1;
		}
		return 0;
		//����λ��ȣ�������ȣ�
	}
}*/
bign change(char str[]) {	//ת��
	bign a;
	a.len = strlen(str);
	for (int i = 0;i < a.len;i++)
	{
		a.d[i] = str[a.len - 1 - i] - '0';
	}
	/*for (int i = 0;i < a.len;i++) {
		if (isdigit(str[a.len - 1 - i]))	//0~9
			a.d[i] = str[a.len - 1 - i] - '0';
		else	//A~Z
			a.d[i] = str[a.len - 1 - i] - 'A' + 10;
	}*/
	return a;
}
bign add(bign a, bign b, int& carry) {
	bign c;
	carry = 0;
	int len = (a.len > b.len) ? a.len : b.len;
	for (int i = 0;i != len;i++) {
		int temp = a.d[i] + b.d[i] + carry;
		c.d[c.len++] = temp % 10;
		carry = temp / 10;
	}
	if (carry) {
		c.d[c.len++] = carry;
	}
	return c;
}
/*bign divide(bign a, int m, int b, int& r) {
	bign c;
	c.len = a.len;
	r = 0;
	for (int i = a.len - 1;i >= 0;i--) {
		r = r * m + a.d[i];	//��Ϊ��m���Ƶģ����Գ���m
		if (r < b) c.d[i] = 0;
		else {	//�൱�ڳ�bȡ���
			c.d[i] = r / b;
			r %= b;
		}
	}
	while (c.len  >= 1 && c.d[c.len - 1] == 0)
		c.len--;	//������λ��0
	return c;
}*/
void print(bign a) {
	for (int i = a.len - 1;i >= 0;i--) {
		printf("%d", a.d[i]);
	}
}
/*bool cmp(bign a, bign b) {
	if (compare(a, b) == 1&& compare(a, b)==0) return false;
	if (compare(a, b) == -1)return true;
}*/
int main()
{
	char s1[maxn], s2[maxn], s3[maxn], s4[maxn];
	//�ֱ�Ϊa,b��������С������
			char input[maxn];
			char* p1 = s1, * p2 = s2, * p3 = s3, * p4 = s4;
			printf("�������һ������");
			scanf("%s", input);
			int pointflag = 0;//��־λ������¼��С��λ��������λ��
			for (int i = 0;i != strlen(input);i++) {
				if (input[i] == '.') {
					pointflag = 1;
					continue;
				}
				if (pointflag)* p2++ = input[i];//���˳����������
				else{ *p1++ = input[i]; }
			}
			*p1 = '\0';
			*p2 = '\0';
			printf("������ڶ�������");
			scanf("%s", input);//��ȡ�ڶ���������
			//ͬ��ֱ�ȡ������С�����֣�
			pointflag = 0;
			for (int i = 0; i != strlen(input); i++) {
				if (input[i] == '.') {
					pointflag = 1;
					continue;
				}
				if (pointflag)
					* p4++ = input[i];
				else
					*p3++ = input[i];
			}
			*p3 = '\0';
			*p4 = '\0';
			// �Ѷ�����ַ���ת���� bign 
			bign ia = change(s1);//��������
			bign fa = change(s2);
			bign ib = change(s3);//С������
			bign fb = change(s4);
			//���мӷ����㣻
			int carry;
			bign ians = add(ia, ib, carry);
			//С�����ּӷ�
			//����ͳһ����
			if (fa.len < fb.len) {	// ��֤ fa �ĳ��Ȳ�С�� fb 
				bign temp = fa;
				fa = fb;
				fb = temp;
			}
			//������Ȳ�һ������ fb ���油 0���Ա���ӣ���Ϊbign�����ǵ��Ŵ�ģ�����Ҫ��������ʼλ�ò�������Ǻ��棻
			if (fa.len > fb.len) {
				int offset = fa.len - fb.len;
				memmove(fb.d + offset, fb.d, fb.len * sizeof(int));
				//��С�����ֵ�ֵ����ƫ�ƣ��ٲ���
				//��Ϊ��С������
				memset(fb.d, 0, offset * sizeof(int));
				fb.len = fa.len;
				//void *memmove( void* dest, const void* src, size_t count );
				//��src��ָ�ڴ�������count���ֽڵ�dest��ָ�ڴ�����
			}
			bign fans = add(fa, fb, carry);
			// ���С�������н�λ�����������ּ�һ��ĨȥС���������λ �����ǽ�λ
			if (carry) {
				bign one;
				one.len = 1;
				one.d[0] = 1;
				ians = add(ians, one, carry);
				fans.d[fans.len--] = 0;//ȥ��С��λ���λ����Ϊ�Ѿ�����������

			}
			// ɾ������С�����ֵ�λ�� 0 
			int offset = 0;
			for (;offset != fans.len;offset++)//ȷ���ж��ٶ����0
			{
				if (fans.d[offset != 0]) break;
			}
			memmove(fans.d, fans.d + offset, (fans.len - offset) * sizeof(int));
			//������ĵط����ǵ�����ȥ0
			fans.len -= offset;
			//���������С����
			print(ians);
			putchar('.');
			print(fans);
			putchar('\n');
	return 0;
}

