#include "VideoSystem.h"

bool VideoSystem::isValid()
{
	return (valid);
}

VideoSystem::VideoSystem(void)
{
	enemies = new std::vector<EnemyPlayer>();
	valid = true;
	video::E_DRIVER_TYPE driverType = askForDriverType();
	if ( driverType == video::EDT_COUNT ) 
	{
		valid = false;
		return;
	}
	user = new User();
	//MyEventReceiver receiver;
	device = createDevice(driverType, core::dimension2d<u32>(getXresolution(), getYresolution()), getColorDepth(), false, false, false, user->getReceiver());
	if ( device == 0 ) 
	{
		valid = false;
		return;
	}
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

	setLevel( "media/map-20kdm2.pk3", "20kdm2.bsp");

	device->getCursorControl()->setVisible(false);

	user->init(  this->smgr  );
	user->addToSelector( this->q3node );

	bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	bill->setMaterialTexture(0, driver->getTexture("media/particle.bmp"));
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
	bill->setID(ID_IsNotPickable);

	scene::IAnimatedMeshSceneNode* node = 0;

	// Add an MD2 node, which uses vertex-based animation.
	/*node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("media/faerie.md2"),
						0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	node->setPosition(core::vector3df(-70,-15,-120)); // Put its feet on the floor.
	node->setScale(core::vector3df(2, 2, 2)); // Make it appear realistically scaled
	node->setMD2Animation(scene::EMAT_POINT);
	node->setAnimationSpeed(20.f);
	material = video::SMaterial();
	material.setTexture(0, driver->getTexture("media/faerie2.bmp"));
	material.Lighting = true;
	material.NormalizeNormals = true;
	node->getMaterial(0) = material;

	// Now create a triangle selector for it.  The selector will know that it
	// is associated with an animated node, and will update itself as necessary.
	selector = smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);
	selector->drop(); // We're done with this selector, so drop it now.
	*/

	// This X files uses skeletal animation, but without skinning.
	/*node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("media/mutant.x"),
						0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	node->setPosition(core::vector3df(-70,-66,0)); // Put its feet on the floor.
	node->setRotation(core::vector3df(0,-90,0)); // And turn it towards the camera.
	node->setAnimationSpeed(20.f);
	selector = smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);
	selector->drop();*/

	// And this B3D file uses skinned skeletal animation.
	/*node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("media/ninja.b3d"),
						0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	node->setScale(core::vector3df(10, 10, 10));
	node->setPosition(core::vector3df(-70,-66,-60));
	node->setRotation(core::vector3df(0,90,0));
	node->setAnimationSpeed(10.f);
	node->getMaterial(0).NormalizeNormals = true;
	// Just do the same as we did above.
	selector = smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);
	selector->drop();*/

	material.setTexture(0, 0);
	material.Lighting = false;

	// Add a light, so that the unselected nodes aren't completely dark.
	scene::ILightSceneNode * light = smgr->addLightSceneNode(0, core::vector3df(-60,100,400),
		video::SColorf(1.0f,1.0f,1.0f,1.0f), 600.0f);
	light->setID(ID_IsNotPickable); // Make it an invalid target for selection.
	material.Wireframe=true;
}


VideoSystem::~VideoSystem(void)
{
	if ( device != 0 ) {
		device->drop();
	}
	delete user;
	delete enemies;
}

video::E_DRIVER_TYPE VideoSystem::askForDriverType()
{
	//video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	//return driverType;
	return video::E_DRIVER_TYPE::EDT_DIRECT3D9;
}

int VideoSystem::getXresolution()
{
	return 800;
}

int VideoSystem::getYresolution()
{
	return 600;
}

int VideoSystem::getColorDepth()
{
	return 16;
}

void VideoSystem::setLevel( char * zippedArchive, char * fileName )
{
	device->getFileSystem()->addZipFileArchive( zippedArchive );
	scene::IAnimatedMesh* q3levelmesh = smgr->getMesh( fileName );
	q3node = 0;

	// The Quake mesh is pickable, but doesn't get highlighted.
	if (q3levelmesh)
		q3node = smgr->addOctreeSceneNode(q3levelmesh->getMesh(0), 0, IDFlag_IsPickable);

	if (q3node == 0)
	{
		valid = false;
		return;
	} else {
		q3node->setPosition(core::vector3df(-1350,-130,-1400));
	}
}

