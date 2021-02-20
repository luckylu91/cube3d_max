#ifndef PARAMS_PARSE_UTILS_H
# define PARAMS_PARSE_UTILS_H

# include "parse.h"

int	parse_resolution(char *line, int *w, int *h);
int	parse_text_param(char *line, char **text);
int	parse_image_path(char *line, t_pack *p, t_img *im);
int	parse_color(char *line, int *color);
int	color_or_text(char *line, int *color, char **text);
int	parse_fc(t_pack *p, char *line, t_img *im);

#endif
