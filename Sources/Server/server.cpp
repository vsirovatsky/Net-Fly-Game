#include "server.h"
#include "server_user.h"
#include "../custom_type.h"

Server::Server()
: next_user_id(1)
{
	// Connect essential signals - connecting, disconnecting and receiving events
	slots.connect(network_server.sig_client_connected(), this, &Server::on_client_connected);
	slots.connect(network_server.sig_client_disconnected(), this, &Server::on_client_disconnected);
	slots.connect(network_server.sig_event_received(), this, &Server::on_event_received);

	// Set up event dispatchers to route incoming events to functions
	login_events.func_event("Login").set(this, &Server::on_event_login);
	game_events.func_event("Game-RequestStart").set(this, &Server::on_event_game_requeststart);
	game_events.func_event("ping").set(this, &Server::on_event_game_ping);
	game_events.func_event("player_state").set(this, &Server::on_event_game_userstate);
	game_events.func_event("player_hit").set(this, &Server::on_event_game_playerhit);
	
	game_running = false;
}

Server::~Server()
{
}

// Server main loop
void Server::exec()
{
	network_server.start("4556");

	cl_log_event("system", "SERVER started");

	while (true)
	{
		// Wait till we receive any network events
		CL_Event::wait(network_server.get_event_arrived());
		network_server.process_events();
	}

	network_server.stop();
}

// A new client is connecting
void Server::on_client_connected(CL_NetGameConnection *connection)
{
	cl_log_event("network", "Client connected");

	// Create user and attach it to connection
	ServerUser *user = new ServerUser();
	user->attach_to_connection(connection);
}

// A client disconnected
void Server::on_client_disconnected(CL_NetGameConnection *connection)
{
	cl_log_event("network", "Client disconnected");

	ServerUser *user = ServerUser::get_user(connection);
	if(user)
	{
		CL_NetGameEvent e1("player_leaved", user->id);
		network_server.send_event( e1 ); 
		delete user;
	}

	// Shut down running game for test-purposes
	//if(game_running)
	//	game_running = false;
}

// An event was received from a client
void Server::on_event_received(CL_NetGameConnection *connection, const CL_NetGameEvent &e)
{
	cl_log_event("events", "Client sent event: %1", e.to_string());

	ServerUser *user = ServerUser::get_user(connection);
	if(user)
	{
		bool handled_event = false;

		if (user->id == 0)	// User has not logged in, so route events to login dispatcher
		{
			// Route login events
			handled_event = login_events.dispatch(e, user);
		}
		else
		{
			// Route game events
			handled_event = game_events.dispatch(e, user);
		}

		if (!handled_event)
		{
			// We received an event which we didn't hook up
			cl_log_event("events", "Unhandled event: %1", e.to_string());
		}
	}
}

// "Login" event was received
void Server::on_event_login(const CL_NetGameEvent &e, ServerUser *user)
{
	cl_log_event("events", "Client requested login");

	CL_String user_name = e.get_argument(0);

	if(user_name.length() == 0)
	{
		user->send_event(CL_NetGameEvent("Login-Fail", "Missing user name"));
	}
	else
	{
		// Assign name and id to User object (created when user connected earlier)
		user->user_name = user_name;
		user->id = next_user_id++;

		user->send_event(CL_NetGameEvent("Login-Success",user->id));
	}
}

// "Game-RequestStartGame" event was received
void Server::on_event_game_requeststart(const CL_NetGameEvent &e, ServerUser *user)
{
	cl_log_event("events", "Client requested game start");

	if(game_running == false)
	{
		game_running = true;

		CL_String map_name = "Map1";
		int max_players = 6;

		CustomType position(143,22,3);

		CL_NetGameEvent loadMapEvent("Game-LoadMap");
		loadMapEvent.add_argument(map_name);
		loadMapEvent.add_argument(max_players);
		loadMapEvent.add_argument(position);
		network_server.send_event(loadMapEvent);

		network_server.send_event(CL_NetGameEvent("Game-Start"));
	}
}

void Server::on_event_game_ping(const CL_NetGameEvent &e, ServerUser *user)
{
	cl_log_event("events", "ping from " + user->id);
}

void Server::on_event_game_userstate(const CL_NetGameEvent &e, ServerUser *user)
{
	CL_NetGameEventValue v0 = e.get_argument( 0 );
	CL_NetGameEventValue v1 = e.get_argument( 1 );
	CL_NetGameEventValue v2 = e.get_argument( 2 );
	CL_NetGameEventValue v3 = e.get_argument( 3 );
	CL_NetGameEventValue v4 = e.get_argument( 4 );
	CL_NetGameEventValue v5 = e.get_argument( 5 );

	CL_NetGameEvent e1("player_state");
	CL_NetGameEventValue valueX( v0.to_number() );
	e1.add_argument( valueX );
	CL_NetGameEventValue valueY( v1.to_number() );
	e1.add_argument( valueY );
	CL_NetGameEventValue valueZ( v2.to_number() );
	e1.add_argument( valueZ );
	CL_NetGameEventValue valueXdir( v3.to_number() );
	e1.add_argument( valueXdir );
	CL_NetGameEventValue valueYdir( v4.to_number() );
	e1.add_argument( valueYdir );
	CL_NetGameEventValue valueZdir( v5.to_number() );
	e1.add_argument( valueZdir );
	// 7th
	e1.add_argument( user->id );
	network_server.send_event( e1 ); 
}

void Server::on_event_game_playerhit(const CL_NetGameEvent &e, ServerUser *user)
{
	int targetId = e.get_argument(0).to_integer();
	int hit = e.get_argument(1).to_integer();
	CL_NetGameEvent e1("player_hit", targetId, hit);
	network_server.send_event( e1 ); 
}
