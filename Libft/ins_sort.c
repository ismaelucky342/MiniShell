/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:05:07 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:05:07 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Insertion Sort Function
void	ins_sort(int array[], int n)
{
	int	element;
	int	i;
	int	j;

	i = 1;
	while (i < n)
	{
		element = array[i];
		j = i - 1;
		while (j >= 0 && array[j] > element)
		{
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = element;
		i++;
	}
}

// #include <stdio.h>
// // Function to print the elements of an array
// void	printArray(int array[], int n)
// {
// 	int	i;

// 	for (i = 0;i < n;i++)
// 		printf("%d ", array[i]);
// }
// // Main Function
// int	main(void)
// {
// 	int array[] = {122, 17, 93, 3, 56};
// 	int n = sizeof(array) / sizeof(array[0]);
// 	insertionSort(array, n);
// 	printArray(array, n);
// 	return (OK);
// }