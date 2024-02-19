#include <stdio.h>

int scan(int *n, int a)
{
	int flag = scanf("%d", n);

	while (flag != 1)
	{
		if (flag == EOF)
			return -1;
			
		printf("Incorrect number entered!\nTry again:\n");
		scanf("%*[^\n]");
		flag = scanf("%d", n);
	}
	
	if (a == 1)
	{
		while (*n <= 0)
		{
			printf("The number must be greater than 0!\nTry again:\n");
			flag = scanf("%d", n);

			if (flag == EOF)
				return -1;
		}
	}
	

	return 0;
}
