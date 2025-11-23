/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:09:16 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/23 02:09:22 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define ""

// MACROS
# define	TRUE 1
# define	FALSE 0
# define	MAX_LONG "9223372036854775807"

// EXECUTION MESSAGES
# define PROMPT ""

// ERRORES
# define INPUT_ERROR ""
# define MANY_ARGS "too many arguments"
// errores en los builtins
# define ACCES_MSG			"Search permissions denie for one of the components of path"
# define ENOENT_MSG			"No such file or directory"
# define ENAMETOOLONG_MSG	"path is too long"

// ** cd
#define DIR_FAILED "Error: No such file or directory"
#define	HOME_FAILED "HOME not set"

# endif
