void switch_test() 
{
	int a = 0;

	switch (a)
	{
	a = 2;
	printf("a = 2\n");
	case 0:
		printf("0\n");
	case 1:
		a = 3;
		printf("1\n");
		break;
	case 2:
		printf("2\n");
	default:
		printf("d\n");
		break;
	}
}
