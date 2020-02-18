/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:46:39 by stross            #+#    #+#             */
/*   Updated: 2020/02/18 11:49:12 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int argc, char **argv)
{
	t_head		*head;

	if (argc != 2)
		error_usage();
	if (!(head = (t_head*)ft_memalloc(sizeof(t_head))))
		error_allocation();
	create_file(argv, head);
	free_head(head);
	return (0);
}