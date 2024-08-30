#include "../includes/minishell.h"

static size_t compute_color_string_length(const char *str, const char *color)
{
    return (ft_strlen(color) + ft_strlen(RESET)) * ft_strlen(str) + ft_strlen(str) + 1;
}

static void append_color_and_reset(char *out, char c, const char *color)
{
    size_t out_len = ft_strlen(out);
    ft_strlcat(out, color, out_len + 1);
    out[out_len + ft_strlen(color)] = c;
    out[out_len + ft_strlen(color) + 1] = '\0';
    ft_strlcat(out, RESET, out_len + ft_strlen(color) + 2);
}

char *color_string(char *str, char *color)
{
    char *out;
    size_t len;

    len = compute_color_string_length(str, color);
    out = ft_calloc(len, 1);
    if (!out)
        return (NULL);

    *out = '\0';
    while (*str)
    {
        append_color_and_reset(out, *str, color);
        str++;
    }
    return (out);
}