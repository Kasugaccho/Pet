#define ASLIB_INCLUDE_DL
#include <AsLib.hpp>
#include <forward_list>

struct Pet {
	AnimeUI ui;
	int32_t hp = 0;

	Pet() = default;
	const Pet(const AnimeMainData* const add_tmd, const uint8_t add_alpha, const Pos4& add_pos4, const int32_t hp_) :ui(add_tmd, add_alpha, add_pos4), hp(hp_) {}
	const Pet(const AnimeMainData* const add_tmd, const uint8_t add_alpha, const PosA4R& add_pos4, const int32_t hp_) : ui(add_tmd, add_alpha, add_pos4), hp(hp_) {}
};

int32_t asMain()
{
	MainControl as(u8"a", Pos2(540, 960));

	//アニメーションファイル
	const AnimeMainData petA(5, asLoadTex(u8"Picture/Pet/pet.png", 5));
	//画像ファイル
	const AnimeMainData foodA(1, asLoadTex(u8"Picture/Pet/food.png", 1));
	const TextureMainData bg(asLoadTex(u8"Picture/BG/bg.png"));

	//アニメーション管理ファイル
	Pet pet(&petA, 255, PosA4R(100.0f, 100.0f, 50.0f, 50.0f), 10);
	std::vector<AnimeUI> food;
	size_t r = size_t(asRand8(10));
	food.resize(r);
	for (AnimeUI& i : food) {
		i.setUI(&foodA, 255, PosA4R(float(asRand32(asWindowSize().x)), 0.0f, 20.0f, 20.0f));
	}

	while (asLoop())
	{
		bg.draw();
		pet.ui.fpsUpdate().addSizeF(Pos2R(0.1f, 0.01f)).drawF();
		for (size_t i = 0; i < r; ++i) {
			if (food[i].addPosF(0.0f, 0.9f).drawF().isOutWindowF()) {
				food.erase(food.begin() + i);
				--r;
				--i;
			}
		}
	}

	return 0;
}