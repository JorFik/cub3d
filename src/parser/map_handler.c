/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:18:28 by apeposhi          #+#    #+#             */
/*   Updated: 2024/08/19 00:46:16 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int ft_validate_first_line(t_data *playground)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	temp = ft_strtrim(playground->map_2d[0], "1 \t");
	if (ft_strlen(temp))
		return (ft_handle_invalid(playground));
	while (playground->map_2d[0][j])
	{
		if (playground->map_2d[0][j] == ' ' || playground->map_2d[0][j] == '\t')
		{
			while (playground->map_2d[i][j] == ' ' || playground->map_2d[i][j] == '\t')
				i++;
			if (playground->map_2d[i][j] == '0')
				return (0);
			i = 0;
		}
		j++;
	}
	free(temp);
	return (1);
}

int	ft_validate_last_line(t_data *playground)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	temp = ft_strtrim(playground->map_2d[playground->map_height - 1], "1 \t");
	if (ft_strlen(temp))
		return (ft_handle_invalid(playground)); // add error message
	while (playground->map_2d[playground->map_height - 1][j])
	{
		if (playground->map_2d[playground->map_height - 1][j] == ' ' 
			|| playground->map_2d[playground->map_height - 1][j] == '\t')
		{
			while (playground->map_2d[playground->map_height - 1 - i][j] == ' '
				|| playground->map_2d[playground->map_height - 1 - i][j] == '\t')
				i++;
			if (playground->map_2d[playground->map_height - 1 - i][j] == '0')
				return (0);
			i = 0;
		}
		j++;
	}
	free(temp);
	return (1);
}

static int	ft_handle_side(t_data *playground)
{
	size_t	i;
	size_t	first;
	size_t	last;
	char	*row;

	if (!playground || !playground->map_2d)
		return (0);

	i = -1;
	while (playground->map_2d[++i] != NULL)
	{
		row = playground->map_2d[i];
		first = 0;
		while (row[first] == ' ')
			first++;
		last = ft_strlen(row) - 1;
		while (last > 0 && row[last] == ' ')
			last--;
		if (last <= first || row[first] != '1' || row[last] != '1')
			return (ft_handle_invalid(playground));
	}
	return (1);
}

static int	ft_assign_values(t_data *playground)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = -1;
	while (playground->map_2d[++i] != NULL)
	{
		j = -1;
		while (playground->map_2d[i][++j] != '\0')
		{
			if (playground->map_2d[i][j] == 'N' \
				|| playground->map_2d[i][j] == 'S' \
				|| playground->map_2d[i][j] == 'W' \
				|| playground->map_2d[i][j] == 'E')
			{
				playground->player_x = j;
				playground->player_y = i;
				playground->player_d = playground->map_2d[i][j];
				temp = ft_strdup(playground->map_2d[i]);
				temp[j] = '0';
				playground->map_2d[i] = ft_strdup(temp);
				free(temp);
			}
		}
	}
	return (1);
}

static int	ft_validate_map_elements(t_data *playground)
{
	char *temp;
	int total_directions;

	temp = ft_strdup(playground->map_data);
	temp = ft_cut_chr(temp, '\n');
	temp = ft_cut_chr(temp, ' ');
	temp = ft_cut_chr(temp, '0');
	temp = ft_cut_chr(temp, '1');
	if (ft_strlen(temp) == 0)
		return (free(temp), ft_handle_invalid(playground));
	total_directions = ft_count_directions(temp);
	if (total_directions != 1)
		return (free(temp), ft_handle_invalid(playground));
	ft_assign_values(playground);
	if (ft_strlen(temp) != 1)
        return (free(temp), ft_handle_invalid(playground));
    free(temp);
	return (0);
}

int ft_handle_map(t_data *playground)
{
	int	indicator;

	playground->map_2d = ft_split(playground->map_data, '\n');
	indicator = ft_validate_first_line(playground);
	if (indicator)
		ft_validate_last_line(playground);
	ft_validate_map_elements(playground);
	playground->map_height = ft_arrlen(playground->map_2d);
	ft_handle_side(playground);
	return (1);
}
