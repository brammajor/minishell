/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahooghe   <ahooghe@student.s19.be   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:53:56 by ahooghe           #+#    #+#             */
/*   Updated: 2023/09/28 13:42:05 by ahooghe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_variable_value(char **env)
{
	char	*full_var;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	full_var = *env;
	while (full_var[i] && full_var[i] != '=')
		i++;
	if (!full_var[i])
		return (0);
	j += i + 1;
	while (full_var[j] && full_var[j] != '\n')
		j++;
	if (j < 1)
		return (0);
	value = ft_substr(*env + i + 1, 0, j);
	if (!value)
		return (0);
	return (value);
}

int	fetch_value_len(char **env)
{
	int		len;
	int		i;
	char	*value;

	len = 0;
	i = 0;
	value = *env;
	while (value[i] && value[i] != '=')
		i++;
	i ++;
	while (value[len + i] && value[len + i] != '\n')
		len++;
	return (len);
}

void	update_content(char *new_content, char *content,
	char *variable, char **cursor)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	k = -1;
	while (*(content + ++i) && content + i != *cursor)
	{
		new_content[j] = content[i];
		j++;
	}
	i++;
	while (*(content + i) && ft_isalnum(*(content + i)))
		i++;
	while (variable[++k])
	{
		new_content[j] = variable[k];
		j++;
	}
	*cursor = new_content + j;
	copy_content_end(new_content, content, i, j);
}

void	update_with_error(char *new_content, char *content,
	char *error_code, char **cursor)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	k = -1;
	while (*(content + ++i) && content + i != *cursor)
	{
		new_content[j] = content[i];
		j++;
	}
	i++;
	while (*(content + i) && ft_isalnum(*(content + i)))
		i++;
	while (error_code[++k])
	{
		new_content[j] = error_code[k];
		j++;
	}
	*cursor = new_content + j;
	i++;
	copy_content_end(new_content, content, i, j);
}

char	*replace_with_value(char *content, char **cursor,
	int name_len, char **env)
{
	char	*variable;
	int		content_len;
	char	*new_content;

	variable = extract_variable_value(env);
	if (!variable)
		return (0);
	content_len = ft_strlen(content) - name_len + fetch_value_len(env);
	new_content = ft_calloc(sizeof(char), content_len);
	if (!new_content)
		return (0);
	update_content(new_content, content, variable, cursor);
	free(variable);
	free(content);
	return (new_content);
}
