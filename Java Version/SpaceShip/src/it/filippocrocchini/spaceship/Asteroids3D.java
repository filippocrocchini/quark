package it.filippocrocchini.spaceship;

import org.joml.Vector3f;

import it.filippocrocchini.engine.common.Color;
import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.spaceship.objects.Debris;
import it.filippocrocchini.spaceship.objects.Ship;
import it.filippocrocchini.spaceship.objects.asteroid.AsteroidField;

public class Asteroids3D{
	public Ship ship;
	public AsteroidField asteroidField;
	public Debris debris;
//	public Debris debris2;
	
	public void setup(){		
		ship = new Ship(null);
		asteroidField = new AsteroidField(null, new Vector3f(50000,50000,50000), 100);
		
		debris = new Debris(null,new Color(1f,1f,1f));
//		debris2 = new Debris(null,Color.BLUE);
		
		Engine.getGameObjectManager().addGameObject(ship);
		Engine.getGameObjectManager().addGameObject(debris);
//		Engine.getGameObjectManager().addGameObject(debris2);
		Engine.getGameObjectManager().addGameObject(asteroidField);
		
		Engine.setMainCamera(ship.getCamera());
	}
	

	public static void main(String[] args) {		
		Asteroids3D game = new Asteroids3D();		
		Engine.create("Game", 1280, 720, false);
//		Engine.create("Game", 1920, 1080, false);
		Engine.start();
		Engine.setShowDebugInfo(false);
		
		try {
			Engine.loadShader("Phong");
		} catch (AssertionError e) {
			e.printStackTrace();
		}
		
		game.setup();
	}
}
