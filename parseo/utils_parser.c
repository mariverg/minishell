/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:40:17 by mariverg          #+#    #+#             */
/*   Updated: 2025/01/13 15:44:09 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parseo.h"
 
bool is_valid_token_sequence(t_token *current, t_token *next)
{
    if (!current)
        return true;
    
    // No puede haber dos pipes seguidos
    if (current->type == TOKEN_PIPE && (!next || next->type == TOKEN_PIPE))
        return false;
    
    // Después de una redirección debe venir una palabra
    if ((current->type >= TOKEN_REDIR_IN && current->type <= TOKEN_APPEND) &&
        (!next || (next->type != TOKEN_WORD && next->type != TOKEN_DQUOTE && 
                  next->type != TOKEN_SQUOTE)))
        return false;
    
    return true;
}

void print_syntax_error(t_token *token)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    if (!token)
        ft_putstr_fd("newline", 2);
    else
        ft_putstr_fd(token->value, 2);
    ft_putstr_fd("'\n", 2);
}

bool validate_syntax(t_token *tokens)
{
    t_token *current;
    
    // Verificar si el primer token es un operador no válido
    if (tokens && tokens->type == TOKEN_PIPE)
    {
        print_syntax_error(tokens);
        return false;
    }
    
    current = tokens;
    while (current)
    {
        if (!is_valid_token_sequence(current, current->next))
        {
            print_syntax_error(current->next);
            return false;
        }
        current = current->next;
    }
    
    return true;
}
