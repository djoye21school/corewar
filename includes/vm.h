/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 10:21:55 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/31 16:15:42 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdio.h>
# include <unistd.h>
# include "./op.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <time.h>
# include <stdbool.h>
#include <ncurses.h>

#define SIZE_64				64
#define HEIGHT (MEM_SIZE / SIZE_64 + 4)
#define WIDTH	(SIZE_64 * 3 + 100)
#define COMMENT SIZE_64 * 3 + 5
#define KEY_SPACE 32

typedef struct			s_champion
{
	unsigned int		n;
	char				name[PROG_NAME_LENGTH + 1];
	char				com[COMMENT_LENGTH + 1];
	unsigned int		size;
	char 				*code;
}						t_champion;

typedef struct		s_cur
{
	int				id;
	int 			id_player;
	int 			pos;
	int				step;
	int 			carry;
	unsigned char	operation;
	int 			reg[REG_NUMBER];
	int 			cyc_before_op;
	int 			last_cyc_live;
	struct s_cur	*next;
}					t_cur;

typedef struct	s_bit_field
{
	int			octet1 : 8;
	int			octet2 : 8;
	int			octet3 : 8;
	int			octet4 : 8;
}				t_bit_field;

typedef	union	u_4bytes
{
	t_bit_field field;
	int			hex;
}				t_4bytes;

typedef struct		s_arg
{
	unsigned char	arg_0 : 2;
	unsigned char	arg_3 : 2;
	unsigned char	arg_2 : 2;
	unsigned char	arg_1 : 2;
}					t_arg;

typedef	union		u_4bits
{
	t_arg			field;
	unsigned char	arg;
}					t_4bits;

typedef struct		s_op
{
	char 			*name;
	int				arg_count;
	int				arg_type[3];
	int 			code;
	int 			need_cycles;
	char 			*opisanie;
	int 			code_type_arg;
	int 			dir_size; // 0 это 4, 1 это 2
}					t_op;

typedef struct		s_vm
{
	int				dump;
	int				d;
	int				color;
	int				players;
	int 			global;
	int 			check;
	t_champion		*champ[MAX_PLAYERS];
	unsigned char	arena[MEM_SIZE];
	char			map_color[MEM_SIZE];
	t_cur			*curs;
}					t_vm;

int 	init_champ(int *i, char **av, int n, t_vm *vm);
void	champ_in_vm(t_champion *ch, t_vm *vm, int n);
int 	exec_magic(int fd);
int 	build_arena(t_vm *vm);
int 	check_n(t_vm *vm, int n);
int 	check_ch_name(char **av, int i);

int 	cur_init(t_vm *vm);

int		print_arena(t_vm *vm, int step, int size);
int 	war_coming(t_vm *vm);
int     check_value(t_op *op_tab, unsigned char id_op, unsigned char arg);

WINDOW	*init_visu(WINDOW *vm_window);
void	print_visu(WINDOW *vm_window, t_vm *vm, int step);
void	print_matrix(WINDOW *vm_window, t_vm *vm);
void	print_sub_win(t_vm *vm, WINDOW *vm_window);

int     check_arg(t_op *op_tab, unsigned char id_op, unsigned char arg);

#endif
