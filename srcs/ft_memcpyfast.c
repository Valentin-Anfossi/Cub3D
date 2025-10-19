/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpyfast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi/jelucian <vanfossi@student.42n    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 07:13:43 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/19 02:23:35 by vanfossi/je      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memcpyfast(void *dest, const void *src, size_t n)
{
	unsigned char		*uc_dest;
	const unsigned char	*uc_src;

	uc_dest = (unsigned char *)dest;
	uc_src = (const unsigned char *)src;
	if (n == 0 || dest == src)
		return (dest);
	while (n >= 8)
	{
		*(size_t *)uc_dest = *(const size_t *)uc_src;
		uc_dest += 8;
		uc_src += 8;
		n -= 8;
	}
	while (n--)
		*uc_dest++ = *uc_src++;
	return (dest);
}
