#include<stdio.h>
#include<stdarg.h>
#include<math.h>
#include<string.h>
#define MAXSIZE_BYTY 64
unsigned char hex_tab[] = { '0','1','2','3','4','5','6','7','8','9',\
                            'a', 'b', 'c', 'd', 'e', 'f' };
unsigned char hex_tab2[] = { '0','1','2','3','4','5','6','7','8','9',\
							'A', 'B', 'C', 'D', 'E', 'F' };





int  out_num(long n, int base,char lead, int maxwidth)
{
	unsigned long m = 0; int count = 0, i = 2,width=0;int base1;
	char buf[MAXSIZE_BYTY]; 
	char * s = buf + sizeof(buf), lead2 = NULL;    // sizeof�������'\0' ��strlen����,ע������sָ��buf��ĩ��

	*--s = '\0';                               //��--���ڸ�ֵ����������Ϊsizeof����������ڵĳ���
	base1 = base;
	if (base ==1)base = 10;
	lead2 = lead;
	if (lead == '1'||lead=='3') { lead = ' '; }
	else if (lead == '2'||lead=='4') { lead = '0'; }
	if (n < 0) { m = -n; }                      //�����������Ǹ�����ȡ��
	else { m = n; }
	if (base == 15)
	{
		do {
			*--s = hex_tab2[m % (base + 1)]; count++;
		} while ((m /= (base + 1)) != 0);
	}
	else {
		do {
			*--s = hex_tab[m % base]; count++;
		} while ((m /= base) != 0);
		//��Ҫ��ӡ�����ִӸ�λ��ʼһλһλ�洢������buf�У�������治��ָ��bufĩ�ˣ�
	}
	if ((lead2 == '1' || lead2 == '2') && (base == 16 || base == 15))
	{
		maxwidth -= 2;
	}
	else if ((lead2 == '1' || lead2 == '2') && base == 8)
	{
		maxwidth -= 1;
	}
	if (lead2 == '-')
	{
		if (n < 0) {
			*--s = '-';    //�����Ļ��Ӹ���
			maxwidth--;
		}
		else if ((lead2 == '3' || lead2 == '4') && n > 0) {
			*--s = '+';
			maxwidth--;
		}
		while (*s != '\0')
		{
			if (base1 != 1) putchar(*s);
			*s++;
			width++;
		}
		if (maxwidth >= count)
		{
			while (maxwidth - count)
			{
				if (base1 != 1) putchar(' ');
				width++;
				maxwidth--;
			}
		}
		return width;
	}
	if (maxwidth >= count)
	{
		while (maxwidth - count)
		{
			*--s = lead;
			maxwidth--;
		}
	}
	if ((lead2 == '1' || lead2 == '2') && (base == 16 || base == 15))
	{
		if(base==15)*--s = 'X';
		if(base==16)*--s = 'x';
		*--s = '0';
	}
	if ((lead2 == '1' || lead2 == '2') && base == 8) { *--s = '0'; }
	if (n < 0)
		*s = '-';    //�����Ļ��Ӹ���
	else if ((lead2 == '3' || lead2 == '4') && n > 0) 
		*s = '+';
	while (*s != '\0')
	{
		if(base1!=1) putchar(*s);
		s++;
		width++;
	}
	return width;
}
void out_s(const char* q,char lead,int i,int j)
{
	int count = strlen(q);
	if (j < count&&j!=0) {   //�����ȱ�ʵ���ַ������ٵ�ʱ��
		if (count <i)
		{
			i -= j;
			while (i--)
				putchar(lead);
		}
		 count = j;
		while (count)
		{
			putchar(*q); q++;
			count--;
		}
		return;
	}
	if (count < i)
	{
		while (i - count)
		{
			putchar(lead); i--;
		}
	}
	for (int count1 = 0; *q != NULL; q++)
	{
		putchar(*q); count1++;
		if (count1 >= count)break;
	}
}
double p_float(double n,int i)
{
	double integer;
	if (i == 0) { i = 6; }
	while (i)
	{
		n =n*10;
		i--;
	}
	if ((modf(n, &integer) * 10 )>= 5) { n +=1;}
	return n;
}
int out_f(double dvar, char lead, char s,int base,int maxwidth, int accuracy)
{
	double integer,fvar;
	int count,count1=0;
	modf(dvar,&integer);
	count = 0; fvar = integer;
	while (dvar > 10)
	{
		count++;
		dvar /= 10;
	}
	while (dvar < 1)
	{
		count++;
		dvar *= 10;
	}
	count1+=out_num(dvar, base, lead, maxwidth); 
	if (base!= 1) 
		putchar('.');
	count1+=out_num(p_float(modf(dvar, &integer), accuracy), base, ' ', 0);
	if (base != 1)
		putchar(s);
	if (fvar > 0&& base != 1)putchar('+');
	else if(fvar <=0 && base != 1) putchar('-');
	count1 += out_num(count, base, '0', 2);
	return count1 += 3;
}
int out_float(double dvar, int base,char lead, int maxwidth,int accuracy)
{
	double integer=0;
	int ivar1 = 0;
	if (lead == '-')
	{
		maxwidth -= out_num(dvar, base, lead, 0) + 1; putchar('.'); ivar1 += maxwidth - 1;
		ivar1 += out_num(p_float(modf(dvar, &integer), accuracy), base, lead, maxwidth);
	}
	else {
		maxwidth -= (accuracy + 1);
		ivar1 += out_num(dvar, base, lead, maxwidth); putchar('.');
		ivar1 += out_num(p_float(modf(dvar, &integer), accuracy), base, ' ', 0);
	}
	return ivar1;
}
void out_g(double dvar, int base, char s, char lead, int maxwidth, int accuracy)
{
	int ivar1, ivar2;
	ivar1 = out_float(dvar, 1, lead, maxwidth, accuracy);
	ivar2 = out_f(dvar, lead, 'e', 1, maxwidth, accuracy); 
	if (ivar1 <= ivar2)
	{
		out_float(dvar, 10, lead, maxwidth, accuracy);
	}
	else
	{
		out_f(dvar, lead, s, 10, maxwidth, accuracy);
	}
}
int tprintf(const char* format, ...)
{
	va_list ap;
	const char* p,*q;
	char cvar,buffer[MAXSIZE_BYTY];
	int ivar,ivar1=0,ivar2=0,count;
	double dvar,integer,fvar;
	if (format == 0)
		return -1;
	va_start(ap, format);/*��ָ��format��ָ��ĵ�ַ��ֵ��ap*/


	for(p = format;*p;++p)
	{
		if (*p != '%')
		{
			putchar(*p);
			continue;
		}
		else{	
			char lead = ' ',lead2=' ';
			int  maxwidth = 0,accuracy=0;

			p++;
			if (*p == '#')
			{
				lead2 ='#';                    
				p++;
			}//����#˵��Ҫ�Ա�׼ʮ����������� #��ǰ���������ͬʱ�����ڸ�ʽ���Ʒ��У�����Ҫ��������������ʶ
			if (*p == '+') {
				lead2 = '+';
				p++;
			}
			if (*p == '0') {                   //������0��˵��ǰ������0
				lead = '0';
				p++;
			}//��-�����ڸ�ʽ���Ʒ���ǰ��������Ч��ֱ����lead����ʶ
			if (*p == '-') {                   
				lead ='-';
				p++;
			}
			if (lead2 == '#' && lead == ' ') { lead = '1'; }
			else if (lead2 == '#' && lead == '0') { lead = '2'; }
			else if (lead2 == '+' && lead == ' ') { lead = '3'; }
			else if (lead2 == '+' && lead == '0') { lead = '4'; }
			while (*p >= '0' && *p <= '9') {		 //�����ŵ���������С��ȣ������С���
				maxwidth *= 10;
				maxwidth += (*p - '0');
				p++;
			}
			if (*p == '.')
			{
				p++;
				while (*p >= '0' && *p <= '9') {		 //�����ŵ������Ǿ���
					accuracy *= 10;
					accuracy += (*p - '0');
					p++;
				}
			}
			switch (*p)
			{
			case 'd':
				ivar = va_arg(ap, int);
				if (accuracy >= maxwidth) { 
					if (ivar < 0) maxwidth = accuracy + 1;
					else maxwidth = accuracy; 
					lead = '0'; }
				out_num(ivar, 10, lead, maxwidth);/*���apָ��ָ��Ĳ�����ֵ������apָ����һ����intָ����ǰ��õĲ�������*/
				break;
			case 'i':
				ivar = va_arg(ap, int);
				if (accuracy >= maxwidth) {
					if (ivar < 0) maxwidth = accuracy + 1;
					else maxwidth = accuracy;
					lead = '0';
				}
				out_num(ivar, 10, lead, maxwidth);
				break;
			case 's':
				q = va_arg(ap, char*);
				out_s(q, lead, maxwidth, accuracy);
				break;
			case 'c':
				putchar(va_arg(ap, char));
				break;


			case 'o':
				out_num(va_arg(ap, unsigned int), 8,lead, maxwidth);
				break;
			case 'u':
				out_num(va_arg(ap, unsigned int), 10, lead, maxwidth);//����޷�����ʱҲ������%d
				break;								  //��ʱ�ǽ��޷���ת�����з�������Ȼ�������
			case 'x':								  //����̵�ʱ����ò�Ҫ��ôд����Ϊ����Ҫ����һ��ת����ʹ CPU ����һ�����ù���
				out_num(va_arg(ap, unsigned int), 16, lead, maxwidth);
				break;
			case 'X':			
				out_num(va_arg(ap, unsigned int), 15, lead, maxwidth);
				break;
			case 'b':								  
				out_num(va_arg(ap, unsigned int), 2, lead, maxwidth);
				break;
			case '%':
				putchar('%');
				break;

            //#��ʽ
			case 'f':
				dvar = va_arg(ap, double); 
				out_float(dvar,10,lead,maxwidth, accuracy);
				break;
			case 'g':
				dvar = va_arg(ap, double); 
				out_g(dvar, 10,'e', lead, maxwidth, accuracy);
				break;
			case 'G':
				dvar = va_arg(ap, double);
				out_g(dvar, 10,'E', lead, maxwidth, accuracy);
				break;
			case 'e':
				dvar = va_arg(ap, double); 
				out_f(dvar, lead,'e',10, maxwidth, accuracy);
				break;
			case 'E':
				dvar = va_arg(ap, double);
				out_f(dvar, lead, 'E',10, maxwidth, accuracy);
				break;
			default:
				putchar(*p);
				break;
			}
		}
	}
	va_end(ap);/*��ap��ֵָ��NULL*/
	return 1;
}

