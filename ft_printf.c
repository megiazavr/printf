/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megiazar <megiazar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:40:01 by megiazar          #+#    #+#             */
/*   Updated: 2025/05/20 20:31:15 by megiazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_s_c(char *s, char c, t_type type)
{
	int	count;

	count = 0;
	if (type == CHAR)
		count += write(1, &c, 1);
	if (type == STRING)
	{
		if (!s)
			s = "(null)";
		while (*s)
		{
			count += write(1, s, 1);
			s++;
		}
	}
	return (count);
}

static int	ft_putnbr(long n, int format)
{
	int			count;
	char		tmp;

	count = 0;
	if (format == SIGNED && n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		count += ft_putnbr(n / 10, format);
	tmp = n % 10 + '0';
	count += write(1, &tmp, 1);
	return (count);
}

static int	ft_hex(unsigned long n, char format)
{
	int		count;
	char	tmp;

	count = 0;
	tmp = "0123456789abcdef"[n % 16];
	if (format == 'p')
	{
		if (n == 0)
			return (write(1, "(nil)", 5));
		count += write(1, "0x", 2);
		format = 'x';
	}
	if (n >= 16)
		count += ft_hex(n / 16, format);
	if (format == 'X')
		tmp = ft_toupper(tmp);
	count += write(1, &tmp, 1);
	return (count);
}

int	ft_specifier(char spec, va_list args)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count += ft_s_c(NULL, va_arg(args, int), CHAR);
	else if (spec == 's')
		count += ft_s_c(va_arg(args, char *), 0, STRING);
	else if (spec == 'd' || spec == 'i')
		count += ft_putnbr(va_arg(args, int), SIGNED);
	else if (spec == 'u')
		count += ft_putnbr(va_arg(args, unsigned int), UNSIGNED);
	else if (spec == 'x' || spec == 'X')
		count += ft_hex(va_arg(args, unsigned int), spec);
	else if (spec == 'p')
		count += ft_hex(va_arg(args, unsigned long), 'p');
	else if (spec == '%')
		count += write(1, "%", 1);
	else
		count += ft_printf("%%%c", spec);
	return (count);
}

int	ft_printf(const char *fmt, ...)
{
	va_list				args;
	size_t				count;
	int					i;

	va_start(args, fmt);
	if (!fmt)
		return (-1);
	count = 0;
	i = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			if (!fmt[i + 1]) 
				return (-1);
			i++;
			count += ft_specifier(fmt[i++], args);
		}
		else
			count += write(1, &fmt[i++], 1);
	}
	va_end(args);
	return (count);
}

int	main(void)
{
	int	i;

	ft_printf("\nTESTE PARA %%S\n\n");
	i = printf("|OLD %s|\n", NULL);
	printf("Result OLD NULL = %d\n", i);
	i += printf("|OLD %s|\n", "Ola meus amigos");
	i += printf("|OLD %s|\n", "123");
	printf("Result OLD = %d\n\n", i);
	i = ft_printf("|NEW %s|\n", NULL);
	ft_printf("Result NEW NULL = %d\n", i);
	i += ft_printf("|NEW %s|\n", "Ola meus amigos");
	i += ft_printf("|NEW %s|\n", "123");
	ft_printf("Result NEW = %d\n", i);



	
	i = ft_printf("%", 'A', "meo3w");
	ft_printf("Result is %d\n", i);
	i = printf("%", 'A', "meo3w");
	printf("Result is %d\n\n", i);

	i = ft_printf("Hello %");
	ft_printf("Result is %d\n", i);
	i = printf("Hello %");
	printf("Result is %d\n\n", i);

	i = ft_printf(" NULL %s NULL\n", NULL);
	i = printf(" NULL %s NULL\n", NULL);
	ft_printf("Result is %d\n", i);
	printf("Result is %d\n\n", i);

	i = ft_printf("%i %u %x\n",-2147483648, 78, 6666);
	i = printf("%i %u %x\n",-2147483648, 78, 6666);
	ft_printf("Result is %d\n", i);
	printf("Result is %d\n\n", i);

	i = ft_printf("%p\n", (void *)0);
	i = printf("%p\n", (void *)0);
	ft_printf("Result is %d\n", i);
	printf("Result is %d\n\n", i);

	i = ft_printf(" %p %p \n", 0, 0);
	i = printf(" %p %p ", (void *)0, (void *)0);
	ft_printf("Result is %d\n", i);
	printf("Result is %d\n", i);
}