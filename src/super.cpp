#include <iostream>
#include "BHand.h"
#include "BHandAppHelper.h"
using namespace std;

BHand bh;
char   buf[100];     // Buffer for reading back hand parameters
int    value;        // Some commands use an int* instead of
int    result;       // Return value (error) of all BHand calls

void Error()
{
  printf("[BHand] ERROR: %d\n%s\n", result, bh.ErrorMessage(result));
  exit(0);
}

// get the difference in time between two timevals (difference in ms)
double diffclock(timeval* currentTime, timeval* startTime)
{
  if (((currentTime->tv_usec)/1000. - (startTime->tv_usec)/1000.) < 0.0) {
    return ((1000.0 + (currentTime->tv_usec)/1000.) - (startTime->tv_usec)/1000.);
  } else {
    return ((currentTime->tv_usec)/1000. - (startTime->tv_usec)/1000.);
  }
}

void Initialize()
{
  // Set hardware description before initialization
  int hwIndex = BHandHardware::getBHandHardwareIndex("BH8-280");
  if (hwIndex < 0)
  {
    printf("\n\nThe API has not been compiled to include target hand.\n");
      Error();
  }
  bh.setHardwareDesc(hwIndex);
  bool use280Config = (strcmp(bh.getHardwareDesc()->getModelNumber(), "BH8-280") == 0);

  if (result = handInitWithMenu(&bh))
    Error();
  printf("Initialization...");
  if (result = bh.InitHand(""))
    Error();
  else
    printf(" Done\n");
}


void doneMoving(char motor)
{
  int mode, hold;
  bh.Get(motor, "MODE", &mode);
  bh.Get(motor, "HOLD", &hold);

  if (mode!=0 & (mode==3 | hold==0)) 
    return false;

  return true;
}

int SimpleGrasp()
{

cout << "--- [BHand] Simple Grasp started..." << endl;

  int rc;

  int sg[4], sg_cur[4], pos_cur[4];
  bh.Get("G", "SG", sg);
 
  bh.Set("G", "V", 20);
  bh.Set("S", "V", 0);
  bh.Set("G", "TSTOP", "0");
  bh.Set("G", "MODE", 4);
  
/** Start grasping. When every fingers feels the object stop and hold the grasp */
  bool flag[3] = {true, true, true};
  flag[2] = false;

  while(flag[0] | flag[1] | flag[2]) 
  {
    bh.Get("G", "P", pos_cur);
    bh.Get("G", "SG", sg_cur);
    
    for (int finger=1; finger<=3; finger++) {
      if (sg_cur[finger-1] - sg[finger-1] > 400 && pos_cur[finger-1] > 80000) 
      {
        bh.Set((char)finger, "MODE", 0);
        flag[finger-1] = false;
      }
      
    }

    int counter = 0;
    if (doneMoving("1") && doneMoving("2") && doneMoving("3")) counter++;

    if (counter > 1000) {
      ROS_INFO("[BHand Server] Simple grasp: I didn't feel forces, but I terminated due to abscence of movement");
      break;
    }
  }

  bh.Set("S", "MODE", 0);
}

int ExecuteHandshake()
{
}


int ExecuteHandover()
{
  printf("Execute Experiment: Press Any Key to Abort...");

  SimpleGrasp();

  bh.Set("1", "M", 100000);

  if (result = bh.Close( "S" ))
    Error();
  if (UnbufferedGetChar() != EOF)
    return 1;

  if (result = bh.Close( "1" ))
    Error();
  if (UnbufferedGetChar() != EOF)
    return 1;

  if (result = bh.Close( "3" ))
    Error();
  if (UnbufferedGetChar() != EOF)
    return 1;

  if (result = bh.Close( "2" ))
    Error();
  if (UnbufferedGetChar() != EOF)
    return 1;

  if (result = bh.Open( "2" ))
    Error();
  if (UnbufferedGetChar() != EOF)
    return 1;

  if (result = bh.Open( "3" ))
    Error();
  if (UnbufferedGetChar() != EOF)
    return 1;

  if (result = bh.Open( "1" ))
    Error();
  if (UnbufferedGetChar() != EOF)
    return 1;

  if (result = bh.StopMotor( "" ))
    Error();
  if (UnbufferedGetChar() != EOF)
    return 1;

  return 0;
}

int main()
{
  setvbuf(stdout, 0, _IONBF, 0);

  /* Turn on unbuffered input */
  UnbufferedInputStart();

  Initialize();

  cout << "-- [BHand] Initializing Software..." << endl;
  cout << "-- [BHand] Which experiment you want to run?" << endl;
  cout << "-- [BHand] 1: Handshake" << endl;
  cout << "-- [BHand] 2: Handover" << endl;
  int option;
  cin >> option;

  switch (option){
    case 1:
      cout << "-- [BHand] Executing handshake experiment" << endl;
      ExecuteHandshake();
      break;
    case 2:
      cout << "-- [BHand] Executing handover experiment" << endl;
      ExecuteHandover();
      break;
    default:
      cout << "-- [BHand] Please type a valid experiment id" << endl;
      return 0;
  }
 
  cout << "-- [BHand] Done..." << endl;

  /* Turn off unbuffered input */
  UnbufferedInputEnd();
  return 0;
}
