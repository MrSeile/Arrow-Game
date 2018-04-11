#include "UserInterface.h"

static void Reset(Rocket &r, World &world)
{
	world.levelImg.loadFromFile(world.ImgPath);
	world.levelTex.loadFromFile(world.ImgPath);
	world.levelSpr.setTexture(world.levelTex);
	r.drawable.setFillColor(world.rocketColor);
	r.acc = { 0, 0 };
	r.vel = { 0, 0 };
	r.pos = { world.iX, world.iY };
	r.drawable.setRotation(world.rotation);
}

UserInterface::UserInterface(sf::RenderWindow &window, Rocket &r, Controller &ctr)
{
	m_font.loadFromFile("res/font/font.ttf");

	ResetUi(window, r, ctr);
}

void UserInterface::ResetUi(sf::RenderWindow &window, Rocket &r, Controller &ctr)
{
	// Clear everything
	m_menu.Clear();
	m_pause.Clear();
	m_play.Clear();
	m_finish.Clear();

	////////////////////
	// MENU
	////////////////////
	// Sprites
	sf::Texture* menuImg_t = new sf::Texture;
	menuImg_t->loadFromFile("res/img/menu.png");

	ui::Sprite* menuImg = m_menu.AddSprite("menuImg", sf::Vector2f(0, 0));
	menuImg->setTexture(*menuImg_t);
	menuImg->setOrigin(sf::Vector2f(menuImg->getLocalBounds().width / 2.f, menuImg->getLocalBounds().height / 2.f));

	menuImg->setUpdateFunction([&](ui::Sprite *self)
	{
		self->setScale(((float)window.getSize().x / (float)self->getTexture()->getSize().x) / 1.1f, ((float)window.getSize().y / (float)self->getTexture()->getSize().y) / 1.1f);

		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2)));
	});

	// Texts
	ui::Text* title = m_menu.AddText("text1", sf::Vector2i(10, 10), m_font);
	title->setOutlineColor(sf::Color::Black);
	title->setOutlineThickness(2);
	title->setString("Arrow Game");
	title->setCharacterSize(80);

	title->setUpdateFunction([&](ui::Text *self)
	{
		self->setPosition(window.mapPixelToCoords(sf::Vector2i((int)(window.getSize().x - self->getGlobalBounds().width - 80), (int)(window.getSize().y - self->getGlobalBounds().height * 1.5f - 10))));
	});

	// Buttons
	ui::Button *resB = m_menu.AddButton("Reset", sf::Vector2f(), m_font);
	resB->text.setString("Reset progress");
	resB->text.setCharacterSize(20);
	resB->shape.setSize(sf::Vector2f(resB->text.getGlobalBounds().width + 20, 30));

	resB->setUpdateFunction([&](ui::Button *self)
	{
		self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i(10, window.getSize().y - 40)));
	});

	resB->setClickFunction([&](ui::Button *self)
	{
		if (MessageBox(NULL, "Are you sure?", "WARNING", MB_YESNO) == IDYES)
		{
			for (World &w : ctr.worlds)
			{
				w.able = w.index != 0 ? false : true;
				w.completed = 0;
				w.record = NO_RECORD;
			}

			ResetUi(window, r, ctr);
		}
	});

	sf::Vector2f pos(10, 10);

	for (World &w : ctr.worlds)
	{
		ui::Button* b = m_menu.AddButton(w.id, sf::Vector2f(), m_font);

		b->text.setString(w.id);
		b->text.setCharacterSize(20);
		b->shape.setSize(sf::Vector2f(b->text.getLocalBounds().width + 20, 30));
		b->setAble(w.able);

		if (pos.x + b->shape.getGlobalBounds().width * 1.1 >= window.getSize().x)
		{
			pos.y += 40;
			pos.x = 10;
		}

		b->setUpdateFunction([&, pos](ui::Button *self)
		{
			self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i((int)pos.x, (int)pos.y)));

			if (w.completed = 1)
			{
				if		(w.record < w.time.goldT)		self->shape.setFillColor({ 255, 200, 000 });
				else if (w.record < w.time.silverT)		self->shape.setFillColor({ 210, 210, 210 });
				else if (w.record < w.time.bronzeT)		self->shape.setFillColor({ 165, 113, 100 });
				else if (w.record < w.time.maxT)		self->shape.setFillColor({ 255, 255, 255 });
				else									self->shape.setFillColor({ 255, 255, 255 });
			}
		});

		b->setClickFunction([&](ui::Button *self)
		{
			for (World &w : ctr.worlds)
			{
				if (self->id == w.id)
				{
					ctr.state = State::Pause;
					ctr.level = w.index;
					ctr.cWorld = &w;

					Reset(r, *ctr.cWorld);

					ctr.cWorld->timer.restart();
				}
			}
		});

		pos.x += b->shape.getGlobalBounds().width * 1.1f + 5;
	}

	/////////////////////////
	// PAUSE
	/////////////////////////
	// Sprites
	sf::Texture* rewardsImg_t = new sf::Texture;
	rewardsImg_t->loadFromFile("res/img/Pause.png");

	ui::Sprite *rewardsImg = m_pause.AddSprite("rewards", sf::Vector2f());
	rewardsImg->setTexture(*rewardsImg_t);
	rewardsImg->setScale(0.7f, 0.7f);
	rewardsImg->setOrigin(sf::Vector2f(rewardsImg->getLocalBounds().width / 2.f, rewardsImg->getLocalBounds().height / 2.f));

	rewardsImg->setUpdateFunction([&](ui::Sprite *self)
	{
		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y - 70)));
	});

	// Texts
	ui::Text *levelTitleP = m_pause.AddText("levelTitleP", sf::Vector2i(), m_font);
	levelTitleP->setCharacterSize(40);
	levelTitleP->setOutlineThickness(1);
	levelTitleP->setOutlineColor(sf::Color::Black);

	levelTitleP->setUpdateFunction([&](ui::Text *self)
	{
		std::stringstream lTitleText;
		lTitleText << ctr.cWorld->id;

		self->setString(lTitleText.str().c_str());
		self->setOrigin(sf::Vector2f(self->getLocalBounds().width / 2.f, 0));

		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, 10)));
	});

	ui::Text *goldT = m_pause.AddText("goldT", sf::Vector2i(), m_font);
	goldT->setFillColor(sf::Color::Black);
	goldT->setCharacterSize(22);

	goldT->setUpdateFunction([&](ui::Text *self)
	{
		std::stringstream goldT_t;
		goldT_t << std::fixed << std::setprecision(3) << ctr.cWorld->time.goldT << "s";

		self->setString(goldT_t.str().c_str());

		self->setPosition(window.mapPixelToCoords(sf::Vector2i((int)(window.getSize().x / 2) - 260, (int)(window.getSize().y) - 90)));
	});

	ui::Text *silverT = m_pause.AddText("silverT", sf::Vector2i(), m_font);
	silverT->setFillColor(sf::Color::Black);
	silverT->setCharacterSize(22);

	silverT->setUpdateFunction([&](ui::Text *self)
	{
		std::stringstream silverT_t;
		silverT_t << std::fixed << std::setprecision(3) << ctr.cWorld->time.silverT << "s";

		self->setString(silverT_t.str().c_str());

		self->setPosition(window.mapPixelToCoords(sf::Vector2i((int)(window.getSize().x / 2) - 25, (int)(window.getSize().y) - 90)));
	});

	ui::Text *bronzeT = m_pause.AddText("bronzeT", sf::Vector2i(), m_font);
	bronzeT->setFillColor(sf::Color::Black);
	bronzeT->setCharacterSize(22);

	bronzeT->setUpdateFunction([&](ui::Text *self)
	{
		std::stringstream bronzeT_t;
		bronzeT_t << std::fixed << std::setprecision(3) << ctr.cWorld->time.bronzeT << "s";

		self->setString(bronzeT_t.str().c_str());

		self->setPosition(window.mapPixelToCoords(sf::Vector2i((int)(window.getSize().x / 2) + 210, (int)(window.getSize().y) - 90)));
	});

	ui::Text *recordT = m_pause.AddText("recordT", sf::Vector2i(), m_font);
	recordT->setFillColor(sf::Color::Black);
	recordT->setOutlineThickness(1);
	recordT->setOutlineColor(sf::Color::White);
	recordT->setCharacterSize(20);

	recordT->setUpdateFunction([&](ui::Text *self)
	{
		std::stringstream t_record;
		if ((int)ctr.cWorld->record != NO_RECORD)
		{
			t_record << std::fixed << std::setprecision(3) << "Record:\n" << ctr.cWorld->record << "s";
		}
		else
		{
			t_record << std::fixed << std::setprecision(3) << "Record:\n--.---";
		}

		self->setString(t_record.str().c_str());

		self->setPosition(window.mapPixelToCoords(sf::Vector2i((int)(window.getSize().x / 2) - 430, (int)(window.getSize().y) - 95)));
	});

	/////////////////
	// Playing
	/////////////////
	// Texts
	ui::Text *currentT = m_play.AddText("currentT", sf::Vector2i(), m_font);
	currentT->setOutlineThickness(2);
	currentT->setOutlineColor(sf::Color::White);

	currentT->setUpdateFunction([&](ui::Text *self)
	{
		if		(ctr.cWorld->currentT < ctr.cWorld->time.goldT)		self->setFillColor({ 255, 200,   0 });
		else if (ctr.cWorld->currentT < ctr.cWorld->time.silverT)	self->setFillColor({ 210, 210, 210 });
		else if (ctr.cWorld->currentT < ctr.cWorld->time.bronzeT)	self->setFillColor({ 165, 113, 100 });
		else														self->setFillColor({ 255, 255, 255 });
		
		std::stringstream currentT_t;
		currentT_t << std::fixed << std::setprecision(3) << ctr.cWorld->currentT << "s";

		self->setString(currentT_t.str().c_str());

		self->setPosition(window.mapPixelToCoords(sf::Vector2i(5, 5)));
	});

	/////////////////
	// End
	/////////////////
	// Sprites
	sf::Texture *winSpr_texture = new sf::Texture;
	winSpr_texture->loadFromFile("res/img/winScreen.png");
	
	ui::Sprite *winSpr = m_finish.AddSprite("winSpr", sf::Vector2f());
	winSpr->setTexture(*winSpr_texture);
	winSpr->setScale(0.5f, 0.5f);
	winSpr->setOrigin(winSpr->getLocalBounds().width / 2.f, winSpr->getLocalBounds().height / 2.f);

	winSpr->setUpdateFunction([&](ui::Sprite *self)
	{
		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2)));
	});

	// Texts
	ui::Text *newRecordT = m_finish.AddText("newRecord", sf::Vector2i(), m_font);
	newRecordT->setCharacterSize(30);
	newRecordT->setFillColor(sf::Color::Black);

	newRecordT->setUpdateFunction([&](ui::Text *self)
	{
		if (ctr.cWorld->currentT == ctr.cWorld->record)
		{
			self->setString("NEW RECORD!");
		}
		else
		{
			self->setString("");
		}

		self->setOrigin(self->getLocalBounds().width / 2.f, 0);
		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, (window.getSize().y / 2) - 55)));
	});

	ui::Text *levelTitleF = m_finish.AddText("levelTitleF", sf::Vector2i(), m_font);
	levelTitleF->setCharacterSize(40);
	levelTitleF->setOutlineThickness(1);
	levelTitleF->setOutlineColor(sf::Color::Black);

	levelTitleF->setUpdateFunction([&](ui::Text *self)
	{
		std::stringstream lTitleText;
		lTitleText << ctr.cWorld->id;

		self->setString(lTitleText.str().c_str());
		self->setOrigin(self->getLocalBounds().width / 2.f, 0);

		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, (window.getSize().y / 2) - 120)));
	});

	ui::Text *finalT = m_finish.AddText("finalT", sf::Vector2i(), m_font);
	finalT->setOutlineThickness(1);
	finalT->setOutlineColor(sf::Color::Black);

	finalT->setUpdateFunction([&](ui::Text *self)
	{
		if		(ctr.cWorld->currentT < ctr.cWorld->time.goldT)		self->setFillColor({ 255, 200,   0 });
		else if (ctr.cWorld->currentT < ctr.cWorld->time.silverT)	self->setFillColor({ 210, 210, 210 });
		else if (ctr.cWorld->currentT < ctr.cWorld->time.bronzeT)	self->setFillColor({ 165, 113, 100 });
		else														self->setFillColor({ 255, 255, 255 });

		std::stringstream finalT_t;
		finalT_t << std::fixed << std::setprecision(3) << ctr.cWorld->currentT << "s";

		self->setString(finalT_t.str().c_str());

		self->setOrigin(self->getLocalBounds().width / 2, self->getLocalBounds().height / 2);

		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2)));
	});

	// BUTTONS
	ui::Button *nextB = m_finish.AddButton("nextB", sf::Vector2f(), m_font);
	nextB->text.setString("Next Level\n[SPACE]");
	nextB->text.setCharacterSize(15);
	nextB->shape.setSize(sf::Vector2f(100, 45));

	nextB->setClickFunction([&](ui::Button *self)
	{
		if (ctr.worlds[ctr.level].NextLevel != "NULL")
		{
			ctr.state = State::Pause;
			ctr.level++;
			ctr.cWorld = &ctr.worlds[ctr.level];
			Reset(r, *ctr.cWorld);
			ctr.cWorld->timer.restart();
		}
	});

	nextB->setUpdateFunction([&](ui::Button *self)
	{
		self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i((window.getSize().x / 2) + 97, (window.getSize().y / 2) + 78)));
		self->text.setPosition(self->shape.getPosition().x + 5, self->shape.getPosition().y + 2);
	});

	ui::Button *resetB = m_finish.AddButton("resetB", sf::Vector2f(), m_font);
	resetB->text.setString("Restart\n[R]");
	resetB->text.setCharacterSize(15);
	resetB->shape.setSize(sf::Vector2f(100, 45));

	resetB->setClickFunction([&](ui::Button *self)
	{
		ctr.state = State::Pause;
		Reset(r, *ctr.cWorld);
		ctr.cWorld->timer.restart();
	});

	resetB->setUpdateFunction([&](ui::Button *self)
	{
		self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i((window.getSize().x / 2) - 50, (window.getSize().y / 2) + 78)));
		self->text.setPosition(self->shape.getPosition().x + 5, self->shape.getPosition().y + 2);
	});

	ui::Button *menuB = m_finish.AddButton("menuB", sf::Vector2f(), m_font);
	menuB->text.setString("Menu\n[M]");
	menuB->text.setCharacterSize(15);
	menuB->shape.setSize(sf::Vector2f(100, 45));

	menuB->setClickFunction([&](ui::Button *self)
	{
		ctr.state = State::Menu;
		Reset(r, *ctr.cWorld);
		ResetUi(window, r, ctr);
	});

	menuB->setUpdateFunction([&](ui::Button *self)
	{
		self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i((window.getSize().x / 2) - 205, (window.getSize().y / 2) + 78)));
		self->text.setPosition(self->shape.getPosition().x + 5, self->shape.getPosition().y + 2);
	});
}

