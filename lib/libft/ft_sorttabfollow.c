/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorttabfollow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 14:31:24 by lvasseur          #+#    #+#             */
/*   Updated: 2018/05/24 15:20:24 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sorttabfollow(char ***tab, char ***follower, int nbstrings)
{
	char	*tmp;
	int		i;
	char	**taba;
	char	**tabb;

	taba = *tab;
	tabb = *follower;
	i = 1;
	while (i < nbstrings)
	{
		if (ft_strcmp(taba[i], taba[i - 1]) < 0)
		{
			tmp = taba[i];
			taba[i] = taba[i - 1];
			taba[i - 1] = tmp;
			tmp = tabb[i];
			tabb[i] = tabb[i - 1];
			tabb[i - 1] = tmp;
			i = 0;
		}
		i++;
	}
}
