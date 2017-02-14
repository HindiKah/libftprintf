/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pflags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 15:39:39 by ybenoit           #+#    #+#             */
/*   Updated: 2017/02/02 18:23:23 by ybenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_arg		*put_octal(t_arg *tvar);
t_arg		*put_hexa(t_arg *tvar);
t_arg		*pflag_str(t_arg *tvar);

t_arg		*pflag_0(t_arg *tvar)
{
	int		i;
	int		j;
	int		tmp;
	char	*n_ret;

	tmp = 0;
	if (ft_strchr("cCsS", tvar->type))
		return (pflag_str(tvar));
	tvar->p0 = (tvar->p0 < tvar->p && tvar->base == 16) ? tvar->p : tvar->p0;
	j = ft_strlen(tvar->ret);
	i = tvar->p0;
	if (i <= j || (ft_strchr(tvar->pref, '-') && tvar->p == 0))
		return (tvar);
	n_ret = (char*)malloc(sizeof(char) * (i + 1));
	n_ret[i] = '\0';
	j = i - j;
	while (tmp < j)
		n_ret[tmp++] = '0';
	tmp = 0;
	while (tvar->ret[tmp])
		n_ret[j++] = tvar->ret[tmp++];
	free(tvar->ret);
	tvar->ret = n_ret;
	return (tvar);
}

t_arg		*pflag_str(t_arg *tvar)
{
	char	*n_ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	n_ret = (char*)malloc(sizeof(char) * (tvar->p0 + 2));
	while (j < tvar->p0 && tvar->ret[j])
	{
		n_ret[j] = tvar->ret[j];
		j++;
	}
		n_ret[j] = '\0';
	free(tvar->ret);
	tvar->ret = n_ret;
	return (tvar);
}


t_arg		*pflag_none(t_arg *tvar)
{
	int		j;
	int		tmp;
	char	*n_ret;
	
	tvar->p0 = (tvar->p0 < tvar->p && tvar->base == 8) ? tvar->p : tvar->p0;
	if (tvar->p0 == 0 && tvar->value == 0 && tvar->p == 0 && tvar->dot == 1)
	{
		tvar->ret[0] = '\0';
		return (NULL);
	}
	tmp = 0;
	j = ft_strlen(tvar->ret);
	if (tvar->p <= j)
		return (tvar);
	n_ret = (char*)malloc(sizeof(char) * (tvar->p + 1));
	n_ret[tvar->p] = '\0';
	j = tvar->p - j;
	while (tmp < tvar->p)
		n_ret[tmp++] = ' ';
	tmp = 0;
	if (!(tvar->p0 == 0 && tvar->value == 0))
	{
		while (tvar->ret[tmp])
			n_ret[j++] = tvar->ret[tmp++];
	}
	n_ret[tvar->p] = '\0';
	free(tvar->ret);
	tvar->ret = n_ret;
	return (tvar);
}

t_arg		*pflag_sharp(t_arg *tvar)
{
	if (tvar->type == 'X' || tvar->type == 'x' || tvar->type == 'p')
		put_hexa(tvar);
	else if (tvar->type == 'o')
		put_octal(tvar);
	return(tvar);
}

t_arg		*put_hexa(t_arg *tvar)
{
	int		i;
	int		j;
	char	*n_ret;
	n_ret = (char*)malloc(sizeof(char) * (ft_strlen(tvar->ret) + 3));
	i = 2;
	j = (tvar->p < tvar->p0) ? i : 0;
	while (tvar->ret[j])
		n_ret[i++] = tvar->ret[j++];
	n_ret[i] = '\0';
	i = 2;
	n_ret[0] = '0';
	n_ret[1] = 'x';
	if (tvar->type == 'X')
		n_ret = ft_strmaj(n_ret);
	free(tvar->ret);
	tvar->ret = n_ret;
	return (tvar);
}

t_arg		*put_octal(t_arg *tvar)
{
	int		i;
	int		j;
	char	*n_ret;

	n_ret = (char*)malloc(sizeof(char) * (ft_strlen(tvar->ret) + 3));
	i = 1;
	j = (tvar->p < tvar->p0) ? i : 0;
	while (tvar->ret[j])
		n_ret[i++] = tvar->ret[j++];
	n_ret[i] = '\0';
	i = 1;
	n_ret[0] = '0';
	free(tvar->ret);
	tvar->ret = n_ret;
	return (tvar);
}

t_arg		*pflag_less(t_arg *tvar)
{
	int		i;
	char	*n_ret;

	i = 0;
	while (tvar->ret[i] && tvar->ret[i] == ' ')
		i++;
	if (i == 0 || tvar->ret[i] == '\0')
		return (tvar);
	tvar->ret = ft_str_resize(tvar->ret, i, ft_strlen(tvar->ret));
	n_ret = (char*)malloc(sizeof(char) * tvar->p);
	n_ret = ft_strcpy(n_ret, tvar->ret);
	i = ft_strlen(tvar->ret);
	while (i < tvar->p)
		n_ret[i++] = ' ';
	n_ret[i] = '\0';
	free(tvar->ret);
	tvar->ret = n_ret;
	return (tvar);
}

t_arg		*pflag_more(t_arg *tvar)
{
	if (tvar->sign == -1)
		tvar->ret = add_less(tvar->ret);
	else if (tvar->sign == 1)
		tvar->ret = add_more(tvar->ret);
	return (tvar);
}
