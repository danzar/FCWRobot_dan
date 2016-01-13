#ifndef FcwServo_h
#define FcwServo_h

void FcwServoSetup(int RightPin, int LeftPin);
void Turn(int RL);
void TurnRandom();
void AvoidObstacle();
void Stop();
void Run(int FB);
void ProcessMove(int moveCommand);

#endif