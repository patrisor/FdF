/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isodd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:21:38 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/09 09:52:51 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isodd(int num)
{
	int bool;

	bool = 0; 
	if(num&1)
		bool = 1; 
	return bool;
}