#include "PerformanceMeter.h"
#include "RandomDiceRecognizer.h"
#include "MyDiceRecognizer.h"


int main()
{
	// you are only allowed to change the line below!
	IDiceRecognizer *recognizer = new MyDiceRecognizer();

	PerformanceMeter(recognizer).evaluate();

	delete recognizer;
	system("pause");
	return 0;
}
