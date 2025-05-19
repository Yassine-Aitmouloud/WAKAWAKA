/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:20:48 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/19 12:38:07 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef HERE_DOC_H
# define HERE_DOC_H

#include "minishell.h"
#define HERE_DOC_FILE "/tmp/.here_doc"
t_token *handle_heredoc(t_token *tokens);

#endif