int main()
{
	double dvar = 341.2347858594324,fvar=1.2345678,dvar1=345675.456,dvar2=0.00343;
	int ivar = -4765;
	int var = 345678;
	char s[8] = "sfwert",s2[]= "asffgghhhabcde";
	char c = 'w';
	tprintf("���������1.2345678(��ʽ%%-9.5f):%-9.5f*****\n",fvar);
	tprintf("���������341.2347858594324(��ʽ%%+09.3f):%+09.3f\n", dvar);
	tprintf("���������341.2347858594324(��ʽ%%.9f):%.9f\n\n", dvar);
	tprintf("���������1.2345678(��ʽ%%g):%g\n", fvar);
	tprintf("���������341.2347858594324(��ʽ%%g):%g\n", dvar);
	tprintf("���������0.00343(��ʽ%%e):%e\n", dvar2);
	tprintf("���������345675.456(��ʽ%%e):%e\n\n", dvar1);

	tprintf("�������-4765(��ʽΪ%%+06d):%+06d\n�������-4765(��ʽ%%.9d):%.9d\n", ivar,ivar); 
	tprintf("�������-4765(��ʽ%%-7d):%-7d***\n\n", ivar);

	tprintf("����ַ���sfwert(��ʽΪ%%09.3s):%09.3s\n", s);
	tprintf("����ַ���sfwert(��ʽΪ%%3.3s):%03.3s\n", s);
	tprintf("����ַ���sfwert(��ʽΪ%%09s):%09s\n\n", s);

	tprintf("��ʮ����345678���Ϊ�˽�����(��ʽ%%#09o)��%#09o\n",var);
	tprintf("��ʮ����345678���Ϊʮ��������(��ʽ%%#09x):%#09x  ��д(��ʽ%%#X):%#X\n", var,var);

	tprintf("\n***************************printf���*******************************\n");

	printf("���������1.2345678(��ʽ%%-9.5f):%-9.5f*****\n", fvar);
	printf("���������341.2347858594324(��ʽ%%+09.3f):%+09.3f\n", dvar);
	printf("���������341.2347858594324(��ʽ%%.9f):%.9f\n\n",dvar);
	printf("���������1.2345678(��ʽ%%g):%g \n", fvar);
	printf("���������341.2347858594324(��ʽ%%g):%g\n", dvar);
	printf("���������0.00343(��ʽ%%e):%e\n", dvar2);
	printf("���������345675.456(��ʽ%%e):%e\n\n", dvar1);

	printf("�������-4765(��ʽΪ%%06d):%+06d \n�������-4765(��ʽ%%.9d):%.9d\
 \n�������-4765(��ʽ%%-7d):%-7d***\n\n", ivar,ivar,ivar);

	printf("����ַ���sfwert(��ʽΪ%%09.3s):%09.3s\n", s);
	printf("����ַ���sfwert(��ʽΪ%%3.3s):%3.3s\n", s);
	printf("����ַ���sfwert(��ʽΪ%%09s):%09s\n\n", s);

	printf("��ʮ����345678���Ϊ�˽�����(��ʽ%%#09o)��%#09o\n", var);
	printf("��ʮ����345678���%Ϊʮ��������(��ʽ%%#09x)��%#09x   ��д(��ʽ%%#X):%#X\n", var,var);

}

