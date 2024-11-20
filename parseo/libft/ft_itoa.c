/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 08:09:42 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/18 12:56:48 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//calcula el numero de digitos en el numero entero n
static int	get_num_digits(int n)
{
	int	num_digits;
	int	temp;

	num_digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		num_digits++;
	}
	temp = n;
	while (temp != 0)
	{
		temp /= 10;
		num_digits++;
	}
	return (num_digits);
}

static char	*convert_to_string(int n, int num_digits, int sign)
{
	int		i;
	char	*str;

	str = (char *)malloc((num_digits + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[num_digits] = '\0';
	i = num_digits - 1;
	if (n == 0)
		str[i] = '0';
	while (n != 0)
	{
		if (n % 10 < 0)
			str[i] = -(n % 10) + '0';
		else
			str[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		num_digits;
	char	*str;

	sign = 1;
	if (n < 0)
		sign = -1;
	num_digits = get_num_digits(n);
	str = convert_to_string(n, num_digits, sign);
	return (str);
}
/* int main()
{
	int numb1 = 0;
	int numb2 = 123456789;
	int numb3 = -123456789;

	char *c1 = ft_itoa(numb1);
	char *c2 = ft_itoa(numb2);
	char *c3 = ft_itoa(numb3);

	printf("ft_itoa(%d) = %s\n", numb1, c1);
	printf("ft_itoa(%d) = %s\n", numb2, c2);
	printf("ft_itoa(%d) = %s\n", numb3, c3);

	free(c1);
	free(c2);
	free(c3);
	return(0);
} */