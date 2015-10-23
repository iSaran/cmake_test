#include <iostream>
#include "BHand.h"
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
  //int hwIndex = BHandHardware::getBHandHardwareIndex("BH8-262");
  int hwIndex = BHandHardware::getBHandHardwareIndex("BH8-280");
  if (hwIndex < 0)
  {
    printf("\n\nThe API has not been compiled to include target hand.\n");
      Error();
  }
  bh.setHardwareDesc(hwIndex);
  bool use280Config = (strcmp(bh.getHardwareDesc()->getModelNumber(), "BH8-280") == 0);
  //printf("\nuse280Config = %d\n", use280Config);
  //if (result = bh.InitSoftware(com_port, THREAD_PRIORITY_TIME_CRITICAL))
  //  Error();

  printf("Initialization...");
  if (result = bh.InitHand(""))
    Error();
  else
    printf(" Done\n");
}

int Execute()
{
  printf("Execute: Press Any Key to Abort...");


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

  printf("-- [BHand] Initializing Software...");
  Initialize();
  printf("-- [BHand] Executing - ");
  //Execute();
  bh.Set("1", "M", 100000);
  printf("-- [BHand] Done\n");

  /* Turn off unbuffered input */
  UnbufferedInputEnd();
  return 0;

  cout << "BHand object created." << endl;
}
