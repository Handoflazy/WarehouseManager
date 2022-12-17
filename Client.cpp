#include"Header.h"
#include"Menu.h"
#include"Object.h"


int main()
{
	Warehouse* s1 = startUp();
	MenuGeneral(s1);
	s1->update();
	
}