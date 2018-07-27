/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averemiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 14:13:46 by averemiy          #+#    #+#             */
/*   Updated: 2018/07/27 14:22:04 by averemiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
#define VM_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "op.h"
# include "print_ncurses.h"

typedef struct			s_rule
{
	int					aff;
	int					visual;
	int					dump;
}						t_rule;

typedef struct			s_player
{
	unsigned char		*p_name;
	unsigned char		*p_comment;
	unsigned int		*p_code;
	int					p_id;
	int					p_size;
	int					p_live;
	int					stand;
	struct s_player		*next;
}						t_player;

typedef struct			s_pc
{
	int					carry;
	int					parent;
	unsigned int		reg[16];
	int					live;
	int					command;
	int					cicles;
	int					size;
	unsigned int		arg[3];
	int					change;
	struct s_pc			*next;
}						t_pc;

typedef struct			s_op
{
	char				*name;
	int					arg;
	int					weight[3];
	int					number;
	int					cicles;
	char				*des;
	int					codage;
	int					carry;
	int					label;
}						t_op;

void			get_command(unsigned char *map, t_pc *pc);
int				check_cycle(t_player *p, int j, int cycle);
t_op			op_tab[17];
void			set_bit(int place, unsigned char *map, unsigned int number, t_pc *pc);
void			print_map(unsigned char *map, t_pc *pc, t_player *p, int y);
void			solve(t_player *p, unsigned char *map, t_pc *pc_1);
char			*ft_dec_to_binary(int tmp);
int				bit_mask(int stand, int size);
int				find_weight(int stand, int cmd);
unsigned int	take_arg(unsigned char *map, int size, int stand);
int				get_map(unsigned char *map, int coord);
int				take_bit(t_pc *pc, int number, int arg);
int				red_arg(unsigned char *map, t_pc *pc, int size);
void			sti(unsigned char *map, t_pc **pc);
void			put_in_map(t_player *p, unsigned char *map);
void			zjmp(unsigned char *map, t_pc **pc);
void			live(unsigned char *map, t_player *p, t_pc *pc);
void			and(unsigned char *map, t_pc **pc);
void			st(unsigned char *map, t_pc **pc);
void			ld(unsigned char *map, t_pc **pc);
void			fork_1(unsigned char *map, t_pc *pc, t_pc **main);
void			xor(unsigned char *map, t_pc **pc);
void			add(unsigned char *map, t_pc **pc);
void			sub(unsigned char *map, t_pc **pc);
void			ldi(unsigned char *map, t_pc **pc);
void			lldi(unsigned char *map, t_pc **pc);
void			delete_one_pc(t_pc **pc);
t_player		*read_p_from_f(char *name, int id);
void			delete_pc(t_pc **pc, int j);
int				set_place(int place);
int				c_c_sti(int codege);
int				get_size(unsigned char *map, int cmd, int size);
int				c_c_ld_lld(int codage);
int				c_c_sti(int codage);
int				c_c_add_sub(int codage);
int				c_c_and_or_xor(int codage);
int				c_c_ldi_lldi(int codage);
int				c_c_st(int codage);
int				create_with_number(t_player **p, int size, int i, char **argv);
int				try_to_read(t_player **p, char *str, int nbr);
int				read_dump(t_rule *rule, char **argv, int argc, int i);
t_pc			*create_pc(t_player *p);
int				count_player(t_player *p);

typedef struct		s_ncurse
{
	int				win;
	int				players;
	int				step;
	int				proc;
	int				pause;
	int				debug;
	char			**names;
	int				sizes[4];
	int				changes[5];
	unsigned char	*tab;
}					t_ncurse;
void				print_ncurses(t_ncurse *crwr, t_pc *pc);
void				init_colors(void);
void				print_template(int x, int y, t_ncurse *crwr);
void				print_finish(t_ncurse *crwr, int i, char ch);
void				print_field_start(t_ncurse *crwr, int i, int y, int x);
void				print_help(void);
void				print_music(t_ncurse *crwr);
void				sighandler(int signum);
void				print_check_buttons(t_ncurse *crwr, char ch);
void				check_pause(t_ncurse *crwr, int pause, char ch);
void				step_by_step(t_ncurse *crwr);

#define BUF_SIZE 1
#endif