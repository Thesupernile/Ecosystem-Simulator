#include "animal.cpp"

class herbivore : public animal
{
	private:
		
	public:
		herbivore(int xCoord, int yCoord) : animal(xCoord, yCoord) {
			_canEatPlant = true;
		}
};