/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:31:23 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/12/18 19:07:10 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
		DID SOMEONE SAY FREEDOM??

.       .,oo8888888888888888ooo,.
.    ,od88888888888888888888888888oo,
. ,o0MMMMMMMMNMMMMM8888888888888888888o.
.d888888888V'.o   ```VoooooooOOOOOOOOIII,
.l888LLLLl:  O , ,O    ``VlMM88888IIAMMMMMOMb,
.l8888888LLb `VooV',O,MoodlM88888IIIMMMMV'ddMOMb,
.l88888888888booooooOlllllIIIIIIIIIAMMV',dMMOOMMMb,
.888888888888888888LLLLIAMMMMMMMMMMMMMMMMMOOOMMMMMMb,
.8M8888888888LLLMMMAAMMMAAMMMMMMMMMMMMMMOOOOMMMMMMMMb
.88M8888888lll888888mmmmmmmmmmmmmmvvvvvvvvvvvvv,`MMMM
.8888M888888llllllllllllllV::::V''~~        ~~'V lMMV
.M8888MMM888888TTTMl8lllllb:::V'                `IiM'
.MMMMM8888M8k88888l8Mklllllk:A'                  `V'
.lMMMMMM888888888888MMMMMlll:M  
.l8MM8MMMM8888888888888MMMMllM
*/
void	freedom(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
