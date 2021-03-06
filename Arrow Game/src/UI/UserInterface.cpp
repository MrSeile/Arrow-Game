#include "UserInterface.h"

void UserInterface::Apply(Controller& ctr)
{
	ctr.settings.SetAudioLevel(m_options->Get<ui::Slider>("audioSlider")->GetValue());
	ctr.settings.SetUIScale(m_options->Get<ui::Slider>("scaleSlider")->GetValue());
}

UserInterface::UserInterface(sf::RenderWindow& window, Rocket& r, Controller& ctr, std::thread& ligthing)
{
	zoom = 1.f;

	m_font.loadFromFile("res/font/font.ttf");

	m_menu =	new ui::Widget();
	m_options = new ui::Widget();
	m_pause =	new ui::Widget();
	m_play =	new ui::Widget();
	m_finish =	new ui::Widget();

	////////////////////
	// MENU
	////////////////////
	// Sprites
	sf::Texture* menuImg_t = new sf::Texture;
	menuImg_t->loadFromFile("res/img/menu.png");

	ui::Sprite* menuImg = new ui::Sprite("menuImg");
	menuImg->setTexture(*menuImg_t);
	menuImg->setOrigin(sf::Vector2f(menuImg->getLocalBounds().width / 2.f, menuImg->getLocalBounds().height / 2.f));

	menuImg->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Sprite*>(obj);

		self->setScale(((float)(window.getSize().x * zoom) / (float)self->getTexture()->getSize().x), ((float)(window.getSize().y * zoom) / (float)self->getTexture()->getSize().y));

		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2)));
	});
	m_menu->AddObject(menuImg);
	m_options->AddObject(menuImg);

	// Title
	ui::Text* title = new ui::Text("title");
	title->setFont(m_font);
	title->setOutlineColor(sf::Color::Black);
	title->setOutlineThickness(2);
	title->setString("Arrow Game");
	title->setCharacterSize(100U);

	title->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Text*>(obj);

		self->setPosition(window.mapPixelToCoords(sf::Vector2i(((int)((window.getSize().x) - (self->getGlobalBounds().width / zoom) - (20 / zoom))), (int)((window.getSize().y) - (self->getGlobalBounds().height / zoom) - (40 / zoom)))));
	});
	m_menu->AddObject(title);

	// Quit button
	ui::Button* quitB = new ui::Button("quitButton");
	quitB->text.setFont(m_font);
	quitB->text.setCharacterSize(30);
	quitB->text.setString("X");
	quitB->shape.setSize(sf::Vector2f(30, 30));

	quitB->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Button*>(obj);

		self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x - (int)(self->shape.getSize().x / zoom) - (int)(10 / zoom), (int)(10 / zoom))));
	});

	quitB->SetClickFunction([&](ui::UIObject* obj)
	{
		if (MessageBox(NULL, "Are you sure?", "WARNING", MB_YESNO) == IDYES)
		{
			CloseGame(window, ctr, ligthing);
		}
	});

	m_menu->AddObject(quitB);

	// Option button
	ui::Button* optionsBut = new ui::Button("OptionsBut");
	optionsBut->text.setFont(m_font);
	optionsBut->text.setString("Options");
	optionsBut->text.setCharacterSize(20);
	optionsBut->shape.setSize(sf::Vector2f(optionsBut->text.getGlobalBounds().width + 20, 30));

	optionsBut->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Button*>(obj);

		self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i((int)(10 / zoom), window.getSize().y - (int)(self->shape.getSize().y / zoom) - (int)(10 / zoom))));
	});

	optionsBut->SetClickFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Button*>(obj);
		ctr.SetState(State::Options);
		BeginPlay(ctr);
	});
	m_menu->AddObject(optionsBut);

	// Worlds
	for (World& w : ctr.worlds)
	{
		ui::Button* b = new ui::Button(w.id);
		b->text.setFont(m_font);
		b->text.setString(w.id);
		b->text.setCharacterSize(20);
		b->shape.setSize(sf::Vector2f(b->text.getLocalBounds().width + 20, 30));

		b->SetBeginPlayFunction([&](ui::UIObject* obj)
		{
			auto self = dynamic_cast<ui::Button*>(obj);
			self->SetAble(w.able);
		});

		b->SetUpdateFunction([&](ui::UIObject* obj)
		{
			auto self = dynamic_cast<ui::Button*>(obj);
			if (self != levelButtons[0])
			{
				ptrdiff_t index = std::find(levelButtons.begin(), levelButtons.end(), self) - levelButtons.begin();

				ui::Button* prev = levelButtons[index - 1];

				sf::Vector2f newPos(prev->GetPosition().x + prev->shape.getSize().x + 6, prev->GetPosition().y);

				if (newPos.y == window.mapPixelToCoords(sf::Vector2i(0, (int)(10 / zoom))).y)
				{
					sf::Vector2i quitPos = window.mapCoordsToPixel(m_menu->Get<ui::Button>("quitButton")->GetPosition());

					if ((window.mapCoordsToPixel(newPos).x + (self->shape.getSize().x / zoom)) < quitPos.x - (20 / zoom))
					{
						self->shape.setPosition(newPos);
					}
					else
					{
						self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i((int)(10 / zoom), 0)).x, newPos.y + 40);
					}
				}
				else
				{
					if ((window.mapCoordsToPixel(newPos).x + (self->shape.getSize().x / zoom)) < window.getSize().x)
					{
						self->shape.setPosition(newPos);
					}
					else
					{
						self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i((int)(10 / zoom), 0)).x, newPos.y + 40);
					}
				}
			}
			else
			{
				self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i((int)(10 / zoom), (int)(10 / zoom))));
			}

			if (w.completed == 1)
			{
				if		(w.record < w.time.goldT)		self->shape.setFillColor({ 255, 200, 000 });
				else if (w.record < w.time.silverT)		self->shape.setFillColor({ 210, 210, 210 });
				else if (w.record < w.time.bronzeT)		self->shape.setFillColor({ 165, 113, 100 });
				else if (w.record < w.time.maxT)		self->shape.setFillColor({ 255, 255, 255 });
				else									self->shape.setFillColor({ 255, 255, 255 });
			}
		});

		b->SetClickFunction([&](ui::UIObject* obj)
		{
			auto self = dynamic_cast<ui::Button*>(obj);
			for (World& w : ctr.worlds)
			{
				if (self->id == w.id)
				{
					ctr.SetState(State::Pause);
					BeginPlay(ctr);
					ctr.level = w.index;
					ctr.cWorld = &w;

					r.Reset(*ctr.cWorld);

					ctr.cWorld->timer.restart();
				}
			}
		});

		m_menu->AddObject(b);
		levelButtons.push_back(b);
	}

	/////////////////////////
	// OPTIONS
	/////////////////////////
	// Audio title
	ui::Text* audioText = new ui::Text("audioText");
	audioText->setFont(m_font);
	audioText->setCharacterSize(40);
	audioText->setFillColor(sf::Color::Black);
	audioText->setString("Audio");
	audioText->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Text*>(obj);
		self->setPosition(window.mapPixelToCoords(sf::Vector2i((int)(50 / zoom), (int)(100 / zoom))));
	});
	
	m_options->AddObject(audioText);

	// Audio slider
	ui::Slider* audioSlider = new ui::Slider("audioSlider", m_font);
	audioSlider->SetSize(300, 20);
	audioSlider->SetRange({ 0, 100 });
	audioSlider->SetStep(0.5f);
	audioSlider->GetText().setFillColor(sf::Color::Black);

	audioSlider->SetBeginPlayFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Slider*>(obj);
		self->SetValue(ctr.settings.GetAudioLevel());
	});

	audioSlider->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Slider*>(obj);
		ui::Text* title = m_options->Get<ui::Text>("audioText");

		//self->SetSize(300.f, 20.f);
		self->SetPosition(title->getPosition().x + 50, title->getPosition().y + 60);
	});
	m_options->AddObject(audioSlider);

	// Scale slider
	ui::Slider* scaleSlider = new ui::Slider("scaleSlider", m_font);
	scaleSlider->SetSize(300, 20);
	scaleSlider->SetRange({ 0.2f, 1.8f });
	scaleSlider->SetValue(1.f);
	scaleSlider->SetStep(0.1f);
	scaleSlider->GetText().setFillColor(sf::Color::Black);

	scaleSlider->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Slider*>(obj);
		ui::Text* title = m_options->Get<ui::Text>("audioText");

		self->SetPosition(title->getPosition().x + 50, title->getPosition().y + 60 + 20 + 20);
	});
	m_options->AddObject(scaleSlider);

	// Sprites
	/*sf::Texture* optionsBackgrowndText = new sf::Texture;
	optionsBackgrowndText->loadFromFile("res/img/menu.png");

	ui::Sprite* optionsBkgd = new ui::Sprite("optionsBkgd");
	optionsBkgd->setTexture(*optionsBackgrowndText);
	optionsBkgd->setOrigin(sf::Vector2f(optionsBkgd->getLocalBounds().width / 2.f, optionsBkgd->getLocalBounds().height / 2.f));

	optionsBkgd->SetUpdateFunction([&](ui::Sprite* self)
	{
		self->setScale(((float)window.getSize().x / (float)self->getTexture()->getSize().x), ((float)window.getSize().y / (float)self->getTexture()->getSize().y));

		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2)));
	});*/
	//m_options->AddObject(optionsBkgd);

	// Buttons
	/*ui::Button* resB = new ui::Button("Reset");
	resB->text.setFont(m_font);
	resB->text.setString("Reset progress");
	resB->text.setCharacterSize(20);
	resB->shape.setSize(sf::Vector2f(resB->text.getGlobalBounds().width + 20, 30));

	resB->SetUpdateFunction([&](ui::Button* self)
	{
		self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i(10, window.getSize().y - 40)));
	});

	resB->SetClickFunction([&](ui::Button* self)
	{
		if (MessageBox(NULL, "Are you sure?", "WARNING", MB_YESNO) == IDYES)
		{
			for (World& w : ctr.worlds)
			{
				w.able = w.index != 0 ? false : true;
				w.completed = 0;
				w.record = NO_RECORD;
			}
		}
	});
	m_options->AddObject(resB);*/

	ui::Button* backBut = new ui::Button("OptionsBack");
	backBut->text.setFont(m_font);
	backBut->text.setString("Back");
	backBut->text.setCharacterSize(20);
	backBut->shape.setSize(sf::Vector2f(backBut->text.getGlobalBounds().width + 20, 30));

	backBut->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Button*>(obj);
		self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i((int)(10 / zoom), window.getSize().y - (int)(40 / zoom))));
	});

	backBut->SetClickFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Button*>(obj);
		if (ctr.settings.GetAudioLevel() != m_options->Get<ui::Slider>("audioSlider")->GetValue())
		{
			switch (MessageBox(NULL, "Do you want to save?", "WARNING", MB_YESNOCANCEL))
			{
			case IDYES:
			{
				Apply(ctr);
				ctr.SetState(State::Menu);
				BeginPlay(ctr);
				break;
			}
			case IDNO:
			{
				ctr.SetState(State::Menu);
				BeginPlay(ctr);
				break;
			}
			case IDCANCEL:
			{
				break;
			}
			}
		}
		else
		{
			ctr.SetState(State::Menu);
			BeginPlay(ctr);
		}
	});
	m_options->AddObject(backBut);

	ui::Button* applyBut = new ui::Button("applyBut");
	applyBut->text.setFont(m_font);
	applyBut->text.setString("Apply");
	applyBut->text.setCharacterSize(20);
	applyBut->shape.setSize(sf::Vector2f(backBut->text.getGlobalBounds().width + 20, 30));

	applyBut->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Button*>(obj);
		self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x - (int)(self->shape.getSize().x / zoom) - (int)(10 / zoom), window.getSize().y - (int)(40 / zoom))));
	});

	applyBut->SetClickFunction([&](ui::UIObject* obj)
	{
		Apply(ctr);
	});
	m_options->AddObject(applyBut);

	ui::Button* acceptBut = new ui::Button("acceptBut");
	acceptBut->text.setFont(m_font);
	acceptBut->text.setString("Accept");
	acceptBut->text.setCharacterSize(20);
	acceptBut->shape.setSize(sf::Vector2f(acceptBut->text.getGlobalBounds().width + 20, 30));

	acceptBut->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Button*>(obj);
		self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i(	window.mapCoordsToPixel(m_options->Get<ui::Button>("applyBut")->shape.getPosition()).x - (int)(self->shape.getSize().x / zoom) - (int)(10 / zoom),
																		window.getSize().y - (int)(40 / zoom))));
	});

	acceptBut->SetClickFunction([&](ui::UIObject* obj)
	{
		Apply(ctr);
		ctr.SetState(State::Menu);
		BeginPlay(ctr);
	});
	m_options->AddObject(acceptBut);

	// Texts
	ui::Text* optionsTitle = new ui::Text("optionsTitle");
	optionsTitle->setFont(m_font);
	optionsTitle->setCharacterSize(50);
	optionsTitle->setString("Options");
	optionsTitle->setFillColor(sf::Color::Black);
	optionsTitle->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Text*>(obj);
		self->setPosition(window.mapPixelToCoords(sf::Vector2i((int)(20 / zoom), (int)(20 / zoom))));
	});
	m_options->AddObject(optionsTitle);

	/////////////////////////
	// PAUSE
	/////////////////////////
	// Sprites
	sf::Texture* rewardsImg_t = new sf::Texture;
	rewardsImg_t->loadFromFile("res/img/Pause.png");

	ui::Sprite* rewardsImg = new ui::Sprite("rewards");
	rewardsImg->setTexture(*rewardsImg_t);
	rewardsImg->setScale(0.7f, 0.7f);
	rewardsImg->setOrigin(sf::Vector2f(rewardsImg->getLocalBounds().width / 2.f, rewardsImg->getLocalBounds().height / 2.f));

	rewardsImg->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Sprite*>(obj);
		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y - (int)((70 / zoom)))));
	});
	m_pause->AddObject(rewardsImg);

	// Texts
	ui::Text* levelTitleP = new ui::Text("levelTitleP");
	levelTitleP->setFont(m_font);
	levelTitleP->setCharacterSize(40);
	levelTitleP->setOutlineThickness(1);
	levelTitleP->setOutlineColor(sf::Color::Black);

	levelTitleP->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Text*>(obj);
		std::stringstream lTitleText;
		lTitleText << ctr.cWorld->id;

		self->setString(lTitleText.str().c_str());
		self->setOrigin(sf::Vector2f(self->getLocalBounds().width / 2.f, 0));

		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, (int)(10 / zoom))));
	});
	m_pause->AddObject(levelTitleP);

	ui::Text* goldT = new ui::Text("goldT");
	goldT->setFont(m_font);
	goldT->setFillColor(sf::Color::Black);
	goldT->setCharacterSize(22);

	goldT->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Text*>(obj);
		std::stringstream goldT_t;
		goldT_t << std::fixed << std::setprecision(3) << ctr.cWorld->time.goldT << "s";

		self->setString(goldT_t.str().c_str());

		self->setPosition(window.mapPixelToCoords(sf::Vector2i((int)(window.getSize().x / 2) - (int)(230 / zoom), (int)(window.getSize().y) - (int)(90 / zoom))));
	});
	m_pause->AddObject(goldT);

	ui::Text* silverT = new ui::Text("silverT");
	silverT->setFont(m_font);
	silverT->setFillColor(sf::Color::Black);
	silverT->setCharacterSize(22);

	silverT->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Text*>(obj);
		std::stringstream silverT_t;
		silverT_t << std::fixed << std::setprecision(3) << ctr.cWorld->time.silverT << "s";

		self->setString(silverT_t.str().c_str());

		self->setPosition(window.mapPixelToCoords(sf::Vector2i((int)(window.getSize().x / 2) - (int)(25 / zoom), (int)(window.getSize().y) - (int)(90 / zoom))));
	});
	m_pause->AddObject(silverT);

	ui::Text* bronzeT = new ui::Text("bronzeT");
	bronzeT->setFont(m_font);
	bronzeT->setFillColor(sf::Color::Black);
	bronzeT->setCharacterSize(22);

	bronzeT->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Text*>(obj);
		std::stringstream bronzeT_t;
		bronzeT_t << std::fixed << std::setprecision(3) << ctr.cWorld->time.bronzeT << "s";

		self->setString(bronzeT_t.str().c_str());

		self->setPosition(window.mapPixelToCoords(sf::Vector2i((int)(window.getSize().x / 2) + (int)(190 / zoom), (int)(window.getSize().y) - (int)(90 / zoom))));
	});
	m_pause->AddObject(bronzeT);

	ui::Text* recordT = new ui::Text("recordT");
	recordT->setFont(m_font);
	recordT->setFillColor(sf::Color::Black);
	recordT->setOutlineThickness(1);
	recordT->setOutlineColor(sf::Color::White);
	recordT->setCharacterSize(20);

	recordT->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Text*>(obj);
		std::stringstream t_record;
		if ((int)ctr.cWorld->record != NO_RECORD)
		{
			t_record << std::fixed << std::setprecision(3) << "Record:\n" << ctr.cWorld->record << "s";
		}
		else
		{
			t_record << "Record:\n--.---";
		}

		self->setString(t_record.str().c_str());

		self->setPosition(window.mapPixelToCoords(sf::Vector2i((int)(window.getSize().x / 2) - (int)(400 / zoom), (int)(window.getSize().y) - (int)(95 / zoom))));
	});
	m_pause->AddObject(recordT);

	/////////////////
	// Playing
	/////////////////
	// Texts
	ui::Text* currentT = new ui::Text("currentT");
	currentT->setFont(m_font);
	currentT->setOutlineThickness(2);
	currentT->setOutlineColor(sf::Color::White);

	currentT->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Text*>(obj);
		if		(ctr.cWorld->currentT < ctr.cWorld->time.goldT)		self->setFillColor({ 255, 200,   0 });
		else if (ctr.cWorld->currentT < ctr.cWorld->time.silverT)	self->setFillColor({ 210, 210, 210 });
		else if (ctr.cWorld->currentT < ctr.cWorld->time.bronzeT)	self->setFillColor({ 165, 113, 100 });
		else														self->setFillColor({ 255, 255, 255 });
		
		std::stringstream currentT_t;
		currentT_t << std::fixed << std::setprecision(3) << ctr.cWorld->currentT << "s";

		self->setString(currentT_t.str().c_str());

		self->setPosition(window.mapPixelToCoords(sf::Vector2i((int)(5 / zoom), (int)(5 / zoom))));
	});
	m_play->AddObject(currentT);

	/////////////////
	// End
	/////////////////
	// Sprites
	sf::Texture* winSpr_texture = new sf::Texture;
	winSpr_texture->loadFromFile("res/img/winScreen.png");
	
	ui::Sprite* winSpr = new ui::Sprite("winSpr");
	winSpr->setTexture(*winSpr_texture);
	winSpr->setScale(0.5f, 0.5f);
	winSpr->setOrigin(winSpr->getLocalBounds().width / 2.f, winSpr->getLocalBounds().height / 2.f);

	winSpr->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Sprite*>(obj);
		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2)));
	});
	m_finish->AddObject(winSpr);

	// Texts
	ui::Text* newRecordT = new ui::Text("newRecord");
	newRecordT->setFont(m_font);
	newRecordT->setCharacterSize(30);
	newRecordT->setFillColor(sf::Color::Black);

	newRecordT->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Text*>(obj);
		if (ctr.cWorld->currentT == ctr.cWorld->record)
		{
			self->setString("NEW RECORD!");
		}
		else
		{
			self->setString("");
		}

		self->setOrigin(self->getLocalBounds().width / 2.f, 0);
		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, (window.getSize().y / 2) - (int)(55 / zoom))));
	});
	m_finish->AddObject(newRecordT);

	ui::Text* levelTitleF = new ui::Text("levelTitleF");
	levelTitleF->setFont(m_font);
	levelTitleF->setCharacterSize(40);
	levelTitleF->setOutlineThickness(1);
	levelTitleF->setOutlineColor(sf::Color::Black);

	levelTitleF->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Text*>(obj);
		std::stringstream lTitleText;
		lTitleText << ctr.cWorld->id;

		self->setString(lTitleText.str().c_str());
		self->setOrigin(self->getLocalBounds().width / 2.f, 0);

		self->setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, (window.getSize().y / 2) - (int)(120 / zoom))));
	});
	m_finish->AddObject(levelTitleF);

	ui::Text* finalT = new ui::Text("finalT");
	finalT->setFont(m_font);
	finalT->setOutlineThickness(1);
	finalT->setOutlineColor(sf::Color::Black);

	finalT->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Text*>(obj);
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
	m_finish->AddObject(finalT);

	// BUTTONS
	ui::Button* nextB = new ui::Button("nextB");
	nextB->text.setFont(m_font);
	nextB->text.setString("Next Level\n[SPACE]");
	nextB->text.setCharacterSize(15);
	nextB->shape.setSize(sf::Vector2f(100, 45));

	nextB->SetClickFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Button*>(obj);
		if (ctr.worlds[ctr.level].NextLevel != "NULL")
		{
			ctr.SetState(State::Pause);
			BeginPlay(ctr);
			ctr.level++;
			ctr.cWorld = &ctr.worlds[ctr.level];
			r.Reset(*ctr.cWorld);
			ctr.cWorld->timer.restart();
		}
	});

	nextB->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Button*>(obj);
		self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i((window.getSize().x / 2) + (int)(88 / zoom), (window.getSize().y / 2) + (int)(71 / zoom))));
		self->text.setPosition(self->shape.getPosition().x + 5, self->shape.getPosition().y + 2);
	});
	m_finish->AddObject(nextB);

	ui::Button* resetB = new ui::Button("resetB");
	resetB->text.setFont(m_font);
	resetB->text.setString("Restart\n[R]");
	resetB->text.setCharacterSize(15);
	resetB->shape.setSize(sf::Vector2f(100, 45));

	resetB->SetClickFunction([&](ui::UIObject* obj)
	{
		ctr.SetState(State::Pause);
		BeginPlay(ctr);
		r.Reset(*ctr.cWorld);
		ctr.cWorld->timer.restart();
	});

	resetB->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Button*>(obj);
		self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i((window.getSize().x / 2) - (int)(45 / zoom), (window.getSize().y / 2) + (int)(71 / zoom))));
		self->text.setPosition(self->shape.getPosition().x + 5, self->shape.getPosition().y + 2);
	});
	m_finish->AddObject(resetB);

	ui::Button* menuB = new ui::Button("menuB");
	menuB->text.setFont(m_font);
	menuB->text.setString("Menu\n[M]");
	menuB->text.setCharacterSize(15);
	menuB->shape.setSize(sf::Vector2f(100, 45));

	menuB->SetClickFunction([&](ui::UIObject* obj)
	{
		ctr.SetState(State::Menu);
		BeginPlay(ctr);
		r.Reset(*ctr.cWorld);
	});

	menuB->SetUpdateFunction([&](ui::UIObject* obj)
	{
		auto self = dynamic_cast<ui::Button*>(obj);
		self->shape.setPosition(window.mapPixelToCoords(sf::Vector2i((window.getSize().x / 2) - (int)(186 / zoom), (window.getSize().y / 2) + (int)(71 / zoom))));
		self->text.setPosition(self->shape.getPosition().x + 5, self->shape.getPosition().y + 2);
	});
	m_finish->AddObject(menuB);


	////////////////////////
	// CALL BEGIN PLAY
	////////////////////////
	BeginPlay(ctr);
}

