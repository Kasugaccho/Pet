#define ASLIB_INCLUDE_DL
#include <AsLib.hpp>

//ペットの管理
struct Pet {
	AnimeUI ui;
	int32_t hp = 0;
	Pos2R speed = { 2.0f,2.0f };

	Pet() = default;
	const Pet(const AnimeMainData* const add_tmd, const uint8_t add_alpha, const Pos4& add_pos4, const int32_t hp_) :ui(add_tmd, add_alpha, add_pos4), hp(hp_) {}
	const Pet(const AnimeMainData* const add_tmd, const uint8_t add_alpha, const PosA4R& add_pos4, const int32_t hp_) : ui(add_tmd, add_alpha, add_pos4), hp(hp_) {}

	Pet& move(std::vector<AnimeUI>& food)
	{
		//餌があるか調べ、もし餌があったら最小距離の餌へ移動する
		size_t dis_id = 0;
		float dis = 0.0f;
		if (searchMin(food, this->ui.PosF(), dis_id, &dis) == -1) return *this;
		//餌の方向に向かって移動する
		this->ui.addPosF(Pos2R(((food[dis_id].PosF().x < this->ui.PosF().x) ? this->speed.x*(-1) : this->speed.x), ((food[dis_id].PosF().y < this->ui.PosF().y) ? this->speed.y*(-1) : this->speed.y)));
		//餌を食べる
		if (dis < 2.8f) food.erase(food.begin() + dis_id);
		return *this;
	}
};

int32_t asMain()
{
	MainControl as(u8"a", Pos2(540, 960));

	//画像ファイル
	const AnimeMainData petA(5, asLoadTex(u8"Picture/Pet/pet.png", 5));
	const AnimeMainData foodA(1, asLoadTex(u8"Picture/Pet/food.png", 1));
	const TextureMainData bg(asLoadTex(u8"Picture/BG/bg.png"));

	//ペット
	Pet pet(&petA, 150, PosA4R(100.0f, 100.0f, 100.0f, 100.0f), 10);

	//餌
	std::vector<AnimeUI> food;
	food.resize(size_t(asRand8(10)));
	for (AnimeUI& i : food) i.setUI(&foodA, 255, PosA4R(float(asRand32(asWindowSize().x)), 0.0f, 20.0f, 20.0f));

	//メインループ
	while (as.loop())
	{
		//背景を描画
		bg.draw();
		pet.move(food).ui.fpsUpdate().addSizeF(0.0f).drawF();
		for (size_t i = 0; i < food.size(); ++i) {
			//餌がウィンドウ外に出たら餌を消す
			if (food[i].addPosF(0.0f, 0.5f).drawF().isOutWindowF()) { food.erase(food.begin() + i); --i; }
		}

		//タッチされたら餌を出す
		if (as.isUp()) {
			food.emplace_back();
			food[food.size() - 1].setUI(&foodA, 255, PosA4R(float(asRand32(asWindowSize().x)), 0.0f, 20.0f, 20.0f));
		}

	}

	return 0;
}