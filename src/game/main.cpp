#include "../core/tins2017.h"
#include "../core/gameconstants.h"

int main(int argc, char** argv) {
    Tins2017 tsr( GameConstants::WindowWidth, GameConstants::WindowHeight );
	tsr.exec(argc, argv);
	return 0;
}
