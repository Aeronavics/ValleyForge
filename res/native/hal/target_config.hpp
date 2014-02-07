// TODO - This needs to be fixed up.

//Linux has no well-defined controller definition but have one anyways to fit the interface
#ifdef __linux__
enum CAN_CTRL {CAN_0, NB_CTRL};
#endif

// The linux has no well-defined message objects but have as many as I can to fit the interface
#ifdef __linux__
enum CAN_BUF { BUF_0 };
enum CAN_FIL { FIL_0 };
enum CAN_MSK { MSK_0 };
#endif //__Native_Linux__

