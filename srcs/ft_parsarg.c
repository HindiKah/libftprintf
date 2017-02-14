/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsarg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:00:01 by ybenoit           #+#    #+#             */
/*   Updated: 2017/02/11 13:54:49 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_arg		*parse_this_arg(t_arg *tvar, const char *format);

t_arg		*parse_args(t_arg *tvar, const char *format)
{
	int		i;
	int		j;
	int		i_tvar;

	tvar = (t_arg*)malloc(sizeof(t_arg) * ft_countparams(format) + 1);
	i = 0;
	j = 0;
	i_tvar = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			j = i;
			while (format[j] && !ft_strchr("sSpdDioOuUxXcC", format[j]))
				j++;
			tvar->type = format[j];
			tvar[i_tvar].argend = j;
			tvar->index = i;
			parse_this_arg(&tvar[i_tvar], format + i + 1);
			i = tvar[i_tvar].argend;
			i_tvar++;
		}
		i++;
	}
	tvar[i_tvar].type = 'e';
	return (tvar);
}

t_arg		*parse_this_arg(t_arg *tvar, const char *format)
{
	int i;

	i = 0;
	init_pflag(tvar, format);
	while (*format && !ft_strchr(" 0123456789sSpdDioOuUxXcC", *format))
		format++;
	init_precision(tvar, format);
	while (*format && ft_strchr(" 0123456789.", *format))
			format++;
	init_flag(tvar, format);
	if (ft_strchr("di", tvar->type))
		tvar->base = 10;
	else if (ft_strchr("pxX", tvar->type))
		tvar->base = 16;
	else if (ft_strchr("o", tvar->type))
		tvar->base = 8;
	else
	tvar->base = 0;
	return (tvar);
}

t_arg		*init_precision(t_arg *tvar, const char *format)
{
	int dot;
	int p0;
	int space;

	tvar->p = 0;
	tvar->p0 = 0;
	space = (*format == ' ') ? 1 : 0;
	p0 = 0;
	dot = 0;
	if ((format = whatisnext_c(format, ' '))[0] == '0')
		p0 = 1;
	tvar->p = ft_atoi(format);
	while (*format && (*format != '.' || ft_strchr("sSpdDioOuUxXcChljz%", *format)))
		format++;
	if (*format == '.')
	{
		dot = 1;
		format++;
	}
	tvar->p0 = ft_atoi(format);
	treat_precision(tvar, dot, p0, space);
	return(tvar);
}

t_arg		*treat_precision(t_arg *tvar, int dot, int p0,  int space)
{
	tvar->p = (tvar->p0 >= tvar->p && space == 1) ? tvar->p0 + 1 : tvar->p;
	tvar->p0 = (tvar->p0 == 0 && dot == 0 && p0 == 1) ? tvar->p : tvar->p0;
	tvar->p = (tvar->p < tvar->p0 && space == 0 
			&& !ft_strchr("sScC",tvar->type)) ? tvar->p0 : tvar->p;
	return(tvar);
}

t_arg		*init_flag(t_arg *tvar, const char *format)
{
	if (*format + 2)
	{
		tvar->flag = (ft_strchr("hljz",  *format)) ? *format : '0';
		if ((tvar->flag == 'h' || tvar->flag == 'l') && tvar->flag == format[1])
			tvar->flag = ft_toupper(tvar->flag);
	}
	else
		tvar->flag = '0';
	return (tvar);
}

