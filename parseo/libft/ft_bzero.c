/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:04:15 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/09 11:35:16 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		ft_memset(str, '\0', n);
		i++;
	}
}
/* int	main()
{
	char str[22] = "hola como estas mundo";
	ft_bzero(str, 2);
	printf("str: %s\n", &str[2]);
	return (0);
} */