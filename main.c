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

#include "ft_select.h"

t_node		*ft_stock(char **av)
{
	 t_node	*list;
	 t_node	*node;
	 int		i;

	 if (!(list = ft_memalloc(sizeof(t_node))))
		  return (0);
	 i = 0;
	 node = list;
	 while (av[i])
	 {
		  list->content = ft_strdup(av[i]);
		  list->index = i;
		  if (av[i + 1])
			   list->next = ft_memalloc(sizeof(t_node));
		  else
			   list->next = NULL;
		  list = list->next;
		  i++;
	 }
	 return (node);
}

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

char *get_content(t_node *node, int i)
{	
	int c = 0;
	while(node)
	{
		if(c == i)
		{
			return (node->content);
		}
		c++;
		node =node->next;
	}
	return (NULL);
}
void	clear_node(t_node *node, int i)
{
	while(node)
	{
		if(node->index == i)
		{
			tputs(tgoto(tgetstr("cm", 0), 0, i), 0, output);
			if (node->check == 1)
				tputs(tgetstr("mr", 0), 0, output);
			ft_putstr_fd(node->content,g_data.fd);
			tputs(tgetstr("me", 0), 0, output);
		}
		node =node->next;
	}
}

void	clear_node1(t_node *node, int i)
{
	while(node)
	{
		if(node->index == i)
			tputs(tgoto(tgetstr("cm", 0), 0, i), 0, output);
		node =node->next;
	}
}
void    ft_select(t_node *node, int i)
{
	while (node)
	{
		if (node->index == i && node->check == 0)
		{
			clear_node1(node,i);
			tputs(tgetstr("mr", 0), 0, output);
			ft_putstr_fd(node->content,g_data.fd);
			node->check = 1;
			tputs(tgoto(tgetstr("cm", 0), 0, i), 0, output);
			tputs(tgetstr("me", 0), 0, output);
		}
		else if (node->index == i && node->check == 1)
		{
			clear_node1(node,i);
			node->check = 0;
			ft_putstr_fd(node->content,g_data.fd);
			tputs(tgoto(tgetstr("cm", 0), 0, i), 0, output);
			tputs(tgetstr("me", 0), 0, output);
		}
		node = node->next;
	}
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
	int r = 0;
	tgetent(buf, getenv("TERM"));
	tputs(tgetstr("ti", 0), 0, output);
	int i = 0;
	int k = 1;
	int l = 0;
	t_node *node, *head;
	head = ft_stock(av);
	tputs(tgetstr("vi", 0), 0, output);
	node = head;
	while (1)
	{
		if (k == 1)
		{
			while(head)
			{
				tputs(tgoto(tgetstr("cm", 0), 0, i), 0, output);
				ft_putstr_fd(head->content,g_data.fd);
				head->check = 0;
				head = head->next;
				i++;
			}
			k = -1;
			l = i;
			i = 0;
			tputs(tgoto(tgetstr("cm", 0), 0, i), 0, output);
			tputs(tgetstr("us", 0), 0, output);
			ft_putstr_fd(node->content,g_data.fd);
			tputs(tgetstr("me", 0), 0, output);
		}
		r = 0;
		if (read(0, &r, sizeof(int)) > 0)
		{
			if (r == 4283163)
			{
				if (i > 0)
				{
					clear_node(node, i);
					--i;
					if (node->check == 0)
					{
						tputs(tgoto(tgetstr("cm", 0), 0, i), 0, output);
						tputs(tgetstr("us", 0), 0, output);
						ft_putstr_fd(get_content(node,i),g_data.fd);
						tputs(tgetstr("ue", 0), 0, output);
					}
				}
				else if (i == 0)
				{
					clear_node(node, i);
					i = l - 1;
					if (node->check == 0)
					{
						tputs(tgoto(tgetstr("cm", 0), 0, i), 0, output);
						tputs(tgetstr("us", 0), 0, output);
						ft_putstr_fd(get_content(node,i),g_data.fd);
						tputs(tgetstr("ue", 0), 0, output);
					}
				}
			}
			else if (r == 4348699)
			{
				if (i < l - 1)
				{
					clear_node(node, i);
					++i;
					if (node->check == 0)
					{
						tputs(tgoto(tgetstr("cm", 0), 0, i), 0, output);
						tputs(tgetstr("us", 0), 0, output);
						ft_putstr_fd(get_content(node,i),g_data.fd);
						tputs(tgetstr("ue", 0), 0, output);
					}
				}
				else if (i == l - 1)
				{
					clear_node(node, i);
					i = 0;
					if (node->check == 0)
					{
						tputs(tgoto(tgetstr("cm", 0), 0, i), 0, output);
						tputs(tgetstr("us", 0), 0, output);
						ft_putstr_fd(get_content(node,i),g_data.fd);
						tputs(tgetstr("ue", 0), 0, output);
					}
				}
			} 
			else if (r == 32)
				ft_select(node, i);
			else if (r == 10)
			{
				tputs(tgetstr("te", 0), 0, output);
				while (node)
				{
					if (node->check == 1)
						ft_putendl_fd(node->content, 0);
					node = node->next;
				}
				tputs(tgetstr("ve", 0), 0, output);
				exit(0);
			}
		}
	}
}


