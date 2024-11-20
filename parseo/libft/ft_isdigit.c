/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:29:07 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/10 17:43:22 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/* int main()
{
	char c1 = '7';
	char c2 = 'h';
	printf("%d\n", ft_isdigit(c1));
	printf("%d\n", ft_isdigit(c2));
	return (0);
} */