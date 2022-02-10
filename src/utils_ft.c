#include <unistd.h>

void	ft_putnbr_u(unsigned int n)
{
	char	c;

	c = '0' + (n % 10);
	if (n < 10)
		write(1, &c, 1);
	else
	{
		ft_putnbr_u(n / 10);
		write(1, &c, 1);
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	ans;

	i = 0;
	ans = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = (str[i] == '-') * (-1) + (str[i] == '+');
		i++;
	}
	while (str[i] == '0')
		i++;
	if (str[i] > '0' && str[i] <= '9')
		ans = sign * (str[i++] - '0');
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((ans * 10 + sign * (str[i] - '0') > 0) != (ans > 0))
			return (0);
		ans = ans * 10 + sign * (str[i] - '0');
		i++;
	}
	return (ans);
}