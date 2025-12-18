/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:44 by tlorette          #+#    #+#             */
/*   Updated: 2025/07/07 14:35:14 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	char	*str;
	size_t	total_size;

	total_size = count * size;
	if (size && count > SIZE_MAX / size)
		return (NULL);
	p = malloc(total_size);
	if (!p)
		return (NULL);
	str = (char *)p;
	while (total_size > 0)
	{
		*str = 0;
		str++;
		total_size--;
	}
	return (p);
}

static void	*gnl_memcpy(char *dst, char *src, size_t n)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (n > 0)
	{
		dst[i] = src[i];
		i++;
		n--;
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

char	*gnl_join(char *stash, char *buffer, size_t n)
{
	char	*r;
	size_t	len_stash;

	if (!stash)
		len_stash = 0;
	else
		len_stash = ft_strlen(stash);
	r = (char *) malloc ((len_stash + n + 1));
	if (!r)
		return (free(stash), NULL);
	if (stash)
	{
		gnl_memcpy(r, stash, len_stash);
		free(stash);
	}
	gnl_memcpy(r + len_stash, buffer, n);
	r[len_stash + n] = '\0';
	return (r);
}
