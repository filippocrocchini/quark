package it.filippocrocchini.engine.core.particles;

import static org.lwjgl.opengl.GL11.*;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.graphics.particles.ParticleBatch;
import it.filippocrocchini.engine.common.graphics.particles.ParticleSystem;

public class ParticleManager {
	
	public Set<ParticleSystem> particleSystems;
	public Map<ParticleSystem, ParticleBatch> particleBatches;
	
	public int nextIndex = 0;
	
	public ParticleManager() {
		particleSystems = new HashSet<>();
		particleBatches = new HashMap<>();
	}
	
	public void addParticleSystem(ParticleSystem p) {
		particleSystems.add(p);
		particleBatches.put(p, new ParticleBatch());
	}
	
	public void removeParticleSystem(ParticleSystem p) {
		particleSystems.remove(p);
		particleBatches.get(p).cleanup();
		particleBatches.remove(p);
	}
	
	public void update() {
		for(ParticleSystem ps : particleSystems) {
			if(!ps.isEnabled()) continue;
			if(!ps.isDirty()) continue;
			if(particleBatches.get(ps).isInitialized()) {
				particleBatches.get(ps).setOffsetBuffer(ps.getParticlesPositions());
				ps.isDirty = false;
			}
		}
	}
	
	public void render() {
		if(Engine.getShader("Particle") == null) return;
		
		Engine.getShader("Particle").bind();
		Engine.getShader("Particle").setProjectionMatrixUniform(Engine.mainCamera.getProjectionMatrix());
		Engine.getShader("Particle").setViewMatrixUniform(Engine.mainCamera.getViewMatrix());
		
		glDisable(GL_CULL_FACE);
		for(ParticleSystem ps : particleSystems) {
			if(ps.isEnabled()) {
				Engine.getShader("Particle").setModelColorUniform(ps.getColor());
				particleBatches.get(ps).render();
			}
		}
		glEnable(GL_CULL_FACE);
	}
}
