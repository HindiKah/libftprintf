/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 21:12:48 by ybenoit           #+#    #+#             */
/*   Updated: 2017/02/11 14:02:17 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char		*final_print(const char *format, t_arg *tvar, va_list all_arg);
size_t			ft_arglen(t_arg *tvar);

int			ft_printf(const char *format, ...)
{
	va_list		all_arg;
	t_func		*my_func;
	t_funf		*my_funf;
	t_arg		*tvar;

	tvar = (t_arg*)malloc(sizeof(t_arg) * ft_countparams(format));
	my_func = NULL;
	my_funf = NULL;
	va_start(all_arg, format);
	my_func = ft_init_func(my_func);
	my_funf = ft_init_funf(my_funf);
	tvar = parse_args(tvar, format);
	ft_do_all_fun(my_funf, my_func, all_arg, tvar);

/*
	int i = 0;
	printf("\nFT_PRINTF\nstruct s_arg:\n{\n\tflag = %c\n\ttype= %c\n\tpref= %s\n\tprecision= %d\n\tprecision2= %d\n\ti_end= %d\n\tbase = %d\n\tSign = %d\n\tvalue = %d\n\tRET = |%s|\n}\n\n", tvar[i].flag, tvar[i].type, tvar[i].pref, tvar[i].p, tvar[i].p0, tvar[i].argend, tvar[i].base,tvar[i].sign,tvar[i].value, tvar[i].ret);
*/

	ft_putstr(final_print(format, tvar, all_arg));
	va_end(all_arg);

	return (ft_strlen(final_print(format, tvar, all_arg)));
}

char		*final_print(const char *format, t_arg *tvar, va_list all_arg)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	ret = (char*)malloc(sizeof(char) * (ft_strlen(format) + ft_arglen(tvar)));
	ret[0] = '\0';
	i = 0;
	k = 0;
	j = 0;
	while (format[i])
	{
		if (i == tvar[k].index && tvar[k].type != 'e')
		{
			ret = ft_strjoin(ret, ft_str_resize_nf((char*)format, j, i));
			ret = ft_strjoin(ret, tvar[k].ret);
			i = tvar[k].argend;
			j = i + 1;
			k++;
		}
		i++;
	}
	if (j != i)
		ret = ft_strjoin(ret, ft_str_resize_nf((char*)format, j, i));
	return (ret);
}

size_t			ft_arglen(t_arg *tvar)
{
	int		i;
	size_t	ret;

	ret = 0;
	i = 0;
	while (tvar[i].type != 'e')
		ret += ft_strlen(tvar[i++].ret);
	return (ret);
}
