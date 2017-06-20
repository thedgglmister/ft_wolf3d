/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 21:42:27 by biremong          #+#    #+#             */
/*   Updated: 2017/05/19 21:42:30 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t bytes)
{
	void	*addr;

	addr = malloc(bytes);
	if (!addr)
		ft_error("Malloc Error");
	return (addr);
}
