/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:24:37 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/11 16:56:33 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ==================== error ==================== */

# define ERRCODE_MALLOC 1
# define ERRMSG_MALLOC "ERROR :\nMalloc failed to allocate memory.\n"
# define ERRCODE_READ 2
# define ERRMSG_READ "ERROR :\nFailed to allocate memory in readline function.\n"
# define ERRCODE_PIPE 3
# define ERRMSG_PIPE "ERROR :\nFailed to creating pipe\n"
# define ERRCODE_PID 4
# define ERRMSG_PID "ERROR :\nFailed to creating child process\n"
# define ERRCODE_EXEC 5
# define ERRMSG_EXEC "ERROR :\nFailed while executing the command\n"
# define ERRCODE_PROC 6
# define ERRMSG_PROC "ERROR :\nThe child process did not work correctly\n"
# define ERRCODE_FD 7
# define ERRMSG_FD "ERROR :\nFailed while opening file\n"
# define ERRCODE_DUP2 8
# define ERRMSG_DUP2 "ERROR :\nFailed while running dup2\n"
# define ERRCODE_DUP 9
# define ERRMSG_DUP "ERROR :\nFailed while running dup\n"
# define ERRCODE_GETCWD 10
# define ERRMSG_GETCWD "ERROR :\nFailed while running getcwd\n"
# define ERRCODE_EXPORT_VALUE 11
# define ERRMSG_EXPORT_VALUE "export: `=': not a valid identifier\n"
# define ERRCODE_CD_ARG 12
# define ERRMSG_CD_ARG "cd: too many arguments\n"
# define ERRCODE_SINGLE_QUOT 13
# define ERRMSG_SINGLE_QUOT "ERROR :\nSingle quot no close\n"
# define ERRCODE_DOUBLE_QUOT 14
# define ERRMSG_DOUBLE_QUOT "ERROR :\nDouble quot no close\n"
# define ERRCODE_SYNTAX 15
# define ERRMSG_SYNTAX "syntax error near unexpected symbol \"newline\"\n"
# define ERRCODE_REDIR_ALL 16
# define ERRMSG_REDIR_ALL "syntax error near unexpected symbol > < or |\n"

/* ==================== define ==================== */

# define BUFFER_SIZE 255

# define CMDCUSTOM -38 // commande custome
# define CMD -39       // commande
# define FIL -40       // files
# define ARG -41       // arguments
# define PR -42        // pipe/redirections
# define ERR -43       // commande no fond
# define PCC -44       // pipe ctrl + c
# define PCD -45       // pipe ctrl + d

# define IS_CMD 100 // for parcing
# define IS_ARG 110 // for parcing

/* ==================== include ==================== */

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* ==================== structure ==================== */

typedef struct s_global
{
	char		***tab;
	int			res;
	int			res_tmp;
	int			temp;
	int			temp2;
}				t_global;

typedef struct s_shell
{
	int			pipefd[2];
	int			pipefd_after[2];
	int			fd_exit;
	int			fd_enter;
	int			fd;
	int			i;
	t_global	var_global;
}				t_shell;
/* ==================== glob variable ==================== */

extern int		g_int_temp;

/* ==================== function signal ==================== */

void			sig_ctrl(int sig);
void			cmd_pipe_leave(char *dest, t_shell *shell);

/* ==================== function chevron ==================== */

int				fill_document(char *line, int fd, char *delim);
int				ft_left_chevron_delimiter(char **cmd, int i, t_shell *shell);
int				ft_left_chevron(char **cmd, int i, t_shell *shell);
int				ft_right_chevron(char **cmd, int i, t_shell *shell);
int				ft_right_chevron_apped(char **cmd, int i, t_shell *shell);

/* ==================== function error ==================== */

int				print_error_message(int error_code);
void			ft_print_error(char *src);
int				ft_print_error_custom(char *src);
void			print_error_message_void(int error_code);

/* ==================== function cmd ==================== */

