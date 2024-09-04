#include "../../../includes/minishell.h"

void			quote_as_token(t_tokenizer *tz, int *search) //the content under "" as one token
{
	if ((*search = ft_tokenizer_isquote(tz)))
		ft_tokenizer_pass_quotes(tz, *search);
	ft_tokenizer_advance(tz, 1);
}

t_token			*ft_tokenizer_handle_defined_token(t_tokenizer *tz)
{
	int			index;

	// Avanza mientras encuentra espacios o caracteres ignorables
	while (ft_tokenizer_istype(tz, CHAR_TYPE_SPACE | CHAR_TYPE_PASS))
		ft_tokenizer_advance(tz, 1);

	// Establece la posición de inicio del siguiente token
	ft_tokenizer_set_start_pos(tz, tz->current_position);

	// Verifica si llegó al final del texto
	if (ft_tokenizer_istype(tz, CHAR_TYPE_END_OF_TEXT))
	{
		return token__copy(&g_defined_tokens[TOKEN_END_TOKEN]);
	}

	// Verifica si el token actual es uno de los definidos
	index = ft_tokenizer_isdefined_token(tz, FOREACH_ADVANCE_ITERATOR);
	if (index != TYPE_NONE)
	{
		if (index == TYPE_ERROR)
		{
			return NULL;
		}
		return token__copy(&g_defined_tokens[index]);
	}

	return NULL;
}

t_token			*ft_tokenizer_get_next_token(t_tokenizer *tz)
{
	t_token		*token;
	int			index;

	// Primero maneja tokens definidos
	token = ft_tokenizer_handle_defined_token(tz);
	if (token != NULL)
	{
		return token;
	}

	while (!ft_tokenizer_istype(tz, CHAR_TYPE_END_OF_TEXT | CHAR_TYPE_SPACE | CHAR_TYPE_PASS | CHAR_TYPE_ERROR))
	{
		// Maneja las secuencias de escape
		if (ft_tokenizer_istype(tz, CHAR_TYPE_BACKSLASH))
		{
			ft_tokenizer_advance(tz, 1);
			if (ft_tokenizer_istype(tz, CHAR_TYPE_END_OF_TEXT) && ft_tokenizer_error(ERROR_UNKNOWN, tz) == ERROR)
			{
				return NULL;
			}
			ft_tokenizer_advance(tz, 1);
		}

		index = ft_tokenizer_isdefined_token(tz, FOREACH_DO_NOT_ADVANCE_ITERATOR);
		if (index == TOKEN_ERROR)
		{
			return NULL;
		}
		if (index != TYPE_NONE)
		{
			break;
		}

		// Maneja las comillas
		pass_quote_(tz, &index);
	}

	// Retorna el token encontrado
	return ft_tokenizer_token_grabber(tz, TOKEN_WORD);
}
