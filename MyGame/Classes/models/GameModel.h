#ifndef GAME_MODEL_H  
#define GAME_MODEL_H  

#include <vector>  
#include "CardModel.h"  

// ��Ϸ����ģ��:�洢��Ϸ״̬�Ϳ�������
class GameModel {
public:
    GameModel();

    // ��ӿ��Ƶ�������
    void addPlayfieldCard(const CardModel& card);

    // ��ӿ��Ƶ����ƶ�
    void addStackCard(const CardModel& card);

    // �Ƴ��������Ŀ���
    CardModel removePlayfieldCard(int cardId);

    // �Ƴ����ƶѵĶ�������
    CardModel popStackCard();

    // �ƶ����Ƶ����ƶѶ���
    void pushTrayCard(const CardModel& card);

    // �Ƴ����ƶѶ�������
    CardModel popTrayCard();

    // ��ȡ���������п���
    const std::vector<CardModel>& getPlayfieldCards() const;

    // ��ȡ���ƶ����п���
    const std::vector<CardModel>& getStackCards() const;

    // ��ȡ���ƶ����п���
    const std::vector<CardModel>& getTrayCards() const;

    // ��ȡ���ƶѶ�������
    const CardModel& getTopTrayCard() const;

    const CardModel& getPlayfieldCardById(int cardId) const;

    // �ж��������Ƿ��п���
    bool hasPlayfieldCards() const;

    // �жϿ��ƶ��Ƿ��п���
    bool hasStackCards() const;

    bool isGameOver() const;

private:
    std::vector<CardModel> _playfieldCards;  // ���ƶ�
    std::vector<CardModel> _stackCards;      // ���ƶ�
    std::vector<CardModel> _trayCards;       // ���ƶ�
};

#endif