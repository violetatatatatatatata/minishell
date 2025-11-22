/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:55 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/10 11:35:58 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

//# define ""

// MACROS
# define TRUE 1
# define FALSE 0
# define PATH_MAX 4096

// EXECUTION MESSAGES
# define PROMPT ""

// ERRORES
# define INPUT_ERROR ""
# define MANY_ARGS "too many arguments"
// errores en los builtins
# define ACCES_MSG	"Search permissions denie for one of the components of path"
# define ENOENT_MSG			"No such file or directory"
# define ENAMETOOLONG_MSG	"path is too long"

// ** cd
#define DIR_FAILED "Error: No such file or directory"
#define	HOME_FAILED "HOME not set"

# endif
