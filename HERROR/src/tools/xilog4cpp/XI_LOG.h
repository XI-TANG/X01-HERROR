#pragma once

/*
 * 日志格式：[TAG][LVL][FILE|LINE][INFO]
 *		实例：[-MAIN-][-ERROR-][-main.c|27-][-glfwinit err, cannot init]
 * 计划功能：
 *		1.不同的level带有不同的颜色
 *		2.能够通过TAG关闭LOG
 *		3.能够通过LVL设置（EN）不同等级的LOG
 *		4.计划拥有输出到文件中的功能
 */

 /*只开对应功能的日志，每个TAG对应一个模块*/
enum class XI_LOG_TAG_Enum
{
	XI_LOG_TAG_MAIN,
	XI_LOG_TAG_SHADER,
	XI_LOG_TAG_PLAYER,
	XI_LOG_TAG_DATA
};

/*只开对应的level的日志*/
enum class XI_LOG_LVL_Enum
{
	XI_LOG_FILTER_LVL_SILENT = 0,
	XI_LOG_LVL_ASSERT,
	XI_LOG_LVL_INFO,
	XI_LOG_LVL_VERBOSE,
	XI_LOG_LVL_DEBUG,
	XI_LOG_LVL_WARNING,
	XI_LOG_LVL_ERROR,
	XI_LOG_FILTER_LVL_ALL
};

class XI_LOG
{
public:
	XI_LOG(XI_LOG_TAG_Enum set_tag, XI_LOG_LVL_Enum set_log_level);
};

