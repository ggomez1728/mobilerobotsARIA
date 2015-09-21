
#include "csonar.h"


CSonar::CSonar(){
	//TODO set offset no construtor
	SonarOffsetPosition = {0.0,0.0};
	RelativeAngle = 0.0;
	SonarCone = {15, 0, 3};
}

CSonar::CSonar(float alfa, float bearing, float range){
	//TODO set offset no construtor
	SonarOffsetPosition = { 0.0, 0.0 };
	RelativeAngle = 0.0;
	SonarCone = { alfa, bearing, range };
}

int CSonar::GetMeasure() {
  return stMeasure.Value_m;
}

void CSonar::SetMeasure(int iMeasure) {
  stMeasure.Value_m = iMeasure;
}


void CSonar::SetCone(Cone stCone) {
  SonarCone = stCone ;
}

Cone CSonar::GetCone(){
  return SonarCone;
}

Position CSonar::GetOffsetPosition() {
  return SonarOffsetPosition;
}

