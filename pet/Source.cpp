#define ASLIB_INCLUDE_DL
#include <AsLib.hpp>

//�y�b�g�̊Ǘ�
struct Pet {
	//UI
	AnimeUI ui;
	//�̗�
	int32_t hp = 0;
	//�j������
	Pos2R speed = { 3.0f,3.0f };
	//�ړI�ΏۂƂ̋���
	float dis = 0.0f;

	Pet() = default;
	const Pet(const AnimeMainData* const add_tmd, const uint8_t add_alpha, const Pos4& add_pos4, const int32_t hp_) :ui(add_tmd, add_alpha, add_pos4), hp(hp_) {}
	const Pet(const AnimeMainData* const add_tmd, const uint8_t add_alpha, const PosA4R& add_pos4, const int32_t hp_) : ui(add_tmd, add_alpha, add_pos4), hp(hp_) {}

	Pet& move(std::vector<AnimeUI>& food)
	{
		//�a�����邩���ׁA�����a����������ŏ������̉a�ֈړ�����
		size_t dis_id = 0;
		if (searchMin(food, this->ui.PosF(), dis_id, &this->dis) == -1) return *this;
		//�a�̕����Ɍ������Ĉړ�����
		this->ui.addPosF(Pos2R(((food[dis_id].PosF().x < this->ui.PosF().x) ? this->speed.x*(-1) : this->speed.x), ((food[dis_id].PosF().y < this->ui.PosF().y) ? this->speed.y*(-1) : this->speed.y)));
		//�a��H�ׂ�
		if (this->dis < 2.8f) food.erase(food.begin() + dis_id);
		return *this;
	}
};

int32_t asMain()
{
	MainControl as(u8"Jellyfish", Pos2(960,540),ColorRGB(174,221,222));
	//�摜�t�@�C��
	const AnimeMainData petA(5, asLoadTex(u8"Picture/Pet/pet.png", 5));
	const AnimeMainData foodA(1, asLoadTex(u8"Picture/Pet/food.png", 1));
	const AnimeMainData twitterA(1, asLoadTex(u8"Picture/SNS/twitter.png", 1));

	//�y�b�g
	Pet pet(&petA, 150, PosA4R(100.0f, 100.0f, 100.0f, 100.0f), 10);
	//�a
	std::vector<AnimeUI> food;
	food.resize(size_t(asRand8(10)));
	for (AnimeUI& i : food) i.setUI(&foodA, 255, PosA4R(float(asRand32(asWindowSize().x)), 0.0f, 20.0f, 20.0f));

	//SNS
	AnimeUI twitterUI(&twitterA, 150, Pos4(100, 100, 200, 200));
	Twitter t;

	//���C�����[�v
	while (as.loop())
	{
		pet.move(food).ui.fpsUpdate().addSizeF(0.0f,1000.0f).addRota(0.01f).drawRF();
		for (size_t i = 0; i < food.size(); ++i) {
			//�a���E�B���h�E�O�ɏo����a������
			if (food[i].addPosF(0.0f, 0.3f).drawF().isOutWindowF()) { food.erase(food.begin() + i); --i; }
		}
		//�^�b�`���ꂽ��a���o��
		if (as.isUp()) {
			food.emplace_back();
			food[food.size() - 1].setUI(&foodA, 255, PosA4R(float(asRand32(asWindowSize().x)), 0.0f, 20.0f, 20.0f));
		}

		if (twitterUI.draw().update().Up()) {
			t.makeUrl(u8"https://goo.gl/DMh1QF").hashtags(u8"test").related(u8"wanotaitei");
			t.text(u8"%E3%82%AF%E3%83%A9%E3%82%B2%E3%82%92%E8%82%B2%E6%88%90%E4%B8%AD%E2%80%A6%E2%80%A6");
			t.send();
		}
	}
	return 0;
}