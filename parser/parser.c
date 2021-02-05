#include "minishell.h"

int g_parse_error;

void	exec_proc(t_list *head) // 인자는 연결리스트의 헤드포인터
{
	t_list	*cur_proc;
	t_cmd	*cmd;

	cur_proc = head->next;
	g_proc_list = head;
	while (cur_proc != NULL)
	{
		cmd = cur_proc->content; // (t_cmd *)형태로 자료형변환을 위해 옮겨담음.
		if (cmd->cmdline[0]) // 명령어가 있으면 실행
		{
			if (cmd->flag == 0)
				exec_cmds(cmd->cmdline);
			
			// if (파이프 조건) 파이프 함수 실행
			// else if (cmd->has_redir) // 파이프 다음 조건식으로 하기
			// 	exec_redir(cmd->cmdline); // envp는 넘기지 않아도..?
		}
		cur_proc = cur_proc->next;
	}
	ft_lstclear(&head, free_cmdline);
}

int		add_node(t_data *data, t_list *head, char *input, int symbol)
{
	data->cmd->flag = symbol;
	if (*(data->buff))
		put_buff_into_cmdline(data);
	if ((data->cmd->cmdline)[0] == 0 && data->cmd->flag <= 1)
		return (ERROR);
	else
	{
		// head에 t_list *p(content:data->cmd, next:NULL)를 복사
		ft_lstadd_back(&head, ft_lstnew(data->cmd));
		data->cmd = ft_calloc(1, sizeof(t_cmd));
		data->cmd->cmdline = ft_calloc(count_token(input) + 1, sizeof(char *));
		data->lstlast = ft_lstlast(head);
	}
	data->k = 0;
	return (SUCCESS);
}

void	put_buff_into_cmdline(t_data *data)
{
	if (*(data->buff) == 0)
		return ;
	data->cmd->cmdline[(data->k)] = ft_strdup(data->buff);
	data->cmd->cmdline[(data->k) + 1] = NULL;
	(data->k)++;
	ft_bzero(data->buff, ft_strlen(data->buff) + 1);
	data->j= 0;
}

void	parse_all_char(char *input, t_data *data, t_list *head)
{	
	if (data->cmd->quote == input[data->i]) // '이나 "이 한 번 더 나온다면 (묶음 완성)
	{
		data->cmd->quote = 0; // 묶음 완성됐으므로 quote 초기화
		if (input[data->i] == '\'') // '에 한해서만 닫는 '를 buff에 담아줌
			data->buff[data->j++] = input[data->i];
	}
	else if (data->cmd->quote == 0 && input[data->i] == '\"') // "이면 quote에만 저장하고 buff엔 담지 않음
		data->cmd->quote = input[data->i];
	else if (data->cmd->quote == 0 && input[data->i] == '\'') // '이면 quote에 저장하고 buff에도 담음 (여는 ' 저장)
	{
		data->cmd->quote = input[data->i];
		data->buff[data->j++] = input[data->i];
	}
	else if (data->cmd->quote == 0 && input[data->i] == ' ')
		put_buff_into_cmdline(data);
	else if (data->cmd->quote == 0 && input[data->i] == ';')
		g_parse_error = add_node(data, head, input, 0);
	else if (data->cmd->quote == 0 && input[data->i] == '|')
		g_parse_error = add_node(data, head, input, 1);
	else
	{
		if (data->cmd->quote == 0 && ft_strchr("><", input[data->i]))
			data->cmd->has_redir = 1; // 리다이렉션 기호가 최소 1개 있다. 아래에서 기호도 buff에 담아줌.
		else if (data->cmd->quote != '\'' && input[data->i] == '\\' && input[data->i + 1])
			data->i++; // i++해서 escape문자는 담지않고 통과하고, 아래에서 escape 다음문자를 buff에 담아줌.
		data->buff[data->j++] = input[data->i];
	}
}

// parse_error에 가는 상황(에러상황)의 경우, exec_proc으로 안 가고 main함수로 돌아가서 free만 하고 끝내야 한다.
void	*parse(char *input_temp)
{
	t_data	data;
	t_list	*head;
	char	*input;

	input = ft_strtrim(input_temp, " ");
	initialize(input, &data, &head);
	g_parse_error = 1;
	while (input[++(data.i)])
	{
		parse_all_char(input, &data, head);
		if (g_parse_error < 1)
			return (parse_error(&data, head, SYNTAX_ERROR));
	}
	if (*(data.buff))
		put_buff_into_cmdline(&data);
	if (data.k)
		ft_lstadd_back(&head, ft_lstnew(data.cmd));
	if (data.cmd->quote != 0)
		parse_error(&data, head, QUOTE_ERROR);
	free(data.buff);
	// g_parse_error <= 0인 경우, exec_cmd로 가지 않고 함수 종료.
	if (g_parse_error == 1)
		exec_proc(head);
	return (NULL);
}
