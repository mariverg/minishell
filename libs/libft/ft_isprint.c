/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:49:16 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/09 11:13:45 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/* int main()
{
	char c1 = 'c';
	char c2 = '8';
	char c3 = '-';
	printf("%d\n", ft_isprint(c1));
	printf("%d\n", ft_isprint(c2));
	printf("%d\n", ft_isprint(c3));
	return (0);
} */