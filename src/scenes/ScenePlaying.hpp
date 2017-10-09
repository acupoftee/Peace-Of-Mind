#pragma once
#include"SceneBase.hpp"

#include <GL/glew.h>

#include "renderer/MasterRenderer.hpp"
#include "map/MapBase.hpp"
#include "player/Player.hpp"

class ScenePlaying : public SceneBase {
public:
	ScenePlaying(const Game& game);

	void update(float delta);
	void render();
	void keyDown(sf::Event::KeyEvent key);
private:
	void updatePlaying(float delta);
	MasterRenderer m_renderer;
	Camera m_camera;

	std::unique_ptr<MapBase> m_map;
	std::unique_ptr<Player> m_player;
	bool m_pause;
};
