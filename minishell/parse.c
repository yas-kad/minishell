/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 17:42:51 by yait-kad          #+#    #+#             */
/*   Updated: 2021/04/05 17:43:08 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void            display_commands(t_command *comd)
{
    t_redirection *curr_redir;
    t_command *new_list;
    new_list = comd;
    printf("\e[1;33mall commands: \e[0m");
    while (new_list != NULL)
    {
		printf("%s\ncommand: ", Cyan);
        if (new_list->command != NULL)
        {
            int j = 0;
            while (new_list->command[j] != NULL)
            {
				printf("[%s]", new_list->command[j]);
                j++;
            }
        }
        printf("\n");
        curr_redir = new_list->redirection;
        while (curr_redir != NULL)
        {
			printf("%stype: {%s} file: {%s}\n", Cyan, curr_redir->type, curr_redir->file);
            curr_redir = curr_redir->next;
        }
		printf("separator: {%d}%s\n", new_list->seperator, RESET);
        new_list = new_list->next;
    }
}

// t_command       *parce(t_token_list *token_list)
// {
//     t_token_list *lst_token;
//     t_token_list *first_word;
//     t_command *cmd = malloc(sizeof(t_command));
//     t_command *curr_cmd = cmd;
//     int size;

//     lst_token = token_list;
//     size = 0;

//     while (lst_token) 
//     {
//         if (lst_token->type == WORD)
//         {
//             size = 0;
//             first_word = lst_token;
//             while (lst_token->type == WORD)
//             {
//                 size++;
//                 lst_token = lst_token->next;
//             }
//             curr_cmd->command = (char **)malloc(sizeof(char *) * (size + 1));
//             int i = 0;
//             while (i < size)
//             {
//                 curr_cmd->command[i] = ft_strdup(first_word->value);
//                 first_word = first_word->next;
//                 i++;
//             }
//             curr_cmd->command[i] = NULL;
//         }
//         if (lst_token->type == REDIR_GREATER || lst_token->type == REDIR_LESSER || lst_token->type == DOUBLE_GREATER)
//         {
//             if (curr_cmd->redirection != NULL)
//                 curr_cmd->redirection = curr_cmd->redirection->next;
//             curr_cmd->redirection = malloc(sizeof(t_redirection));

//             curr_cmd->redirection->type = lst_token->type;
//             lst_token = lst_token->next;
//             curr_cmd->redirection->file = lst_token->value;
//             //curr_cmd->redirection = curr_cmd->redirection->next;
//             if (curr_cmd->redirection == NULL)
//                 printf("Mr tofa7\n");
//         }
//         if (lst_token->type == PIPE)
//         {
//             //curr_cmd->redirection = NULL;
//             //free(cmd->command);
//             curr_cmd->next = NULL;
//             curr_cmd->next = malloc(sizeof(t_command));
//             curr_cmd = curr_cmd->next;
//         }
//         if (lst_token->type == SEMICOLON || lst_token->type == NEWLINE)
//         {
//             curr_cmd->redirection = NULL;
//             //free(cmd->command);
//             curr_cmd->next = NULL;
//         }
        
//         lst_token = lst_token->next;
//     }
//     return (cmd);
// }

void                destroy_redirection_list(t_redirection *redirection)
{
    t_redirection *curr_redir;

    curr_redir = redirection;

    while (curr_redir)
    {
        if (curr_redir->file)
        {
            free(curr_redir->file);
            curr_redir->file = NULL;
        }
        if (curr_redir->type)
        {
            free(curr_redir->type);
            curr_redir->type = NULL;
        }
        free(curr_redir);
        curr_redir = curr_redir->next;
    }
    free(curr_redir);
    // while (redirection != NULL)
    // {
    //     current_redirection = redirection;
    //     redirection = (redirection)->next;
    //     free(current_redirection->file);
    //     free(current_redirection->type);
    //     free(current_redirection);
    //     current_redirection = NULL;
    // }
    // redirection = NULL;
}

t_redirection       *initial_redirection(char *type, char *value, t_env *lenv)
{
    t_redirection *new_redirection;

    //new_redirection = redirection;
    new_redirection = malloc(sizeof(t_redirection));
	if (type == DOUBLE_LESSER)
    {
		new_redirection->type = ft_strdup(type);
    	new_redirection->file = treat_heredocs(value, lenv);
    	new_redirection->next = NULL;
	}else
	{
		new_redirection->type = ft_strdup(type);
    	new_redirection->file = ft_strdup(value);
    	new_redirection->next = NULL;
	}
    return (new_redirection);
}

char	*check_name_hdc(char *buffer, int *k)
{
	char *name;
	int i;

	i = *k;
	if (ft_isalnum(buffer[i + 1]) == 1 || buffer[i + 1] == '_')
		ft_new_str(buffer, i);
	if (ft_isdigit(buffer[i]) == 1)
		name = ft_substr(buffer, i++, 1);
	else
		name = get_dollar_name(buffer, &i);
	*k = i;
	return (name);
}

void	expand_herdocs(char **buffer, t_env *lenv)
{
	char	*before_dollar;
	char	*env_name;
	char	*after_dollar;
	char	*tmp;
	//char	*buffer2;
	int		i;
	size_t	len;

	i = 0;
	// before_dollar = ft_strdup("");
	// before_dollar = NULL;
	while ((*buffer)[i] != '\0')
	{
		if ((*buffer)[i] == '$' && (ft_isalnum((*buffer)[i + 1]) == 1
			|| (*buffer)[i + 1] == '_'))
		{
			//ft_new_str(buffer, i);
			before_dollar = ft_substr((*buffer), 0, i);
			env_name = check_name_hdc((*buffer), &i);
			after_dollar = after_dollar_value((*buffer), i);
			len = dollar_val(&(*buffer), env_name, before_dollar, lenv);
			tmp = ft_strjoin((*buffer), after_dollar);
			free((*buffer));
			printf("p2[%p]\n", &tmp);
			(*buffer) = tmp;
			// printf("p[%p]\n", tmp);
			//free(tmp);
			//printf("pp[%p]\n", tmp);
			free(before_dollar);
			free(env_name);
			free(after_dollar);
			i = len - 1;
		}
		i++;
	}
	// if (before_dollar == NULL)
	// 	before_dollar = ft_strdup("");
	// return (buffer);
}

char	*remove_quotes(char *delimiter, int *qt)
{
	int		i;
	char		state;
	i = 0;
	while (delimiter[i] != '\0')
	{
		if (delimiter[i] == '"' || delimiter[i] == '\'')
		{
			*qt = 1;
			state = delimiter[i];
			ft_new_str(delimiter, i);
			while (delimiter[i] != '\0' && delimiter[i] != state)
				i++;
			if (delimiter[i] == state)
				ft_new_str(delimiter, i);
			i--;
		}
		i++;
	}
	return (delimiter);
}

char	*treat_heredocs(char *delimiter, t_env *lenv)
{
	char	*line;
	char	*buffer;
	char	*tmp;
	char	*tmp1;
	int	q_exist;

	q_exist = 0;
	buffer = ft_strdup("");
	// if delimiter has quotes(single or double) no expanding
	// if (delimiter[0] == '"' || delimiter[0] == '\'')
	// {
	// 	q_exist = 1;
	// }
	delimiter = remove_quotes(delimiter, &q_exist);
	while (1)
	{
		
		line = readline(">>");
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}
		tmp1 = ft_strjoin(line, "\n");
		free(line);
		line = tmp1;
		// printf("ptmp1[%p]\n", tmp1);
		// printf("pline[%p]\n", line);

		tmp = ft_strjoin(buffer, line);
		free(line);
		free(buffer);
		buffer = tmp;
		// printf("ptmp[%p]\n", tmp);
		//join lines to buffer with '\n'
	}
	//(void)lenv;
	if (q_exist == 0)
	{
		//printf("p5[%p]\n", &buffer);
		/*buffer = */expand_herdocs(&buffer, lenv);
		// printf("pbuff[%p]\n", buffer);
		//free(buffer);
		//buffer = tmp;
	}
		//printf("p[%p]\n", &buffer);
		// printf("herdocs[%s]\n", buffer);
	return (buffer);
}

