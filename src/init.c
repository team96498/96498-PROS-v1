
#include "main.h"

void initializeIO() {

pinMode(1, OUTPUT); //configures digital port 1 as output

}
//void autoDrive(){

  /*user code*/
//}
void initialize() {
  FQuad = encoderInit(FQUAD_TOP_PORT, FQUAD_BOTTOM_PORT, false);
  LQuad = encoderInit(LQUAD_TOP_PORT, LQUAD_BOTTOM_PORT, false);
  RQuad = encoderInit(RQUAD_TOP_PORT, RQUAD_BOTTOM_PORT, false);
  





}
