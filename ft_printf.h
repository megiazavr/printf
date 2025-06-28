/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megiazar <megiazar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:44:07 by megiazar          #+#    #+#             */
/*   Updated: 2025/05/23 18:26:43 by megiazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

typedef enum e_num_type
{
	SIGNED, 0
	UNSIGNED 1
}	t_num_type;

typedef enum e_type
{
	CHAR,
	STRING
}	t_type;

int	ft_printf(const char *fmt, ...);
int	ft_toupper(int c);

#endif