void                add_redirection(t_redirection *redirection, char *type, char *value, t_env *lenv)
{
    t_redirection *new_redirection;

    new_redirection = redirection;
    while (new_redirection->next != NULL)
    {
        new_redirection = new_redirection->next;
    }
    new_redirection->next = malloc(sizeof(t_redirection));
	if (type == DOUBLE_LESSER)
	{
		new_redirection->next->type = ft_strdup(type);
    	new_redirection->next->file = treat_heredocs(value, lenv);
    	new_redirection->next->next = NULL;
		// value = treat_heredocs(value, lenv);
	}
	else
	{
		new_redirection->next->type = ft_strdup(type);
		new_redirection->next->file = ft_strdup(value);
		new_redirection->next->next = NULL;
	}
}
int                 tab_size(char **cmd_args)
{
    int i;

    i = 0;
    while (cmd_args[i] != NULL)
        i++;
    return (i);
}
void                add_separator(t_command *cmd, char *sep)
{
    if (sep == PIPE)
        cmd->seperator = e_pipe;
    else if (sep == SEMICOLON)
        cmd->seperator = e_semicolon;
    else
        cmd->seperator = e_newline;
}
t_command           *initial_cmd(char **cmd_arg, t_redirection *redirection, char *sep)
{
    t_command *first_cmd;
    int size;
    int i;

    first_cmd = malloc(sizeof(t_command));
    i = 0;
    first_cmd->command = NULL;
    if (cmd_arg != NULL)
    {
    	size = tab_size(cmd_arg);
        first_cmd->command = (char **)malloc(sizeof(char *) * (size + 1));
        while (cmd_arg[i] != NULL)
        {
            first_cmd->command[i] = ft_strdup(cmd_arg[i]);
            i++;
        }
        first_cmd->command[i] = NULL;
    }
    first_cmd->redirection = redirection;

    add_separator(first_cmd, sep);
    first_cmd->next = NULL;
    return(first_cmd);
}

