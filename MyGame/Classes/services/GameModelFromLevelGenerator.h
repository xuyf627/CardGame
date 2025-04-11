#ifndef GAME_MODEL_FROM_LEVEL_GENERATOR_H  
#define GAME_MODEL_FROM_LEVEL_GENERATOR_H  

#include <memory>  
#include "models/GameModel.h"  
#include "configs/models/LevelConfig.h"  

// 游戏模型生成器服务
class GameModelFromLevelGenerator {
public:
    static std::unique_ptr<GameModel> generateGameModel(const LevelConfig& levelConfig);

private:
    //  生成卡牌ID
    static int generateCardId();

    static int s_nextCardId;
};

#endif