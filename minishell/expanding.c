/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:06:00 by yait-kad          #+#    #+#             */
/*   Updated: 2021/04/03 12:06:03 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_new_str(char *str, int index)
{
    while (str[index] != '\0')
    {
        str[index] = str[index + 1];
        index++;
    }
}

int        expand_double_quotes(char **str, int index, t_env *env_list)
{
        
        while ((*str)[index] != '\0')
        {
            //index++;
            if ((*str)[index] == '\\')
            {
                if (ft_strchr("\\`$\"",(*str)[index + 1]) != NULL)
                {
                    ft_new_str((*str), index);
                }
                //else if (str[index + 1] == '$')
                   // ft_new_str(str, index--);
            }
            else if ((*str)[index] == '$' && (ft_strchr("\" \t", (*str)[index + 1]) == NULL))
            {
                (*str) = take_dollar_name((*str), &index, env_list, 3);
                // index--;
            }
			//printf("comd[%c]i[%d]\n", (*str)[index], index);
			if ((*str)[index] == '"')
            {
				ft_new_str((*str), index);
				index--;
				break;
            }
            index++;
        }
    return(index);
}

int         expand_single_quote(char *str, int index)
{
        while (str[index] != '\0')
        {
            if (str[index] == '\'')
            {
                ft_new_str(str, index);
                index--;
                break;
            }
            index++;
        }
    return (index);
}

char            *get_dollar_name(char *command,int *j)
{
    char *name;
    char *ptr;
    char *tmp;
    int i;

    i = *j;
    name = ft_strdup("");
        
    while (command[i] != '\0' && (ft_isalnum(command[i]) == 1
		|| command[i] == '_'))
    {
        ptr = ft_substr(command, i, 1);
        tmp = ft_strjoin(name, ptr);
        free(name);
        name = tmp;
        free(ptr);
        i++;
    }
    *j = i;
    return(name);
}

char            *after_dollar_value(char *command1, int i)
{
    char *after_dollar;
    int j;
    int start;

    j = 0;
    start = i;
    while (command1[i++] != '\0')
        j++;
    after_dollar = ft_substr(command1,start, j);
    return (after_dollar);
}

void            dollar_zero(char **comd, char *old_comd, size_t *k)
{
    size_t len;
    char *tmp;

    //len = *k;
    len = ft_strlen(old_comd) + ft_strlen("My_Minishell");
    tmp = ft_strjoin(old_comd,"My_Minishell");
    free(*(comd));
    *(comd) = tmp;
    *k = len;
}

void	dollar_q(char **comd, char *old_comd, size_t *k)
{
	size_t len;
	char *str;
	char *tmp;

	str = ft_itoa(dollar_question);
	dollar_question = 0;
	len = ft_strlen(old_comd) + ft_strlen(str);
	tmp = ft_strjoin(old_comd, str);
	free((*comd));
	(*comd) = tmp;
	*k = len;
}

size_t          dollar_val(char **comd, char *name, char *old_comd, t_env *envl)
{
    char *tmp;
    int len;

    len = 0;
    while (envl != NULL)
    {
        if (ft_strcmp(name,envl->name) == 0)
        {
            len = ft_strlen(old_comd) + ft_strlen(envl->value);
            tmp = ft_strjoin(old_comd,envl->value);
            free(*(comd));
            *(comd) = tmp;
            break;
        }
        else
        {
            len = ft_strlen(old_comd) + 1;
            tmp = ft_strjoin(old_comd,"");
            free(*(comd));
            *(comd) = tmp;
        }
            envl = envl->next;
    }
    return(len);
}

void            name_empty(char **comd, char *old_comd, size_t *k)
{
    size_t len;
    char *tmp;

    len = *k;
    len = ft_strlen(old_comd);
    tmp = ft_strjoin(old_comd,"");
    free(*(comd));
    *(comd) = tmp;
    *k = len;
}

void	expand_name(char *comd, int *k, char type)
{
	//char *name;
	int i;

	i = *k;
	while (comd)
	{
		if (comd[i] == type)
		{
			ft_new_str((comd),i);
			break;
		}
		i++;
	}
	*k = i;
	//return (ft_strdup(""));
}

int	check_name(char **comd, int *k, char **name, char type_f)
{
	char type;
	int tmp;
	int i;

	i = *k;
	tmp = 0;
	if ((*comd)[i + 1] == '?')
	{
		ft_new_str((*comd),i);
		(*name) = ft_substr((*comd),i++,1);
	}
	else if (((*comd)[i + 1] == '"' || (*comd)[i + 1] == '\'') && type_f != 3)
	{
		(*name) = ft_strdup("");
		type = (*comd)[i + 1];
		// printf("1comd[%c]type{%c}\n", *comd[i],type);
		ft_new_str((*comd),i);
		// printf("comd[%c]\n", *comd[i]);
		ft_new_str((*comd),i);
		// printf("3comd[%c]\n", *comd[i]);
		expand_name((*comd), &i, type);
// printf("34comd[%s]\n", *comd);
// printf("3comd[%c]\n", (*comd)[i]);
		//ambiguous redirect
		//printf("$\"'HOME'\"\n");

		tmp = 1;
	}
	else
	{
		if (ft_isalnum((*comd)[i + 1]) == 1 || (*comd)[i + 1] == '_')
		{
			ft_new_str((*comd),i);
		}
		if (ft_isdigit((*comd)[i]) == 1)
		{
			(*name) = ft_substr((*comd),i++,1);
		}
		else
		{
			(*name) = get_dollar_name((*comd), &i);
		}
	}
    *k = i;
	return (tmp);
}

void            free_tvar(t_d_var dvar)
{
    free(dvar.old_comd);
    free(dvar.after_dollar);
    free(dvar.name);
}

char            *take_dollar_name(char *comd, int *k, t_env *envl, int type)
{
    t_d_var dvar;

    dvar.i = *k;
    dvar.len = 0;
	//dvar.name = ft_strdup("");
	//printf("[%p]\n",dvar.name);
    dvar.old_comd = ft_substr(comd,0,dvar.i);
	//printf("after[%s]i[%d]\n",dvar.old_comd, dvar.i);
    dvar.t = check_name(&comd, &dvar.i, &dvar.name, type);
	dvar.after_dollar = after_dollar_value(comd, dvar.i);
	if (dvar.t == 0)
	{
		//printf("after[%s]i[%d]\n",dvar.after_dollar, dvar.i);
		if (ft_strcmp(dvar.name, "") == 0 && dvar.t == 0)
			dvar.i++;
		*k = dvar.i;
		if (ft_strcmp(dvar.name, "") != 0 && dvar.t == 0)
		{
			if (ft_strcmp(dvar.name, "?") == 0)
				dollar_q(&comd, dvar.old_comd, &dvar.len);
			else if (ft_strcmp(dvar.name, "0") == 0)
				dollar_zero(&comd, dvar.old_comd, &dvar.len);
			else
				dvar.len = dollar_val(&comd, dvar.name, dvar.old_comd, envl);
			*k = dvar.len - 1;
		}
		else if (dvar.t == 0)
			name_empty(&comd, dvar.old_comd, &dvar.len);
		dvar.tmp = ft_strjoin(comd,dvar.after_dollar);
		//printf("[%p]\n",dvar.name);
		//printf("comd[%s]i[%d]\n",comd, dvar.i);
		free(comd);
		comd = dvar.tmp;
		if (ft_strcmp(comd,"") == 0 && type == 1)
			printf("\e[1;91m$%s: ambiguous redirect\e[0m\n", dvar.name);
	}else
		*k = dvar.i;
	free_tvar(dvar);
    return(comd);
}

void	expand_command(t_command *cmd_c, t_env *env_list)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_c->command[i] != NULL)
	{
		j = 0;
		while (cmd_c->command[i][j] != '\0')
		{
			if (cmd_c->command[i][j] == '$')
				cmd_c->command[i] = take_dollar_name(cmd_c->command[i], &j, env_list, 0);
			if (cmd_c->command[i][j] == '\\')
				ft_new_str(cmd_c->command[i], j);
			else if (cmd_c->command[i][j] == '"')
			{
				ft_new_str(cmd_c->command[i], j);
				j = expand_double_quotes(&cmd_c->command[i], j, env_list);
			}else if (cmd_c->command[i][j] == '\'')
			{
				//printf("singl[%d]p[%c]\n",j,cmd_c->command[i][j]);
				ft_new_str(cmd_c->command[i], j);
				j = expand_single_quote(cmd_c->command[i], j);
			}
			//printf("singlout[%d]p[%c]\n",j,cmd_c->command[i][j]);
			j++;
		}
		i++;
	}
}

void        expand_redirection(t_command *cmd_r, t_env *env_r)
{
    t_redirection *current_redir_list;
    current_redir_list = cmd_r->redirection;
    int i;

    while (current_redir_list)
    {
        i = 0;
		if (ft_strcmp(current_redir_list->type, "DOUBLE_LESSER") != 0)
		{
        	while (current_redir_list->file[i] != '\0')
        	{
        	    if (current_redir_list->file[i] == '$')
        	       current_redir_list->file = take_dollar_name(current_redir_list->file, &i, env_r, 1);
        	    if (current_redir_list->file[i] == '\\')
        	        ft_new_str(current_redir_list->file, i);
        	    else if (current_redir_list->file[i] == '"')
        	    {
        	        ft_new_str(current_redir_list->file, i);
        	        i = i + expand_double_quotes(&current_redir_list->file, i, env_r);
        	    }else if (current_redir_list->file[i] == '\'')
        	    {
        	        ft_new_str(current_redir_list->file, i);
        	        i = i + expand_single_quote(current_redir_list->file, i);
        	    }
        	    i++;
        	}
		}
        current_redir_list = current_redir_list->next;
    }
}

void       expanding(t_command *cmd, t_env *env_lst)
{
    int i,j;
    i = 0;
    j = 0;
    //while (cmd->seperator != 1 && cmd->seperator != 2)
   // {
        //while (cmd->command != NULL)
       // {
    //printf("before expanding[%s]\n",cmd->command[0]);
    //printf("before expanding[%s]\n",cmd->command[1]);
    if (cmd->command != NULL)
        expand_command(cmd, env_lst);
    if (cmd->redirection)
        expand_redirection(cmd,env_lst);
}

void        display_error(char *value)
{
	printf("\e[1;91mMy_Minishell: syntax error near unexpected token %s\e[0m\n",value);
	dollar_question = 258;
}

void        destroy_list(t_token_list *lst)
{
    t_token_list *tmp;
	while (lst != NULL) 
    {
        tmp = lst;
        lst = lst->next;
        free(tmp->value);
        free(tmp);
        tmp = NULL;
    }
    free(lst);
}

int			quotes_end(char *value, int *k)
{
	int backslash;
    int j;

    j = *k;
    j++;
	backslash = 0;
	while (value[j] != '\0' && value[j] != '"')
    {
        if (value[j] == '\\')
        {
            backslash = check_backslash(value, j);
            if (backslash % 2 != 0)
            {
                j = j + backslash;
                backslash = 0;
            }else
            {
                j = j + backslash - 1;
                backslash = 0;
            }
        }
        j++;
    }
    *k = j;
    if (value[j] == '"')
        return(1);
    else //if (value[j] != '\0')
        return(-1);
	//return (j);
}

int         single_quote_end(char *value, int *k)
{
    int j;

    j = *k;
    j++;
    while (value[j] != '\0' && value[j] != '\'')
        j++;
    *k = j;
    if (value[j] == '\'')
        return(1);
    else 
        return(-1);
}

int         check_quotes(char *value)
{
    int j;
    int backslash;
    int result;
    //char c;

    j = 0;
    backslash = 0;
    result = 0;
    while (value[j])
    {
        if (value[j] == '\"')
        {
            //c = value[j];
            //j++;
            result = quotes_end(value, &j);
        }
        else if (value[j] == '\'')
        {
            result = single_quote_end(value, &j);
        }
        else if (value[j] == '\\')
        {
            if (check_backslash(value, j) % 2 != 0)
                j++;
        }
        j++;
    }
    return(result);
}

int         check_backslash_end(char *value)
{
    int backslash;
    int i;

    backslash = 0;
    i = 0;
    while (value[i] != '\0')
    {
        while (value[i] == '\\')
        {
            backslash++;
            i++;
        }
        if (value[i] == '\0')
            return(backslash);
        else
            backslash = 0;
        i++;
    }
    return (backslash);
}

int         syntax_error_NONE(t_token_list *token_none, t_token_list *head)
{
    int result;

    result = 0;
    if (token_none->next->type == PIPE || token_none->next->type == SEMICOLON)
    {
        display_error(token_none->next->value);
        destroy_list(head);
        result = 1;
        //break;
    }
    else if (token_none->next->type == NEWLINE)
    {
        destroy_list(head);
        result = 1;
        //break;
    }
    return(result);
}

int         syntax_error_redir(t_token_list *token_redir, t_token_list *head)
{
    int result;

    result = 0;
     if (token_redir->next->type != WORD)
    {
        display_error(token_redir->next->value);
        destroy_list(head);
        result = 1;
        //break;
    }
    return(result);
}

int         syntax_error_pipe(t_token_list *token_pipe, t_token_list *head)
{
    int result;

    result = 0;
    if (token_pipe->next->type == PIPE || token_pipe->next->type == SEMICOLON)
    {
        display_error(token_pipe->next->value);
        destroy_list(head);
        result = 1;
        //break;
    }
    else if (token_pipe->next->type == NEWLINE)
    {
        display_error(token_pipe->next->value);
        destroy_list(head);
        result = 1;
        //break;
    }
    return(result);
}

int         syntax_error_word(t_token_list *token_word, t_token_list *head)
{
    int result;

    result = 0;
    if (((check_backslash_end(token_word->value))) % 2 != 0)
    {
		printf("%ssyntax error multiple line not allowed\n%s", RED, RESET);
		dollar_question = 258;
        destroy_list(head);
        result = 1;
//        break;
    }
    if (check_quotes(token_word->value) == -1)
    {
		printf("%ssyntax error multiple line not allowed\n%s", RED, RESET);
		dollar_question = 258;
        destroy_list(head);
        result = 1;
        //break;
    }
    return(result);
}

int         syntax_error_semi(t_token_list *token_semi, t_token_list *head)
{
    int result;

    result = 0;
    if (ft_strcmp(token_semi->value, ";;") == 0)
    {
        display_error(token_semi->value);
        destroy_list(head);
        result = 1;
    }
    else if (token_semi->next->type == PIPE || token_semi->next->type == SEMICOLON)
    {
        display_error(token_semi->next->value);
        destroy_list(head);
        result = 1;
        //break;
    }
    // else if (token_semi->next->type == NEWLINE)
    // {
    //     destroy_list(token_semi);
    //     result = 1;
    //     //break;
    // }
    return(result);
}

int         check_error(t_token_list *tokn_lst, t_token_list *old)
{
    int result;

    result = 0;
    if (tokn_lst->type == NONE)
        result = syntax_error_NONE(tokn_lst, old);
    else if (tokn_lst->type == REDIR_GREATER || tokn_lst->type == REDIR_LESSER
    	|| tokn_lst->type == DOUBLE_LESSER || tokn_lst->type == DOUBLE_GREATER)
        result = syntax_error_redir(tokn_lst, old);
    else if (tokn_lst->type == PIPE)
        result = syntax_error_pipe(tokn_lst, old);
    else if (tokn_lst->type == WORD)
        result = syntax_error_word(tokn_lst, old);
    else if (tokn_lst->type == SEMICOLON)
        result = syntax_error_semi(tokn_lst,old);
    return(result);
}

int        check_syntax_error(t_token_list *old)
{

    int result;
    t_token_list *token_lst = old;
    result = 0;
    while (token_lst->type != NEWLINE)
    {
        result = check_error(token_lst,old);
        if (result == 1)
            break;
        token_lst = token_lst->next;
    }
    return (result);
}
