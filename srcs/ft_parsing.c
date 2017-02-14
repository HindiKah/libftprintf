/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:46:51 by ybenoit           #+#    #+#             */
/*   Updated: 2017/02/11 13:35:12 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_arg		*ft_init_value(t_arg *tvar, va_list all_arg, t_funf *my_funf)
{
	int i;

	i = 0;
	while (ft_strchr(my_funf[i].flag, tvar->type) == NULL)
		i++;
	tvar = my_funf[i].f(tvar, all_arg);
	return (tvar);
}
