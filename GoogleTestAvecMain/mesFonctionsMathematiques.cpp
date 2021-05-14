#include "mesFonctionsMathematiques.h"

// NB : Ces deux fonctions contiennent volontairement des erreurs.
//      Si vous ne les voyez pas, GoogleTest vous aidera à les voir.

int factorielle(int const n)
{
	int fact = 1;
	for (int i = 2; i < n; ++i)
		fact *= i;
	return fact;
}

bool estUnCarreParfait(int const n)
{
	int i;
	for (i = 1; i * i < n; ++i);
	return (i * i == n);
}