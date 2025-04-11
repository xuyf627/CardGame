#ifndef LEVEL_CONFIG_LOADER_H  
#define LEVEL_CONFIG_LOADER_H  

#include <string>  
#include "../models/LevelConfig.h"  

// πÿø®≈‰÷√º”‘ÿ∆˜
class LevelConfigLoader {
public:
    static LevelConfig loadLevelConfig(int levelId);

    static LevelConfig loadLevelConfigFromJson(const std::string& jsonString);

private:
    static std::string getLevelConfigPath(int levelId);
};

#endif