void VideoSystem::run(void)
{
	scene::ISceneNode* highlightedSceneNode = 0;
	scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	int lastFPS = -1;

	// draw the selection triangle only as wireframe
	

	while(device->run())
	if (device->isWindowActive())
	{
		enemyMutex.lock();
		driver->beginScene(true, true, 0);
		smgr->drawAll();

		// Unlight any currently highlighted scene node
		if (highlightedSceneNode)
		{
			highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, true);
			highlightedSceneNode = 0;
		}

		// All intersections in this example are done with a ray cast out from the camera to
		// a distance of 1000.  You can easily modify this to check (e.g.) a bullet
		// trajectory or a sword's position, or create a ray from a mouse click position using
		// ISceneCollisionManager::getRayFromScreenCoordinates()
		core::line3d<f32> ray;
		ray.start = this->user->getCamera()->getPosition();
		ray.end = ray.start + (this->user->getCamera()->getTarget() - ray.start).normalize() * 1000.0f;

		// Tracks the current intersection point with the level or a mesh
		core::vector3df intersection;
		// Used to show with triangle has been hit
		core::triangle3df hitTriangle;

		// This call is all you need to perform ray/triangle collision on every scene node
		// that has a triangle selector, including the Quake level mesh.  It finds the nearest
		// collision point/triangle, and returns the scene node containing that point.
		// Irrlicht provides other types of selection, including ray/triangle selector,
		// ray/box and ellipse/triangle selector, plus associated helpers.
		// See the methods of ISceneCollisionManager
		scene::ISceneNode * selectedSceneNode =
			collMan->getSceneNodeAndCollisionPointFromRay(
					ray,
					intersection, // This will be the position of the collision
					hitTriangle, // This will be the triangle hit in the collision
					IDFlag_IsPickable, // This ensures that only nodes that we have
							// set up to be pickable are considered
					0); // Check the entire scene (this is actually the implicit default)

		// If the ray hit anything, move the billboard to the collision position
		// and draw the triangle that was hit.
		if(selectedSceneNode)
		{
			bill->setPosition(intersection);

			// We need to reset the transform before doing our own rendering.
			driver->setTransform(video::ETS_WORLD, core::matrix4());
			driver->setMaterial(material);
			driver->draw3DTriangle(hitTriangle, video::SColor(0,255,0,0));

			// We can check the flags for the scene node that was hit to see if it should be
			// highlighted. The animated nodes can be highlighted, but not the Quake level mesh
			if((selectedSceneNode->getID() & IDFlag_IsHighlightable) == IDFlag_IsHighlightable)
			{
				highlightedSceneNode = selectedSceneNode;

				// Highlighting in this case means turning lighting OFF for this node,
				// which means that it will be drawn with full brightness.
				highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
			}
			EnemyPlayer * p = getTargetPlayer( selectedSceneNode );
			user->iterate( this->device, p );
		} else {
			user->iterate( this->device );
		}

		// We're all done drawing, so end the scene.
		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw str = L"Collision detection example - Irrlicht Engine [";
			str += driver->getName();
			str += "] FPS:";
			str += fps;

			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}
		enemyMutex.unlock();
	}
}

void VideoSystem::enemyState( int id, UserState * state )
{
	enemyMutex.lock();
	std::vector<EnemyPlayer>::iterator it;
	bool found = false;
	for ( it=enemies->begin() ; it < enemies->end(); it++ )
	{
		if ( it->getId() == id ) 
		{
			found = true;
			if ( state != 0) 
			{
				it->place( state->x, state->y, state->z, state->xDir, state->yDir, state->zDir );
			} else {
				//it->getNode()->drop();
				enemies->erase( it );
			}
			break;
		}
	}
	if ( !found && (state != 0))
	{
		EnemyPlayer * ep = new EnemyPlayer( this->smgr, this->selector, id );
		ep->place( state->x, state->y, state->z, state->xDir, state->yDir, state->zDir );
		enemies->push_back( *ep );
	}
	enemyMutex.unlock();
}

EnemyPlayer * VideoSystem::getTargetPlayer( scene::ISceneNode * selectedSceneNode ){
	if ( enemies->empty() ) 
	{
		return 0;
	}
	for ( int i = 0 ; i < enemies->size(); i++ )
	{
		if (enemies->at(i).getNode() == selectedSceneNode)
		{
			return &(enemies->at(i));
		}
	}
	return 0;
}