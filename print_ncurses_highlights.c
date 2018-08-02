/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ncurses_highlights.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 13:21:23 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/02 13:21:25 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_highlights(t_ncurse *crwr, int s[], int x, int y)
{
	int		i;

	i = -1;
	while (++i < 4096)
	{
		if (s[i] > 0)
		{
			attron(COLOR_PAIR(s[i]) | A_STANDOUT);
			mvprintw(y + i / 64, (x + (i % 64 * 3)), "%.2X", crwr->tab[i]);
			attroff(COLOR_PAIR(s[i]) | A_STANDOUT);
			s[i] *= -1;
		}
		else if (s[i] < 0)
		{
			if (crwr->chng[i] == 0)
			{
				attron(COLOR_PAIR(2));
				mvprintw(y + i / 64, (x + (i % 64 * 3)), "%.2X", crwr->tab[i]);
				attroff(COLOR_PAIR(2));
			}
			else
			{
				attron(COLOR_PAIR(crwr->chng[i]));
				mvprintw(y + i / 64, (x + (i % 64 * 3)), "%.2X", crwr->tab[i]);
				attroff(COLOR_PAIR(crwr->chng[i]));
			}
			s[i] = 0;
		}
	}
}

void		check_highlites(t_ncurse *crwr, t_pc *temp, char *cmd)
{
	static int	s[4096];
	int			i;
	int			x;
	int			y;

	x = 4;
	y = 9;
	if (ft_strequ(cmd, "write"))
	{
		i = (temp->size) % 4096;
		s[i] = (crwr->chng[i] == 0 ? 0 : crwr->chng[i]);
	}
	if (ft_strequ(cmd, "print"))
		print_highlights(crwr, s, x, y);
}
