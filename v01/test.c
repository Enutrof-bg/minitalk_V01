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

char *ft_call_bit(unsigned char c)
{	
	char *bit;
	int i;

	i = 0;
	bit = malloc(sizeof(char) * (8));
	while (i < 8)
	{
		bit[i] = '0';
		i++;
	}
	// bit = ft_base(c, i, bit);
	// bit[8] = '\0';
	ft_base(c, 7, bit);
	bit[8] = '\0';
	return (bit);
}

int main()
{
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

	char *test = "Bonjour";
	ft_pustr(test);
}