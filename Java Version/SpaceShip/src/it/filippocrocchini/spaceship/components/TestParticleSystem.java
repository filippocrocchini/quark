package it.filippocrocchini.spaceship.components;

import org.joml.Vector3f;

import it.filippocrocchini.engine.common.Color;
import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.engine.common.graphics.particles.ParticleSystem;

public class TestParticleSystem extends ParticleSystem {
	
	public float[] positions;
	public float[] speeds;
	private Color c;
	
	public TestParticleSystem(GameObject parent, Color c) {
		super(parent);
		this.c = c;
		positions = new float[3 * 5000];
		speeds = new float[3 * 5000];
		
		for(int i =0;i<positions.length; i++) {
			positions[i] = (float)Math.random() * 100 - 50;
			speeds[i] = (float)(Math.random()-0.5);
		}
		isDirty = true;
	}

	@Override
	public float[] getParticlesPositions() {
		return positions;
	}

	@Override
	public Color getColor() {
		return c;
	}

	@Override
	public void update(double delta) {
		if(!isDirty) {
			Vector3f camera = Engine.mainCamera.getParentGameObject().transform.position;
			float dist = 0;
			
			for(int i =0;i<positions.length; i+=3) {
				dist = (float) Math.sqrt(Math.pow(positions[i] - camera.x, 2) + Math.pow(positions[i+1] - camera.y, 2) + Math.pow(positions[i+2] - camera.z, 2));
				if(dist > 50) {
					positions[i] = camera.x + (float)Math.random() * 100 - 50;
					positions[i+1] = camera.y + (float)Math.random() * 100 - 50;
					positions[i+2] = camera.z + (float)Math.random() * 100 - 50;
					continue;
				}
//				speeds[i] = Math.min(speeds[i] * 1f  + (float)(Math.random() - 0.5)*0.2f,1);
//				speeds[i+1] = Math.min(speeds[i+1] * 1f  + (float)(Math.random() - 0.5)*0.2f,1);
//				speeds[i+2] = Math.min(speeds[i+2] * 1f  + (float)(Math.random() - 0.5)*0.2f,1);
//				positions[i] += (float)(speeds[i] * delta)*0.0001f;
//				positions[i+1] += (float)(speeds[i+1] * delta)*0.0001f;
//				positions[i+2] += (float)(speeds[i+2] * delta)*0.0001f;
			}
		}
		isDirty = true;
	}

}
