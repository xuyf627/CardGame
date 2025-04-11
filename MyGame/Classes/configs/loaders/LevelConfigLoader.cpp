#include "LevelConfigLoader.h"  
#include "cocos2d.h"  
#include "json/document.h"  
#include "json/stringbuffer.h"  

USING_NS_CC;

LevelConfig LevelConfigLoader::loadLevelConfig(int levelId) { 
    std::string configPath = getLevelConfigPath(levelId);

    std::string jsonString = FileUtils::getInstance()->getStringFromFile(configPath);

    // ¥”JSON◊÷∑˚¥Æº”‘ÿπÿø®≈‰÷√  
    return loadLevelConfigFromJson(jsonString);
}

LevelConfig LevelConfigLoader::loadLevelConfigFromJson(const std::string& jsonString) {
    LevelConfig config;
  
    rapidjson::Document doc;
    doc.Parse(jsonString.c_str());

    if (doc.HasParseError() || !doc.IsObject()) {
        CCLOG("Error parsing level config JSON");
        return config;
    }

    // Ω‚Œˆ÷˜≈∆«¯≈‰÷√  
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray()) {
        const rapidjson::Value& playfieldArray = doc["Playfield"];
        std::vector<CardConfig> playfield;

        for (rapidjson::SizeType i = 0; i < playfieldArray.Size(); i++) {
            const rapidjson::Value& card = playfieldArray[i];

            if (card.IsObject() && card.HasMember("CardFace") && card.HasMember("CardSuit") && card.HasMember("Position")) {
                CardConfig cardConfig;
                cardConfig.cardFace = card["CardFace"].GetInt();
                cardConfig.cardSuit = card["CardSuit"].GetInt();

                const rapidjson::Value& position = card["Position"];
                if (position.IsObject() && position.HasMember("x") && position.HasMember("y")) {
                    cardConfig.position = Vec2(position["x"].GetFloat(), position["y"].GetFloat());
                }

                playfield.push_back(cardConfig);
            }
        }

        config.setPlayfield(playfield);
    }

    // Ω‚Œˆø®≈∆∂—≈‰÷√  
    if (doc.HasMember("Stack") && doc["Stack"].IsArray()) {
        const rapidjson::Value& stackArray = doc["Stack"];
        std::vector<CardConfig> stack;

        for (rapidjson::SizeType i = 0; i < stackArray.Size(); i++) {
            const rapidjson::Value& card = stackArray[i];

            if (card.IsObject() && card.HasMember("CardFace") && card.HasMember("CardSuit")) {
                CardConfig cardConfig;
                cardConfig.cardFace = card["CardFace"].GetInt();
                cardConfig.cardSuit = card["CardSuit"].GetInt();

                if (card.HasMember("Position") && card["Position"].IsObject() &&
                    card["Position"].HasMember("x") && card["Position"].HasMember("y")) {
                    cardConfig.position = Vec2(card["Position"]["x"].GetFloat(), card["Position"]["y"].GetFloat());
                }

                stack.push_back(cardConfig);
            }
        }

        config.setStack(stack);
    }

    return config;
}

std::string LevelConfigLoader::getLevelConfigPath(int levelId) {
    return "levels/level_" + std::to_string(levelId) + ".json";
}