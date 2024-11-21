/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:21:38 by mariverg          #+#    #+#             */
/*   Updated: 2024/01/11 12:33:47 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Función auxiliar para contar el número de subcadenas
static int	count_substrings(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

// Función auxiliar para contar el número de subcadenas
static int	aux_substring(const char *s, char c, char **result)
{
	int	j;
	int	i;
	int	k;
	int	len;

	len = ft_strlen(s);
	i = 0;
	j = 0;
	k = 0;
	while (i < len)
	{
		while (s[i] == c)
			i++;
		k = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > k)
		{
			result[j] = ft_substr(s, k, i - k);
			if (result[j] == NULL)
				return (-1);
			j++;
		}
	}
	return (0);
}

static void	free_split(char **result)
{
	int	i;

	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

// Función principal ft_split
char	**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	char	**result;

	count = count_substrings(s, c);
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		result[i] = NULL;
		i++;
	}
	if (aux_substring(s, c, result) == -1)
	{
		free_split(result);
		return (NULL);
	}
	result[count] = NULL;
	return (result);
}
/* int main()
{
	char *str = "hola mundo como estas";
	char **words = ft_split(str, ' ');
	for(int i = 0; words[i] != NULL; i++) {
	printf("Palabra %d: %s\n", i, words[i]);
	free(words[i]);
	}
  free(words);
	return(0);
} */