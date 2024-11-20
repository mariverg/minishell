/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:33:35 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/15 11:50:07 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
/* int main()
{
	char c1 = '9';
	char c2 = 'A';
	char c3 = '@';
	printf("%d\n", ft_isalnum(c1));
	printf("%d\n", ft_isalnum(c2));
	printf("%d\n", ft_isalnum(c3));
	return (0);
} */