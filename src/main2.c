/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:13:39 by lvasseur          #+#    #+#             */
/*   Updated: 2018/11/30 16:15:07 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			time_handle(void)
{
	float			current_frame;
	static float	last_frame = 0.0f;
	static int		fps = 0;
	static float	fpstime = 0.0f;

	current_frame = glfwGetTime();
	if (last_frame == 0.0f)
		last_frame = current_frame;
	g_delta_time = current_frame - last_frame;
	last_frame = current_frame;
	fps++;
	fpstime += g_delta_time;
	if (fpstime >= 1.0f)
	{
		ft_putstr("FPS: ");
		ft_putnbr(fps);
		ft_putchar('\n');
		fpstime -= 1.0f;
		fps = 0;
	}
}

t_obj			init_obj(char **av)
{
	t_obj	obj;

	obj.vertex = NULL;
	obj.indices = NULL;
	obj.uv = NULL;
	obj.isize = 0;
	obj.vsize = 0;
	obj.uvsize = 0;
	if (parse(av[1], &obj) == -1)
	{
		obj.vsize = -1;
		return (obj);
	}
	obj.uv = generate_uv(obj.vertex, obj.vsize, &obj.uvsize);
	return (obj);
}
