#ifndef PARAMS_PARSE_FUNS_H
# define PARAMS_PARSE_FUNS_H

# include "parse.h"

int	parse_r(t_pack *p, char *line);
int	parse_no(t_pack *p, char *line);
int	parse_so(t_pack *p, char *line);
int	parse_ea(t_pack *p, char *line);
int	parse_we(t_pack *p, char *line);
int	parse_s(t_pack *p, char *line);
int	parse_f(t_pack *p, char *line);
int	parse_c(t_pack *p, char *line);
int	parse_game(t_pack *p, char *line);
int	parse_mouse(t_pack *p, char *line);

#endif
