#include "client.h"
#include "../custom_type.h"

Client::Client()
{
    // Connect essential signals - connecting, disconnecting and receiving events
    slots.connect(network_client.sig_event_received(), this, &Client::on_event_received);
    slots.connect(network_client.sig_connected(), this, &Client::on_connected);
    slots.connect(network_client.sig_disconnected(), this, &Client::on_disconnected);

    // Set up event dispatchers to route incoming events to functions
    login_events.func_event("Login-Success").set(this, &Client::on_event_login_success);
    login_events.func_event("Login-Fail").set(this, &Client::on_event_login_fail);
    game_events.func_event("Game-LoadMap").set(this, &Client::on_event_game_loadmap);
    game_events.func_event("Game-Start").set(this, &Client::on_event_game_startgame);
    game_events.func_event("player_state").set(this, &Client::on_event_game_playerstate);
    game_events.func_event("player_hit").set(this, &Client::on_event_game_playerhit);
    game_events.func_event("player_leaved").set(this, &Client::on_event_game_playerleaved);

    quit = false;
    logged_in = false;
    user = 0;
    id = -1;
}

Client::~Client()
{
}


// Connect to localhost server
void Client::connect_to_server()
{
    try
    {
        Preferences pref;
        network_client.connect(pref.getIp(), pref.getPort());
    }
    catch(const CL_Exception &e)
    {
        cl_log_event("error", e.message);
    }
}

void Client::disconnect_of_server()
{
	try
	{
		quit = true;
		logged_in = false;
		user = 0;
		id = -1;
		network_client.disconnect();
	}
	catch(const CL_Exception &e)
	{
		cl_log_event("error", e.message);
	}
}

// Successfully connected to server
void Client::on_connected()
{
	cl_log_event("network", "Connected to server");

	// For demonstration purposes, lets fail a login
	//network_client.send_event(CL_NetGameEvent("Login", "")); // We will receive an error event for this, as we don't send a proper user name

	// Properly login
	network_client.send_event(CL_NetGameEvent("Login", "my user name"));
}

// Disconnected from server
void Client::on_disconnected()
{
	cl_log_event("network", "Disconnected from server");
	quit = true;
	logged_in = false;
	user = 0;
	id = -1;
}

// An event was received from server
void Client::on_event_received(const CL_NetGameEvent &e) 
{
	//cl_log_event("events", "Server sent event: %1", e.to_string());

	bool handled_event = false;
	
	if(!logged_in)
	{
		// We haven't logged in, so route events to login dispatcher
		handled_event = login_events.dispatch(e);
	}
	else
	{
		// We have logged in, so route events to game dispatcher
		handled_event = game_events.dispatch(e);
	}

	if(!handled_event)
	{
		// We received an event which we didn't hook up
		cl_log_event("events", "Unhandled event: %1", e.to_string());
	}
}

// "Login-Success" event was received
void Client::on_event_login_success(const CL_NetGameEvent &e)
{
	cl_log_event("events", "Login success");

	logged_in = true;
	id = e.get_argument(0).to_integer();

	network_client.send_event(CL_NetGameEvent("Game-RequestStart"));
}

// "Login-Fail" event was received
void Client::on_event_login_fail(const CL_NetGameEvent &e)
{
	CL_String fail_reason = e.get_argument(0);

	cl_log_event("events", "Login failed: %1", fail_reason);
}

// "Game-LoadMap" event was received
void Client::on_event_game_loadmap(const CL_NetGameEvent &e) 
{
	CL_String map_name = e.get_argument(0);
	int max_players = e.get_argument(1);
	CustomType position = e.get_argument(2);

	cl_log_event("events", "Loading map: %1 with %2 players, Position %3,%4,%5", map_name, max_players, position.get_x(), position.get_y(), position.get_z());
}

// "Game-Start" event was received
void Client::on_event_game_startgame(const CL_NetGameEvent &e) 
{
	cl_log_event("events", "Starting game!");
}

void Client::listenLoop()
{
	while (!quit)
	{
		CL_Event::wait(network_client.get_event_arrived());
		network_client.process_events();
	}
}

void Client::speakLoop()
{
	while (!quit)
	{
		Sleep(100);
		if ( logged_in && (user!=0) ) {
			UserState * state = new UserState();
			user->populateState( state );
			CL_NetGameEvent e("player_state", state->x, state->y, state->z);
			CL_NetGameEventValue valueX(state->xDir);
			e.add_argument( valueX );
			CL_NetGameEventValue valueY(state->yDir);
			e.add_argument( valueY );
			CL_NetGameEventValue valueZ(state->zDir);
			e.add_argument( valueZ );
			network_client.send_event( e );
			delete (state);
		}
	}
}

void Client::on_event_game_playerstate(const CL_NetGameEvent &e)
{
	if ( logged_in && (user!=0) ) 
	{
		int enemyId = e.get_argument( 6 ).to_integer();
		if ( enemyId != this->id ) 
		{
			UserState * state = new UserState();
			state->x = e.get_argument( 0 ).to_number();
			state->y = e.get_argument( 1 ).to_number();
			state->z = e.get_argument( 2 ).to_number();
			state->xDir = e.get_argument( 3 ).to_number();
			state->yDir = e.get_argument( 4 ).to_number();
			state->zDir = e.get_argument( 5 ).to_number();
			
			system->enemyState( enemyId, state );
			delete ( state );
		}
	}
}

void Client::hit( int id, int amount )
{
	CL_NetGameEvent e("player_hit", id, amount);
	network_client.send_event( e );
}

void Client::on_event_game_playerhit(const CL_NetGameEvent &e)
{
	if ( this->id == e.get_argument(0).to_integer() ) 
	{
		int amount = e.get_argument(1).to_integer();
		std::string s = "Me Hitted! : ";
		s.append( util::NumberToString<int>( amount ) );
		cl_log_event("events", s);
		user->meHitted( amount );
	}
}

void Client::on_event_game_playerleaved(const CL_NetGameEvent &e)
{
	if ( logged_in && (user!=0) ) 
	{
		int enemyId = e.get_argument( 0 ).to_integer();
		if ( enemyId != this->id ) 
		{
			system->enemyState( enemyId, 0 );
		}
	}
}