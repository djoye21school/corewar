/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 11:39:19 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/15 11:39:32 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int 		exec_magic(int fd)
{
	t_4bytes		num;
	unsigned int	c;

	read(fd, &c, 4);
	num.hex = c;
	num.field.o_temp = num.field.octet1;
	num.field.octet1 = num.field.octet4;
	num.field.octet4 = num.field.o_temp;
	num.field.o_temp = num.field.octet2;
	num.field.octet2 = num.field.octet3;
	num.field.octet3 = num.field.o_temp;
	if (num.hex == COREWAR_EXEC_MAGIC)
		return (1);
	return (0);
}

void		replace_ch(t_vm *vm, int n, t_champion *ch)
{
	t_champion	*buf;
	t_champion	*tmp;
	int			i;

	i = n;
	buf = vm->champ[n - 1];
	vm->champ[n - 1] = ch;
	vm->champ[n - 1]->n = n;
	while (i < MAX_PLAYERS)
	{
		if (!vm->champ[i])
		{
			vm->champ[i] = buf;
			break;
		}
		else if (!vm->champ[i]->n)
		{
			tmp = vm->champ[i];
			vm->champ[i] = buf;
			buf = tmp;
			free(tmp);
		}
		i++;
	}
}

void		champ_in_vm(t_champion *ch, t_vm *vm, int n)
{
	int			i;

	i = 0;
	if (n < 0)
	{
		while (i < MAX_PLAYERS && vm->champ[i])
			i++;
		vm->champ[i] = ch;
	}
	else
	{
		if (!vm->champ[n - 1])
		{
			vm->champ[n - 1] = ch;
			vm->champ[n - 1]->n = n;
		}
		else
			replace_ch(vm, n, ch);
	}
}

int			check_n(t_vm *vm, int n)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->champ[i])
			if (vm->champ[i]->n && vm->champ[i]->n == n)
				return (0);
		i++;
	}
	return (1);
}

int 		check_ch_name(char **av, int i)
{
	int l;

	l = ft_strlen(av[i]);
	if (av[i][l - 1] != 'r' || av[i][l - 2] != 'o' || av[i][l - 3] != 'c'
		|| av[i][l - 4] != '.')
		return (0);
	return (1);
}
