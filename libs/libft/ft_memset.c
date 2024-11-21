/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:56:58 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/09 12:32:35 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)str)[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

/* int main()
{
	char str[10] = "aaaaaaaaa";

	ft_memset(str, 'A', 5);
	printf("str: %s\n", str);

	return (0);
} */