void                add_cmd(t_command *cmd, char **cmd_arg, t_redirection *redirection, char *sep)
{
    t_command *new_cmd;
    int size;
    int i;

    new_cmd = cmd;
    i = 0;
    while (new_cmd->next != NULL)
        new_cmd = new_cmd->next;
    new_cmd->next = malloc(sizeof(t_command));
    new_cmd->next->command = NULL;
    if (cmd_arg != NULL)
    {
    	size = tab_size(cmd_arg);
        new_cmd->next->command = (char **)malloc(sizeof(char *) * (size + 1));
        while (cmd_arg[i] != NULL)
        {
            new_cmd->next->command[i] = cmd_arg[i];
            i++;
        }
        new_cmd->next->command[i] = NULL;
    }
    new_cmd->next->redirection = redirection;
    add_separator(new_cmd->next, sep);
    new_cmd->next->next = NULL;
}

t_command           *ft_parse(t_token_list *token_list, t_env *lenv)
{
    t_command       *cmd;
    t_redirection   *redirection;
    t_token_list    *current_token;
    t_token_list    *first_word;
    char **cmd_arg;
    int size;
	int i;

    size = 0;
    current_token = token_list;
    redirection = NULL;
    cmd_arg = NULL;
    cmd = NULL;
    while (current_token)
    {
		if (current_token->type == WORD)
        {
            size = 0;
            first_word = current_token;
            while (current_token->type == WORD)
            {
                size++;
                current_token = current_token->next;
            }
            if (cmd_arg == NULL)
			{
				cmd_arg = (char **)malloc(sizeof(char *) * (size + 1));
				i = 0;
			}
			size = i + size;
            
            while (i < size)
            {
                cmd_arg[i] = ft_strdup(first_word->value);
                first_word = first_word->next;
                i++;
            }
            cmd_arg[i] = NULL;
        }
        if (current_token->type == REDIR_GREATER || current_token->type == REDIR_LESSER 
			|| current_token->type == DOUBLE_LESSER || current_token->type == DOUBLE_GREATER)
        {
            if (!redirection)
                redirection = initial_redirection(current_token->type,current_token->next->value, lenv);
            else
                add_redirection(redirection,current_token->type,current_token->next->value, lenv);
            current_token = current_token->next;
        }
        if (current_token->type == PIPE || current_token->type == SEMICOLON || current_token->type == NEWLINE)
        {
            if (cmd != NULL)
            {
                add_cmd(cmd, cmd_arg, redirection, current_token->type);
                //for (int i = 0; i < size; i++)
                    //free(cmd_arg[i]);
                free(cmd_arg);
				cmd_arg = NULL;
                redirection = NULL;
            }
            else
            {
                cmd = initial_cmd(cmd_arg, redirection, current_token->type);
                for (int i = 0; i < size; i++)
                    free(cmd_arg[i]);
                free(cmd_arg);
				cmd_arg = NULL;
                redirection = NULL;
            }
            //display_commands(cmd);
            //add_cmd(cmd,cmd_arg,redirection);
            //curr_cmd->redirection = NULL;
            //free(cmd->command);
            //curr_cmd->next = NULL;
            //curr_cmd->next = malloc(sizeof(t_command));
            //curr_cmd = curr_cmd->next;
        }
        //if (current_token->type == SEMICOLON || current_token->type == NEWLINE)
       // {
        //    free(cmd_arg);
            //break;
       // }

        //destroy_redirection_list(redirection);
        current_token = current_token->next;
    }
    return(cmd);
}