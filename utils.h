/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:02:55 by vrogiste          #+#    #+#             */
/*   Updated: 2022/09/01 17:04:51 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>
# include <stddef.h>
# include <unistd.h>

/* put */
void	dputstr(int fd, const char *s);
void	dputnbr(int fd, int32_t n);

/* atoi */
int		ft_atoi(const char *str);

#endif
