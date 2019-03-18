#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

//added a few messages for the bank robbers and the miner to communicate
enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_GimmeYourGold,
  Msg_GetOut,
  Msg_YouLose,
  Msg_YouWin,
  Msg_TryAgain
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
    return "StewReady";

  case 2:

	return "GimmeYourGold";

  case 3:

	  return "GetOut";

  case 4:

	  return "YouLose";

  case 5:

	  return "YouWin";
  
  case 6:

	return "TryAgain";

  default:

    return "Not recognized!";
  }
}

#endif