/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:15:14 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/08 17:32:29 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Variations on standard functions
returning the number of printted characters*/

int	ft_putchar(const char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
		ft_putchar(str[i++]);
	return (i);
}

int	ft_putnbr(long int n)
{
	int	count;

	count = 0;
	if (n == INT_MIN)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
		count++;
	}
	if (n > 9)
		count += ft_putnbr(n / 10);
	count += ft_putchar((n % 10) + '0');
	return (count);
}

int	ft_putptr(void *s)
{
	int				count;
	unsigned long	add;

	count = 0;
	add = (unsigned long)s;
	if (!s)
		return (ft_putstr("(nil)"));
	count += ft_putchar('0');
	count += ft_putchar('x');
	count += ft_puthex(add, 'x');
	return (count);
}

int	ft_puthex(unsigned long nbr, const char chr)
{
	int		i;
	char	*base;

	i = 0;
	if (chr == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nbr >= 16)
		i += ft_puthex(nbr / 16, chr);
	ft_putchar(base[nbr % 16]);
	i++;
	return (i);
}
