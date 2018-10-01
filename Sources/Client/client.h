#pragma once
#if !defined(__CLIENT__)
#define __CLIENT__

#include <ClanLib/core.h>
#include <ClanLib/network.h>
#include "User.h"
#include "VideoSystem.h"
#include "Sources\utilsString.h"
#include "Preferences.h"

class Client : public clientListener
{
public:
	Client();
	~Client();
	void listenLoop();
	void speakLoop();
	void connect_to_server();
	void disconnect_of_server();
	void setUser( User* user )
	{
		this->user = user;
		this->user->setClientListener( this );
	}
	void setVideoSystem( VideoSystem * system )
	{
		this->system = system;
	}
	void hit( int id, int amount );
private:
	int id;
	VideoSystem * system;
	User* user;
	const std::auto_ptr<User> user2;
	void on_connected();
	void on_disconnected();

	void on_event_received(const CL_NetGameEvent &e);

	void on_event_login_success(const CL_NetGameEvent &e);
	void on_event_login_fail(const CL_NetGameEvent &e);
	void on_event_game_loadmap(const CL_NetGameEvent &e);
	void on_event_game_startgame(const CL_NetGameEvent &e);
	void on_event_game_playerstate(const CL_NetGameEvent &e);
	void on_event_game_playerhit(const CL_NetGameEvent &e);
	void on_event_game_playerleaved(const CL_NetGameEvent &e);
private:
	CL_NetGameClient network_client;
	CL_SlotContainer slots;

	CL_NetGameEventDispatcher_v0 login_events;
	CL_NetGameEventDispatcher_v0 game_events;

	bool quit;

	bool logged_in;
};

#endif