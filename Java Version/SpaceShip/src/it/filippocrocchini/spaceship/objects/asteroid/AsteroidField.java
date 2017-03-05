package it.filippocrocchini.spaceship.objects.asteroid;

import org.joml.Vector3f;

import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.engine.core.Utils;

public class AsteroidField extends GameObject{
	private Asteroid[] asteroids;
	private Vector3f size = new Vector3f();
	
	public AsteroidField(GameObject parent, Vector3f size, int asteroidCount) {
		super(parent);
		this.size.set(size);
		if(asteroidCount > 0) {
			asteroids = new Asteroid[asteroidCount];
			for(int i = 0; i< asteroidCount; i++) {
				Asteroid asteroid = new Asteroid(this);
				asteroids[i] = asteroid;
				addChild(asteroid);
				
				asteroid.transform.position = new Vector3f(
						(float)((Math.random()) * size.x) - size.x/2f,
						(float)((Math.random()) * size.y) - size.y/2f,
						(float)((Math.random()) * size.z) - size.z/2f
						);
			}
		}
	}

	@Override
	public void onLoad() {		
	}

	@Override
	public void cleanup() {		
	}
}
