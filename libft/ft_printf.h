/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:21:37 by fernacar          #+#    #+#             */
/*   Updated: 2023/05/16 20:34:52 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

typedef struct s_flags
{
	int		width;
	int		precision;
	int		zero;
	int		point;
	int		dash;
	int		plus;
	int		space;
	int		hash;
}			t_flags;

int	parse_first_flags(const char *format, t_flags *flags);

int	print_padding(int n, char c);

int	print_char(char value, t_flags *flags);

int	print_str(const char *value, t_flags *flags);

int	print_ptr(unsigned long value, t_flags *flags);

int	print_int(int value, t_flags *flags);

int	print_uint(unsigned int value, t_flags *flags);

int	print_hex(unsigned int value, t_flags *flags);

int	print_hex_up(unsigned int value, t_flags *flags);

int	ft_printf(const char *format, ...);

#endif
