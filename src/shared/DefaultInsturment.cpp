#include "DefaultInstrument.h"

DefaultInstrument::DefaultInstrument() :
    theIdentity(""),
    theInstrLoc("")
{
    theCommBus = VisaInterface();


}


