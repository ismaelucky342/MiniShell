/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_terminal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:22:48 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 15:22:50 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_restore_terminal(int i)
{
	static struct termios	original_term_settings;

	if (!i)
		tcgetattr(STDIN_FILENO, &original_term_settings);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &original_term_settings);
}
//sip esto esta permitido 
