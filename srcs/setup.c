/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:57:55 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/20 15:20:16 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#include "libft.h"

#include <fcntl.h>

#include <stdlib.h>

char				setup(t_corewar *corewar, char **args) {
	corewar->memory = ft_memalloc(MEM_SIZE);

	while (*args)
	{
		int			fd = open(*args, O_RDONLY);
		char		*buf = ft_memalloc(sizeof(header_t));

		read(fd, buf, sizeof(header_t));
		header_t	*head = (void*)buf;
		printf( "Magic      %x\n", COREWAR_EXEC_MAGIC);
		printf( "Prog_Magic %x\n", head->magic);

		printf( "Prog_Magic %x\n", head->magic >> 8 & 0xff);
		printf( "Prog_Magic %x\n", head->magic >> 16 & 0xff);
		printf( "Prog_Magic %x\n", head->magic >> 24 & 0xff);
		printf("Name %s\n", head->prog_name);
		printf("Size %u\n", head->prog_size);
		printf("Max  %u\n", CHAMP_MAX_SIZE);
		printf("Comment %s\n", head->comment);
		args++;
	}
	return (1);
}
