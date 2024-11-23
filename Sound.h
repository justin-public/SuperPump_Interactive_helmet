//
//  Sound.h
//  Sound
//
//  Created by justin on 2020/12/16.
//

#ifndef Sound_h
#define Sound_h

//#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>
#include "SoftwareSerial.h"
//#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySerial(D1, D2);
//DFRobotDFPlayerMini myDFPlayer;
DFPlayerMini_Fast myDFPlayer;
#endif /* Sound_h */
