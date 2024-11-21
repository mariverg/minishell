/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:40:08 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/09 11:09:35 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/* int main()
{
	char c1 = 'c';
	char c2 = '8';
	char c3 = '-';
	printf("%d\n", ft_isascii(c1));
	printf("%d\n", ft_isascii(c2));
	printf("%d\n", ft_isascii(c3));
	return (0);
} */