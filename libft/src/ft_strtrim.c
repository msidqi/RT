/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 17:18:42 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/19 01:49:17 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_whitespacesskip(const char *s)
{
	size_t	i;
	size_t	len;
	char	*tab;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		if (s[i + 1] == '\0')
			return (ft_strdup(""));
		i++;
	}
	s = s + i;
	len = (ft_strlen(s) - 1);
	while ((s[len] == ' ' || s[len] == '\n' || s[len] == '\t') && len > i)
		len--;
	if (!(tab = ft_strsub(s, 0, len + 1)))
		return (NULL);
	return (tab);
}

char		*ft_strtrim(char const *s)
{
	char *tab;

	if (!s)
		return (NULL);
	if (!(tab = ft_whitespacesskip(s)))
		return (NULL);
	return (tab);
}