char			**ft_fill_tab(char **cmd, int j);
void			ft_cmd(char **cmd, t_shell *shell, char **envp);
int				ft_exec_cmd(char **cmd, int j, t_shell *shell, char **envp);
int				ft_exec_cmd_custom(char **args, char **cmd, t_shell *shell);
int				execvp_custom(char **cmd, int j, t_shell *shell);
int				ft_check_pipe(char **cmd);
int				ft_close_custom(char **args, int saved_stdin, int saved_stdout,
					int status);
int				ft_exec_custom_no_pipe(char **cmd, int i, t_shell *shell);

/* ==================== function utils ==================== */

size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char *s1, char const *s2);
char			*ft_strjoin_4(char *s1, char *s2);
char			*ft_strjoin_modif_pipe(char *s1, char const *s2);
char			**ft_split(const char *str, char sep);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_atoi(const char *nptr);
char			*ft_strdup_char(const char *s, char c);
int				ft_strlen_char(char *src, char c);
char			*ft_itoa(int n);
int				count_nb(int n);

/* ==================== function gnl ==================== */

char			*get_next_line(int fd);
int				ft_chr(char *s);
void			ft_buf_cut(char *dest);
int				ft_len(char *s, int j);
char			*return_and_free(char *s1, char *dest);
char			*ft_join(char *s1, char *s2);

/* ==================== function free ==================== */

void			ft_close_fd(t_shell *shell);
int				ft_free_error_exec(char **cmd, t_shell *shell, char **args);
void			ft_free_cmd(char **cmd);
void			free_global(t_shell *shell);
int				ft_leave_shell(t_shell *shell);

/* ==================== function parcing ==================== */

char			**split_master(char *str, t_shell *shell);
int				ft_verif_syntax(char *str, int i);
int				ft_verif_redir(char *str);
int				ft_fill_tab_arg(char **dest, char *str, int i, t_shell *shell);
char			*ft_chr_dol(char *str, int i, t_shell *shell);
char			*ft_chr_global_var(char *name, t_shell *shell);
char			*ft_strjoin_double_quot(char *dest, char *str, t_shell *shell);
char			*ft_strjoin_sigle_quot(char *s1, char *str);
int				ft_fill_tab_cmd(char **dest, char *str, int i, t_shell *shell);
char			*ft_chrch_name(char *str, int i, t_shell *shell);
int				ft_strlen_chr_dol(char *str, int i, t_shell *shell);
char			*ft_strjoin_paths_cmd(char *paths, char *name);
char			**ft_fill_parsing_tab(char **dest, char *str, int i,
					t_shell *shell);
int				ft_chr_char(char c);
int				ft_chr_char_2(char c);
int				ft_pass_space(char *str, int i);
char			**get_path(t_shell *shell);
int				ft_skeep_redir(char *str, int i);
int				ft_skeep_word(char *str, int i);

/* ==================== function pipe and redir ==================== */

int				ft_redir_pipe(char **cmd, int j, t_shell *shell);
int				ft_redir_pipe2(char **cmd, int i, t_shell *shell);
int				ft_pipe_left(t_shell *shell);
int				ft_pipe_right(t_shell *shell);
int				ft_pipe(char **cmd, int j, t_shell *shell);
int				ft_open_pipe(t_shell *shell, char **cmd, int j);
int				ft_duble_chevron(char **cmd, int i);

/* ==================== function cmd custom ==================== */

int				ft_echo(char **args);
int				ft_pwd(void);
int				ft_cd(char **args);
int				ft_env(t_shell *shell);
int				ft_exit(char **args, char **cmd, t_shell *shell);
int				ft_unset(char **args, t_shell *shell);

/* ========= export function ========= */
int				ft_export(char **args, t_shell *shell);
int				ft_export_3(char *name, char *val, t_shell *shell);
int				ft_export_no_args(t_shell *shell);
char			***fill_last_tab(char ***tab, char *name, char *val,
					t_shell *shell);
char			***fill_last_tab_2(char ***tab, int i, t_shell *shell);
char			***ft_free_line_all(char ***tab);
void			ft_swap_val(char **a, char **b);
char			*ft_strdup_join(const char *s, char *src2);
int				ft_free_line_export(char **tab);

/* ==================== other function ==================== */

int				ft_start_global(char **envp, t_shell *shell);

#endif
