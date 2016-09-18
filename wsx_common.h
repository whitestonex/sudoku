#ifndef _WSX_COMMON_H_
#define _WSX_COMMON_H_

#define WSX_DEBUG_LEVEL_ENV     "WSX_DEBUG_LEVEL"

typedef enum
{
	WSX_DBG_LOG_LEVEL_OFF     = 0,
	WSX_DBG_LOG_LEVEL_ERROR	  = 1,
	WSX_DBG_LOG_LEVEL_WARN	  = 2,
	WSX_DBG_LOG_LEVEL_INFO	  = 3,
	WSX_DBG_LOG_LEVEL_DEBUG	  = 4,

	WSX_DBG_LOG_LEVEL_ALL     = 5
}WSX_DBG_LOG_LEVEL;

#define _WSX_LOG(level,str, fmt, ...) \
    do { \
        char *levelStr = 0; \
        int defaultlevel = WSX_DBG_LOG_LEVEL_ERROR; \
        levelStr = getenv(WSX_DEBUG_LEVEL_ENV); \
        if (levelStr != NULL) \
        { \
            defaultlevel = atoi(levelStr); \
        } \
        if (level <= defaultlevel) \
        { \
            fprintf(stderr, "[WSX] " str " : " fmt " (%s:%d:%s)\n", ## __VA_ARGS__, __FUNCTION__, __LINE__, __FILE__); \
        } \
    } while (0)


# define WSX_LOG_ERROR(fmt, ...)    _WSX_LOG(WSX_DBG_LOG_LEVEL_ERROR, "DEBUG", fmt, ## __VA_ARGS__)

# define WSX_LOG_WARN(fmt, ...)    _WSX_LOG(WSX_DBG_LOG_LEVEL_WARN, "DEBUG", fmt, ## __VA_ARGS__)

# define WSX_LOG_INFO(fmt, ...)    _WSX_LOG(WSX_DBG_LOG_LEVEL_INFO, "DEBUG", fmt, ## __VA_ARGS__)

# define WSX_LOG_DEBUG(fmt, ...)    _WSX_LOG(WSX_DBG_LOG_LEVEL_DEBUG, "DEBUG", fmt, ## __VA_ARGS__)

#endif