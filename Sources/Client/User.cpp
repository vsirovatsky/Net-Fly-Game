#include "User.h"

int MOVEMENT_SPEED = 5;

User::User()
{
	health = 100;
	receiver = new MyEventReceiver();
	sound = new SoundSystem();
}

void User::init( scene::ISceneManager* smgr )
{
	selector = 0;
	this->smgr = smgr;

	camera = smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, ID_IsNotPickable, 0, 0, true, 3.f);
	camera->setPosition(core::vector3df(50,50,-60));
	//camera->setTarget(core::vector3df(-70,30,-60));
	//camera->setPosition(core::vector3df(50,-66,-60));
	camera->setTarget(core::vector3df(0,90,0));
    //_ASSERT( camera == 0 );
	createMyPerson();
}


User::~User(void)
{
	delete (sound);
}

void User::addToSelector( scene::IMeshSceneNode* node )
{
	if ( node )
	{
		selector = smgr->createOctreeTriangleSelector(
				node->getMesh(), node, 128);
		node->setTriangleSelector(selector);
		if (selector)
		{
			scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
				selector, camera, core::vector3df(30,40,30),
				core::vector3df(0,-10,0), core::vector3df(0,30,0));
			selector->drop(); // As soon as we're done with the selector, drop it.
			camera->addAnimator(anim);
			anim->drop();  // And likewise, drop the animator when we're done referring to it.
		}
	}
}

scene::ICameraSceneNode* User::getCamera()
{
	return this->camera;
}

void User::createMyPerson()
{
	character = 0;
	/*character = smgr->addAnimatedMeshSceneNode(smgr->getMesh("media/dwarf.x"),
						0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	//character->setPosition(core::vector3df(-70,-66,0));
	character->setPosition(core::vector3df(50,-66,-60));
	//character->setRotation(core::vector3df(0,-90,0));
	character->setRotation(core::vector3df(0,90,0));
	character->setAnimationSpeed(20.f);*/

	character = smgr->addMeshSceneNode(smgr->getMesh("media/ninja.b3d"),
						0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	character->setScale(core::vector3df(10, 10, 10));
	character->setPosition(core::vector3df(-70,-66,-60));
	character->setRotation(core::vector3df(0,90,0));
	//character->setAnimationSpeed(10.f);
}

void User::iterate( IrrlichtDevice *device )
{
		/*if ( then == 0 ) {
			then = device->getTimer()->getTime();
		}
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		//Check if keys W, S, A or D are being held down, and move the
		// sphere node around respectively.
		core::vector3df nodePosition = character->getPosition();

		if(receiver->IsKeyDown(irr::KEY_KEY_W))
			nodePosition.Y += MOVEMENT_SPEED * frameDeltaTime;
		else if(receiver->IsKeyDown(irr::KEY_KEY_S))
			nodePosition.Y -= MOVEMENT_SPEED * frameDeltaTime;

		if(receiver->IsKeyDown(irr::KEY_KEY_A))
			nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
		else if(receiver->IsKeyDown(irr::KEY_KEY_D))
			nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;

		character->setPosition(nodePosition);*/
	if (receiver->isMouseClicked())
	{
		sound->playShot();
	}
	if(receiver->IsKeyDown(irr::KEY_KEY_M))
	{
		sound->MusicToggle();
	}

	stateMutex.lock();
	core::vector3df v = camera->getPosition();
	core::vector3df pos = camera->getAbsolutePosition();
	core::vector3df target = camera->getTarget();
	core::vector3df dir = target - pos; 
	core::vector3df rotation = dir.normalize().getHorizontalAngle();  
	stateMutex.unlock();

	v.Y -= 70;
	v.X += 10;
	character->setPosition( v );

	//rotation.X = -rotation.X;
	character->setRotation(rotation); 

	
	//core::vector3df r = camera->getRotation();
	//core::vector3df chR = character->getRotation();
	//chR = chR.rotationToDirection( r );
	//r = r.invert();
	//character->setRotation( chR );
	
}

void User::iterate( IrrlichtDevice *device, EnemyPlayer * p )
{
	if (receiver->isMouseClicked())
	{
		sound->playShot();
		if (p != 0) {
			cListener->hit( p->getId(), 10 );
		}
	}
	if(receiver->IsKeyDown(irr::KEY_KEY_M))
	{
		sound->MusicToggle();
	}

	stateMutex.lock();
	core::vector3df v = camera->getPosition();
	core::vector3df pos = camera->getAbsolutePosition();
	core::vector3df target = camera->getTarget();
	core::vector3df dir = target - pos; 
	core::vector3df rotation = dir.normalize().getHorizontalAngle();  
	stateMutex.unlock();

	v.Y -= 70;
	v.X += 10;
	character->setPosition( v );

	//rotation.X = -rotation.X;
	character->setRotation(rotation); 
}

MyEventReceiver * User::getReceiver()
{
	return this->receiver;
}

void User::populateState( UserState * state )
{
	stateMutex.lock();
	core::vector3df v = camera->getPosition();
	core::vector3df target = camera->getRotation();
	state->x = v.X;
	state->y = v.Y;
	state->z = v.Z;
	state->xDir = target.X;
	state->yDir = target.Y;
	state->zDir = target.Z;
	stateMutex.unlock();
}

void User::acceptState( UserState * state )
{
	stateMutex.lock();
	core::vector3df v;
	v.X = state->x;
	v.Y = state->y;
	v.Z = state->z;
	camera->setPosition( v );
	core::vector3df t;
	t.X = state->xDir;
	t.Y = state->yDir;
	t.Z = state->zDir;
	camera->setRotation( t );
	stateMutex.unlock();
}

void User::meHitted( int amount )
{
	health = (health - amount);
	if ( health <= 0)
	{
		exit(0);
	}
}