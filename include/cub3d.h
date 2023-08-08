/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:54:38 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/08 13:25:41 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
#include <stdbool.h>
# include "libft.h"
# include "gnl.h"
# define WIDTH 1280
# define HEIGHT 720
# define FOV 60
# define PI 3.141592653589793
# define RAD_TO_DEG 57.2958
# define DEG_TO_RAD 0.0174533
# define GRID 20

#define RECTCOLOR 0x7BB30C
#define FLOOR 0x1859B3
#define WALL 0x2DB362
#define RAY 0xB3160C
#define GRID_C 0x9029B3

/*Key kode define*/


#ifdef __linux__
	#define KEY_UP 65362
	#define KEY_DN 65364
	#define KEY_RG 65363
	#define KEY_LE 65361
	#define KEY_W 119
	#define KEY_S 115
	#define KEY_D 100
	#define KEY_A 97
	#define ESC 65307
#else
	#define KEY_UP 126
	#define KEY_DN 125
	#define KEY_RG 124
	#define KEY_LE 123
	#define KEY_W 13
	#define KEY_S 1
	#define KEY_D 2
	#define KEY_A 0
	#define ESC 53

#endif

typedef struct s_map_row
{
	char			*row;
	struct s_map_row	*next;
	struct s_map_row	*back;
}	t_map_row;
typedef struct s_file
{
	char	*north;
	char	*west;
	char	*east;
	char	*south;
}	t_file;
typedef struct s_vertex
{
	double	x;
	double	y;
}	t_vertex;

typedef struct s_vect
{
	t_vertex	a;
	t_vertex	b;
}	t_vect;

typedef struct s_player
{
	int		height;
	int		width;
	double	xpos;
	t_vertex	*point;
	double	ypos;
	double	angle;
	double	xrot;
	double	yrot;
}	t_player;

typedef struct s_img{
	void	*img_ptr;
	char	*addr;
	int		line;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_texture
{
	int		w;
	int		h;
	t_img	*texture_img;
}	t_texture;

typedef struct s_map
{
	int	xmap;
	int	ymap;
	int off_map;
	t_map_row	*map_compo;
}	t_map;

typedef	struct s_ray
{
	t_vertex	*hit_point_h;
	t_vertex	*hit_point_v;
	double		angle;
}	t_ray;

typedef enum s_err
{
	MLX,
	XPM,
	MAP,
	CUB,
	VALID,
	COLOR_SET
}	e_err;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_collector	*col;
	t_img		*main_img;
	t_map		*map;
	t_player	*player;
	t_ray		*ray;
	int			number_of_files;
	int			floor_color;
	int			ciel_color;
	char		**files_arr;
	t_img		*texture;
}	t_data;


/*****DEBUG******/
typedef struct s_elem
{
	int				content;
	struct s_elem	*next;
}	t_elem;

t_data	*ft_init(char *filename);
void	ft_set_img(t_img *img, int width, int height,t_data *data);
t_img	*ft_img_alloc();
t_elem	*ft_single_color(int *addr);
void	ft_put_pix(t_img *img, int x, int y, int color,t_data *data);
void	ft_put_main_img(t_data *data);
int		color_code(int r ,int g ,int b);
int		ft_parse(char *filename, t_data *data);
void	ft_free_strings(char **s);
void	ft_free_all(t_data *data);
void	ft_draw_init(t_data *data);
t_img	*ft_img_init(t_data *data);
void	ft_update(t_data *data);
char	**ft_gsplit(char const *s, char c, t_collector **col);
void	ft_print_err(int type);
void	ft_free_error_type(t_collector **col, int type);

char	*ft_gsubstr(char const *s, unsigned int start, size_t len, t_collector **col);
int		ft_gatoi(const char *str, t_collector **col);

t_map_row	*ft_new_row(char *addr, t_collector **col);
t_map_row	*ft_last_row(t_map_row *lst);
void	ft_row_add_back(t_map_row **list, t_map_row *new_node);


/****************/
#endif
