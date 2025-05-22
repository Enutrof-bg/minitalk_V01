#include "minitalk.h"

// int ft_power(int n, int power)
// {
// 	int i;
// 	int result;

// 	result = n;
// 	i = 0;
// 	while (i < power)
// 	{
// 		result = result * n;
// 		i++;
// 	}
// 	return (result);
// }

// char *ft_send_char(unsigned char c)
// {
// 	char *bit;
// 	int i;
// 	int binaire;

// 	i = 0;
// 	bit = malloc(sizeof(char) * (8 + 1));
// 	while (i < 8)
// 	{
// 		binaire = c % ft_power(2, 7 - i - 2);
// 		if (binaire == 1)
// 			bit[i] = '1';
// 		else
// 			bit[i] = '0';
// 		printf("bit[%i]%c\n", i, bit[i]);
// 		c = c / 2;
// 		i++;
// 	}
// 	bit[8] = '\0';
// 	return (bit);
// }

void 	ft_base(int c, int i, char *newstr)
{
	if (c >= 2)
	{
		ft_base(c / 2, i - 1, newstr);
	}
	newstr[i] = "01"[c % 2];
}

// char *ft_call_bit(unsigned char c)
// {	
// 	char *bit;
// 	int i;

// 	i = 0;
// 	bit = malloc(sizeof(char) * (8));
// 	while (i < 8)
// 	{
// 		bit[i] = '0';
// 		i++;
// 	}
// 	// bit = ft_base(c, i, bit);
// 	// bit[8] = '\0';
// 	ft_base(c, 7, bit);
// 	bit[8] = '\0';
// 	return (bit);
// }

void	ft_call_bit(unsigned char c, char *bit)
{	
	int i;

	i = 0;
	while (i < 8)
	{
		bit[i] = '0';
		i++;
	}
	ft_base(c, 7, bit);
	bit[8] = '\0';
}

int main()
{
	char bit[9];

	ft_call_bit(116, bit);
	printf("%s\n", bit);
	// printf("%d\n", 1 % 128);
	// char *test = ft_send_char(1);
	// printf("resultat : %s\n\n\n", test);
	// free(test);
	
	// char *test2 = ft_call_bit(127);
	// printf("%s\n", test2);
	// free(test2);

	// ft_putchar(106);
	// write(1, &106, 1);
	// printf("PID %d\n", getpid());
	// char happy[] = { 0xe2, 0x98, 0xba };
	// write(1, happy, 3);

	// pause();

	// // happy[] = { 0xe2, 0x98, 0xba };
	// write(1, happy, 3);

	// char *test = "가 각 갂 갃 간 갅 갆 갇 갈 갉 갊 갋 갌 갍 갎 갏 감 갑 값 갓 갔 강 갖 갗 갘 같 갚 갛 개 객 갞 갟 갠 갡 갢 갣 갤 갥 갦 갧 갨 갩 갪 갫 갬 갭 갮 갯 갰 갱 갲 갳 갴 갵 갶 갷 갸 갹 갺 갻 갼 갽 갾 갿 걀 걁 걂 걃 걄 걅 걆 걇 걈 걉 걊 걋 걌 걍 걎 걏 걐 걑 걒 걓 걔 걕 걖 걗 걘 걙 걚 걛 걜 걝 걞 걟 걠 걡 걢 걣 걤 걥 걦 걧 걨 걩 걪 걫 걬 걭 걮 걯 거 걱 걲 걳 건 걵 걶 걷 걸 걹 걺 걻 걼 걽 걾 걿 ... ";
	// char *test = "éèôê";
	// ft_pustr(test);
}