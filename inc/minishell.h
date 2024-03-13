/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:02:09 by aserebry          #+#    #+#             */
/*   Updated: 2024/03/05 13:03:28 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>

# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"

# define READ_END 0
# define WRITE_END 1

extern int	g_status;

typedef struct s_cmd
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}			t_cmd;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_mini;

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

void	child_builtin(t_cmd *prompt, t_mini *n, int l, t_list *cmd);
void	*check_to_fork(t_cmd *prompt, t_list *cmd, int fd[2]);
char	*expand_vars(char *str, int i, int quotes[2], t_cmd *prompt);
char	*expand_path(char *str, int i, int quotes[2], char *var);
t_list	*fill_nodes(char **args, int i);
char	*ft_strtrim_all(char const *s1, int squote, int dquote);
int		get_fd(int oldfd, char *path, int flags[2]);
t_mini	*get_outfile1(t_mini *node, char **args, int *i);
t_mini	*get_outfile2(t_mini *node, char **args, int *i);
t_mini	*get_infile1(t_mini *node, char **args, int *i);
t_mini	*get_infile2(t_mini *node, char **args, int *i);
int		get_here_doc(char *str[2], char *aux[2]);
void	*check_args(char *out, t_cmd *p);
char	*mini_getprompt(void);
int		ft_unset(t_cmd *prompt);
int		builtin(t_cmd *prompt, t_list *cmd, int *is_exit, int n);
int		is_builtin(t_mini *n);
int		ft_cd(t_cmd *prompt);
int		ft_echo(t_list *cmd);
int		ft_export(t_cmd *prompt);
int		ft_pwd(void);
int		export_err_not_valid_key(int errcode);
int		key_validator(const char *s);
void	process_empty_args(char **envp);
void	exec_custom(char ***out, char *full, char *args, char **envp);
char	**ft_cmdsubsplit(char const *s, char *set);
char	**ft_cmdtrim(char const *s, char *set);
void	*exec_cmd(t_cmd *prompt, t_list *cmd);
void	get_cmd(t_cmd *prompt, t_list *start, char **split_path, char *path);
void	*mini_perror(int err_type, char *param, int err);
int		mini_exit(t_list *cmd, int *is_exit);
void	cd_error(char **str[2], t_cmd *p);
void	free_content(void *content);
int		ft_countchar(char *s, char c);
char	**ft_dup_matrix(char **m);
char	**ft_extend_matrix(char **in, char *newstr);
void	ft_free_matrix(char ***m);
int		ft_isspace(char c);
char	**ft_matrix_replace_in(char ***big, char **small, int n);
int		ft_matrixlen(char **m);
int		ft_putmatrix_fd(char **m, int nl, int fd);
int		ft_putnchar_fd(char c, int fd, int n);
int		ft_putstrn_fd(char *s, int fd, int n);
int		ft_strchr_i(const char *s, int c);
char	**ft_subsplit(char const *s, char *needle);
int		ft_strchars_i(const char *s, char *set);
int		ft_putendl_m_fd(char *s, int fd);
int		ft_putstr_m_fd(char *s, int fd);
void	handle_sigint(int sig);
int		ft_atoi2(const char *nptr, long *nbr);
int		check_redir(char **args);
char	*ft_getenv(char	*var, char **envp, int n);
char	**ft_setenv(char *var, char *value, char **envp, int n);
t_mini	*mini_init(void);
void	norminette_makes_me_do_this(int *i, char **args, t_list *cmds[2]);

#endif
