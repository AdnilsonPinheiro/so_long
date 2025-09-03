/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:51:11 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/03 17:13:45 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_writearg(const char chr, va_list ap)
{
	if (chr == '%')
		return (ft_putchar(chr));
	else if (chr == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (chr == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (chr == 'd' || chr == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	else if (chr == 'X' || chr == 'x')
		return (ft_puthex(va_arg(ap, unsigned int), chr));
	else if (chr == 'p')
		return (ft_putptr(va_arg(ap, void *)));
	else if (chr == 'u')
		return (ft_putnbr(va_arg(ap, unsigned int)));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		res;
	int		i;

	i = 0;
	res = 0;
	if (!str)
		return (0);
	va_start (ap, str);
	while (str[i])
	{
		if (str[i] == '%' && ft_strchr("cspdiuxX%", str[i + 1]))
		{
			i++;
			res += ft_writearg(str[i], ap);
		}
		else
			res += ft_putchar(str[i]);
		i++;
	}
	va_end(ap);
	return (res);
}
