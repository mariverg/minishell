/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:43:21 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/16 13:28:27 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	s;
	int	val;

	s = 1;
	val = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-')
		s = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		val = val * 10 + (*str - '0');
		str++;
	}
	val *= s;
	return (val);
}
/* int main()
{
    const char  *str1 = "-12345";
	const char  *str2 = "216565";
	const char  *str3 = "-2147483648";
	const char  *str4 = "2147483647";

	printf("ft_atoi(str1) = %d\n", ft_atoi(str1));
	printf("ft_atoi(str2) = %d\n", ft_atoi(str2));
	printf("ft_atoi(str3) = %d\n", ft_atoi(str3));
	printf("ft_atoi(str4) = %d\n", ft_atoi(str4));
	return (0);
} */