/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:08:34 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/22 13:45:56 by avelandr         ###   ########.fr       */
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

# define COLOR0 "\x1B[38;2;62;182;233m"
# define COLOR1 "\x1B[38;2;83;206;247m"
# define COLOR2 "\x1B[38;2;53;194;177m"
# define COLOR3 "\x1B[38;2;228;183;94m"
# define COLOR4 "\x1B[38;2;120;183;112m"
# define COLOR5 "\x1B[38;2;211;118;110m"
# define COLOR6 "\x1B[38;2;255;150;109m"
# define COLOR7 "\x1B[38;2;156;64;64m"
# define RESET "\x1b[m"

// \x1B[38;2;R;G;Bm

# define BG_BLACK   "\x1B[40m"
# define BG_RED     "\x1B[41m"
# define BG_GREEN   "\x1B[42m"
# define BG_YELLOW  "\x1B[43m"
# define BG_BLUE    "\x1B[44m"
# define BG_MAGENTA "\x1B[45m"
# define BG_CYAN    "\x1B[46m"
# define BG_WHITE   "\x1B[47m"

// \x1B[48;2;R;G;Bm

#endif