void UserInterface::Update(const State& state, sf::RenderWindow& window)
{
	switch (state)
	{
	case State::Menu:
		m_menu->Update(window);
		break;

	case State::Options:
		m_options->Update(window);
		break;

	case State::Pause:
		m_pause->Update(window);
		break;
	
	case State::Playing:
		m_play->Update(window);
		break;

	case State::End:
		m_finish->Update(window);
		break;
	}
}

void UserInterface::Draw(const State& state, sf::RenderWindow& window)
{
	switch (state)
	{
	case State::Menu:
		m_menu->Draw(window);
		break;
		
	case State::Options:
		m_options->Draw(window);
		break;

	case State::Pause:
		m_pause->Draw(window);
		break;

	case State::Playing:
		m_play->Draw(window);
		break;

	case State::End:
		m_finish->Draw(window);
		break;
	}
}

void UserInterface::CheckInput(Controller& ctr, Rocket& r, sf::RenderWindow& window, const sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		switch (ctr.GetState())
		{
		case State::Menu:
			if (e.key.code == sf::Keyboard::Q)
			{
				m_menu->Get<ui::Slider>("audioSlider")->SetValue(0.5f);
			}
			break;

		case State::Options:
			if (e.key.code == sf::Keyboard::Escape)
			{
				m_options->Get<ui::Button>("OptionsBack")->GetClickEvent()(m_options->Get<ui::Button>("OptionsBack"));
			}
			break;

		case State::Pause:
			if (e.key.code == sf::Keyboard::Up)
			{
				ctr.SetState(State::Playing);
				BeginPlay(ctr);
				ctr.cWorld->timer.restart();
			}
			if (e.key.code == sf::Keyboard::M || e.key.code == sf::Keyboard::Escape)
			{
				ctr.SetState(State::Menu);
				BeginPlay(ctr);
			}
			break;

		case State::Playing:

			break;

		case State::End:
			if (e.key.code == sf::Keyboard::Space)
			{
				ui::Button* functButton = m_finish->Get<ui::Button>("nextB");
				functButton->GetClickEvent()(functButton);
				break;
			}
			if (e.key.code == sf::Keyboard::R)
			{
				ui::Button* functButton = m_finish->Get<ui::Button>("resetB");
				functButton->GetClickEvent()(functButton);
				break;
			}
			if (e.key.code == sf::Keyboard::M)
			{
				ui::Button* functButton = m_finish->Get<ui::Button>("menuB");
				functButton->GetClickEvent()(functButton);
				break;
			}
			break;
		}
	}

	switch (ctr.GetState())
	{
	case State::Menu:
		m_menu->CheckInput(window, e);
		break;

	case State::Options:
		m_options->CheckInput(window, e);
		break;

	case State::Pause:
		m_pause->CheckInput(window, e);
		break;

	case State::Playing:
		m_play->CheckInput(window, e);
		break;

	case State::End:
		m_finish->CheckInput(window, e);
		break;
	}
}

void UserInterface::BeginPlay(Controller& ctr)
{
	switch (ctr.GetState())
	{
	case State::Menu:
		m_menu->BeginPlay();
		break;

	case State::Options:
		m_options->BeginPlay();
		break;

	case State::Pause:
		m_pause->BeginPlay();
		break;

	case State::Playing:
		m_play->BeginPlay();
		break;

	case State::End:
		m_finish->BeginPlay();
		break;
	}
}

ui::Widget* UserInterface::GetMenuWidget()
{
	return m_menu;
}

ui::Widget* UserInterface::GetOptionsWidget()
{
	return m_options;
}

ui::Widget* UserInterface::GetPauseWidget()
{
	return m_pause;
}

ui::Widget* UserInterface::GetPlayWidget()
{
	return m_play;
}

ui::Widget* UserInterface::GetFinishWidget()
{
	return m_finish;
}
