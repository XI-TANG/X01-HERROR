#include "XI_LOG.h"
#include <iostream>

XI_LOG::XI_LOG(XI_LOG_TAG_Enum set_tag, XI_LOG_LVL_Enum set_log_level, const char* info) 
{
	int lineRow = __LINE__;
	if (set_tag == XI_LOG_TAG_Enum::XI_LOG_TAG_MAIN) {
		printf("[-MAIN-][-INFO-][-LINE: %d-][- %s]\t\n", lineRow, info);
	}
}