
#include "main.h"

void initializeIO() {

pinMode(1, OUTPUT); //configures digital port 1 as output

}
//void autoDrive(){

  /*user code*/
//}
void initialize() {
  FQuad = encoderInit(FQuad_Top, FQuad_Bottom, false);
  LQuad = encoderInit(LQuad_Top, LQuad_Bottom, false);
  RQuad = encoderInit(RQuad_Top, RQuad_Bottom, false);






}
