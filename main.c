#include "get_next_line.h"
#include "so_long.h"

char	**store_map(int fd)
{
	int		i;
	int		j;
	char	*line;
	char	**map;
	char	**tmp_map;
	size_t	map_size;

	i = 0;
	j = 0;
	map = NULL;
	map_size = 0;
	map = malloc(sizeof(char *) * 1);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (j == 0)
			j = ft_strlen(line);
		else if (ft_strlen(line) != j)
		{
			write(2, "Erro1\n", 6);
			free(line);
			free_map(map, i);
			return (NULL);
		}
		tmp_map = ft_realloc(map, sizeof(char *) * map_size, sizeof(char *) * (i
					+ 2));
		if (!tmp_map)
		{
			write(2, "Erro2\n", 6);
			free(line);
			free_map(map, i);
			return (NULL);
		}
		map = tmp_map;
		map[i] = line;
		i++;
		map_size = i;
	}
	if (!line && i == 0)
	{
		free_map(map, i);
		return (NULL);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	open_map_file(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nopen", 10);
		return (-1);
	}
	return (fd);
}
int	check_for_ber(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 5 || name[0] == '.' || ft_strcmp(name + len - 4, ".ber") != 0)
	{
		write(2, "Error\n.ber", 10);
		return (0);
	}
	return (1);
}
int	close_window(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
    return (0);
}
void	count_map(t_map **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*map)->map[i])
	{
		j = 0;
		while ((*map)->map[i][j])
			j++;
		i++;
	}
	(*map)->rows = i;
	(*map)->cols = j;
}
int game_in(t_map *map)
{
	t_game	game;
	game.mlx = mlx_init();
	count_map(&map);
	if (!game.mlx)
	{
		write(2, "Error\nmlx", 9);
		return (0);
	}
	game.win = mlx_new_window(game.mlx, map->cols * 64, map->rows * 64, "so_long");
	mlx_loop(game.mlx);
	return 1;
}

int	main(int ac, char **av)
{
	int	i;
	int	fd;
	int	check_valid_map;

	i = 0;
	check_valid_map = 0;
	t_map(map) = {0};
	if (ac != 2)
	{
		write(2, "Error\nacs", 9);
		return (0);
	}
	if (check_for_ber(av[1]) == 0)
		return (0);
	fd = open_map_file(av[1]);
	if (fd == -1)
	{
		write(2, "Error\nop", 8);
		return (0);
	}
	map.map = store_map(fd);
	if (map.map == NULL)
	{
		write(2, "Error\nstore", 11);
		close(fd);
		return (0);
	}
	while (map.map[i])
	{
		if (validate_map_line(map.map[i]) == 0)
		{
			close(fd);
			free_map(map.map, map.rows);
			return (0);
		}
		i++;
	}
	if (all_walls(map.map) == 0)
	{
		close(fd);
		free_map(map.map, map.rows);
		write(2, "Error\nwalls", 11);
		return (0);
	}
	if (check_for_data(&map) == 0)
	{
		close(fd);
		free_map(map.map, map.rows);
		return (0);
	}
	map.rows = i;
	if (chack_valid_path(&map) == 0)
	{
		write(2, "Error\ncep", 10);
		close(fd);
		free_map(map.map, map.rows);
		return (0);
	}
	close(fd);
	game_in(&map);
	free_map(map.map, map.rows);
	return (1);
}
