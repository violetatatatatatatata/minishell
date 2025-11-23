/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:08:34 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/23 16:24:16 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define BLACK   "\x1B[30m"
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define WHITE   "\x1B[37m"

# define COLOR0 "\x1B[38;2;209;247;255m"
# define COLOR1 "\x1B[38;2;19;62;124m"
# define COLOR2 "\x1B[38;2;154;159;23m"
# define COLOR3 "\x1B[38;2;254;232;1m"
# define COLOR4 "\x1B[38;2;84;193;230m"
# define COLOR5 "\x1B[38;2;57;196;230m"
# define COLOR6 "\x1B[38;2;234;0;217m"
# define COLOR7 "\x1B[38;2;113;28;145m"
# define RESET "\x1b[m"

// Para modificar el RGB
// \x1B[38;2;R;G;Bm

# define BG_BLACK   "\x1B[40m"
# define BG_RED     "\x1B[41m"
# define BG_GREEN   "\x1B[42m"
# define BG_YELLOW  "\x1B[43m"
# define BG_BLUE    "\x1B[44m"
# define BG_MAGENTA "\x1B[45m"
# define BG_CYAN    "\x1B[46m"
# define BG_WHITE   "\x1B[47m"

// Para modificar el RGB de fondo
// \x1B[48;2;R;G;Bm

#endif