void UserInterface::Update(const State &state, sf::RenderWindow &window)
{
	switch (state)
	{
	case State::Menu:
		m_menu.Update(window);
		break;

	case State::Pause:
		m_pause.Update(window);
		break;
	
	case State::Playing:
		m_play.Update(window);
		break;

	case State::End:
		m_finish.Update(window);
		break;
	}
}

void UserInterface::Draw(const State &state, sf::RenderWindow &window)
{
	switch (state)
	{
	case State::Menu:
		m_menu.Draw(window);
		break;

	case State::Pause:
		m_pause.Draw(window);
		break;

	case State::Playing:
		m_play.Draw(window);
		break;

	case State::End:
		m_finish.Draw(window);
		break;
	}
}

void UserInterface::CheckInput(Controller &ctr, Rocket &r, sf::RenderWindow &window, const sf::Event &evt)
{
	if (evt.type == sf::Event::KeyPressed)
	{
		switch (ctr.state)
		{
		case State::Menu:
			break;

		case State::Pause:
			if (evt.key.code == sf::Keyboard::Up)
			{
				ctr.state = State::Playing;
				ctr.cWorld->timer.restart();
			}
			if (evt.key.code == sf::Keyboard::M)
			{
				ctr.state = State::Menu;
				ResetUi(window, r, ctr);
			}
			break;

		case State::Playing:

			break;

		case State::End:
			if (evt.key.code == sf::Keyboard::Space)
			{
				m_finish.GetButton("nextB")->getClickEvent()(m_finish.GetButton("nextB"));
				break;
			}
			if (evt.key.code == sf::Keyboard::R)
			{
				m_finish.GetButton("resetB")->getClickEvent()(m_finish.GetButton("resetB"));
				break;
			}
			if (evt.key.code == sf::Keyboard::M)
			{
				m_finish.GetButton("menuB")->getClickEvent()(m_finish.GetButton("menuB"));
				break;
			}
			break;
		}
	}

	if (evt.type == sf::Event::MouseButtonPressed)
	{
		if (evt.key.code == sf::Mouse::Left)
		{
			switch (ctr.state)
			{
			case State::Menu:
				m_menu.CheckInput(window);
				break;

			case State::Pause:
				m_pause.CheckInput(window);
				break;

			case State::Playing:
				m_play.CheckInput(window);
				break;

			case State::End:
				m_finish.CheckInput(window);
				break;
			}
		}
	}
}

Widget& UserInterface::GetMenuWidget()
{
	return m_menu;
}

Widget& UserInterface::GetPauseWidget()
{
	return m_pause;
}

Widget& UserInterface::GetPlayWidget()
{
	return m_play;
}

Widget& UserInterface::GetFinishWidget()
{
	return m_finish;
}
