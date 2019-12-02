/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:09:39 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/19 12:09:00 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "libft/libft.h"

typedef struct s_data
{
	int fd;
}			t_data;

t_data g_data;

int     output(int str)
{
  write (g_data.fd, &str, 1);
  return (0);
}


int main(int ac , char **av)
{
	g_data.fd = open("/dev/tty", O_RDWR);
	char buf[1024];
	ac = 0;
	struct termios  config;
	if(tcgetattr(0, &config) < 0)
		puts("error");
	config.c_lflag &= ~(ECHO | ICANON);
	if(tcsetattr(0, 0, &config) < 0)
		puts("error");
	int	r = 0;
	tgetent(buf, getenv("TERM"));
	tputs(tgetstr("cl", 0), 0, output);
	int i = 1;	
	int k = 0;
	int j = 0;
	while (1)
	{
		if (k == 0)
		{
			while (av[i])
			{
				ft_putstr(av[i]);
				tputs(tgoto(tgetstr("cm", 0), 0, i), 0, output);
				i++;
			}
			k = 1;
			j = i;
		}
		if (read(0, &r, sizeof(int)) > 0)
		{
			if (r == 4283163 && i > 0)
			{
				tputs(tgoto(tgetstr("cm", 0), 0, --i), 0, output);
				tputs(tgetstr("us", 0), 0, output);
			}
			else if(r == 4348699 && i < j - 2)
			{
				tputs(tgoto(tgetstr("cm", 0), 0, ++i), 0, output);
				tputs(tgetstr("us", 0), 0, output);
			}
		}
	}
}