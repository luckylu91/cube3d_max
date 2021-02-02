#include "parse.h"

static void set_theta_pos(t_pack *p, int i, int j)
{
	p->pos.x = i + .5;
	p->pos.y = j + .5;
	if (p->map.grid[i][j] == 'N')
		p->theta = -M_PI / 2;
	else if (p->map.grid[i][j] == 'S')
		p->theta = M_PI / 2;
	if (p->map.grid[i][j] == 'W')
		p->theta = M_PI;
	else if (p->map.grid[i][j] == 'E')
		p->theta = 0;
	p->theta = p->theta;
	p->theta_v = 0;
}


static int addback_sprite(t_list **asprites, t_sprite *new_val)
{
	t_list		*new_elem;

	if (!(new_elem = ft_lstnew(new_val)))
		return (-1);
	ft_lstadd_back(asprites, new_elem);
	return (1);
}

//
void print_sprite(void *sptr)
{
	t_sprite *s = (t_sprite*)sptr;
	printf("sprite %p:\n", s);
	printf("\tpos = %2f,%2f\n", s->pos.x, s->pos.y);
	printf("\ttype '%c'\n", s->type);
	fflush(stdout);
}
//


static t_sprite *add_sprite(t_pack *p, int i, int j, char type)
{
	t_sprite	*sprite;

	if (!(sprite = ft_calloc(1, sizeof(t_sprite))))
		return (NULL);
	sprite->type = type;
	sprite->pos.x = i + .5;
	sprite->pos.y = j + .5;
	sprite->path = NULL;
	sprite->previous_block.x = i;
	sprite->previous_block.y = j;
	// //
	// printf("sprite index: %ld\n", (ft_strchr(sprites_str, type) - sprites_str));
	// //
	sprite->simg = sprite_img_from_type(p, type);
	if (addback_sprite(&p->sprites, sprite) == -1)
	{
		free(sprite);
		return (NULL);
	}
	// //
	// printf("coucou\n");
	// ft_lstiter(p->sprites, &print_sprite);
	// //
	if (ft_strchr(ENEMIES, type)
		&& addback_sprite(&p->enemies, sprite) == -1)
	{
		free(sprite);
		return (NULL);
	}
	// //
	// printf("End of map_objects_init\n");
	// ft_lstiter(p->sprites, &print_sprite);
	// //
	return (sprite);
}

static void complete_dir_pos(t_pack *p)
{
	p->dir.x = cos(p->theta);
	p->dir.y = sin(p->theta);
	p->dir3d.x = cos(p->theta);
	p->dir3d.y = sin(p->theta);
	p->dir3d.z = 0.;
	p->pos3d.x = p->pos.x;
	p->pos3d.y = p->pos.y;
	p->pos3d.z = 0.5;
	p->dir_ortho.x = sin(p->theta);
	p->dir_ortho.y = cos(p->theta);
}

int set_map_objects_sprites(t_pack *p)
{
	int i;
	int j;
	t_sprite *pea_sprite;

	i = -1;
	while (++i < p->map.width)
	{
		j = -1;
		while (++j < p->map.height)
		{
			if (ft_strchr("NSWE", p->map.grid[i][j]))
				set_theta_pos(p, i, j);
			else
			{
				if (p->map.grid[i][j] == GHOST && !add_sprite(p, i, j, GHOST))
					return (load_sprite_error(p));
				if (p->map.grid[i][j] != OUTSIDE && p->map.grid[i][j] != WALL)
				{
					if (!(pea_sprite = add_sprite(p, i, j, PEA)))
						return (load_sprite_error(p));
					p->map.pea_sprites_grid[i][j] = pea_sprite;
					p->map.peas_count++;
				}
			}
		}
	}
	//
	printf("End of map_objects_init\n");
	ft_lstiter(p->sprites, &print_sprite);
	//
	complete_dir_pos(p);
	return (1);
}