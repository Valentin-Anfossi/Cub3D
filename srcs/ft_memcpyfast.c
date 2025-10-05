/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpyfast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 07:13:43 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/02 05:17:14 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	*ft_memcpyfast(void *dest, const void *src, size_t n)
// {
// 	unsigned char	*uc_dest;
// 	const unsigned char	*uc_src;

// 	uc_dest = (unsigned char *)dest;
// 	uc_src = (const unsigned char *)src;

// 	if (n == 0 || dest == src)
// 		return (dest);

// 	while (n >= 8)
// 	{
// 		*(size_t *)uc_dest = *(const size_t *)uc_src;
// 		uc_dest += 8;
// 		uc_src += 8;
// 		n -= 8;
// 	}
// 	while (n--)
// 		*uc_dest++ = *uc_src++;

// 	return (dest);
// }

void *ft_memcpyfast(void *dest, const void *src, size_t n) {
    unsigned long *ldest = (unsigned long *)dest;
    const unsigned long *lsrc = (const unsigned long *)src;
    while (n >= 64) {
        ldest[0] = lsrc[0];
        ldest[1] = lsrc[1];
        ldest[2] = lsrc[2];
        ldest[3] = lsrc[3];
        ldest[4] = lsrc[4];
        ldest[5] = lsrc[5];
        ldest[6] = lsrc[6];
        ldest[7] = lsrc[7];
        ldest += 8;
        lsrc += 8;
        n -= 64;
    }
    while (n >= 8) {
        *(size_t *)ldest = *(const size_t *)lsrc;
        ldest += 2;
        lsrc += 2;
        n -= 8;
    }
    unsigned char *uc_dest = (unsigned char *)ldest;
    const unsigned char *uc_src = (const unsigned char *)lsrc;
    while (n--)
        *uc_dest++ = *uc_src++;
    return dest;
}