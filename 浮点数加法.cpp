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
struct bign {	//存储大整数
	int d[maxn];
	int len;
	bign() {
		memset(d, 0, sizeof(d));
		len = 0;
	}
};
/*int compare(bign a, bign b) {
	if (a.len > b.len) return 1;//a大
	else if (a.len < b.len)return -1;//a小
	else {
		for (int i = a.len - 1;i >= 0;i--) {
			//从高位到低位比较；
			if (a.d[i] > b.d[i])return 1;
			else if (a.d[i] < b.d[i]) return -1;
		}
		return 0;
		//所有位相等，两数相等；
	}
}*/
bign change(char str[]) {	//转换
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
		r = r * m + a.d[i];	//因为是m进制的，所以乘上m
		if (r < b) c.d[i] = 0;
		else {	//相当于除b取余吧
			c.d[i] = r / b;
			r %= b;
		}
	}
	while (c.len  >= 1 && c.d[c.len - 1] == 0)
		c.len--;	//消除高位的0
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
	//分别为a,b的整数，小数部分
			char input[maxn];
			char* p1 = s1, * p2 = s2, * p3 = s3, * p4 = s4;
			printf("请输入第一个数：");
			scanf("%s", input);
			int pointflag = 0;//标志位，区别录入小数位还是整数位；
			for (int i = 0;i != strlen(input);i++) {
				if (input[i] == '.') {
					pointflag = 1;
					continue;
				}
				if (pointflag)* p2++ = input[i];//结合顺序自右向左
				else{ *p1++ = input[i]; }
			}
			*p1 = '\0';
			*p2 = '\0';
			printf("请输入第二个数：");
			scanf("%s", input);//读取第二个浮点数
			//同理分别取出整数小数部分；
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
			// 把读入的字符串转换成 bign 
			bign ia = change(s1);//整数部分
			bign fa = change(s2);
			bign ib = change(s3);//小数部分
			bign fb = change(s4);
			//进行加法计算；
			int carry;
			bign ians = add(ia, ib, carry);
			//小数部分加法
			//首先统一长度
			if (fa.len < fb.len) {	// 保证 fa 的长度不小于 fb 
				bign temp = fa;
				fa = fb;
				fb = temp;
			}
			//如果长度不一样，在 fb 后面补 0，以便相加，因为bign存数是倒着存的，则需要在数组起始位置补零而不是后面；
			if (fa.len > fb.len) {
				int offset = fa.len - fb.len;
				memmove(fb.d + offset, fb.d, fb.len * sizeof(int));
				//把小数部分的值往后偏移，再补零
				//即为再小数后补零
				memset(fb.d, 0, offset * sizeof(int));
				fb.len = fa.len;
				//void *memmove( void* dest, const void* src, size_t count );
				//由src所指内存区域复制count个字节到dest所指内存区域
			}
			bign fans = add(fa, fb, carry);
			// 如果小数部分有进位，让整数部分加一，抹去小数部分最高位 ，考虑进位
			if (carry) {
				bign one;
				one.len = 1;
				one.d[0] = 1;
				ians = add(ians, one, carry);
				fans.d[fans.len--] = 0;//去掉小数位最高位，因为已经补到整数了

			}
			// 删掉所有小数部分低位的 0 
			int offset = 0;
			for (;offset != fans.len;offset++)//确定有多少多余的0
			{
				if (fans.d[offset != 0]) break;
			}
			memmove(fans.d, fans.d + offset, (fans.len - offset) * sizeof(int));
			//把有零的地方覆盖掉，即去0
			fans.len -= offset;
			//输出整数，小数；
			print(ians);
			putchar('.');
			print(fans);
			putchar('\n');
	return 0;
}

